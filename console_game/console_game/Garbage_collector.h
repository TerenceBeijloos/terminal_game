#pragma once

#include <set>

class GCElement;

class Garbage_collector
{
private:
    Garbage_collector() = default;

public:
    virtual                ~Garbage_collector();

private:
    static  void            assign(GCElement*);
    static  void            signoff(GCElement*);

private:
    typedef std::set<GCElement*> GarbageSet;

private:
    GarbageSet              m_cSet;

private:
    static Garbage_collector m_cInstance;

private:
    friend class GCElement;
};

