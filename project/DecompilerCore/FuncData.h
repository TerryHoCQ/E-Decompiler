#pragma once
#include ".\common\Address.h"
#include ".\common\Op.h"


namespace DecompilerCore
{
	class AddrSpaceManager;
	//用于存储反编译的结果的核心结构体
	class FuncData
	{
	public:
		FuncData();
		FuncData(AddrSpaceManager* );
		~FuncData();
	public:
		void followFlow(const Address& baddr);
	private:
		AddrSpaceManager* spaceMgr;
	};
}
