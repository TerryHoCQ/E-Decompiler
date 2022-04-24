#pragma once
#include "Address.h"
#include <list>
#include <map>

namespace DecompilerCore
{
	class AsmOp
	{
		friend class AsmOpBank;
	public:
		enum
		{
			startbasic = 1,	    //ָ����basicBlockͷ
			branch = 2,			//ָ���Ǹ���ת
			call = 4,			//ָ���Ǹ�call
			returns = 0x8,		//ָ���Ǹ�����
			dead = 0x20,		//ָ����δ����
		};
		//ָ������
		enum OpCode 
		{
			CPUI_DEFAULT = 0x0,
			//��������תָ��
			CPUI_BRANCH,
			//������תָ��
			CPUI_CBRANCH,
			//��ת��
			CPUI_BRANCHIND,
			//CALLָ��
			CPUI_CALL,
			//����ָ��,
			CPUI_RETURN,
			//����ָ��,
			CPUI_ERROR
		};

		union OpData
		{
			std::uint64_t JmpAddr;
			std::uint64_t callAddr;
		};
	
	public:
		AsmOp();
		AsmOp(const SeqNum& sq);
		//ָ���Ƿ�Ϊcall
		bool isCall(void) const;
		void setFlag(std::uint32_t fl);
		void setOpcode(OpCode op);
		//����ָ���
		void setAsmLen(unsigned char len);
		//��ȡָ���
		unsigned char getAsmLen();
		//��ȡָ������
		OpCode getOpCode(void);
		//��ȡָ���ַ
		Address getAddress();
		//��ǰָ���Ƿ�Ϊ��������ʼָ��
		bool isBlockStart(void) const;
		//��ǵ�ǰָ���ǻ�������ʼָ��
		void opMarkStartBasic();
		const SeqNum& getSeqNum(void) const;
	public:
		mutable std::int32_t flags;
		//ָ������
		OpData opdata;
	private:
		//ָ������
		SeqNum start;
		//ָ������
		OpCode opcode;
		//ָ���
		unsigned char asmLen;
		std::list<AsmOp*>::iterator insertiter;	//��alive/dead�б��е�λ��
	};


	//alive��dead��������ָ����û�б����ӵ�������
	class AsmOpBank
	{
		std::map<Address, AsmOp*> optree;	//ָ��
		std::list<AsmOp*> deadlist;			//deadָ���б�
		std::list<AsmOp*> alivelist;		//aliveָ���б�
		std::list<AsmOp*> returnlist;		//returnָ���б�
		std::uint32_t uniqid;				//������
	public:
		AsmOpBank();
		//����ָ��
		AsmOp* create(const Address& pc);
		//��������Ѱ��ָ��OP
		AsmOp* findOp(const Address& pc) const;
		std::list<AsmOp*>::const_iterator beginDead(void) const;
		std::list<AsmOp*>::const_iterator endDead(void) const;
	};
}

