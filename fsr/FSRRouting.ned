simple FSRRouting
{
    parameters:
        @class(FSRRouting);
        @display("i=block/routing");

        double scope1Interval @unit(s);
        double scope2Interval @unit(s);
        int maxDistance;
        string routingTableModule;
        string interfaceTableModule;

    gates:
        input ipIn;
        output ipOut;
}
