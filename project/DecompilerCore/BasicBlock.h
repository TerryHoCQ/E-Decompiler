#pragma once
#include <vector>
#include ".\common\Address.h"
#include "..\IDAWrapper.h"


namespace DecompilerCore
{
	class BasicBlock
	{
	public:
		BasicBlock();
		~BasicBlock();
	public:
		//基本块起始地址
		Address startAddr;
		//基本块结束地址
		Address endAddr;
		//地址列表
		std::vector<Address> insList;
	};
}

