#include "CapstoneWrapper.h"
#include "..\SectionManager.h"

CapstoneWrapper gCapstoneWrapper;

CapstoneWrapper& CapstoneWrapper::Instance()
{
	return gCapstoneWrapper;
}

CapstoneWrapper::CapstoneWrapper()
{
	cs_open(CS_ARCH_X86, CS_MODE_32, &handle);
	cs_option(handle, CS_OPT_DETAIL, CS_OPT_ON);
	cs_option(handle, CS_OPT_SKIPDATA, CS_OPT_OFF);

	g_ins = cs_malloc(handle);
}

CapstoneWrapper::~CapstoneWrapper()
{
	cs_close(&handle);
	if (g_ins) {
		cs_free(g_ins, 1);
	}
}

bool CapstoneWrapper::disasm(std::uint64_t addr, cs_insn*& ins)
{
	ins = g_ins;
	unsigned char* codeBuf = SectionManager::LinearAddrToVirtualAddr(addr);
	size_t codeSize = 16;
	return cs_disasm_iter(handle, (const uint8_t**)&codeBuf, &codeSize, &addr, ins);
}