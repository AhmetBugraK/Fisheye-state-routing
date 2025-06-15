import inet.node.inet.WirelessHost;
import FSRRouting;


module MyWirelessHost extends WirelessHost
{
    submodules:
        fsr: FSRRouting {
            parameters:
                @display("p=150,150");
        }
    connections allowunconnected:
        //fsr.ipOut --> ipv4.transportIn;
		//ipv4.transportOut --> fsr.ipIn;

}
