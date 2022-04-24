#pragma once
#include <capstone/capstone.h>
#include <cstdint>

enum InsBranchType
{
	BTNormal = 0x0,
	//条件跳转
	BTCondJmp = 0x1,
	//无条件跳转
	BTUncondJmp = 0x2,
	//返回指令
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