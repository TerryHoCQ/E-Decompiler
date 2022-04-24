#pragma once
#include <capstone/capstone.h>
#include <cstdint>

enum InsBranchType
{
	BTNormal = 0x0,
	//������ת
	BTCondJmp = 0x1,
	//��������ת
	BTUncondJmp = 0x2,
	//����ָ��
	BTRet = 0x3,
};

class CapstoneWrapper
{
public:
	static CapstoneWrapper& Instance();
	CapstoneWrapper();
	~CapstoneWrapper();
	bool disasm(std::uint64_t addr, cs_insn*& ins);
private:
	csh handle;
	cs_insn* g_ins;
};