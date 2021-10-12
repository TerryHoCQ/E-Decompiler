#pragma once

//ר���������������Ե�Architecture

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

	//ִ�з����붯��
	int4 performActions(Funcdata& data);

	std::string emitPCode(unsigned int startAddr,unsigned int endAddr);
private:
	void buildLoader(DocumentStorage& store) override;
	//�������ݿ�
	Scope* buildDatabase(DocumentStorage& store) override;
	//������������
	void buildTypegrp(DocumentStorage& store) override;
	//�����Զ���ķ����붯��
	void buildAction(DocumentStorage& store) override;

	Translate* buildTranslator(DocumentStorage& store) override;
protected:
	Translate* m_translate;
private:
	std::stringstream m_err;

	//������Ϣ
	std::unique_ptr<IDASymbol> m_symbols;
	std::map<std::string, std::string> m_injectionMap;

	ActionGroup m_ScanAction;
};