#pragma once
#include "Ghidra/printc.hh"
#include "GhidraDecompiler.h"

class IDAPrintCapability : public PrintLanguageCapability
{
public:
	explicit IDAPrintCapability();
	PrintLanguage* buildLanguage(Architecture* glb) override;
private:
	static IDAPrintCapability inst;
};

class IDAEmit :public EmitPrettyPrint
{
public:
	const std::map<std::string, MemoryLocation>& getSymbolAddr() const;
protected:
	int4 beginFunction(const Funcdata* fd) override;
	int4 openParen(char o, int4 id = 0) override;
	void closeParen(char c, int4 id) override;
	void tagOp(const char* ptr, syntax_highlight hl, const PcodeOp* op) override;
	void tagVariable(const char* ptr, syntax_highlight hl,const Varnode* vn, const PcodeOp* op) override;
	void tagFuncName(const char* ptr, syntax_highlight hl, const Funcdata* fd, const PcodeOp* op) override;
	void tagField(const char* ptr, syntax_highlight hl, const Datatype* ct, int4 off) override;
	void tagLabel(const char* ptr, syntax_highlight hl, const AddrSpace* spc, uintb off) override;
	void print(const char* str, syntax_highlight hl = no_color) override;
	void tagType(const char* ptr, syntax_highlight hl, const Datatype* ct) override;

protected:
	Funcdata* m_fd;
	std::map<std::string, MemoryLocation> m_symbolMap;
};

class IDAPrint : public PrintC
{
public:
	IDAPrint(Architecture* g, const string& nm);
	const IDAEmit& getEmitter() const;
};