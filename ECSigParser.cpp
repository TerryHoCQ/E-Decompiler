#include "ECSigParser.h"
#include <funcs.hpp>
#include <bytes.hpp>
#include <segment.hpp>
#include <name.hpp>
#include <ua.hpp>
#include <allins.hpp>
#include <auto.hpp>
#include <fpro.h>
#include <diskio.hpp>
#include <search.hpp>
#include "SectionManager.h"
#include "ImportsParser.h"
#include "EDecompiler.h"
#include "common/public.h"

mid_KrnlJmp ECSigParser::m_KrnlJmp;
std::map<ea_t, qstring> ECSigParser::mMap_BasicFunc;
uint32 ECSigParser::m_UserResourceStartAddr = 0x00000000;
uint32 ECSigParser::m_UserResourceEndAddr = 0x0;
std::map<ea_t, qstring> ECSigParser::mSave_SubFunc;
bool ECSigParser::bFuzzySig = false;

bool isJumpInst(uint16 itype)
{
	if (itype >= NN_ja && itype <= NN_jmpshort) {
		return true;
	}
	return false;
}

const char* GetDataType(uint8 n)
{
	switch (n)
	{
	case 0:
		return "BYTE";
	case 1:
		return "WORD";
	case 2:
		return "DWORD";
	default:
		break;
	}
	return NULL;
}

const char* GetRegName(uint16 reg)
{
	switch (reg)
	{
	case 0:
		return "EAX";
	case 1:
		return "ECX";
	case 2:
		return "EDX";
	case 3:
		return "EBX";
	case 4:
		return "ESP";
	case 5:
		return "EBP";
	case 6:
		return "ESI";
	case 7:
		return "EDI";
	}

	msg("[GetRegName]To do...\n");
	return NULL;
}


qstring ECSigParser::GetInsPattern_Three(insn_t& ins)
{
	qstring ret;
	unsigned char* pData = SectionManager::LinearAddrToVirtualAddr(ins.ip);
	for (char n = 0; n < ins.ops[0].offb; ++n) {
		ret.append(UCharToStr(pData[n]));
	}
	if (IsUserResourceOffset(ins.ops[0].addr)) {
		for (char n = ins.ops[0].offb; n < ins.ops[1].offb; ++n) {
			ret.append("??");
		}
	}
	else {
		for (char n = ins.ops[0].offb; n < ins.ops[1].offb; ++n) {
			ret.append(UCharToStr(pData[n]));
		}
	}

	if (IsUserResourceImm(ins.ops[1].value)) {
		for (char n = ins.ops[1].offb; n < ins.size; ++n) {
			ret.append("??");
		}
	}
	else {
		for (char n = ins.ops[1].offb; n < ins.size; ++n) {
			ret.append(UCharToStr(pData[n]));
		}
	}

	return ret;
}

qstring ECSigParser::GetInsPattern_Two(insn_t& ins, char offset)
{
	qstring ret;
	unsigned char* pData = SectionManager::LinearAddrToVirtualAddr(ins.ip);

	for (char n = 0; n < ins.size; ++n) {
		if (n < offset) {
			ret.append(UCharToStr(pData[n]));
		}
		else {
			ret.append("??");
		}
	}
	return ret;
}

qstring GetInsHex(insn_t& ins)
{
	qstring ret;
	unsigned char* pData = SectionManager::LinearAddrToVirtualAddr(ins.ip);
	for (unsigned int n = 0; n < ins.size; ++n) {
		ret.append(UCharToStr(pData[n]));
	}
	return ret;
}

qstring ECSigParser::GetSig_LongJmp(insn_t& ins)
{
	qstring ret;
	unsigned char* pData = SectionManager::LinearAddrToVirtualAddr(ins.ip);

	//����תͳһģ������
	if (ins.size >= 5) {
		ret.append(UCharToStr(pData[0]));
		return ret;
	}

	ret = GetInsHex(ins);
	return ret;
}

bool ECSigParser::IsUserResourceOffset(uint32 offset)
{
	int32 distance = (uint32)offset;
	if (distance < 0) {
		offset = -offset;
	}
	return IsUserResourceImm(offset);
}

bool ECSigParser::IsUserResourceImm(uint32 imm)
{
	if (imm >= m_UserResourceStartAddr && imm < m_UserResourceEndAddr) {
		return true;
	}
	return false;
}

ea_t ECSigParser::SeachEFuncEnd(func_t* pFunc)
{
	ea_t ret = BADADDR;

	compiled_binpat_vec_t binPat;
	parse_binpat_str(&binPat, 0x0, "8B E5 5D", 16);
	segment_t* pSegment = getseg(pFunc->start_ea);
	if (!pSegment) {
		return BADADDR;
	}

	ea_t startAddr = pFunc->start_ea;

	while (true) {
		ret = bin_search2(startAddr, pSegment->end_ea, binPat, 0x0);
		if (ret == BADADDR) {
			return BADADDR;
		}
		ret = ret + 3;
		insn_t tmpIns;
		if (!decode_insn(&tmpIns, ret)) {
			return BADADDR;
		}
		if (ret + tmpIns.size >= pFunc->end_ea && tmpIns.itype == NN_retn) {
			break;
		}
		startAddr = ret;
	}
	return ret;
}

bool ECSigParser::IsEStandardFunction(ea_t startAddr)
{
	unsigned int head = get_dword(startAddr);
	if ((head & 0xFFFFFF) == 0xEC8B55) {
		return true;
	}
	return false;
}

qstring ECSigParser::GetSig_Nop(insn_t& ins)
{
	qstring ret;

	if (ins.ops[0].type == o_void) {
		ret = GetInsHex(ins);
		return ret;
	}
	

	msg("[GetSig_Nop]To do...\n");
	return ret;
}

qstring ECSigParser::GetSig_Call(insn_t& ins, qvector<qstring>& vec_saveSig,bool& out_bSkipState)
{
	qstring ret;
	if (ins.ops[0].type == o_near) {
		//����ص�����
		if (ins.ops[0].addr == m_KrnlJmp.Jmp_MReportError) {
			ea_t lastInsAddr = ins.ip;
			out_bSkipState = true;
			insn_t LastIns;
			lastInsAddr = decode_prev_insn(&LastIns, lastInsAddr);
			if (LastIns.itype == NN_push && LastIns.ops[0].type == o_imm) {
				vec_saveSig[vec_saveSig.size() - 1] = "";
			}
			lastInsAddr = decode_prev_insn(&LastIns, lastInsAddr);
			if (LastIns.itype == NN_push && LastIns.ops[0].type == o_imm) {
				vec_saveSig[vec_saveSig.size() - 2] = "";
			}
			else if (isJumpInst(LastIns.itype)) {
				vec_saveSig[vec_saveSig.size() - 2] = "";
				return getUTF8String("<����ص�>");
			}
			lastInsAddr = decode_prev_insn(&LastIns, lastInsAddr);
			if (LastIns.itype == NN_push && LastIns.ops[0].type == o_imm) {
				vec_saveSig[vec_saveSig.size() - 3] = "";
				vec_saveSig[vec_saveSig.size() - 4] = "";
			}
			return getUTF8String("<����ص�>");
		}
		//����DLL����
		if (ins.ops[0].addr == m_KrnlJmp.Jmp_MCallDllCmd) {
			insn_t LastIns;
			decode_prev_insn(&LastIns, ins.ip);
			//�ж���һ��ָ���ǲ���mov eax,DLL���
			if (LastIns.itype == NN_mov && LastIns.ops[0].reg == 0 && LastIns.ops[1].type == o_imm) {
				vec_saveSig[vec_saveSig.size() - 1] = "B8????????";
				qstring DLLFuncName = ImportsParser::mVec_ImportsApi[LastIns.ops[1].value].ApiName;
				ret.sprnt("[%s]", DLLFuncName.c_str());
				return ret;
			}
		}
		//ϵͳ����֧�ֿ��������֧�ֿ�
		if (ins.ops[0].addr == m_KrnlJmp.Jmp_MCallKrnlLibCmd || ins.ops[0].addr==m_KrnlJmp.Jmp_MCallLibCmd) {
			insn_t LastIns;
			decode_prev_insn(&LastIns, ins.ip);
			//�ж���һ��ָ���ǲ���mov ebx,�����ַ
			if (LastIns.itype == NN_mov && LastIns.ops[0].reg == 3 && LastIns.ops[1].type == o_imm) {
				vec_saveSig[vec_saveSig.size() - 1] = "BB????????";
				if (bFuzzySig) {
					return getUTF8String("<δ֪����>");
				}
				qstring KrnlLibName = get_name(LastIns.ops[1].value);
				if (KrnlLibName.substr(0, 4) == "sub_") {
					msg("[GetSig_Call]Function not Scanned,%a", LastIns.ops[1].value);
					ret = getUTF8String("<δ֪����>");
					return ret;
				}
				ret.sprnt("<%s>", KrnlLibName.c_str());
				return ret;
			}
		}
		if (ins.ops[0].addr == m_KrnlJmp.Jmp_MReadProperty) {
			ret = getUTF8String("<��ȡ�������>");
			return ret;
		}
		if (ins.ops[0].addr == m_KrnlJmp.Jmp_MWriteProperty) {
			ret = getUTF8String("<�����������>");
			return ret;
		}
		if (ins.ops[0].addr == m_KrnlJmp.Jmp_MMalloc) {
			ret = getUTF8String("<�����ڴ�>");
			return ret;
		}
		if (ins.ops[0].addr == m_KrnlJmp.Jmp_MRealloc) {
			ret = getUTF8String("<���·����ڴ�>");
			return ret;
		}
		if (ins.ops[0].addr == m_KrnlJmp.Jmp_MFree) {
			ret = getUTF8String("<�ͷ��ڴ�>");
			return ret;
		}
		if (ins.ops[0].addr == m_KrnlJmp.Jmp_MExitProcess) {
			ret = getUTF8String("<����>");
			return ret;
		}
		if (ins.ops[0].addr == m_KrnlJmp.Jmp_MOtherHelp) {
			ret = getUTF8String("<��������>");
			return ret;
		}

		//call $addr+0x5
		if (ins.ip + 5 == ins.ops[0].addr) {
			return GetInsHex(ins);
		}

		auto it = mMap_BasicFunc.find(ins.ops[0].addr);
		if (it != mMap_BasicFunc.end()) {
			ret.sprnt("<%s>", getUTF8String(it->second.c_str()).c_str());
			return ret;
		}

		//�û��Զ��庯��
		qstring subFuncName = mSave_SubFunc[ins.ops[0].addr];
		if (subFuncName.empty()) {
			//��ֹ�ݹ�ѭ��
			mSave_SubFunc[ins.ops[0].addr] = "<RecurFunc>";
			subFuncName = GetFunctionMD5(ins.ops[0].addr);
			if (subFuncName.empty()) {
				//��ʾ�ú�����ʵ���������
				ret = GetInsHex(ins);
				mSave_SubFunc[ins.ops[0].addr] = ret;
				return ret;
			}
			ret.sprnt("<%s>", subFuncName.c_str());
			mSave_SubFunc[ins.ops[0].addr] = ret;
			return ret;
		}
		ret.sprnt("%s", subFuncName.c_str());
		return ret;
	}
	
	msg("[GetSig_Call]To do...\n");
	return ret;
}

qstring ECSigParser::GetSig_FloatInstA(insn_t& ins)
{
	qstring ret;
	if (ins.ops[0].type == o_reg) {
		return GetInsHex(ins);
	}

	if (ins.ops[0].type == o_mem) {
		unsigned char* pData = SectionManager::LinearAddrToVirtualAddr(ins.ip);
		for (char n = 0; n < ins.size; ++n) {
			if (n >= ins.ops[0].offb) {
				ret.append("??");
			}
			else {
				ret.append(UCharToStr(pData[n]));
			}
		}
		return ret;
	}

	if (ins.ops[0].type == o_phrase) {
		return GetInsHex(ins);
	}

	//fadd [ebp-0xC]
	if (ins.ops[0].type == o_displ) {
		if (IsUserResourceOffset(ins.ops[0].addr)) {
			unsigned char* pData = SectionManager::LinearAddrToVirtualAddr(ins.ip);
			for (char n = 0; n < ins.size; ++n) {
				if (n >= ins.ops[0].offb) {
					ret.append("??");
				}
				else {
					ret.append(UCharToStr(pData[n]));
				}
			}
		}
		else {
			ret = GetInsHex(ins);
		}
		return ret;
	}
	msg("[GetSig_FloatInstA]To do...\n");
	return ret;
}

qstring ECSigParser::GetSig_FloatInstB(insn_t& ins)
{
	qstring ret;
	if (ins.ops[1].type == o_mem) {
		unsigned char* pData = SectionManager::LinearAddrToVirtualAddr(ins.ip);
		for (char n = 0; n < ins.size; ++n) {
			if (n >= ins.ops[1].offb) {
				ret.append("??");
			}
			else {
				ret.append(UCharToStr(pData[n]));
			}
		}
		return ret;
	}

	//fadd [ebp-0xC]
	if (ins.ops[1].type == o_displ) {
		if (IsUserResourceOffset(ins.ops[1].addr)) {
			unsigned char* pData = SectionManager::LinearAddrToVirtualAddr(ins.ip);
			for (char n = 0; n < ins.size; ++n) {
				if (n >= ins.ops[1].offb) {
					ret.append("??");
				}
				else {
					ret.append(UCharToStr(pData[n]));
				}
			}
		}
		else {
			ret = GetInsHex(ins);
		}
		return ret;
	}
	return GetInsHex(ins);
}


qstring ECSigParser::GetSig_FlexDoubleInst(insn_t& ins)
{
	qstring ret;
	ret.reserve(ins.size * 2 + 1);

	if (ins.ops[0].type == o_reg) {
		//mov eax,ebx
		//mov eax,[eax+ebx]
		if (ins.ops[1].type == o_reg || ins.ops[1].type == o_phrase) {
			ret = GetInsHex(ins);
			return ret;
		}

		// mov eax,[0x401000]
		if (ins.ops[1].type == o_mem) {
			unsigned char* pData = SectionManager::LinearAddrToVirtualAddr(ins.ip);
			for (char n = 0; n < ins.size; ++n) {
				if (n >= ins.ops[1].offb) {
					ret.append("??");
				}
				else {
					ret.append(UCharToStr(pData[n]));
				}
			}
			return ret;
		}

		//mov eax,[eax+ebx-0x401000]
		if (ins.ops[1].type == o_displ) {
			if (IsUserResourceOffset(ins.ops[1].addr)) {
				unsigned char* pData = SectionManager::LinearAddrToVirtualAddr(ins.ip);
				for (char n = 0; n < ins.size; ++n) {
					if (n >= ins.ops[1].offb) {
						ret.append("??");
					}
					else {
						ret.append(UCharToStr(pData[n]));
					}
				}
			}
			else {
				ret = GetInsHex(ins);
			}
			return ret;
		}

		//mov eax,0x401000
		if (ins.ops[1].type == o_imm) {
			goto label_HEX_PAT;
		}
	}

	if (ins.ops[0].type == o_mem) {
		//mov [0x401000],eax
		if (ins.ops[1].type == o_reg) {
			unsigned char* pData = SectionManager::LinearAddrToVirtualAddr(ins.ip);
			for (char n = 0; n < ins.size; ++n) {
				if (n >= ins.ops[0].offb) {
					ret.append("??");
				}
				else {
					ret.append(UCharToStr(pData[n]));
				}
			}
			return ret;
		}
		//mov [0x401000],0x501000
		if (ins.ops[1].type == o_imm) {
			unsigned char* pData = SectionManager::LinearAddrToVirtualAddr(ins.ip);
			if (IsUserResourceImm(ins.ops[1].value)) {
				for (char n = 0; n < ins.size; ++n) {
					if (n >= ins.ops[0].offb) {
						ret.append("??");
					}
					else {
						ret.append(UCharToStr(pData[n]));
					}
				}
			}
			else {
				for (char n = 0; n < ins.size; ++n) {
					if (n >= ins.ops[0].offb && n < ins.ops[1].offb) {
						ret.append("??");
					}
					else {
						ret.append(UCharToStr(pData[n]));
					}
				}
			}
			return ret;
		}
	}

	if (ins.ops[0].type == o_phrase) {
		//mov [eax+ebx],eax
		if (ins.ops[1].type == o_reg) {
			return GetInsHex(ins);
		}
		//mov [eax+ebx],0x401000
		if (ins.ops[1].type == o_imm) {
			goto label_HEX_PAT;
		}
	}
	
	if (ins.ops[0].type == o_displ) {

		//mov [ebp+ebx+0x401000],eax 
		if (ins.ops[1].type == o_reg) {
			if(IsUserResourceOffset(ins.ops[0].addr)) {
				unsigned char* pData = SectionManager::LinearAddrToVirtualAddr(ins.ip);
				for (char n = 0; n < ins.size; ++n) {
					if (n >= ins.ops[0].offb && n < ins.ops[1].offb) {
						ret.append("??");
					}
					else {
						ret.append(UCharToStr(pData[n]));
					}
				}
			}
			else {
				ret = GetInsHex(ins);
			}
			return ret;
		}

		//mov [eax+ebx-0x401000],0x401000
		if (ins.ops[1].type == o_imm) {
			unsigned char* pData = SectionManager::LinearAddrToVirtualAddr(ins.ip);
			for (char n = 0; n < ins.ops[0].offb; ++n) {
				ret.append(UCharToStr(pData[n]));
			}
			if (IsUserResourceOffset(ins.ops[0].addr)) {
				for (char n = ins.ops[0].offb; n < ins.ops[1].offb; ++n) {
					ret.append("??");
				}
			}
			else {
				for (char n = ins.ops[0].offb; n < ins.ops[1].offb; ++n) {
					ret.append(UCharToStr(pData[n]));
				}
			}
			if (IsUserResourceImm(ins.ops[1].value)) {
				for (char n = ins.ops[1].offb; n < ins.size; ++n) {
					ret.append("??");
				}
			}
			else {
				for (char n = ins.ops[1].offb; n < ins.size; ++n) {
					ret.append(UCharToStr(pData[n]));
				}
			}
			return ret;
		}
	}

	msg("[GetSig_FlexDoubleInst]To do...\n");
	return ret;

label_HEX_PAT:
	if (IsUserResourceImm(ins.ops[1].value)) {
		unsigned char* pData = SectionManager::LinearAddrToVirtualAddr(ins.ip);
		for (char n = 0; n < ins.size; ++n) {
			if (n < ins.ops[1].offb) {
				ret.append(UCharToStr(pData[n]));
			}
			else {
				ret.append("??");
			}
		}
	}
	else {
		ret = GetInsHex(ins);
	}
	return ret;
}

qstring ECSigParser::GetSig_Imul(insn_t& ins)
{
	qstring ret;

	if (ins.ops[0].type == o_reg) {
		if (ins.ops[1].type == o_phrase) {
			//imul eax,[eax+ebx]
			if (ins.ops[2].type == o_void) {
				return GetInsHex(ins);
			}
		}
	}

	msg("[GetSig_Imul]To do...\n");
	return ret;
}

qstring ECSigParser::GetSig_LogicInst(insn_t& ins)
{
	qstring ret;

	if (ins.ops[0].type == o_reg) {
		if (ins.ops[1].type == o_reg) {
			ret = GetInsHex(ins);
			return ret;
		}

		//test eax,0x401000
		if (ins.ops[1].type == o_imm) {
			ret = GetInsHex(ins);
			return ret;
		}
	}


	msg("[GetSig_LogicInst]To do...\n");
	return ret;
}


qstring ECSigParser::GetSig_FlexSingleInst(insn_t& ins)
{
	qstring ret;

	//push reg
	if (ins.ops[0].type == o_reg) {
		ret = GetInsHex(ins);
		return ret;
	}

	if (ins.ops[0].type == o_mem) {
		goto label_PAT;
	}

	//push [eax]
	if (ins.ops[0].type == o_phrase) {
		ret = GetInsHex(ins);
		return ret;
	}


	//push [eax+ebx+0x401000]
	if (ins.ops[0].type == o_displ) {
		if (IsUserResourceOffset(ins.ops[0].addr)) {
			goto label_PAT;
		}
		else {
			ret = GetInsHex(ins);
		}
		return ret;
	}
	
	if (ins.ops[0].type == o_imm) {
		if (IsUserResourceImm(ins.ops[0].value)) {
			goto label_PAT;
		}
		else {
			ret = GetInsHex(ins);
		}
		return ret;
	}

	msg("[GetSig_FlexSingleInst]To do...\n");
	return ret;
label_PAT:
	unsigned char* pData = SectionManager::LinearAddrToVirtualAddr(ins.ip);
	for (char n = 0; n < ins.size; ++n) {
		if (n >= ins.ops[0].offb) {
			ret.append("??");
		}
		else {
			ret.append(UCharToStr(pData[n]));
		}
	}
	return ret;
}

void ECSigParser::InitECSigResource(uint32 startAddr, uint32 endAddr)
{
	m_UserResourceStartAddr = startAddr;
	m_UserResourceEndAddr = endAddr;
}

void ECSigParser::InitECSigBasciFunc(std::map<ea_t, qstring>& mhash)
{
	mMap_BasicFunc.clear();
	mMap_BasicFunc = mhash;
}

void ECSigParser::InitECSigKrnl(mid_KrnlJmp& inFunc)
{
	m_KrnlJmp = inFunc;
}

void ECSigParser::Debug_outputECSig()
{
	ea_t funcStartAddr = 0x401004;

	const char* functionList[] = {
"__get",
"__get_byte",
"__query_bit",
"__set",
"__set_bit_off",
"__set_bit_on",
"__set_byte",
"__set_short",
"_ֻȡ����",
"AES_DES_�㷨",
"API_ȡ�հ��ı�",
"API_ȡ�հ��ֽڼ�",
"BASE64�����_ASM_��ʼ��",
"BASE64����_ASM",
"BASE64����_ASM",
"bin2hex",
"CallObject",
"COM_AddRef",
"COM_bstr_t",
"COM_QueryInterface",
"COM_Release",
"COM_StringToCLSID",
"COM_StringtoIID",
"COM_����COM����",
"COM_���������ռ�",
"E���ݿ�_���ٲ�ѯ",
"E���ݿ�_�޸������ݿ�",
"hex2bin",
"HIBYTE",
"HIWORD",
"IP_10����תIP",
"IP_16����תIP",
"IP_ת��10����",
"IP_ת��16����",
"LOBYTE",
"LOWORD",
"OCX_ж��",
"OCX_ע��",
"rar_�����ļ�",
"RAR_����ѹ���ļ�",
"rar_��ʼ��",
"rar_��ѹ",
"RAR_��ѹ�ļ�",
"rar_ȡѹ�����ڵ��ļ�����",
"rar_ɾ��ѹ�����ڵ��ļ�",
"rar_����ļ�ע��",
"rar_ѹ��",
"SafeRelease",
"����_Ansi��ASCII_�ı���",
"����_Ansi��Unicode",
"����_Ansi��Unicode_JS",
"����_Ansi��Unicode_�ı���",
"����_ansi��usc2",
"����_ansi��usc2_EX",
"����_Ansi��Utf8",
"����_Ansi��Utf8_����",
"����_Ansi��Utf8_��BOM�ļ�",
"����_ASCII��Unicode",
"����_BASE64����",
"����_BASE64����A",
"����_BASE64����",
"����_BASE64����A",
"����_Base64תͼƬ",
"����_BIG5������",
"����_BIG5������",
"����_gb2312��utf8",
"����_RC4����",
"����_RC4����",
"����_Unicode��Ansi",
"����_Unicode��Ansi_JS",
"����_Unicode��Ansi_����",
"����_Unicode��Ansi_�ı���",
"����_Unicode��usc2",
"����_Unicode��Utf8",
"����_URL����",
"����_URL����_JS",
"����_URL����_�ֲ�",
"����_URL����_����",
"����_URL����",
"����_URL����_JS",
"����_URL����_�ֲ�",
"����_URL����_����",
"����_usc2��ansi",
"����_usc2��ansi_EX",
"����_usc2��Unicode",
"����_UTF8����",
"����_Utf8��Ansi",
"����_Utf8��Ansi_����",
"����_utf8��gb2312",
"����_Utf8��Unicode",
"����_UTF8����",
"����_U����ת��",
"����_����ת������",
"����_���嵽BIG5",
"����_���嵽����",
"����_���嵽BIG5",
"����_���嵽����",
"����_����JS����",
"�˵�_���",
"�˵�_���������",
"�˵�_ö��",
"�˵�_ö���Ӽ��˵�",
"�˵�_���",
"�˵�_ȡID",
"�˵�_ȡ����",
"�˵�_ȡ���",
"�˵�_ȡ����",
"�˵�_ȡ�Ӿ��",
"�˵�_ɾ��",
"�˵�_���",
"�˵�_���ͼ��",
"�˵�_�޸ı���",
"�˵�_�ػ�",
"����_Call",
"����_COM����GUID",
"����_��׼���",
"����_��׼����",
"����_�����˳�",
"����_�ȴ����ڳ���",
"����_�ȴ�������ʧ",
"����_�ȴ������ʧ",
"����_�ȴ��ؼ����ݸı�",
"����_����DLL����",
"����_����",
"����_����IE������",
"����_�����Ҽ��˵�",
"����_��ֹ�ظ�����",
"����_�ڴ�������EXE",
"����_ȡ��װĿ¼",
"����_ȡ��������",
"����_ȡ������ַ_API",
"����_ȡ������",
"����_ȡ�ļ��汾��",
"����_ȡ�ӳ����ַ",
"����_����������ͼ��״̬",
"����_ɾ������",
"����_ɾ������1",
"����_����GUID",
"����_�Ƿ񱻵���",
"����_�Ƿ�ر�",
"����_�Ƿ��������������",
"����_������������",
"����_��ӵ�IE������",
"����_�����ж�",
"����_��ʾ������ͼ��",
"����_��ʾ����ͼ��",
"����_д��־",
"����_��ʱ",
"����_����������ͼ��",
"����_��������ͼ��",
"����_����Ex",
"����_ִ���ı��ӳ���",
"����_ִ�������ӳ���",
"����_ִ�������ӳ���1",
"����_����",
"����_������ö��",
"����_��ť�����ֹ",
"����_���������ȼ�",
"����_����Flash",
"����_�ȴ�����",
"����_�����Ϸ���Ϣ",
"����_���Ƶ�������",
"����_�������ָ��",
"����_���´���",
"����_����",
"����_�ر�",
"����_������",
"����_��ԭ",
"����_����",
"����_�����ȼ�_ж��",
"����_�����ȼ�_ע��",
"����_��������_ж��",
"����_��������_ע��",
"����_��������",
"����_�������л���ָ���Ĵ���",
"����_��ֹ�ر�",
"����_��ֹ��ͼ",
"����_���ö�ٽ�����Ϣ",
"����_���ȡ����ID",
"����_���ȡ����·��",
"����_���ȡ������",
"����_���ȡ�߳�ID",
"����_���ȡ�߳̾��",
"����_����Ƿ���Ч",
"����_�ؼ�IDȡ���",
"����_�ؼ�����_����",
"����_�ؼ�����_����",
"����_�ؼ��ӱ߿�",
"����_ë������Ч",
"����_ö��",
"����_ö�ٽӿ�",
"����_ö�������Ӵ���",
"����_ö���Ӵ���",
"����_ģ����������",
"����_���α༭���Ҽ�",
"����_���οؼ��Ҽ�",
"����_����������Ҽ�",
"����_Ƕ������",
"����_ǿ����ʾ",
"����_ȡIE�������",
"����_ȡ�߿�߶�",
"����_ȡ�߿���",
"����_ȡ����",
"����_ȡ����W",
"����_ȡ��������",
"����_ȡ�����",
"����_ȡ���˴��ھ��",
"����_ȡ�����ļ���·��",
"����_ȡ�����",
"����_ȡ�����EX",
"����_ȡ���λ��",
"����_ȡ���λ��1",
"����_ȡ�������",
"����_ȡ������λ��",
"����_ȡ������",
"����_ȡ������",
"����_ȡ����",
"����_ȡ���",
"����_ȡ���_�ݹ�",
"����_ȡ���_ģ��",
"����_ȡ�ͻ�������",
"����_ȡ�ؼ�ID",
"����_ȡ�ؼ���С",
"����_ȡ�ؼ�����",
"����_ȡ�ؼ�����",
"����_ȡ�������������",
"����_ȡ��չ��ʽ",
"����_ȡ����",
"����_ȡ��Ļ���",
"����_ȡ���������",
"����_ȡ��괦���ھ��",
"����_ȡ��괦�ؼ�����",
"����_ȡλ�úʹ�С",
"����_ȡ���ߴ�����",
"����_ȡСͼ��",
"����_ȡ��ʽ",
"����_ȡָ�����괦���",
"����_ȡ������",
"����_ȡ�ַ������",
"����_ȡ����",
"����_ȡ����",
"����_ȡ���괦��ɫ",
"����_ȡ�������",
"����_ȡ�����Ӿ��",
"����_�ȼ�ж��",
"����_�ȼ�ж������",
"����_�ȼ�ע��",
"����_����",
"����_����Ex",
"����_��Ϊ�޽���",
"����_�Ƿ��ڵ�",
"����_�Ƿ����",
"����_�Ƿ񼤻�",
"����_�Ƿ��ֹ",
"����_�Ƿ�ɼ�",
"����_�Ƿ�ȫ��",
"����_�Ƿ���Ӧ",
"����_�Ƿ����Ӵ���",
"����_�Ƿ�����Ļ��",
"����_�Ƿ������",
"����_�Ƿ��ö�",
"����_�Ƿ��Ӵ���",
"����_�Ƿ����",
"����_�Ƿ���С��",
"����_��ס����",
"����_�޳����",
"����_�޳���չ���",
"����_��ʾ����",
"����_���Ƴߴ�",
"����_�������д���",
"����_д��",
"����_ѭ���ر�",
"����_��������ť",
"����_����Сͼ��",
"����_Բ�ǻ�",
"����_�ñ���",
"����_�ô�͸",
"����_�ô��ڻ�",
"����_�ô�������",
"����_�ö�",
"����_�ø�",
"����_�ø�����",
"����_�ù�����λ��",
"����_�ý���",
"����_�ÿؼ�����",
"����_�ÿؼ�����",
"����_�ÿؼ�״̬",
"����_��͸����",
"����_��͸����ɫ",
"����_��λ�úʹ�С",
"����_��״̬",
"����_�ػ�",
"����_ע�ᴰ���ȼ�",
"����_������ǰ",
"����_���",
"����_��С��",
"����ͼ�����ֽڼ�",
"����_ȡ��������������",
"���߼���",
"���߼���_ͨ�ð�",
"��ַ_ȡAPI��ַ",
"�����ӳ���_",
"�����ӳ���_����",
"������_�з���ת�޷���",
"�ԳƼ���",
"�Գƽ���",
"�Ի���_���ļ�",
"�Ի���_���ļ���ѡ��",
"�Ի���_����ɫѡ���",
"�Ի���_����ļ�",
"�Ի���_��ӵ��ղؼ�",
"�Ի���_�����ղؼ�",
"������Ϣ�߼�",
"������Ϣ�ı�",
"������Ϣ����",
"��ʽ���ı�A",
"��ʽ���ı�A_����",
"��ʽ���ı�W",
"��ʽ���ı�W_����",
"����_ȥ����ɫ",
"���_ȡ�����",
"���_ȡ�����_Ӳ����",
"���_ȡ���������_Ӳ����",
"������_ȡ����Ȩ���ھ��",
"������_ȡ��������",
"������_ȡͼƬ",
"������_ȡλͼ����A",
"������_ȡλͼ����B",
"������_ȡ�ı�",
"������_ȡ�ı�W",
"������_ȡ�ļ�",
"������_������",
"������_��ͼƬ",
"������_���ı�",
"������_���ļ�",
"������_���ֽڼ�",
"������_����",
"������_ֹͣ����",
"����_����",
"����_������ȡ����",
"����_������ȡ����1",
"����_����ȡ������",
"����_����",
"����_ģ������",
"����_ȡ��Сд״̬",
"����_ȡ���ܼ���",
"����_ȡ���ܼ�״̬",
"����_ȡС����״̬",
"����_����",
"����_��Ϣ",
"����_��ϰ���",
"����_����",
"����_DEP����",
"����_IDȡ���ھ��",
"����_IDȡ���ھ��EX",
"����_IDȡ������",
"����_IDȡģ��",
"����_ID�Ƿ���Ч",
"����_PIDȡ�˿�",
"����_PIDȡ·��",
"����_����",
"����_����Ex",
"����_����W",
"����_��",
"����_��1",
"����_��λ",
"����_�˿�ȡPID",
"����_�ر�",
"����_����",
"����_����1",
"����_��ֹ����",
"����_ö��",
"����_��ȡID",
"����_��ȡ���",
"����_�ڴ�ʹ��",
"����_ǿ���򿪽���",
"����_ǿ����������",
"����_ȡID����",
"����_ȡIO��ȡ����",
"����_ȡIO��ȡ�ֽ�",
"����_ȡIO��������",
"����_ȡIO�����ֽ�",
"����_ȡIOд�����",
"����_ȡIOд���ֽ�",
"����_ȡ����·��",
"����_ȡ��ID",
"����_ȡ��������ʱ��",
"����_ȡ�����",
"����_ȡ·��",
"����_ȡ·��W",
"����_ȡ������",
"����_ȡ������32",
"����_ȡģ����",
"����_ȡ��������",
"����_ȡͬ��ID",
"����_ȡͬ��IDW",
"����_ȡϵͳ�����б�",
"����_ȡ�߳���",
"����_ȡ�û���",
"����_ȡ���ȼ�",
"����_ȡԶ�̻ỰID",
"����_ȡ�ӽ���ID",
"����_ȡ�ӽ���IDW",
"����_ȡ�Խ���ID",
"����_�Ƿ񱻹���",
"����_�Ƿ����",
"����_�Ƿ�Ϊ64λ",
"����_�ػ�",
"����_�ػ�W",
"����_����Ȩ��",
"����_����Ȩ�޵�Debug",
"����_��ͣ",
"����_�����ȼ�",
"����_��ֹ����",
"����_��ֹ����W",
"����ͨ��_���Ͷ�_��������",
"����ͨ��_���ն�_��ʼ��",
"����ͨ��_���ն�_�رռ���",
"����ͨ��_���ն�_��ʼ����",
"����ͨ��_���ն�_�������",
"����ͨ��_���ն�_�������",
"����ͨ��_���ն�_ȡ������",
"����ͨ��_���ն�_ֹͣ����",
"������_����ɫ",
"������_����",
"������_ģ��",
"������_ģ��S",
"����_�˵�ʮ",
"����_����ʮ����ʮ",
"����_����ʮ",
"����_��ʮ����ʮ",
"����_ʮ����",
"����_ʮ����",
"����_ʮ����ʮ��",
"����_ʮ��ʮ��",
"����_ʮ����ʮ",
"����_ʮ����ʮ_���",
"����_ʮ������ת�з��ŵ�ʮ����",
"����_�з��ŵ�ʮ����תʮ������",
"�ؼ�_Բ�ǻ�",
"����̨_���ٱ༭ģʽ",
"��_ȡ�ڲ�������ַ",
"��_�ͷ��ڲ�������ַ",
"��ص�_ȡ���ַ",
"��ص�_�ͷŻص�",
"�б��_����Ϊ�����ļ�",
"�б��_���������ļ�",
"Ŀ¼_����",
"Ŀ¼_����",
"Ŀ¼_����W",
"Ŀ¼_�������ļ���",
"Ŀ¼_��λ",
"Ŀ¼_����",
"Ŀ¼_�����ļ�_cmd",
"Ŀ¼_����",
"Ŀ¼_����",
"Ŀ¼_���ϵͳ����",
"Ŀ¼_ö����Ŀ¼",
"Ŀ¼_ö����Ŀ¼1",
"Ŀ¼_ǿ�����",
"Ŀ¼_���",
"Ŀ¼_ȡsystem32Ŀ¼",
"Ŀ¼_ȡWindowsĿ¼",
"Ŀ¼_ȡx86ϵͳĿ¼",
"Ŀ¼_ȡ����ʱ��",
"Ŀ¼_ȡ��С",
"Ŀ¼_ȡ��ǰĿ¼",
"Ŀ¼_ȡ��ǰĿ¼W",
"Ŀ¼_ȡ��·��",
"Ŀ¼_ȡ��ʱĿ¼",
"Ŀ¼_ȡ�ض�Ŀ¼",
"Ŀ¼_ȡ�ض�Ŀ¼EX",
"Ŀ¼_ȡ�ض�Ŀ¼W",
"Ŀ¼_ȡβ��Ŀ¼�����ļ���",
"Ŀ¼_ȡ�ļ���",
"Ŀ¼_ȡ��ϵͳ����",
"Ŀ¼_ȡ����Ŀ¼",
"Ŀ¼_ȡ����Ŀ¼W",
"Ŀ¼_ȡ����Ŀ¼",
"Ŀ¼_ȡ��Ŀ¼��",
"Ŀ¼_ɾ��Ŀ¼",
"Ŀ¼_ɾ��Ŀ¼W",
"Ŀ¼_ɾ������_cmd",
"Ŀ¼_����ϵͳ����",
"Ŀ¼_�Ƿ����",
"Ŀ¼_�Ƿ����W",
"Ŀ¼_�Ƿ���Ϲ淶",
"Ŀ¼_�Ƿ�Ϊ��",
"Ŀ¼_�Ƿ�����Ŀ¼",
"Ŀ¼_ͬ������",
"Ŀ¼_�ƶ�������_cmd",
"Ŀ¼_�ƶ��ļ�_cmd",
"Ŀ¼_���",
"�ڲ�_�����ֽڼ�",
"�ڲ�_ȡ�ļ�����",
"�ڴ�_�����ֽڼ�",
"�ڴ�_ȡcalljmp��ַ",
"�ڴ�_ȡָ����䳤��",
"�ڴ�_�����ڴ�",
"�ڴ�_�ͷ�Զ���ڴ�",
"�ڴ�_��תƫ�ƴ���",
"�ڴ�_д���ڴ�",
"�ڴ�_�޸����ڴ����ͷ�",
"�ڴ�_�޸��ڴ�",
"�ڴ�_Զ�̴����ڴ�_�ı�",
"�ڴ�_Զ�̴����ڴ�_�ֽڼ�",
"�ڴ�_Զ�̵����ӳ���",
"����_�༭��_��������",
"����_�༭��_��ȡ����",
"����_��ѡ��_��������",
"����_��ѡ��_��ȡ����",
"����_���ڿ�_��������",
"����_���ڿ�_��ȡ����",
"����_ѡ���_��������",
"����_ѡ���_��ȡ����",
"����_��Ͽ�_��������",
"����_��Ͽ�_��ȡ����",
"��Ļ����_��ʼ��",
"��Ļ����_����",
"��Ļ����_����",
"ȡ������ջ��ַ_�ֽڼ�",
"ȡ������ָ��",
"ȡ������Ϣ�ı�_API",
"ȡ����ָ��",
"ȡ����_ͨ����",
"ȡ����_ͨ����_����",
"ȡ�ı�����_ASM",
"ȡָ��_ͨ����",
"ȡָ��_ͨ����_����",
"ȡָ��_�ı���",
"ȡָ��_�ֽڼ���",
"ȡָ���ַ_��������",
"ȡָ���ַ_��������",
"ȡָ���ַ_�ı���",
"ȡָ���ַ_С����",
"ȡָ���ַ_������",
"ȡָ���ַ_�ӳ���ָ��",
"ȡָ���ַ_�ֽڼ���",
"ȡָ���ַ_�ֽ���",
"ȡָ��˫����_",
"ȡָ���ı�_",
"ȡָ��С��_",
"ȡָ������_",
"ȡָ���ֽڼ�_",
"ȡ�ӳ����ֽڼ�����",
"ɾ��Unicode��β�հ��ֽ�",
"ʱ��_GMTתΪʱ��",
"ʱ��_GMTתΪʱ��1",
"ʱ��_JSONתΪʱ��",
"ʱ��_WMIʱ��ת����",
"ʱ��_����ת��������",
"ʱ��_����תʮ��λʱ���",
"ʱ��_��ʱ���",
"ʱ��_���ı�",
"ʱ��_��������ת����",
"ʱ��_��ʽ��",
"ʱ��_��ʽ��EX",
"ʱ��_�뵽ʱ�����ʽ",
"ʱ��_�ж϶�ʮ�Ľ���",
"ʱ��_ȡ����ʱ��",
"ʱ��_ȡ����ʱ���",
"ʱ��_ȡ�ڼ���",
"ʱ��_ȡ��������",
"ʱ��_ȡ���_����",
"ʱ��_ȡ���_��ʼ",
"ʱ��_ȡ�����ı�",
"ʱ��_ȡ��ʽ����",
"ʱ��_ȡĳ������",
"ʱ��_ȡũ������",
"ʱ��_ȡ���֤�Ƚ�",
"ʱ��_ȡ���֤�ж�",
"ʱ��_ȡ���֤����",
"ʱ��_ȡ���֤�Ա�",
"ʱ��_ȡʱ����",
"ʱ��_ȡ���ʱ���",
"ʱ��_ȡ����ʱ���",
"ʱ��_ȡ����ʱ���1",
"ʱ��_ȡ�³�",
"ʱ��_ȡ�·�",
"ʱ��_ȡ��ĩ",
"ʱ��_ȡ��������",
"ʱ��_ȡ��ʽ",
"ʱ��_ȡ�й����ڼ�",
"ʱ��_���֤��15��18",
"ʱ��_���֤��ת��",
"ʱ��_ʮ��λʱ���ת����",
"ʱ��_ʱ���ת�ı�",
"ʱ��_ʱ��תΪJSON",
"ʱ��_ͬ��Уʱ",
"ʱ��_���ڼ�ȡ����",
"ʱ��_תΪGMT��ʽ",
"ʱ��_תΪGMT��ʽ1",
"ʱ��_תΪGMT��ʽ2",
"ʱ��_תΪGMT��ʽ3",
"ʱ��_����",
"ʱ��_����",
"���_����",
"���_����",
"���_���켣�ƶ�",
"���_����",
"���_��ָ��",
"���_��λ",
"���_��λ",
"���_����_��װ",
"���_����_ж��",
"���_����",
"���_ȡ��������",
"���_ȡ˫�����ʱ��",
"���_ȡλ��",
"���_ɾ����������Ƴ��¼�",
"���_ɾ��������������Ƴ��¼�",
"���_�ͷ�",
"���_����",
"���_�����������Ƴ��¼�",
"���_��ʾ����",
"���_����",
"���_��Ϣ",
"���_�ƶ�",
"���_���Ҽ�����",
"����_��ת",
"����_�ϲ�",
"����_�ϲ�_����",
"����_����",
"����_ȡ����",
"����_ȥ�ظ�",
"����_ȥ�ظ�_������",
"����_���",
"����_Ѱ������",
"��ʾ��",
"Ͷ����Ϣ����",
"ͼ��_ȡ���",
"ͼ��_ȡ����",
"ͼƬ_��24λͼ",
"ͼƬ_�ָ�",
"ͼƬ_��˹ģ��",
"ͼƬ_��̨��ͼ",
"ͼƬ_��̨�����ͼ",
"ͼƬ_��ˮӡ",
"ͼƬ_ƴ��",
"ͼƬ_ƴ��1",
"ͼƬ_ƽ������",
"ͼƬ_��Ļ��ͼ",
"ͼƬ_��Ļ�����ͼ",
"ͼƬ_ȡ�߶�",
"ͼƬ_ȡ��ʽ",
"ͼƬ_ȡ��ʽW",
"ͼƬ_ȡ���",
"ͼƬ_ȡ���",
"ͼƬ_ȡͼƬ����",
"ͼƬ_ȡ����RGB",
"ͼƬ_ȡ��Ƭ��������",
"ͼƬ_����",
"ͼƬ_����_͸��",
"ͼƬ_ͨ�����ȡͼ��",
"ͼƬ_������RGB",
"ͼƬ_ת��",
"ͼƬ_ת��1",
"ͼƬ_ת��Ex",
"ͼƬ_ת��Ex_ȡ������",
"�ⲿ�༭��_����",
"�ⲿ�༭��_����",
"�ⲿ�༭��_���������",
"�ⲿ�༭��_������",
"�ⲿ�༭��_�����ı�",
"�ⲿ�༭��_����",
"�ⲿ�༭��_�����Ƿ�ı��",
"�ⲿ�༭��_ȡ��������к��к�",
"�ⲿ�༭��_ȡ��������к��к�W",
"�ⲿ�༭��_ȡ���λ��",
"�ⲿ�༭��_ȡ������ı�",
"�ⲿ�༭��_ȡ����",
"�ⲿ�༭��_ȡ��ѡ��",
"�ⲿ�༭��_ȡ����",
"�ⲿ�༭��_ȡָ�����ı�",
"�ⲿ�༭��_ȡָ�����ı�����",
"�ⲿ�༭��_ȫѡ",
"�ⲿ�༭��_ɾ��",
"�ⲿ�༭��_��Ϊ���뷽ʽ",
"�ⲿ�༭��_��Ϊֻ����ʽ",
"�ⲿ�༭��_�滻����",
"�ⲿ�༭��_�����ַ���",
"�ⲿ�༭��_ѡ�а�����",
"�ⲿ�༭��_ѡ�а�λ��",
"�ⲿ�༭��_�ڹ�괦�����ı�",
"�ⲿ�༭��_������",
"�ⲿ�༭��_����ʼѡ��λ��",
"�ⲿ�༭��_���ı߾�",
"�ⲿ�༭��_�����ұ߾�",
"�ⲿ�༭��_ת��IE��ַ��",
"�ⲿ�����б��_��������",
"�ⲿ�����б��_��������_NEW",
"�ⲿ�����б��_ȡ��괦������",
"�ⲿ�����б��_ȡ��괦���к�",
"�ⲿ�����б��_�����ƶ�",
"�ⲿ�����б��_����",
"�ⲿ�����б��_����",
"�ⲿ�����б��_�Զ������п�",
"�ⲿ��ѡ��_ȡ��ѡ��",
"�ⲿ��ѡ��_ȡ״̬",
"�ⲿ��ѡ��_ѡ��",
"�ⲿ������_��ʾ����",
"�ⲿ�б��_��������",
"�ⲿ�б��_������Ŀ",
"�ⲿ�б��_���ұ���",
"�ⲿ�б��_������Ŀ",
"�ⲿ�б��_���",
"�ⲿ�б��_ȡ��괦��Ŀ����",
"�ⲿ�б��_ȡ��Ŀ��",
"�ⲿ�б��_ȡ��Ŀ��ֵ",
"�ⲿ�б��_ȡ��Ŀ�ı�",
"�ⲿ�б��_ȡѡ����",
"�ⲿ�б��_ɾ����Ŀ",
"�ⲿ�б��_�������ȡ��Ŀ����",
"�ⲿ�б��_����Ŀ��ֵ",
"�ⲿ�б��_��ѡ����",
"�ⲿѡ���_���",
"�ⲿѡ���_ȡ��ѡ��",
"�ⲿѡ���_ȡ״̬",
"�ⲿѡ���_ѡ��",
"�ⲿѡ���б��_������Ŀ",
"�ⲿѡ���б��_��",
"�ⲿѡ���б��_������Ŀ",
"�ⲿѡ���б��_���",
"�ⲿѡ���б��_ȡ��Ŀ��",
"�ⲿѡ���б��_ȡ��Ŀ��ֵ",
"�ⲿѡ���б��_ȡ��Ŀ�ı�",
"�ⲿѡ���б��_ѡ��",
"�ⲿѡ���б��_����Ŀ��ֵ",
"�ⲿ��Ͽ�_��������",
"�ⲿ��Ͽ�_������Ŀ",
"�ⲿ��Ͽ�_����",
"�ⲿ��Ͽ�_�����б�",
"�ⲿ��Ͽ�_�ر��б�",
"�ⲿ��Ͽ�_������Ŀ",
"�ⲿ��Ͽ�_��ȷ����",
"�ⲿ��Ͽ�_���",
"�ⲿ��Ͽ�_ȡ�߶�",
"�ⲿ��Ͽ�_ȡ�ṹ��Ϣ",
"�ⲿ��Ͽ�_ȡ�����߶�",
"�ⲿ��Ͽ�_ȡ�������",
"�ⲿ��Ͽ�_ȡ��Ŀ��",
"�ⲿ��Ͽ�_ȡ��Ŀ��ֵ",
"�ⲿ��Ͽ�_ȡ��Ŀ�ı�",
"�ⲿ��Ͽ�_ȡѡ����",
"�ⲿ��Ͽ�_ɾ����Ŀ",
"�ⲿ��Ͽ�_���ø߶�",
"�ⲿ��Ͽ�_���������߶�",
"�ⲿ��Ͽ�_�����������",
"�ⲿ��Ͽ�_����չ���б�",
"�ⲿ��Ͽ�_������ѡ����",
"�ⲿ��Ͽ�_����Ŀ��ֵ",
"����_ȡ�����ļ���С_�����",
"��ҳ_Cookie�ϲ�����",
"��ҳ_Cookie�ϲ�����ex",
"��ҳ_eval����",
"��ҳ_eval����",
"��ҳ_GZIP��ѹ",
"��ҳ_GZIP��ѹ_�ı�",
"��ҳ_GZIPѹ��",
"��ҳ_GZIPѹ��_�ı�",
"��ҳ_IE�������ҳ��ת����",
"��ҳ_JS��ʽ��",
"��ҳ_JS��ʽ��_EX",
"��ҳ_URLȡ���ص�ַ",
"��ҳ_����",
"��ҳ_����html�ĵ�",
"��ҳ_����Ascii����",
"��ҳ_�鿴��ҳ����",
"��ҳ_����Э��ͷ",
"��ҳ_����Э��ͷex",
"��ҳ_������ݷ�ʽ",
"��ҳ_��ָ����ַ",
"��ҳ_��ӡ",
"��ҳ_��ӡԤ��",
"��ҳ_����",
"��ҳ_����_����",
"��ҳ_����S",
"��ҳ_����IE�汾",
"��ҳ_��ԭ��ҳ��ɫ",
"��ҳ_��ֹ����gifͼƬ",
"��ҳ_��ֹ����������",
"��ҳ_��ֹ����������",
"��ҳ_��ֹ������ʾͼƬ",
"��ҳ_��ֹ����һ������",
"��ҳ_��ʼ������Ϣ��",
"��ҳ_������ҳ������ʾ",
"��ҳ_���Cookie",
"��ҳ_���Cookie�ļ�",
"��ҳ_ȡCookie",
"��ҳ_ȡCookie2",
"��ҳ_ȡIP��ַ",
"��ҳ_ȡ����",
"��ҳ_ȡ����Cookie",
"��ҳ_ȡ�˿�",
"��ҳ_ȡ��ݷ�ʽ��ַ",
"��ҳ_ȡʮ������ɫֵ",
"��ҳ_ȡ����IP",
"��ҳ_ȡ�����ļ��ߴ�",
"��ҳ_ȡ�����ļ���",
"��ҳ_ȡ��ҳԴ��",
"��ҳ_ȡ��ַ�ļ���",
"��ҳ_ȡ��ַ����",
"��ҳ_ȡ�ı�_dom",
"��ҳ_ȡ�ı�_reg",
"��ҳ_ȡҳ���ַ",
"��ҳ_ȡ����",
"��ҳ_ȫѡ",
"��ҳ_ɾ��IE�����ļ�",
"��ҳ_������ҳ����",
"��ҳ_�Ƿ�Ϊ��ҳ",
"��ҳ_ֹͣ������Ϣ��",
"��ҳ_�����ļ��Ƿ����",
"��ҳ_���ַ���",
"��ҳ_Э��ͷ_ȡ��Ϣ",
"��ҳ_�������",
"��ҳ_����ȡ����IP",
"��ҳ_��Cookie",
"��ҳ_��Cookie1",
"��ҳ_�������UA",
"��ҳ_�����������",
"��ҳ_ת��ΪHTMLɫ",
"��ҳ_�Զ������ҳ��Ϣ��",
"��ҳ_�Զ������ҳ��Ϣ��_������ֵ",
"��ַ_ȡ���в���",
"��ַ_ȡָ������ֵ",
"�ı�_�����ı����ؼ��������к�",
"�ı�_�����ı���ĳλ��",
"�ı�_�����ı���ĳ�к�",
"�ı�_�����ı���ĳ��ǰ",
"�ı�_�����ı���ĳ�ֺ�",
"�ı�_�����ı���ĳ��ǰ",
"�ı�_������һ��",
"�ı�_��ȡ���м��ı�",
"�ı�_��ȡ�м�_����",
"�ı�_����д",
"�ı�_��Сд",
"�ı�_��СдEX",
"�ı�_��Сдm",
"�ı�_�ݼ�",
"�ı�_����",
"�ı�_�ߵ�",
"�ı�_����",
"�ı�_�ָ��ı�",
"�ı�_����",
"�ı�_����_�Ż�",
"�ı�_����c",
"�ı�_����",
"�ı�_����_�Ż�",
"�ı�_����c",
"�ı�_�����ı�",
"�ı�_�����ı�1",
"�ı�_�ʶ�",
"�ı�_�ʶ�Ex",
"�ı�_ȡGB2312���庺�ֱʻ���",
"�ı�_ȡ����",
"�ı�_ȡ����ex",
"�ı�_ȡ����W",
"�ı�_ȡ��N�鲻�ظ�����",
"�ı�_ȡ���ı��к���",
"�ı�_ȡ���ִ���",
"�ı�_ȡ���м��ı�",
"�ı�_ȡ���ֻ�����",
"�ı�_ȡ������λ��",
"�ı�_ȡ������λ��2",
"�ı�_ȡ�հ��ı�",
"�ı�_ȡĳλ���ı�",
"�ı�_ȡȫ������ƴ��",
"�ı�_ȡ��ĸ",
"�ı�_ȡ��ƴ",
"�ı�_ȡ���Ip",
"�ı�_ȡ�����Χ����",
"�ı�_ȡ�������",
"�ı�_ȡ�������_����",
"�ı�_ȡ�������",
"�ı�_ȡ�������",
"�ı�_ȡ����ַ�",
"�ı�_ȡ�����ĸ",
"�ı�_ȡ�ı���ʼλ��",
"�ı�_ȡ�ı�������",
"�ı�_ȡ�ı�������_�Ż���",
"�ı�_ȡ�ı��г��ִ���",
"�ı�_ȡ�ı�����ʼλ��",
"�ı�_ȡ����",
"�ı�_ȡ�ұ�",
"�ı�_ȡָ�������ı���",
"�ı�_ȡָ�������ı���1",
"�ı�_ȡָ���ļ��ı���",
"�ı�_ȡָ���ļ��ı���1",
"�ı�_ȡ�м�_����",
"�ı�_ȡ�м�_����_����ʽ",
"�ı�_ȡ�ַ������",
"�ı�_ȡ���",
"�ı�_ȥ�ظ��ı�",
"�ı�_ȫѡ",
"�ı�_ɾ������",
"�ı�_ɾ������_���",
"�ı�_ɾ��ָ�������ı���1",
"�ı�_ɾ��ָ���ı���",
"�ı�_ɾ��ָ���ļ��ı���1",
"�ı�_ɾ��ָ���ļ���",
"�ı�_ɾ��β��",
"�ı�_ɾ�ұ�",
"�ı�_ɾ�м�",
"�ı�_ɾ�м�2",
"�ı�_ɾ���",
"�ı�_�Ƿ�UTF8_���",
"�ı�_�Ƿ��д��ĸ",
"�ı�_�Ƿ�Ϊ����",
"�ı�_�Ƿ�Ϊ����2",
"�ı�_�Ƿ�Ϊ����",
"�ı�_�Ƿ�Ϊ˫�ֽ��ַ�",
"�ı�_�Ƿ�Ϊ˫�ֽ��ַ�Ex",
"�ı�_�Ƿ�Ϊ��ĸ",
"�ı�_�Ƿ�Сд��ĸ",
"�ı�_�Ƿ��ظ�",
"�ı�_����ĸ�Ĵ�д",
"�ı�_�滻",
"�ı�_�滻������",
"�ı�_Ͷ��",
"�ı�_Ͷ��W",
"�ı�_�ı��Ƚ�W",
"�ı�_�ı���������",
"�ı�_Ѱ�ҳ��ı���ɾ��",
"�ı�_Ѱ���ı�",
"�ı�_ճ��",
"�ı�_����",
"�ı�_ָ�뵽�ı�A",
"�ı�_ָ�뵽�ı�W",
"�ı�_���ַָ�",
"�ı�_���ַָ�_���",
"�ı�_���ַָ�_����",
"�ı�_���ַָ�_����_�ͷ�",
"�ı�_תƴ��",
"�ı�_�Զ�����",
"�ı�����_ֻȡ����",
"�ı�����_ֻȡ����",
"�ı�����_ֻȡ����",
"�ı�����_ֻȡ��ĸ",
"�ļ�_����",
"�ļ�_�����ļ�Ŀ¼",
"�ļ�_����ϡ���ļ�",
"�ļ�_����ӳ�����",
"�ļ�_��",
"�ļ�_�����ļ���",
"�ļ�_�����ļ���",
"�ļ�_�����ļ���W",
"�ļ�_��λ",
"�ļ�_��λW",
"�ļ�_��λ���",
"�ļ�_��λ���W",
"�ļ�_��ȡӳ�����",
"�ļ�_�����ֽڼ�",
"�ļ�_����",
"�ļ�_����W",
"�ļ�_����չ��",
"�ļ�_����",
"�ļ�_�ر�",
"�ļ�_����",
"�ļ�_�ϲ��ļ�",
"�ļ�_��׺�Ƿ����",
"�ļ�_���ȡ·��",
"�ļ�_·���Ƿ�淶",
"�ļ�_ö��",
"�ļ�_ö��1",
"�ļ�_ö��EX",
"�ļ�_ö��W",
"�ļ�_ȡMP3����ʱ��",
"�ļ�_ȡ�ߴ�",
"�ļ�_ȡ��С",
"�ļ�_ȡ��ʽ",
"�ļ�_ȡ����",
"�ļ�_ȡ��չ��",
"�ļ�_ȡ����",
"�ļ�_ȡ·���̷�",
"�ļ�_ȡĿ¼",
"�ļ�_ȡĿ¼W",
"�ļ�_ȡ���ý�������",
"�ļ�_ȡ������������",
"�ļ�_ȡ������������1",
"�ļ�_ȡʱ��",
"�ļ�_ȡʱ��W",
"�ļ�_ȡʵ�ʴ�С",
"�ļ�_ȡ����",
"�ļ�_ȡͼ��",
"�ļ�_ȡͼ����",
"�ļ�_ȡ�ı�����",
"�ļ�_ȡ�ļ��汾��",
"�ļ�_ȡ�ļ���",
"�ļ�_ȡ�ļ���Ϣ",
"�ļ�_ȥ��չ��",
"�ļ�_ɾ��",
"�ļ�_ɾ��W",
"�ļ�_ɾ��������վ",
"�ļ�_ɾ��ĳ���ļ�",
"�ļ�_ɾ�����ý�",
"�ļ�_ɾ��������",
"�ļ�_�Ƿ�ռ��",
"�ļ�_�Ƿ����",
"�ļ�_�Ƿ����W",
"�ļ�_�Ƿ���ϡ���ļ�",
"�ļ�_�Ƿ�ΪĿ¼",
"�ļ�_�Ƿ�ΪĿ¼W",
"�ļ�_����",
"�ļ�_����1",
"�ļ�_����_���",
"�ļ�_�ļ����Ƿ����",
"�ļ�_����",
"�ļ�_д���ֽڼ�",
"�ļ�_ѭ��ɾ��",
"�ļ�_Ѱ���ļ�W",
"�ļ�_�Ƴ�����",
"�ļ�_�Ƴ�����W",
"�ļ�_�ƶ�",
"�ļ�_�ƶ�W",
"�ļ�_�ƶ���дλ��",
"�ļ�_ִ��",
"�ļ�_ִ��W",
"�ļ�_��ʱ��",
"�ļ�_��ʱ��W",
"�ļ�_�������Ժ��滻",
"ϵͳ_IP·���Ƿ�����",
"ϵͳ_WINS�����Ƿ�����",
"ϵͳ_�����¼�",
"ϵͳ_�����¼�1",
"ϵͳ_������ԭ��",
"ϵͳ_���������ݷ�ʽ",
"ϵͳ_�����Ƿ�֧��ϡ���ļ�",
"ϵͳ_�򿪿������",
"ϵͳ_�򿪿��������",
"ϵͳ_��������������",
"ϵͳ_���ð���",
"ϵͳ_��ʽ������",
"ϵͳ_�ص�Դ",
"ϵͳ_�ػ�",
"ϵͳ_�����Ҽ��˵���ͼ��",
"ϵͳ_������ѯ",
"ϵͳ_��������",
"ϵͳ_��ԭ��ԭɫ",
"ϵͳ_�ָ���Դ����",
"ϵͳ_�ָ�����",
"ϵͳ_�ָ����������",
"ϵͳ_�ָ����������1",
"ϵͳ_�ָ��ļ�ϵͳ�ض���",
"ϵͳ_������",
"ϵͳ_���host",
"ϵͳ_��������",
"ϵͳ_�������״̬",
"ϵͳ_����DPI����",
"ϵͳ_�����ļ�ϵͳ�ض���",
"ϵͳ_��������",
"ϵͳ_��ʼ��ť��ʾ",
"ϵͳ_��ʼ��ť����",
"ϵͳ_��ʱ����_��װ",
"ϵͳ_��ʱ����_ж��",
"ϵͳ_�ж���������ͷ",
"ϵͳ_�������������",
"ϵͳ_�������������1",
"ϵͳ_���ñ�������",
"ϵͳ_ǿ�ƹػ�",
"ϵͳ_ǿ������",
"ϵͳ_ǿ��ע��",
"ϵͳ_�л��û�",
"ϵͳ_������̲���",
"ϵͳ_������̲���1",
"ϵͳ_��ջ���վ",
"ϵͳ_���ϵͳ��ʱĿ¼",
"ϵͳ_ȡCPU��������",
"ϵͳ_ȡCPU����",
"ϵͳ_ȡCPU����",
"ϵͳ_ȡCPUʱ��Ƶ��",
"ϵͳ_ȡCPU���ݿ��",
"ϵͳ_ȡCPU�ͺ�",
"ϵͳ_ȡCPU���к�",
"ϵͳ_ȡCPUһ������",
"ϵͳ_ȡCPUռ����",
"ϵͳ_ȡCPU������",
"ϵͳ_ȡDOS·��",
"ϵͳ_ȡDOSִ�н��",
"ϵͳ_ȡDOSִ�н��T",
"ϵͳ_ȡIE�汾",
"ϵͳ_ȡIE����",
"ϵͳ_ȡMAC��ַ",
"ϵͳ_ȡ����IP",
"ϵͳ_ȡ������",
"ϵͳ_ȡ����ϵͳ���",
"ϵͳ_ȡ���̴�С��Ϣ",
"ϵͳ_ȡ��������",
"ϵͳ_ȡ������Ϣ",
"ϵͳ_ȡ���ҷ���",
"ϵͳ_ȡ�������",
"ϵͳ_ȡ���������",
"ϵͳ_ȡ����ʱ��",
"ϵͳ_ȡ�����·",
"ϵͳ_ȡ����û�������",
"ϵͳ_ȡ��Ļ�ֱ���",
"ϵͳ_ȡ��Ļ����",
"ϵͳ_ȡ�������߶�",
"ϵͳ_ȡ���ڸ�ʽ",
"ϵͳ_ȡ����ͷ����",
"ϵͳ_ȡʱ���ʽ",
"ϵͳ_ȡʱ��",
"ϵͳ_ȡ�����豸����",
"ϵͳ_ȡ��ֵע����W",
"ϵͳ_ȡ���д����̷�",
"ϵͳ_ȡ����ʱ��",
"ϵͳ_ȡ�����û���",
"ϵͳ_ȡ������Ϣ",
"ϵͳ_ȡ������Ϣ_���ǰ�",
"ϵͳ_ȡ����ڵ�����",
"ϵͳ_ȡ����������Ϣ",
"ϵͳ_ȡ��������״̬",
"ϵͳ_ȡ������DNS��׺",
"ϵͳ_ȡ����������",
"ϵͳ_ȡ�ı�ע����W",
"ϵͳ_ȡϵͳDPI",
"ϵͳ_ȡϵͳDPI_ע����",
"ϵͳ_ȡϵͳ�汾",
"ϵͳ_ȡϵͳ�汾_���",
"ϵͳ_ȡϵͳ��Ϣ",
"ϵͳ_ȡϵͳ��Ϣ1",
"ϵͳ_ȡ�Կ���Ϣ�б�",
"ϵͳ_ȡ����Դ����",
"ϵͳ_ȡ����",
"ϵͳ_ȡӲ��������",
"ϵͳ_ȡӲ��������1",
"ϵͳ_ȡ�û���",
"ϵͳ_ȡԶ�̻Ự�������",
"ϵͳ_ȡԶ�̻�����",
"ϵͳ_ȡ���в���",
"ϵͳ_ȡ��ҳ��ַ",
"ϵͳ_ȡ�����ݷ�ʽ",
"ϵͳ_ȡ������",
"ϵͳ_ȥ������",
"ϵͳ_���񴰿���ʾ",
"ϵͳ_���񴰿�����",
"ϵͳ_��������ʾ",
"ϵͳ_����������",
"ϵͳ_ɾ��MAC��ַ",
"ϵͳ_ɾ����ԭ��",
"ϵͳ_ɾ���ƻ�����",
"ϵͳ_����IE�����ַ",
"ϵͳ_����ʱ��",
"ϵͳ_�����������",
"ϵͳ_����ΪĬ�������",
"ϵͳ_�������mac",
"ϵͳ_�Ƿ�64λ����ϵͳ",
"ϵͳ_�Ƿ�Ϊ����Ա",
"ϵͳ_�Ƿ�ΪĬ������",
"ϵͳ_�Ƿ�������",
"ϵͳ_���뷨ѡ��",
"ϵͳ_ˢ��",
"ϵͳ_ˢ����Ļ",
"ϵͳ_��Ӽƻ�����",
"ϵͳ_ͨ�Ų���",
"ϵͳ_�˳���",
"ϵͳ_����ͼ����ʾ",
"ϵͳ_����ͼ������",
"ϵͳ_ϵͳʱ����ʾ",
"ϵͳ_ϵͳʱ������",
"ϵͳ_��ʾ�ػ��Ի���",
"ϵͳ_��ʾ������",
"ϵͳ_��ʾ����",
"ϵͳ_��ʾ���ؿ���������",
"ϵͳ_��ʾ�û�������",
"ϵͳ_��ʾ����",
"ϵͳ_д��ֵע����W",
"ϵͳ_д�ı�ע����W",
"ϵͳ_ж�����",
"ϵͳ_��Ϣ��Ex",
"ϵͳ_�޸�DNS",
"ϵͳ_�޸�IP��ַ�����غ���������",
"ϵͳ_�޸�MAC��ַ",
"ϵͳ_�޸Ŀ�������",
"ϵͳ_�޸��û���",
"ϵͳ_�޸���ҳ",
"ϵͳ_�Թ���Աģʽ��������",
"ϵͳ_�Թ���Աģʽ��������W",
"ϵͳ_��������",
"ϵͳ_�����û�������",
"ϵͳ_Զ�̹ػ�",
"ϵͳ_��������",
"ϵͳ_�ñ�������״̬",
"ϵͳ_����Ļ�ֱ���",
"ϵͳ_�����汳��",
"ϵͳ_����",
"ϵͳ_������Դ������",
"ϵͳ_���巢��",
"ϵͳ_ע�����Ƿ����W",
"ϵͳ_ע�����",
"ϵͳ_ע��",
"ϵͳ_ת��ΪIP��ַ",
"ϵͳ_ת��Ϊ������",
"ϵͳ_����ͼ����ʾ",
"ϵͳ_����ͼ������",
"�߳�_DLLж��",
"�߳�_DLLע��",
"�߳�_��ʼ��COM��",
"�߳�_�������֤",
"�߳�_��",
"�߳�_�ȴ�",
"�߳�_����",
"�߳�_�رվ��",
"�߳�_�ָ�",
"�߳�_���������",
"�߳�_ö��",
"�߳�_����",
"�߳�_����1",
"�߳�_����2",
"�߳�_����_4�ֽ�",
"�߳�_����_8�ֽ�",
"�߳�_����_�ı���",
"�߳�_�������_�ı���",
"�߳�_�������_������",
"�߳�_ȡID",
"�߳�_ȡ��COM��",
"�߳�_ȡ��ֹ�߳��˳�����",
"�߳�_ȡ״̬",
"�߳�_ȡ���߳�ID",
"�߳�_ȡ���߳̾��",
"�߳�_ɾ�����֤",
"�߳�_�˳������",
"�߳�_����",
"�߳�_��CPU",
"У��_ȡcrc32",
"У��_ȡhmac_md5",
"У��_ȡmd2",
"У��_ȡmd4",
"У��_ȡmd5",
"У��_ȡmd5_����",
"У��_ȡmd5_�ı�",
"У��_ȡrc4",
"У��_ȡsha1",
"У��_ȡsha256",
"У��_ȡsha512",
"�ź���_����",
"�ź���_��",
"�ź���_�ݼ�",
"�ź���_����",
"�ź���_����",
"��ɫ_ȡ��ɫ",
"������_�ӿ�ݷ�ʽ��IE�����",
"������_ȡ�����԰�װĿ¼",
"������_������ģ��",
"����_����",
"����_����",
"����_ʱ��",
"����_ֹͣ",
"����_��ͣ",
"����_����",
"����_����",
"����_ȡ����",
"����_����",
"����_������",
"����_���ʽ����",
"����_��С��ת��",
"����_���ֲ���",
"����_��������",
"����_���ż���",
"����_���׵�����",
"����_�ڲ�����",
"����_������",
"����_������",
"����_��׳�",
"����_��ֱ�߾���",
"����_ȡԲ����",
"����_������������˫",
"����_���ص�����",
"����_��ɫת��",
"����_�з���ת�޷���",
"����ת������",
"ָ��_����������_���",
"ָ��_����������_���",
"ָ��_���߼���_���",
"ָ��_������ʱ����_���",
"ָ��_��˫����С����_���",
"ָ��_���ı�",
"ָ��_��С����_���",
"ָ��_������",
"ָ��_���ֽڼ�",
"ָ��_���ֽ���_���",
"ָ��_ȡ��16λ",
"ָ��_ȡ��16λ",
"ָ��_�Ƿ���Ч",
"ָ�뵽����",
"ָ�뻹ԭ",
"ָ��ת��",
"ת��_ת���ݴ�СΪ��׼��ʾ",
"�Ի洰��_��ʽ����Ϣ",
"�Ի洰��_����",
"�Ի洰��_ȡ��Ϣ",
"�Ի洰��_�����",
"�Ի洰��_Ͷ���ı�",
"�ֽڼ�_���ı�",
"�ֽڼ�_������",
"�ֽڼ�_ȡ����",
"�ֽڼ�_ȡ�հ�",
"�ֽڼ�_ȡ�հ��ֽڼ�",
"�ֽڼ�_ȡ�ұ�",
"�ֽڼ�_ȡָ��λ���ֽڼ�",
"�ֽڼ�_ȡָ��",
"�ֽڼ�_ȡ�м�",
"�ֽڼ�_ȡ���",
"�ֽڼ�_ʮ�����Ƶ��ֽڼ�",
"�ֽڼ�_ʮ�����Ƶ��ֽڼ�2",
"�ֽڼ�_�滻",
"�ֽڼ�_�ı�ת�ֽڼ�",
"�ֽڼ�_�ı�ת�ֽڼ�ex",
"�ֽڼ�_Ѱ��",
"�ֽڼ�_Ѱ��ȡ��",
"�ֽڼ�_Ѱ��ȡ��",
"�ֽڼ�_Ѱ��ȡ��",
"�ֽڼ�_Ѱ����",
"�ֽڼ�_���滻",
"�ֽڼ�_�ֽڼ���ʮ������",
"�ֽڼ�_�ֽڼ���ʮ������2",
"�ֽڼ�_�ֽڼ�ת�ı�",
"�ֽڼ�_�ֽڼ�ת�ı�ex"
	};

	func_t* pFunc = get_func(funcStartAddr);
	if (!pFunc) {
		return;
	}

	if (!IsEStandardFunction(pFunc->start_ea)) {
		return;
	}

	ea_t endAddr = SeachEFuncEnd(pFunc);
	if (endAddr == BADADDR) {
		return;
	}

	FILE* hFile = qfopen("D:\\ecoutput.txt", "wb");
	if (!hFile) {
		return;
	}

	int nFuncIndex = 0;
	ea_t startAddr = pFunc->start_ea;
	do
	{
		qstring tmpSig;
		insn_t CurrentIns;
		int insLen = decode_insn(&CurrentIns, startAddr);

		if (!insLen) {
			msg("[Debug_outputECSig]error,decode instruction...\n");
			return;
		}

		if (CurrentIns.itype == NN_call) {
			ea_t callAddr = CurrentIns.ops[0].addr;

			if (callAddr == m_KrnlJmp.Jmp_MReportError) {}
			else if (callAddr == m_KrnlJmp.Jmp_MCallDllCmd) {}
			else if (callAddr == m_KrnlJmp.Jmp_MCallLibCmd) {}
			else if (callAddr == m_KrnlJmp.Jmp_MCallKrnlLibCmd) {}
			else if (callAddr == m_KrnlJmp.Jmp_MMalloc) {}
			else if (callAddr == m_KrnlJmp.Jmp_MRealloc) {}
			else if (callAddr == m_KrnlJmp.Jmp_MFree) {}
			else {
				mSave_SubFunc.clear();
				bFuzzySig = false;
				qstring goodmd5 = GetFunctionMD5(callAddr);
				
				mSave_SubFunc.clear();
				bFuzzySig = true;
				qstring badmd5 = GetFunctionMD5(callAddr);

				qstring funcName = functionList[nFuncIndex];
				
				if (goodmd5 == badmd5) {
					qfprintf(hFile,"%s:%s\n", funcName.c_str(), badmd5.c_str());
				}
				else {
					qfprintf(hFile, "%s:%s\n", funcName.c_str(), goodmd5.c_str());
					qfprintf(hFile, "%s_ģ��:%s\n", funcName.c_str(), badmd5.c_str());
				}

				nFuncIndex++;
			}
		}
	

		startAddr = startAddr + CurrentIns.size;

	} while (startAddr <= endAddr);

	qfclose(hFile);
}

void ECSigParser::ScanMSig(const char* lpsigPath, ea_t rangeStart, ea_t rangeEnd)
{
	qstring str_filePath;
	acp_utf8(&str_filePath, lpsigPath);

	FILE* hFile = fopenRB(str_filePath.c_str());
	if (!hFile)
	{
		return;
	}

	std::multimap<qstring, qstring> map_MSig;

	qstring str_Line;
	while (-1 != qgetline(&str_Line, hFile)) {
		size_t spitIndex = str_Line.find(":");
		if (spitIndex == qstring::npos) {
			continue;
		}
		qstring funcName = str_Line.substr(0, spitIndex);
		qstring funcSig = str_Line.substr(spitIndex + 1);
		if (funcSig.last() == '\r') {
			funcSig.remove_last();
		}
		if (funcSig.length() != 32) {
			continue;
		}
		map_MSig.insert(std::make_pair(funcSig, funcName));
	}

	mSave_SubFunc.clear();
	bFuzzySig = false;
	size_t funcCount = get_func_qty();
	for (unsigned int idx = 0; idx < funcCount; ++idx)
	{
		func_t* pFunc = getn_func(idx);

		if (pFunc->start_ea < rangeStart || pFunc->start_ea >= rangeEnd) {
			continue;
		}

		if (pFunc->start_ea == 0x4A50CF) {
			int a = 0;
		}

		qstring goodMD5 = GetFunctionMD5(pFunc->start_ea);
		auto funcCount = map_MSig.count(goodMD5);

		if (funcCount == 1) {
			auto it = map_MSig.find(goodMD5);
			setFuncName(pFunc->start_ea, it->second.c_str(), SN_FORCE);
			msg("%s%a--%s\n", getUTF8String("ʶ��ģ�麯��").c_str(), pFunc->start_ea, getUTF8String(it->second.c_str()).c_str());
			continue;
		}
		else if (funcCount != 0) {
			auto it = map_MSig.find(goodMD5);
			setFuncName(pFunc->start_ea, it->second.c_str());
			msg("%s%a--%s\n", getUTF8String("ʶ��ģ�麯��").c_str(), pFunc->start_ea, getUTF8String(it->second.c_str()).c_str());
			continue;
		}
		
	}

	mSave_SubFunc.clear();
	funcCount = get_func_qty();
	bFuzzySig = true;
	for (unsigned int idx = 0; idx < funcCount; ++idx)
	{
		func_t* pFunc = getn_func(idx);

		if (pFunc->start_ea < rangeStart || pFunc->start_ea >= rangeEnd) {
			continue;
		}

		qstring badMD5 = GetFunctionMD5(pFunc->start_ea);
		funcCount = map_MSig.count(badMD5);
		if (funcCount) {
			auto it = map_MSig.find(badMD5);
			setFuncName(pFunc->start_ea, it->second.c_str());
			msg("%s%a--%s\n", getUTF8String("ʶ��ģ�麯��").c_str(), pFunc->start_ea, getUTF8String(it->second.c_str()).c_str());
			continue;
		}
		if (funcCount != 0) {

		}
	}
	qfclose(hFile);
	return;
}

qstring ECSigParser::GetFunctionMD5(ea_t FuncStartAddr)
{
	qstring ret_MD5;

	func_t* pFunc = get_func(FuncStartAddr);
	if (!pFunc) {
		return ret_MD5;
	}

	if (!IsEStandardFunction(pFunc->start_ea)) {
		return ret_MD5;
	}

	ea_t endAddr = SeachEFuncEnd(pFunc);
	if (endAddr == BADADDR) {
		return ret_MD5;
	}

	ea_t startAddr = pFunc->start_ea;
	qvector<qstring> vec_SaveSig;
	bool bSkipNextIns = false;
	do
	{
		qstring tmpSig;
		insn_t CurrentIns;
		int insLen = decode_insn(&CurrentIns, startAddr);
		
		if (!insLen) {
			ea_t nextCodeAddr = find_code(startAddr, SEARCH_DOWN | SEARCH_NOSHOW);
			if (nextCodeAddr >= endAddr) {
				nextCodeAddr = endAddr;
			}
			unsigned char* pData = SectionManager::LinearAddrToVirtualAddr(startAddr);
			for (unsigned int n = 0; n < nextCodeAddr - startAddr; ++n) {
				tmpSig.append(UCharToStr(pData[n]));
			}
			vec_SaveSig.push_back(tmpSig);
			startAddr = nextCodeAddr;
			continue;
		}

#ifdef _DEBUG
		if (CurrentIns.ip == 0x0040204B) {
			int a = 0;
		}
#endif
		if (bSkipNextIns) {
			startAddr = startAddr + CurrentIns.size;
			bSkipNextIns = false;
			continue;
		}
		switch (CurrentIns.itype)
		{
		case NN_ja:
		case NN_jae:
		case NN_jb:
		case NN_jbe:
		case NN_jc:
		case NN_jcxz:
		case NN_jecxz:
		case NN_jrcxz:
		case NN_je:
		case NN_jg:
		case NN_jge:
		case NN_jl:
		case NN_jle:
		case NN_jna:
		case NN_jnae:
		case NN_jnb:
		case NN_jnbe:
		case NN_jnc:
		case NN_jne:
		case NN_jng:
		case NN_jnge:
		case NN_jnl:
		case NN_jnle:
		case NN_jno:
		case NN_jnp:
		case NN_jns:
		case NN_jnz:
		case NN_jo:
		case NN_jp:
		case NN_jpe:
		case NN_jpo:
		case NN_js:
		case NN_jz:
		case NN_jmpfi:
		case NN_jmpni:
		case NN_jmpshort:
			tmpSig = GetInsHex(CurrentIns);
			break;
		case NN_jmp:
			tmpSig = GetSig_LongJmp(CurrentIns);
			break;
		case NN_add:
		case NN_cmp:
		case NN_mov:
		case NN_sub:
			tmpSig = GetSig_FlexDoubleInst(CurrentIns);
			break;
		case NN_fldcw:
		case NN_fnstcw:
		case NN_fstsw:
			tmpSig = GetSig_FloatInstA(CurrentIns);
			break;
		case NN_fld:
		case NN_fstp:
		case NN_fild:
		case NN_fadd:
		case NN_fsub:
		case NN_fmul:
		case NN_fdiv:
		case NN_fcomp:
		case NN_fistp:
		case NN_fstcw:
			tmpSig = GetSig_FloatInstB(CurrentIns);
			break;
		case NN_inc:
		case NN_dec:
		case NN_push:
			tmpSig = GetSig_FlexSingleInst(CurrentIns);
			break;
		case NN_call:
			tmpSig = GetSig_Call(CurrentIns, vec_SaveSig, bSkipNextIns);
			break;
		//nopָ��Ĵ����Ǹ�����,�����Ԥ���������ԵĻ�ָ���
		case NN_nop:
			tmpSig = "";
			break;
		//��������ָ��(�۲���)
		case NN_lea:
		case NN_setnz:
		case NN_setz:
		case NN_imul:
		case NN_and:
		case NN_or:
		case NN_shl:
		case NN_shr:
		case NN_xor:
		case NN_test:
		case NN_loop:
		case NN_loopd:
		case NN_fninit:
		case NN_cld:
		case NN_sbb:
		case NN_not:
		case NN_mul:
		case NN_ftst:
		case NN_fnstsw:
		case NN_fchs:
		case NN_cwde:
		case NN_movs:
		case NN_pop:
		case NN_retf:
			tmpSig = GetInsHex(CurrentIns);
			break;
			//��������ָ��(�߶�ȷ��)
		case NN_aaa:
		case NN_aad:
		case NN_aam:
		case NN_aas:
		case NN_adc:
		case NN_arpl:
		case NN_bound:
		case NN_bsf:
		case NN_bsr:
		case NN_bt:
		case NN_btc:
		case NN_btr:
		case NN_bts:
		case NN_cbw:
		case NN_cdqe:
		case NN_clc:
		case NN_cli:
		case NN_clts:
		case NN_cmc:
		case NN_daa:
		case NN_das:
		case NN_wait:
		case NN_cmova:
		case NN_cmovnz:
		case NN_cpuid:
		case NN_leave:
		case NN_xgetbv:
		case NN_vxorpd:
		case NN_vpcmpeqb:
		case NN_vpmovmskb:
		case NN_movdqa:
		case NN_pxor:
		case NN_movq:
		case NN_pcmpeqb:
		case NN_pmovmskb:
		case NN_movzx:
		case NN_vmovdqu:
			tmpSig = GetInsHex(CurrentIns);
			break;
		//���������ָ��
		case NN_lods:
		case NN_stos:
		case NN_retn:
			tmpSig = GetInsHex(CurrentIns);
			break;
		default:
			//msg("UnHandled Instruction--%a\n", CurrentIns.ip);
			tmpSig = GetInsHex(CurrentIns);
			break;
		}

		vec_SaveSig.push_back(tmpSig);
		if (tmpSig.empty() && CurrentIns.itype != NN_nop) {
			msg("%s--%a\n", getUTF8String("��ȡ����ʧ��").c_str(), startAddr);
		}
		startAddr = startAddr + CurrentIns.size;

	} while (startAddr <= endAddr);

	qstring STRING_RESULT;
	for (unsigned int n = 0; n < vec_SaveSig.size(); ++n) {
		STRING_RESULT.append(vec_SaveSig[n]);
	}

	ret_MD5 = CalculateMD5(STRING_RESULT);


#ifdef _DEBUG
	if (!bFuzzySig) {
		msg("[%a]:%s\n", FuncStartAddr, STRING_RESULT.c_str());
	}
#endif // _DEBUG
	
	return ret_MD5;
}

int ECSigParser::GenerateECSig(ea_t addr)
{
	if (!auto_is_ok()) {
		info(getUTF8String("��ȴ�IDA�������...").c_str());
		return false;
	}

	func_t* pFunc = get_func(addr);
	if (!pFunc) {
		return false;
	}

	mSave_SubFunc.clear();
	bFuzzySig = false;
	qstring GoodMd5 = GetFunctionMD5(pFunc->start_ea);
	
	mSave_SubFunc.clear();
	bFuzzySig = true;
	qstring BadMd5 = GetFunctionMD5(pFunc->start_ea);

	msg("[%s%a]:%s\n", getUTF8String("��ȷ����").c_str(), pFunc->start_ea, GoodMd5.c_str());
	msg("[%s%a]:%s\n", getUTF8String("ģ������").c_str(), pFunc->start_ea, BadMd5.c_str());

	return true;
}