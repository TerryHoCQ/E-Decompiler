#include "IDAPrint.h"

IDAPrintCapability IDAPrintCapability::inst;

IDAPrintCapability::IDAPrintCapability()
{
	name = "e-language";
}

PrintLanguage* IDAPrintCapability::buildLanguage(Architecture* glb)
{
	return new IDAPrint(glb, name);
}

const std::map<std::string, MemoryLocation>& IDAEmit::getSymbolAddr() const
{
	return m_symbolMap;
}

int4 IDAEmit::beginFunction(const Funcdata* fd)
{
	m_fd = (Funcdata*)fd;
	m_symbolMap.clear();
	return EmitPrettyPrint::beginFunction(fd);
}

int4 IDAEmit::openParen(char o, int4 id /*= 0*/)
{
	//EmitColorGuard guard(*this, COLOR_KEYWORD);
	return EmitPrettyPrint::openParen(o, id);
}

void IDAEmit::closeParen(char c, int4 id)
{
	return EmitPrettyPrint::closeParen(c, id);
}

void IDAEmit::tagOp(const char* ptr, syntax_highlight hl, const PcodeOp* op)
{
	EmitPrettyPrint::tagOp(ptr, hl, op);
}

void IDAEmit::tagVariable(const char* ptr, syntax_highlight hl, const Varnode* vn, const PcodeOp* op)
{
	auto name = std::string(ptr);
	EmitPrettyPrint::tagVariable(name.c_str(), hl, vn, op);
}

void IDAEmit::tagFuncName(const char* ptr, syntax_highlight hl, const Funcdata* fd, const PcodeOp* op)
{
	auto name = std::string(ptr);
	EmitPrettyPrint::tagFuncName(name.c_str(), hl, fd, op);
}

void IDAEmit::tagField(const char* ptr, syntax_highlight hl, const Datatype* ct, int4 off)
{
	EmitPrettyPrint::tagField(ptr, hl, ct, off);
}

void IDAEmit::tagLabel(const char* ptr, syntax_highlight hl, const AddrSpace* spc, uintb off)
{
	EmitPrettyPrint::tagLabel(ptr, hl, spc, off);
}

void IDAEmit::print(const char* str, syntax_highlight hl /*= no_color*/)
{
	EmitPrettyPrint::print(str, hl);
}

void IDAEmit::tagType(const char* ptr, syntax_highlight hl, const Datatype* ct)
{
	EmitPrettyPrint::tagType(ptr, hl, ct);
}

IDAPrint::IDAPrint(Architecture* g, const string& nm)
	:PrintC(g, nm)
{
	emit = new IDAEmit();
	emit->setMaxLineSize(400);
}

const IDAEmit& IDAPrint::getEmitter() const
{
	return *static_cast<IDAEmit*>(emit);
}