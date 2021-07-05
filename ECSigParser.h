#pragma once
#include <pro.h>
#include <set>
#include <map>

class insn_t;
class mid_KrnlJmp;
class func_t;
class ECSigParser
{
public:
	//����������ģ�麯��������
	static int GenerateECSig(ea_t startAddr);
	static void InitECSigKrnl(mid_KrnlJmp& inFunc);
	static void InitECSigBasciFunc(std::map<ea_t, qstring>& mhash);
	static void InitECSigResource(uint32 startAddr, uint32 endAddr);
	static void ScanMSig(const char* sigPath, ea_t rangeStart, ea_t rangeEnd);
	//����ģʽ��ר�ã���������������
	static void Debug_outputECSig();
private:
	//����һ���û�������MD5
	static qstring GetFunctionMD5(ea_t FuncStartAddr);
	//��������������������������������������������������������
	//���ĵ�������ָ��
	static qstring GetSig_FlexSingleInst(insn_t& ins);
	//����˫������ָ��
	static qstring GetSig_FlexDoubleInst(insn_t& ins);
	//����ָ��
	static qstring GetSig_FloatInstA(insn_t& ins);
	static qstring GetSig_FloatInstB(insn_t& ins);
	//�߼�����ָ��
	static qstring GetSig_LogicInst(insn_t& ins);
	static qstring GetSig_Imul(insn_t& ins);
	static qstring GetSig_Pop(insn_t& ins);
	static qstring GetSig_LongJmp(insn_t& ins);
	static qstring GetSig_Call(insn_t& ins, qvector<qstring>& vec_saveSig, bool& out_bSkipState);
	static qstring GetSig_Nop(insn_t& ins);
	//����Ƿ�Ϊ�����Ա�׼����������Ϊ������ʼ��ַ
	static bool IsEStandardFunction(ea_t startAddr);
	//Ѱ�������Ա�׼����β��,����Ϊ������ʼ��ַ,�������һ��ָ��ĵ�ַ
	static ea_t SeachEFuncEnd(func_t* startAddr);
	//�ж�һ�������Ƿ����û���Դ��ַ��Χ֮��
	static bool IsUserResourceImm(uint32 imm);
	//�ж�һ��ƫ�Ƶ�ַ�Ƿ����û���Դ��ַ��Χ֮��
	static bool IsUserResourceOffset(uint32 offset);
	//����ʽָ��ȡģ������
	static qstring GetInsPattern_Three(insn_t& ins);
	//����ʽָ��ȡģ������
	static qstring GetInsPattern_Two(insn_t& ins, char offset);
private:
	static mid_KrnlJmp m_KrnlJmp;
	static std::map<ea_t, qstring> mMap_BasicFunc;
	static uint32 m_UserResourceStartAddr;
	static uint32 m_UserResourceEndAddr;
	static std::map<ea_t, qstring> mSave_SubFunc;

	//ģ������
	static bool bFuzzySig;
};