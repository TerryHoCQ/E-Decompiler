//#pragma once
//#include <Zydis/Zydis.h>
//#include <string>
//
//enum BranchType
//{
//	BTNormal,
//	BTRet,
//	BTCondJmp,
//	BTUncondJmp,
//};
//
//class ZydisWrapper
//{
//public:
//	static ZydisWrapper& Instance();
//	//获取指令跳转类型
//	static BranchType GetBranchType(ZydisDecodedInstruction* ins);
//
//public:
//	ZydisWrapper();
//	bool disasm(unsigned int addr, ZydisDecodedInstruction* ins);
//	//获取反编译文本
//	std::string GetDisasmText(unsigned int addr);
//private:
//	ZydisDecoder decoder;
//	ZydisFormatter formatter;
//};