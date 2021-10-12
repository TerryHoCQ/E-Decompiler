#pragma once

//专门用来处理易语言的Architecture

#include "Ghidra\sleigh_arch.hh"
#include "IDALoader.h"
#include "IDASymbol.h"

class PcodeRawOut : public PcodeEmit {
public:
	virtual void dump(const Address& addr, OpCode opc, VarnodeData* outvar, VarnodeData* vars, int4 isize);
public:
	std::stringstream m_saveStr;
};

class IDAArchitecture : public SleighArchitecture
{
public:
	IDAArchitecture(const string& targ);	///< Constructor
	~IDAArchitecture();
public:
	void addInjection(std::string functionName, std::string injection);
	
	IDASymbol& getSymbolDatabase() const;

	//执行反编译动作
	int4 performActions(Funcdata& data);

	std::string emitPCode(unsigned int startAddr,unsigned int endAddr);
private:
	void buildLoader(DocumentStorage& store) override;
	//设置数据库
	Scope* buildDatabase(DocumentStorage& store) override;
	//设置数据类型
	void buildTypegrp(DocumentStorage& store) override;
	//设置自定义的反编译动作
	void buildAction(DocumentStorage& store) override;

	Translate* buildTranslator(DocumentStorage& store) override;
protected:
	Translate* m_translate;
private:
	std::stringstream m_err;

	//符号信息
	std::unique_ptr<IDASymbol> m_symbols;
	std::map<std::string, std::string> m_injectionMap;

	ActionGroup m_ScanAction;
};