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
		//生成指令OP集合
		void generateOps(Address startAddr);
		//生成基本块
		void generateBlocks(void);
		//设置分析流地址范围
		void setRange(const Address& b, const Address& e);
	private:
		//递归下降分析
		void fallthru(void);
		//分析单条指令,返回false停止分析
		bool processInstruction(Address& curaddr, bool& startbasic);
		//分析Jmp指令
		bool processJumpInstruction(cs_insn*, AsmOp*);
		//生成边
		void collectEdges(void);
		//获取指令的下一条指令
		AsmOp* fallthruOp(AsmOp* op) const;
		//获取指令的跳转指令
		AsmOp* branchTarget(AsmOp* op) const;
	private:
		//存储分析的流程地址
		std::vector<Address> addrlist;
		//分析流程范围起始地址
		Address baddr;
		//分析流程范围结束地址
		Address eaddr;
		//指令存储
		AsmOpBank obank;
		//流程指令个数
		std::uint32_t insn_count;

		//源指令,edge1数量等于edge2数量
		std::list<AsmOp*> block_edge1;
		//目的指令
		std::list<AsmOp*> block_edge2;
		//分析过的地址
		std::set<Address> visitedAsm;
	};

}

