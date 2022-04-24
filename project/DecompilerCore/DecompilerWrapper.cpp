#include "DecompilerWrapper.h"
#include "..\SectionManager.h"

bool DecompilerWrapper::InitDecompilerWrapper()
{
	if (this->addrSpaceManager.InitAddressSpaceManager(SectionManager::mVec_segInfo) == false)
	{
		return false;
	}


	return true;
}

DecompilerCore::FuncData DecompilerWrapper::decompile(Address startAddr)
{
	FuncData retFunc(&addrSpaceManager);

	retFunc.followFlow(startAddr);


	return retFunc;
}

