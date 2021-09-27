#pragma once
#include "Ghidra/database.hh"
#include "IDAArchitecture.h"


//IDAScope是ScopeInternal的中间代理层

class IDAScope :public Scope
{
public:
	explicit IDAScope(uint8_t id, IDAArchitecture* architecture);

	ScopeInternal* getProxy();
private:
	Scope* buildSubScope(uint8 id, const string& nm) override;

	void addSymbolInternal(Symbol* sym) override;

	SymbolEntry* addMapInternal(Symbol* sym, uint4 exfl, const Address& addr, int4 off, int4 sz, const RangeList& uselim) override;

	SymbolEntry* addDynamicMapInternal(Symbol* sym, uint4 exfl, uint8 hash, int4 off, int4 sz,const RangeList& uselim) override;

private:
	MapIterator begin() const override;
	MapIterator end() const override;
	list<SymbolEntry>::const_iterator beginDynamic() const override;
	list<SymbolEntry>::const_iterator endDynamic() const override;
	list<SymbolEntry>::iterator beginDynamic() override;
	list<SymbolEntry>::iterator endDynamic() override;
	void clear(void) override;
	void clearCategory(int4 cat) override;
	void clearUnlocked() override;
	void clearUnlockedCategory(int4 cat) override;
private:
	void adjustCaches(void) override;
	void removeSymbolMappings(Symbol* symbol) override;
	void removeSymbol(Symbol* symbol) override;
	void renameSymbol(Symbol* sym, const string& newname) override;
	void retypeSymbol(Symbol* sym, Datatype* ct) override;
	void setAttribute(Symbol* sym, uint4 attr) override;
	void clearAttribute(Symbol* sym, uint4 attr) override;
	void setDisplayFormat(Symbol* sym, uint4 attr) override;
private:
	SymbolEntry* findAddr(const Address& addr, const Address& usepoint) const override;
	SymbolEntry* findContainer(const Address& addr, int4 size, const Address& usepoint) const override;
	SymbolEntry* findClosestFit(const Address&, int4, const Address&) const override;
	Funcdata* findFunction(const Address& addr) const override;
	ExternRefSymbol* findExternalRef(const Address& addr) const override;
	LabSymbol* findCodeLabel(const Address& addr) const override;
	SymbolEntry* findOverlap(const Address& addr, int4 size) const;
	void findByName(const string& name, vector<Symbol*>& res) const;
	bool isNameUsed(const std::string&, const Scope*) const override;
	Funcdata* resolveExternalRefFunction(ExternRefSymbol* sym) const override;
	string buildVariableName(const Address& addr, const Address& pc, Datatype* ct, int4& index, uint4 flags) const override;
	string buildUndefinedName(void) const override;
	string makeNameUnique(const string& nm) const override;
	void saveXml(ostream& s) const override;
	void restoreXml(const Element* el) override;
	void printEntries(ostream& s) const override;
	int4 getCategorySize(int4 cat) const override;
	Symbol* getCategorySymbol(int4 cat, int4 ind) const override;
	void setCategory(Symbol* sym, int4 cat, int4 ind) override;
private:
	ScopeInternal m_proxy;
};