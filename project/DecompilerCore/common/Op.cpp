#include "Op.h"

DecompilerCore::AsmOp::AsmOp()
{
	flags = 0;
	opcode = OpCode::CPUI_DEFAULT;
}

DecompilerCore::AsmOp::AsmOp(const SeqNum& sq)
{
	start = sq;
	flags = 0;
	opcode = OpCode::CPUI_DEFAULT;
}

bool DecompilerCore::AsmOp::isCall(void) const
{
	return ((flags & AsmOp::call) != 0);
}

void DecompilerCore::AsmOp::setFlag(std::uint32_t fl)
{
	flags |= fl;
}

void DecompilerCore::AsmOp::setOpcode(OpCode op)
{
	opcode = op;
}

void DecompilerCore::AsmOp::setAsmLen(unsigned char len)
{
	asmLen = len;
}

unsigned char DecompilerCore::AsmOp::getAsmLen()
{
	return asmLen;
}

DecompilerCore::AsmOp::OpCode DecompilerCore::AsmOp::getOpCode(void)
{
	return opcode;
}

DecompilerCore::Address DecompilerCore::AsmOp::getAddress()
{
	return this->start.getAddr();
}

bool DecompilerCore::AsmOp::isBlockStart(void) const
{
	return ((flags & AsmOp::startbasic) != 0);
}

void DecompilerCore::AsmOp::opMarkStartBasic()
{
	this->setFlag(AsmOp::startbasic);
}

const DecompilerCore::SeqNum& DecompilerCore::AsmOp::getSeqNum(void) const
{
	return start;
}

DecompilerCore::AsmOpBank::AsmOpBank()
{
	uniqid = 0x0;
}

DecompilerCore::AsmOp* DecompilerCore::AsmOpBank::create(const Address& pc)
{
	AsmOp* op = new AsmOp(SeqNum(pc, uniqid++));
	optree[pc] = op;
	op->setFlag(AsmOp::dead);
	op->insertiter = deadlist.insert(deadlist.end(), op);
	return op;
}

DecompilerCore::AsmOp* DecompilerCore::AsmOpBank::findOp(const Address& pc) const
{
	std::map<Address, AsmOp*>::const_iterator iter = optree.find(pc);
	if (iter == optree.end()) {
		return (AsmOp*)0;
	}
	return (*iter).second;
}

std::list<DecompilerCore::AsmOp*>::const_iterator DecompilerCore::AsmOpBank::beginDead(void) const
{
	return deadlist.begin();
}

std::list<DecompilerCore::AsmOp*>::const_iterator DecompilerCore::AsmOpBank::endDead(void) const
{
	return deadlist.end();
}
