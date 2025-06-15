message LinkStateUpdate
{
    int sourceId;
    int sequenceNumber;
    int hopCount;
    int numEntries;
    int neighbors[];
}
