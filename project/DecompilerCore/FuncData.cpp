#include "FuncData.h"
#include "FlowInfo.h"
#include "AddrSpaceManager.h"

DecompilerCore::FuncData::FuncData()
{
	
}

DecompilerCore::FuncData::FuncData(AddrSpaceManager* space)
{
	spaceMgr = space;
}

DecompilerCore::FuncData::~FuncData()
{

}

void DecompilerCore::FuncData::followFlow(const Address& baddr)
{
	FlowInfo retFlow;
	retFlow.setRange(spaceMgr->getAddressLowerBound(baddr), spaceMgr->getAddressUpperBound(baddr));
	retFlow.generateOps(baddr);
	retFlow.generateBlocks();
}

