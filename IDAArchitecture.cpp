#include "IDAArchitecture.h"
#include "IDALoader.h"
#include "IDATypeManager.h"
#include "IDAScope.h"
#include "EazyAction.h"

IDAArchitecture::IDAArchitecture(const string& targ):
	SleighArchitecture("ida", targ, &m_err),
	m_ScanAction(Action::rule_onceperfunc, "ESCAN")
{
	
}	

IDAArchitecture::~IDAArchitecture()
{
	SleighArchitecture::shutdown();
}

void IDAArchitecture::addInjection(std::string functionName, std::string injection)
{
	m_injectionMap.emplace(functionName, injection);
}

void IDAArchitecture::buildLoader(DocumentStorage& store)
{
	collectSpecFiles(*errorstream);
	loader = new IDALoader();
}

IDASymbol& IDAArchitecture::getSymbolDatabase() const
{
	return *m_symbols.get();
}

Scope* IDAArchitecture::buildDatabase(DocumentStorage& store)
{
	symboltab = new Database(this, false);
	Scope* globscope = new IDAScope(0, this);
	symboltab->attachScope(globscope, nullptr);
	return globscope;
}

void IDAArchitecture::buildTypegrp(DocumentStorage& store)
{
	types = new IDATypeManager(this);
	types->setCoreType("void", 1, TYPE_VOID, false);
	types->setCoreType("bool", 1, TYPE_BOOL, false);
	types->setCoreType("unsigned char", 1, TYPE_UINT, false);
	types->setCoreType("unsigned short", 2, TYPE_UINT, false);
	types->setCoreType("unsigned int", 4, TYPE_UINT, false);
	types->setCoreType("unsigned long long", 8, TYPE_UINT, false);

	types->setCoreType("char", 1, TYPE_INT, true);
	types->setCoreType("short", 2, TYPE_INT, false);
	types->setCoreType("int", 4, TYPE_INT, false);
	types->setCoreType("signed long long", 8, TYPE_INT, false);
	types->setCoreType("float", 4, TYPE_FLOAT, false);
	types->setCoreType("double", 8, TYPE_FLOAT, false);

	types->setCoreType("__uint8", 1, TYPE_UNKNOWN, false);
	types->setCoreType("__uint16", 2, TYPE_UNKNOWN, false);
	types->setCoreType("__uint32", 4, TYPE_UNKNOWN, false);
	types->setCoreType("__uint64", 8, TYPE_UNKNOWN, false);
	types->setCoreType("code", 1, TYPE_CODE, false);
	types->cacheCoreTypes();
}

void IDAArchitecture::buildAction(DocumentStorage& store)
{	
	SleighArchitecture::buildAction(store);

	//m_ScanAction.addAction(new EActionScanKernel("eaction"),);
}

Translate* IDAArchitecture::buildTranslator(DocumentStorage& store)
{
	m_translate = SleighArchitecture::buildTranslator(store);
	return m_translate;
}

int4 IDAArchitecture::performActions(Funcdata& data)
{
	allacts.getCurrent()->reset(data);
	m_ScanAction.reset(data);

	allacts.getCurrent()->perform(data);
	auto res = m_ScanAction.perform(data);

	if (res < 0)
	{
		return res;
	}

	return res;
}

std::string IDAArchitecture::emitPCode(unsigned int startAddr, unsigned int endAddr)
{
	PcodeRawOut emit;
	int length;

	Address addr(m_translate->getDefaultCodeSpace(), startAddr);
	Address lastaddr(m_translate->getDefaultCodeSpace(), endAddr);

	while (addr < lastaddr) {
		length = m_translate->oneInstruction(emit, addr); // Translate instruction
		addr = addr + length;
	}
	return emit.m_saveStr.str();
}

static void print_vardata(ostream& s, VarnodeData& data)
{
	s << '(' << data.space->getName() << ',';
	data.space->printOffset(s, data.offset);
	s << ',' << dec << data.size << ')';
}



void PcodeRawOut::dump(const Address& addr, OpCode opc, VarnodeData* outvar, VarnodeData* vars, int4 isize)
{
	m_saveStr << std::hex << "[" << addr.getOffset() << "]:";
	if (outvar != (VarnodeData*)0) {
		print_vardata(m_saveStr, *outvar);
		m_saveStr << " = ";
	}
	m_saveStr << get_opname(opc);
	// Possibly check for a code reference or a space reference
	for (int4 i = 0; i < isize; ++i) {
		m_saveStr << ' ';
		print_vardata(m_saveStr, vars[i]);
	}
	m_saveStr << endl;
}
