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
			startbasic = 1,	    //指令是basicBlock头
			branch = 2,			//指令是个跳转
			call = 4,			//指令是个call
			returns = 0x8,		//指令是个返回
			dead = 0x20,		//指令尚未激活
		};
		//指令种类
		enum OpCode 
		{
			CPUI_DEFAULT = 0x0,
			//无条件跳转指令
			CPUI_BRANCH,
			//条件跳转指令
			CPUI_CBRANCH,
			//跳转表
			CPUI_BRANCHIND,
			//CALL指令
			CPUI_CALL,
			//返回指令,
			CPUI_RETURN,
			//错误指令,
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
		//指令是否为call
		bool isCall(void) const;
		void setFlag(std::uint32_t fl);
		void setOpcode(OpCode op);
		//设置指令长度
		void setAsmLen(unsigned char len);
		//获取指令长度
		unsigned char getAsmLen();
		//获取指令类型
		OpCode getOpCode(void);
		//获取指令地址
		Address getAddress();
		//当前指令是否为基本块起始指令
		bool isBlockStart(void) const;
		//标记当前指令是基本块起始指令
		void opMarkStartBasic();
		const SeqNum& getSeqNum(void) const;
	public:
		mutable std::int32_t flags;
		//指令数据
		OpData opdata;
	private:
		//指令序列
		SeqNum start;
		//指令类型
		OpCode opcode;
		//指令长度
		unsigned char asmLen;
		std::list<AsmOp*>::iterator insertiter;	//在alive/dead列表中的位置
	};


	//alive和dead用来区分指令有没有被链接到控制流
	class AsmOpBank
	{
		std::map<Address, AsmOp*> optree;	//指令
		std::list<AsmOp*> deadlist;			//dead指令列表
		std::list<AsmOp*> alivelist;		//alive指令列表
		std::list<AsmOp*> returnlist;		//return指令列表
		std::uint32_t uniqid;				//计数器
	public:
		AsmOpBank();
		//创建指令
		AsmOp* create(const Address& pc);
		//根据序列寻找指令OP
		AsmOp* findOp(const Address& pc) const;
		std::list<AsmOp*>::const_iterator beginDead(void) const;
		std::list<AsmOp*>::const_iterator endDead(void) const;
	};
}

