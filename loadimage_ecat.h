#pragma once
#include "Ghidra/loadimage.hh"


class ECatLoadImage : public LoadImage 
{
public:
	ECatLoadImage();
	//加载指定地址的内存
	virtual void loadFill(uint1* ptr, int4 size, const Address& addr);
	virtual string getArchType(void) const;
	void getReadonly(RangeList& list) const;
	void adjustVma(long);
};