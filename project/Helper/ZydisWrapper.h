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
//	//��ȡָ����ת����
//	static BranchType GetBranchType(ZydisDecodedInstruction* ins);
//
//public:
//	ZydisWrapper();
//	bool disasm(unsigned int addr, ZydisDecodedInstruction* ins);
//	//��ȡ�������ı�
//	std::string GetDisasmText(unsigned int addr);
//private:
//	ZydisDecoder decoder;
//	ZydisFormatter formatter;
//};