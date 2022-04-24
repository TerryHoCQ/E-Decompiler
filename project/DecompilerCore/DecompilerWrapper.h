#pragma once
#include "FlowInfo.h"
#include "FuncData.h"
#include "AddrSpaceManager.h"


using namespace DecompilerCore;
class DecompilerWrapper
{
public:
	bool InitDecompilerWrapper();
	FuncData decompile(Address startAddr);
private:
	AddrSpaceManager addrSpaceManager;
};
