//
// Generated file, do not edit! Created by opp_msgtool 6.1 from FSRPacket.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "FSRPacket_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Class(LinkStateUpdate)

LinkStateUpdate::LinkStateUpdate(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

LinkStateUpdate::LinkStateUpdate(const LinkStateUpdate& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

LinkStateUpdate::~LinkStateUpdate()
{
    delete [] this->neighbors;
}

LinkStateUpdate& LinkStateUpdate::operator=(const LinkStateUpdate& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void LinkStateUpdate::copy(const LinkStateUpdate& other)
{
    this->sourceId = other.sourceId;
    this->sequenceNumber = other.sequenceNumber;
    this->hopCount = other.hopCount;
    this->numEntries = other.numEntries;
    delete [] this->neighbors;
    this->neighbors = (other.neighbors_arraysize==0) ? nullptr : new int[other.neighbors_arraysize];
    neighbors_arraysize = other.neighbors_arraysize;
    for (size_t i = 0; i < neighbors_arraysize; i++) {
        this->neighbors[i] = other.neighbors[i];
    }
}

void LinkStateUpdate::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->sourceId);
    doParsimPacking(b,this->sequenceNumber);
    doParsimPacking(b,this->hopCount);
    doParsimPacking(b,this->numEntries);
    b->pack(neighbors_arraysize);
    doParsimArrayPacking(b,this->neighbors,neighbors_arraysize);
}

void LinkStateUpdate::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->sourceId);
    doParsimUnpacking(b,this->sequenceNumber);
    doParsimUnpacking(b,this->hopCount);
    doParsimUnpacking(b,this->numEntries);
    delete [] this->neighbors;
    b->unpack(neighbors_arraysize);
    if (neighbors_arraysize == 0) {
        this->neighbors = nullptr;
    } else {
        this->neighbors = new int[neighbors_arraysize];
        doParsimArrayUnpacking(b,this->neighbors,neighbors_arraysize);
    }
}

int LinkStateUpdate::getSourceId() const
{
    return this->sourceId;
}

void LinkStateUpdate::setSourceId(int sourceId)
{
    this->sourceId = sourceId;
}

int LinkStateUpdate::getSequenceNumber() const
{
    return this->sequenceNumber;
}

void LinkStateUpdate::setSequenceNumber(int sequenceNumber)
{
    this->sequenceNumber = sequenceNumber;
}

int LinkStateUpdate::getHopCount() const
{
    return this->hopCount;
}

void LinkStateUpdate::setHopCount(int hopCount)
{
    this->hopCount = hopCount;
}

int LinkStateUpdate::getNumEntries() const
{
    return this->numEntries;
}

void LinkStateUpdate::setNumEntries(int numEntries)
{
    this->numEntries = numEntries;
}

size_t LinkStateUpdate::getNeighborsArraySize() const
{
    return neighbors_arraysize;
}

int LinkStateUpdate::getNeighbors(size_t k) const
{
    if (k >= neighbors_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)neighbors_arraysize, (unsigned long)k);
    return this->neighbors[k];
}

void LinkStateUpdate::setNeighborsArraySize(size_t newSize)
{
    int *neighbors2 = (newSize==0) ? nullptr : new int[newSize];
    size_t minSize = neighbors_arraysize < newSize ? neighbors_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        neighbors2[i] = this->neighbors[i];
    for (size_t i = minSize; i < newSize; i++)
        neighbors2[i] = 0;
    delete [] this->neighbors;
    this->neighbors = neighbors2;
    neighbors_arraysize = newSize;
}

void LinkStateUpdate::setNeighbors(size_t k, int neighbors)
{
    if (k >= neighbors_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)neighbors_arraysize, (unsigned long)k);
    this->neighbors[k] = neighbors;
}

void LinkStateUpdate::insertNeighbors(size_t k, int neighbors)
{
    if (k > neighbors_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)neighbors_arraysize, (unsigned long)k);
    size_t newSize = neighbors_arraysize + 1;
    int *neighbors2 = new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        neighbors2[i] = this->neighbors[i];
    neighbors2[k] = neighbors;
    for (i = k + 1; i < newSize; i++)
        neighbors2[i] = this->neighbors[i-1];
    delete [] this->neighbors;
    this->neighbors = neighbors2;
    neighbors_arraysize = newSize;
}

void LinkStateUpdate::appendNeighbors(int neighbors)
{
    insertNeighbors(neighbors_arraysize, neighbors);
}

void LinkStateUpdate::eraseNeighbors(size_t k)
{
    if (k >= neighbors_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)neighbors_arraysize, (unsigned long)k);
    size_t newSize = neighbors_arraysize - 1;
    int *neighbors2 = (newSize == 0) ? nullptr : new int[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        neighbors2[i] = this->neighbors[i];
    for (i = k; i < newSize; i++)
        neighbors2[i] = this->neighbors[i+1];
    delete [] this->neighbors;
    this->neighbors = neighbors2;
    neighbors_arraysize = newSize;
}

class LinkStateUpdateDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_sourceId,
        FIELD_sequenceNumber,
        FIELD_hopCount,
        FIELD_numEntries,
        FIELD_neighbors,
    };
  public:
    LinkStateUpdateDescriptor();
    virtual ~LinkStateUpdateDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(LinkStateUpdateDescriptor)

LinkStateUpdateDescriptor::LinkStateUpdateDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(LinkStateUpdate)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

LinkStateUpdateDescriptor::~LinkStateUpdateDescriptor()
{
    delete[] propertyNames;
}

bool LinkStateUpdateDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<LinkStateUpdate *>(obj)!=nullptr;
}

const char **LinkStateUpdateDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *LinkStateUpdateDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int LinkStateUpdateDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int LinkStateUpdateDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_sourceId
        FD_ISEDITABLE,    // FIELD_sequenceNumber
        FD_ISEDITABLE,    // FIELD_hopCount
        FD_ISEDITABLE,    // FIELD_numEntries
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_neighbors
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *LinkStateUpdateDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "sourceId",
        "sequenceNumber",
        "hopCount",
        "numEntries",
        "neighbors",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int LinkStateUpdateDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "sourceId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "sequenceNumber") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "hopCount") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "numEntries") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "neighbors") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *LinkStateUpdateDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_sourceId
        "int",    // FIELD_sequenceNumber
        "int",    // FIELD_hopCount
        "int",    // FIELD_numEntries
        "int",    // FIELD_neighbors
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **LinkStateUpdateDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *LinkStateUpdateDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int LinkStateUpdateDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    LinkStateUpdate *pp = omnetpp::fromAnyPtr<LinkStateUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_neighbors: return pp->getNeighborsArraySize();
        default: return 0;
    }
}

void LinkStateUpdateDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    LinkStateUpdate *pp = omnetpp::fromAnyPtr<LinkStateUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_neighbors: pp->setNeighborsArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'LinkStateUpdate'", field);
    }
}

const char *LinkStateUpdateDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    LinkStateUpdate *pp = omnetpp::fromAnyPtr<LinkStateUpdate>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string LinkStateUpdateDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    LinkStateUpdate *pp = omnetpp::fromAnyPtr<LinkStateUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: return long2string(pp->getSourceId());
        case FIELD_sequenceNumber: return long2string(pp->getSequenceNumber());
        case FIELD_hopCount: return long2string(pp->getHopCount());
        case FIELD_numEntries: return long2string(pp->getNumEntries());
        case FIELD_neighbors: return long2string(pp->getNeighbors(i));
        default: return "";
    }
}

void LinkStateUpdateDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LinkStateUpdate *pp = omnetpp::fromAnyPtr<LinkStateUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: pp->setSourceId(string2long(value)); break;
        case FIELD_sequenceNumber: pp->setSequenceNumber(string2long(value)); break;
        case FIELD_hopCount: pp->setHopCount(string2long(value)); break;
        case FIELD_numEntries: pp->setNumEntries(string2long(value)); break;
        case FIELD_neighbors: pp->setNeighbors(i,string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LinkStateUpdate'", field);
    }
}

omnetpp::cValue LinkStateUpdateDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    LinkStateUpdate *pp = omnetpp::fromAnyPtr<LinkStateUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: return pp->getSourceId();
        case FIELD_sequenceNumber: return pp->getSequenceNumber();
        case FIELD_hopCount: return pp->getHopCount();
        case FIELD_numEntries: return pp->getNumEntries();
        case FIELD_neighbors: return pp->getNeighbors(i);
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'LinkStateUpdate' as cValue -- field index out of range?", field);
    }
}

void LinkStateUpdateDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    LinkStateUpdate *pp = omnetpp::fromAnyPtr<LinkStateUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_sourceId: pp->setSourceId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_sequenceNumber: pp->setSequenceNumber(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_hopCount: pp->setHopCount(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_numEntries: pp->setNumEntries(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_neighbors: pp->setNeighbors(i,omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LinkStateUpdate'", field);
    }
}

const char *LinkStateUpdateDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr LinkStateUpdateDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    LinkStateUpdate *pp = omnetpp::fromAnyPtr<LinkStateUpdate>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void LinkStateUpdateDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    LinkStateUpdate *pp = omnetpp::fromAnyPtr<LinkStateUpdate>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'LinkStateUpdate'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

