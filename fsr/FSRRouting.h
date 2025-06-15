#ifndef __TPFINAL_FSRROUTING_H
#define __TPFINAL_FSRROUTING_H

#include <omnetpp.h>
#include <map>
#include <vector>
#include <queue>
#include <set>
#include "FSRPacket_m.h"

using namespace omnetpp;

class FSRRouting : public cSimpleModule
{
  protected:
    // Temel bilgiler
    int myAddress;
    int sequenceNumber = 0;

    // Fisheye verileri
    simtime_t scope1Interval;
    simtime_t scope2Interval;
    int maxDistance;

    // Timerlar
    cMessage* scope1Timer = nullptr;
    cMessage* scope2Timer = nullptr;

    // Routing tabloları
    std::map<int, std::vector<int>> topologyTable;  // node -> komşular
    std::map<int, int> seqNumbers;                  // node -> son seq
    std::map<int, int> nextHopTable;                // hedef -> nextHop

    // Ana metodlar
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

    void updateNeighborList();
    void processLinkStateUpdate(LinkStateUpdate *msg);
    void sendLinkStateUpdate(bool fullUpdate);
    void recalculateRoutes();

  public:
    FSRRouting();
    virtual ~FSRRouting();
};

#endif



