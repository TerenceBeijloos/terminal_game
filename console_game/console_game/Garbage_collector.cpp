#include "Garbage_collector.h"
#include "GCElement.h"

Garbage_collector Garbage_collector::m_cInstance;


Garbage_collector::~Garbage_collector()
{
    GarbageSet::iterator iSet, iNext;

    for (iSet = m_cSet.begin(); iSet != m_cSet.end(); iSet = iNext)
    {
        iNext = iSet;
        ++iNext;

        delete* iSet;
    }
}

void Garbage_collector::assign(GCElement* pElement)
{
    m_cInstance.m_cSet.insert(pElement);
}

void Garbage_collector::signoff(GCElement* pElement)
{
    m_cInstance.m_cSet.erase(pElement);
}
