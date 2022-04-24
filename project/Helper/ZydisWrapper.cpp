//#include "ZydisWrapper.h"
//#include "SectionManager.h"
//
//ZydisWrapper g_Zydis;
//
//ZydisWrapper& ZydisWrapper::Instance()
//{
//	return g_Zydis;
//}
//
//
//BranchType ZydisWrapper::GetBranchType(ZydisDecodedInstruction* ins)
//{
//	switch (ins->mnemonic) 
//	{
//	case ZYDIS_MNEMONIC_RET:
//		return BTRet;
//	case ZYDIS_MNEMONIC_JMP:
//		return BTUncondJmp;
//	case ZYDIS_MNEMONIC_JB:
//	case ZYDIS_MNEMONIC_JBE:
//	case ZYDIS_MNEMONIC_JCXZ:
//	case ZYDIS_MNEMONIC_JECXZ:
//	case ZYDIS_MNEMONIC_JKNZD:
//	case ZYDIS_MNEMONIC_JKZD:
//	case ZYDIS_MNEMONIC_JL:
//	case ZYDIS_MNEMONIC_JLE:
//	case ZYDIS_MNEMONIC_JNB:
//	case ZYDIS_MNEMONIC_JNBE:
//	case ZYDIS_MNEMONIC_JNL:
//	case ZYDIS_MNEMONIC_JNLE:
//	case ZYDIS_MNEMONIC_JNO:
//	case ZYDIS_MNEMONIC_JNP:
//	case ZYDIS_MNEMONIC_JNS:
//	case ZYDIS_MNEMONIC_JNZ:
//	case ZYDIS_MNEMONIC_JO:
//	case ZYDIS_MNEMONIC_JP:
//	case ZYDIS_MNEMONIC_JRCXZ:
//	case ZYDIS_MNEMONIC_JS:
//	case ZYDIS_MNEMONIC_JZ:
//		return BTCondJmp;
//	}
//	return BTNormal;
//}
//
//
//std::string ZydisWrapper::GetDisasmText(unsigned int addr)
//{
//	ZydisDecodedInstruction ins;
//	if (disasm(addr, &ins) == false) {
//		return "";
//	}
//	char buffer[256];
//	if ZYAN_FAILED(ZydisFormatterFormatInstruction(&formatter, &ins, buffer, sizeof(buffer), addr)) {
//		return "";
//	}
//	return buffer;
//}
//
//ZydisWrapper::ZydisWrapper()
//{
//	ZydisDecoderInit(&decoder, ZYDIS_MACHINE_MODE_LONG_COMPAT_32, ZYDIS_STACK_WIDTH_32);
//	ZydisFormatterInit(&formatter, ZYDIS_FORMATTER_STYLE_INTEL);
//}
//
//
//bool ZydisWrapper::disasm(unsigned int addr, ZydisDecodedInstruction* ins)
//{
//	ZydisDecodedInstruction ret;
//	
//	unsigned char* codeBuf = SectionManager::LinearAddrToVirtualAddr(addr);
//	if (!codeBuf) {
//		return false;
//	}
//	return ZYAN_SUCCESS(ZydisDecoderDecodeBuffer(&decoder, codeBuf, 16, ins));
//}
//
