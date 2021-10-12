#pragma once
#include "Ghidra/action.hh"

class EKernelLib;
class EActionScanKernel : public Action
{
public:
	EActionScanKernel(const string& g, EKernelLib* eLib) : Action(Action::ruleflags::rule_onceperfunc, "scankernel", g) {
		eKernelLib = eLib;
	}
	virtual Action* clone(const ActionGroupList& grouplist) const {
		if (!grouplist.contains(getGroup())) return (Action*)0;
		return new EActionScanKernel(getGroup(), eKernelLib);
	}

	int4 apply(Funcdata& data) override;
private:
	EKernelLib* eKernelLib;
};