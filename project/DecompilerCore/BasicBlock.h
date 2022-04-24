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
		//��������ʼ��ַ
		Address startAddr;
		//�����������ַ
		Address endAddr;
		//��ַ�б�
		std::vector<Address> insList;
	};
}

