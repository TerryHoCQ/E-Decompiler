#pragma once
#include "BasicBlock.h"
#include ".\common\Op.h"
#include <map>
#include <vector>
#include <set>

struct cs_insn;
namespace DecompilerCore {

	class FlowInfo
	{
	public:
		//����ָ��OP����
		void generateOps(Address startAddr);
		//���ɻ�����
		void generateBlocks(void);
		//���÷�������ַ��Χ
		void setRange(const Address& b, const Address& e);
	private:
		//�ݹ��½�����
		void fallthru(void);
		//��������ָ��,����falseֹͣ����
		bool processInstruction(Address& curaddr, bool& startbasic);
		//����Jmpָ��
		bool processJumpInstruction(cs_insn*, AsmOp*);
		//���ɱ�
		void collectEdges(void);
		//��ȡָ�����һ��ָ��
		AsmOp* fallthruOp(AsmOp* op) const;
		//��ȡָ�����תָ��
		AsmOp* branchTarget(AsmOp* op) const;
	private:
		//�洢���������̵�ַ
		std::vector<Address> addrlist;
		//�������̷�Χ��ʼ��ַ
		Address baddr;
		//�������̷�Χ������ַ
		Address eaddr;
		//ָ��洢
		AsmOpBank obank;
		//����ָ�����
		std::uint32_t insn_count;

		//Դָ��,edge1��������edge2����
		std::list<AsmOp*> block_edge1;
		//Ŀ��ָ��
		std::list<AsmOp*> block_edge2;
		//�������ĵ�ַ
		std::set<Address> visitedAsm;
	};

}

