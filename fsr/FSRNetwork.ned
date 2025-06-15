import inet.node.inet.WirelessHost;
import inet.mobility.single.RandomWaypointMobility;
import inet.physicallayer.wireless.common.medium.RadioMedium;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.visualizer.canvas.integrated.IntegratedCanvasVisualizer;
import inet.visualizer.contract.IIntegratedVisualizer;
import MyWirelessHost;


network FSRNetwork
{
    parameters:
        int numNodes = default(6);
        double playgroundSizeX @unit(m) = default(1000m);
        double playgroundSizeY @unit(m) = default(1000m);

    submodules:
        node[numNodes]: MyWirelessHost {
            parameters:
                @display("i=device/wifilaptop");
                mobility.typename = "RandomWaypointMobility";
        }

        radioMedium: RadioMedium {
            @display("p=100,100");
        }

        configurator: Ipv4NetworkConfigurator {
            @display("p=100,200");
        }
        
        visualizer: <default(firstAvailableOrEmpty("IntegratedCanvasVisualizer"))> like IIntegratedVisualizer if typename != "" {
            @display("p=100,300");
        }
}



