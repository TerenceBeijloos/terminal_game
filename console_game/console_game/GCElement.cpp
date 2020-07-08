#include "GCElement.h"
#include "Garbage_collector.h"

void* GCElement::operator new(size_t nSize)
{
	void* pResult = ::malloc(nSize);
	Garbage_collector::assign(static_cast<GCElement*>(pResult));
	return pResult;
}

void GCElement::operator delete(void* pObject)
{
	Garbage_collector::signoff(static_cast<GCElement*>(pObject));
	::free(pObject);
}
