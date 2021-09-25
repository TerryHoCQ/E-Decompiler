#include "loadimage_ecat.h"
#include "IDAWrapper.h"

ECatLoadImage::ECatLoadImage() :LoadImage("ida")
{

}

void ECatLoadImage::loadFill(uint1* ptr, int4 size, const Address& addr)
{
	IDAWrapper::get_bytes(ptr, size, addr.getOffset());
}

string ECatLoadImage::getArchType(void) const
{
	return "ida";
}

void ECatLoadImage::getReadonly(RangeList& list) const
{

}

void ECatLoadImage::adjustVma(long)
{

}