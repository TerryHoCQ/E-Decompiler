#include "EazyAction.h"
#include "Ghidra/funcdata.hh"
#include "IDAWrapper.h"

int scanType(unsigned int addr)
{
	if (IDAWrapper::get_word(addr) != 0x25FF) {
		return -1;
	}

	auto kernelFunc = IDAWrapper::get_dword(IDAWrapper::get_dword(addr + 2));
	

	return -1;
}

int4 EActionScanKernel::apply(Funcdata& data)
{
	for (int n = 0; n < data.numCalls(); ++n) {

		FuncCallSpecs* fc = data.getCallSpecs(n);
		int kType = scanType(fc->getEntryAddress().getOffset());
		if (kType == -1) {
			continue;
		}
		
		
	}


	return 0;
}
