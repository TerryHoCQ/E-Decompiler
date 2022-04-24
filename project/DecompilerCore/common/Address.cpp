#include "Address.h"

bool DecompilerCore::Address::operator<(const Address& op2) const 
{
	return offset < op2.offset;
}

bool DecompilerCore::Address::operator==(const Address& op2) const
{
	return offset == op2.offset;
}

std::uint64_t DecompilerCore::Address::getAddress()
{
	return offset;
}

DecompilerCore::Address::Address(std::uint64_t addr)
{
	this->offset = addr;
}

DecompilerCore::Address::~Address()
{
	
}

DecompilerCore::SeqNum::SeqNum(void)
{

}

DecompilerCore::Address DecompilerCore::SeqNum::getAddr(void) const
{
	return pc;
}

DecompilerCore::SeqNum::SeqNum(const Address& a, std::uint32_t b) :pc(a)
{
	uniq = b;
}

bool DecompilerCore::SeqNum::operator<(const SeqNum& op2) const
{
	if (pc == op2.pc) {
		return (uniq < op2.uniq);
	}
	return (pc < op2.pc);
}
