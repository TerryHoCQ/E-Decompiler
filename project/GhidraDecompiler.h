#pragma once
#include <string>
#include <map>
#include <memory>

//Ghidra∑¥±‡“Î∆˜


struct MemoryLocation
{
	enum class MemoryLocationType
	{
		RAM,
		Register,
		Stack
	};

	MemoryLocationType type;
	uint64_t offset;
	uint32_t addrSize;
	uint64_t pc;
	uint64_t typeSize;

	MemoryLocation(MemoryLocationType type, uint64_t offset, uint32_t addrSize, uint64_t pc = 0, uint64_t tyepSz = 0)
		: type{ type }, offset{ offset }, addrSize{ addrSize }, pc{ pc }, typeSize{ tyepSz }
	{}


	MemoryLocation(const std::string& name, uint64_t offset, uint32_t addrSize, uint64_t pc = 0, uint64_t tyepSz = 0)
		: offset{ offset }, addrSize{ addrSize }, pc{ pc }, typeSize{ tyepSz }
	{
		if (name == "register" || name == "unique")
		{
			type = MemoryLocationType::Register;
		}
		else if (name == "stack")
		{
			type = MemoryLocationType::Stack;
		}
		else {
			type = MemoryLocationType::RAM;
		}
	}

	static std::string to_string(MemoryLocationType type)
	{
		switch (type)
		{

		case MemoryLocation::MemoryLocationType::RAM:
			return "ram";
		case MemoryLocation::MemoryLocationType::Register:
			return "register";
		case MemoryLocation::MemoryLocationType::Stack:
			return "stack";
		default:
			break;
		}

		return "ram";
	}
};

struct DecompilerResult
{
	std::string	cCode;
	std::string name;
	uint64_t ea;
	std::map<std::string, MemoryLocation> symbolAddress;

	DecompilerResult()
	{
		ea = 0;
	}
	DecompilerResult(std::string name, uint64_t ea, std::string cCode, std::map<std::string, MemoryLocation> symbolAddress)
		:name(name), ea(ea), cCode(cCode), symbolAddress(symbolAddress)
	{

	}
};

enum ArchType
{
	UNKNOWN_ARCH,
	ESTATIC_ARCH,
	EDYNAMIC_ARCH,
};

class IDAArchitecture;
class GhidraDecompiler
{
public:
	GhidraDecompiler();
	~GhidraDecompiler();
	DecompilerResult decompile(uint64_t funcAddress);
	static bool InitGhidraDecompiler();
	static std::unique_ptr<GhidraDecompiler> build();
private:
	ArchType DetectArchitecture();
public:
	std::unique_ptr<IDAArchitecture> m_architecture = nullptr;
};