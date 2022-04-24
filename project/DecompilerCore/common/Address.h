#pragma once
#include <cstdint>

namespace DecompilerCore
{
	class Address
	{
	public:
		Address(std::uint64_t addr = 0);
		~Address();
		bool operator<(const Address& op2) const;
		bool operator==(const Address& op2) const;
		std::uint64_t getAddress();
	public:
		std::uint64_t offset = 0;
	};

	class SeqNum
	{
		Address pc;
		std::uint32_t uniq;	
		std::uint32_t order;
	public:
		SeqNum(void);
		SeqNum(const Address& a, std::uint32_t b);
		Address getAddr(void) const;
		bool operator<(const SeqNum& op2) const;
	};
}