#include "FSRRouting.h"

#include "inet/common/packet/Packet.h"
#include "inet/networklayer/common/L3Address.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/networklayer/contract/ipv4/Ipv4Address.h"
#include "inet/networklayer/ipv4/Ipv4RoutingTable.h"
#include "inet/networklayer/ipv4/Ipv4Route.h"
#include "inet/mobility/contract/IMobility.h"
#include "inet/common/geometry/common/Coord.h"
#include "inet/common/ModuleAccess.h"



using namespace inet;

Define_Module(FSRRouting);

FSRRouting::FSRRouting() {
    scope1Timer = nullptr;
    scope2Timer = nullptr;
}

FSRRouting::~FSRRouting() {
    cancelAndDelete(scope1Timer);
    cancelAndDelete(scope2Timer);
}



void FSRRouting::updateNeighborList() {
    int numNodes = getParentModule()->getParentModule()->par("numNodes").intValue();
    auto myMobility = check_and_cast<IMobility*>(getParentModule()->getSubmodule("mobility"));
    Coord myPos = myMobility->getCurrentPosition();

    std::vector<int> newNeighbors;

    for (int i = 0; i < numNodes; ++i) {
        if (i == myAddress) continue;

        cModule* otherNode = getSimulation()->getSystemModule()->getSubmodule("node", i);
        if (!otherNode) continue;

        auto otherMobility = check_and_cast<IMobility*>(otherNode->getSubmodule("mobility"));
        Coord otherPos = otherMobility->getCurrentPosition();

        double distance = myPos.distance(otherPos);
        if (distance <= 150) {
            newNeighbors.push_back(i);
        }
    }

    // Komşu listeni güncelle
    topologyTable[myAddress] = newNeighbors;

    EV_INFO << "Node[" << myAddress << "] komşuları güncellendi: ";
    for (int n : newNeighbors)
        EV_INFO << n << " ";
    EV_INFO << "\n";
}


void FSRRouting::initialize() {
    myAddress = getParentModule()->getIndex();
    scope1Interval = par("scope1Interval");
    scope2Interval = par("scope2Interval");
    maxDistance = par("maxDistance");

    scope1Timer = new cMessage("scope1Timer");
    scope2Timer = new cMessage("scope2Timer");
    scheduleAt(simTime() + scope1Interval, scope1Timer);
    scheduleAt(simTime() + scope2Interval, scope2Timer);

    EV_INFO << "FSRRouting initialized at node[" << myAddress << "]\n";
    EV_INFO << " - scope1Interval = " << scope1Interval << "\n";
    EV_INFO << " - scope2Interval = " << scope2Interval << "\n";
    EV_INFO << " - maxDistance = " << maxDistance << "\n";

    updateNeighborList();  // ilk komşu listesi
}


void FSRRouting::handleMessage(cMessage *msg) {
    if (msg == scope1Timer) {
        updateNeighborList();
        sendLinkStateUpdate(false);
        scheduleAt(simTime() + scope1Interval, scope1Timer);
    }
    else if (msg == scope2Timer) {
        sendLinkStateUpdate(true);
        scheduleAt(simTime() + scope2Interval, scope2Timer);
    }
    else if (auto *lsu = dynamic_cast<LinkStateUpdate *>(msg)) {
        processLinkStateUpdate(lsu);
    }
    else if (auto *pkt = dynamic_cast<Packet *>(msg)) {
        send(pkt, "ipOut"); // Artık yönlendirme tablosu karar veriyor
    }
    else {
        delete msg;
    }
}


void FSRRouting::sendLinkStateUpdate(bool fullUpdate) {
    auto *msg = new LinkStateUpdate();
    msg->setSourceId(myAddress);
    msg->setSequenceNumber(sequenceNumber++);
    msg->setHopCount(1);

    std::vector<int> neighborsToSend;
    if (fullUpdate) {
        for (auto& entry : topologyTable)
            if (entry.first != myAddress)
                neighborsToSend.push_back(entry.first);
    } else {
        for (int neighbor : topologyTable[myAddress])
            neighborsToSend.push_back(neighbor);
    }

    msg->setNumEntries(neighborsToSend.size());
    msg->setNeighborsArraySize(neighborsToSend.size());
    for (size_t i = 0; i < neighborsToSend.size(); ++i)
        msg->setNeighbors(i, neighborsToSend[i]);

    send(msg, "ipOut");
}

void FSRRouting::processLinkStateUpdate(LinkStateUpdate *msg) {
    int src = msg->getSourceId();
    int seq = msg->getSequenceNumber();

    if (seq > seqNumbers[src]) {
        seqNumbers[src] = seq;
        std::vector<int> neighbors;
        for (int i = 0; i < msg->getNeighborsArraySize(); ++i)
            neighbors.push_back(msg->getNeighbors(i));
        topologyTable[src] = neighbors;

        recalculateRoutes();
    }

    EV_INFO << "LinkStateUpdate received from node[" << src << "] with seq=" << seq << "\n";

    delete msg;
}


void FSRRouting::recalculateRoutes() {
    std::set<int> visited;
    std::map<int, int> distance;
    std::map<int, int> previous;

    distance[myAddress] = 0;
    std::queue<int> q;
    q.push(myAddress);

    while (!q.empty()) {
        int current = q.front(); q.pop();
        visited.insert(current);

        for (int neighbor : topologyTable[current]) {
            if (visited.find(neighbor) == visited.end()) {
                if (distance.find(neighbor) == distance.end() || distance[neighbor] > distance[current] + 1) {
                    distance[neighbor] = distance[current] + 1;
                    previous[neighbor] = current;
                    q.push(neighbor);
                }
            }
        }
    }

    nextHopTable.clear();
    for (auto &[node, _] : distance) {
        if (node == myAddress) continue;
        int hop = node;
        while (previous[hop] != myAddress)
            hop = previous[hop];
        nextHopTable[node] = hop;
    }

    // IP yönlendirme tablosunu güncelle
    Ipv4RoutingTable* routingTable = getModuleFromPar<Ipv4RoutingTable>(par("routingTableModule"), this);

    // Bu modül tarafından eklenen önceki rotaları sil
    for (int i = routingTable->getNumRoutes() - 1; i >= 0; --i) {
        Ipv4Route *route = routingTable->getRoute(i);
        if (route->getSource() == this) {
            routingTable->deleteRoute(route);
        }
    }

    EV_INFO << "Routing table of node[" << myAddress << "] updated:\n";
    for (auto& [destId, hopId] : nextHopTable) {
        auto route = new Ipv4Route();
        route->setSource(this);
        route->setDestination(Ipv4Address(("10.0.0." + std::to_string(destId)).c_str()));
        route->setNetmask(Ipv4Address::ALLONES_ADDRESS);
        route->setGateway(Ipv4Address(("10.0.0." + std::to_string(hopId)).c_str()));

        IInterfaceTable* ifTable = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this);
        route->setInterface(ifTable->findInterfaceByAddress(Ipv4Address(("10.0.0." + std::to_string(myAddress)).c_str())));

        route->setMetric(distance[destId]);

        routingTable->addRoute(route);

        EV_INFO << " - Dest: " << destId << ", NextHop: " << hopId << "\n";
    }
}












