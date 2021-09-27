#include "IDAScope.h"
#include "exception.h"
#include "IDATypeManager.h"

#define UNIMPLEMENTED throw UnImplementedFunction(__func__)

IDAScope::IDAScope(uint8_t id, IDAArchitecture* architecture)
	:Scope(id, "", architecture, this), m_proxy(0, "", architecture, this)
{

}

ScopeInternal* IDAScope::getProxy()
{
	return &m_proxy;
}

Scope* IDAScope::buildSubScope(uint8 id, const string& nm)
{
	return new IDAScope(id, static_cast<IDAArchitecture*>(glb));
}

//不急着实现这些虚函数,等抛异常再说

void IDAScope::addSymbolInternal(Symbol* sym)
{
	UNIMPLEMENTED;
}

SymbolEntry* IDAScope::addMapInternal(Symbol* sym, uint4 exfl, const Address& addr, int4 off, int4 sz, const RangeList& uselim)
{
	UNIMPLEMENTED;
}

SymbolEntry* IDAScope::addDynamicMapInternal(Symbol* sym, uint4 exfl, uint8 hash, int4 off, int4 sz, const RangeList& uselim)
{
	UNIMPLEMENTED;
}

MapIterator IDAScope::begin() const
{
	UNIMPLEMENTED;
}

MapIterator IDAScope::end() const
{
	UNIMPLEMENTED;
}

list<SymbolEntry>::const_iterator IDAScope::beginDynamic() const
{
	UNIMPLEMENTED;
}

list<SymbolEntry>::const_iterator IDAScope::endDynamic() const
{
	UNIMPLEMENTED;
}

list<SymbolEntry>::iterator IDAScope::beginDynamic()
{
	UNIMPLEMENTED;
}

list<SymbolEntry>::iterator IDAScope::endDynamic()
{
	UNIMPLEMENTED;
}

void IDAScope::clear(void)
{
	m_proxy.clear();
}

void IDAScope::clearCategory(int4 cat)
{
	m_proxy.clearCategory(cat);
}

void IDAScope::clearUnlocked()
{
	UNIMPLEMENTED;
}

void IDAScope::clearUnlockedCategory(int4 cat)
{
	UNIMPLEMENTED;
}

void IDAScope::adjustCaches(void)
{
	m_proxy.adjustCaches();
}

void IDAScope::removeSymbolMappings(Symbol* symbol)
{
	UNIMPLEMENTED;
}

void IDAScope::removeSymbol(Symbol* symbol)
{
	m_proxy.removeSymbol(symbol);
}


void IDAScope::renameSymbol(Symbol* sym, const string& newname)
{
	m_proxy.renameSymbol(sym, newname);
}

void IDAScope::retypeSymbol(Symbol* sym, Datatype* ct)
{
	m_proxy.retypeSymbol(sym, ct);
}

void IDAScope::setAttribute(Symbol* sym, uint4 attr)
{
	m_proxy.setAttribute(sym, attr);
}

void IDAScope::clearAttribute(Symbol* sym, uint4 attr)
{
	m_proxy.clearAttribute(sym, attr);
}

void IDAScope::setDisplayFormat(Symbol* sym, uint4 attr)
{
	m_proxy.setDisplayFormat(sym, attr);
}

SymbolEntry* IDAScope::findAddr(const Address& addr, const Address& usepoint) const
{
	UNIMPLEMENTED;
}

SymbolEntry* IDAScope::findContainer(const Address& addr, int4 size, const Address& usepoint) const
{
	auto proxy = static_cast<IDAScope*>(glb->symboltab->getGlobalScope())->getProxy();

	//先调用Ghidra寻找
	auto result = proxy->findContainer(addr, size, usepoint);
	if (result != nullptr)
	{
		return result;
	}

	//To do...
	return nullptr;
}

SymbolEntry* IDAScope::findClosestFit(const Address&, int4, const Address&) const
{
	UNIMPLEMENTED;
}

Funcdata* IDAScope::findFunction(const Address& addr) const
{
	auto proxy = static_cast<IDAScope*>(glb->symboltab->getGlobalScope())->getProxy();

	auto result = proxy->findFunction(addr);
	if (result != nullptr)
	{
		return result;
	}

	auto data = static_cast<IDAArchitecture*>(glb)->getSymbolDatabase().find(addr.getOffset());
	if (!data)
	{
		return nullptr;
	}

	//Ghidra空间创建新函数
	auto sym = proxy->addFunction(addr, data->m_name);
	auto funcData = sym->getFunction();

	//利用IDA刷新函数数据
	//To do...
	//static_cast<IDATypeManager*>(glb->types)->update(*funcData);

	return funcData;
}

ExternRefSymbol* IDAScope::findExternalRef(const Address& addr) const
{
	UNIMPLEMENTED;
}

LabSymbol* IDAScope::findCodeLabel(const Address& addr) const
{
	UNIMPLEMENTED;
}

SymbolEntry* IDAScope::findOverlap(const Address& addr, int4 size) const
{
	UNIMPLEMENTED;
}

void IDAScope::findByName(const string& name, vector<Symbol*>& res) const
{
	UNIMPLEMENTED;
}

bool IDAScope::isNameUsed(const std::string&, const Scope*) const
{
	UNIMPLEMENTED;
}

Funcdata* IDAScope::resolveExternalRefFunction(ExternRefSymbol* sym) const
{
	UNIMPLEMENTED;
}

std::string IDAScope::buildVariableName(const Address& addr, const Address& pc, Datatype* ct, int4& index, uint4 flags) const
{
	UNIMPLEMENTED;
}

std::string IDAScope::buildUndefinedName(void) const
{
	UNIMPLEMENTED;
}

std::string IDAScope::makeNameUnique(const string& nm) const
{
	UNIMPLEMENTED;
}

void IDAScope::saveXml(ostream& s) const
{
	UNIMPLEMENTED;
}

void IDAScope::restoreXml(const Element* el)
{
	UNIMPLEMENTED;
}

void IDAScope::printEntries(ostream& s) const
{
	UNIMPLEMENTED;
}

int4 IDAScope::getCategorySize(int4 cat) const
{
	UNIMPLEMENTED;
}

Symbol* IDAScope::getCategorySymbol(int4 cat, int4 ind) const
{
	UNIMPLEMENTED;
}

void IDAScope::setCategory(Symbol* sym, int4 cat, int4 ind)
{
	UNIMPLEMENTED;
}

