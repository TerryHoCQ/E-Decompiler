#include "IDALoader.h"
#include "IDAWrapper.h"

IDALoader::IDALoader() :LoadImage("ida")
{

}

void IDALoader::loadFill(uint1* ptr, int4 size, const Address& addr)
{
	IDAWrapper::get_bytes(ptr, size, addr.getOffset());
}

string IDALoader::getArchType(void) const
{
	return "ida";
}

void IDALoader::getReadonly(RangeList& list) const
{

}

void IDALoader::adjustVma(long)
{

}