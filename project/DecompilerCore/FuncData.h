#pragma once
#include ".\common\Address.h"
#include ".\common\Op.h"


namespace DecompilerCore
{
	class AddrSpaceManager;
	//���ڴ洢������Ľ���ĺ��Ľṹ��
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
