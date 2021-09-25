#pragma once

//专门用来处理易语言的Architecture

#include "Ghidra\sleigh_arch.hh"
#include "loadimage_ecat.h"


class IDAArchitecture : public SleighArchitecture
{
public:
	IDAArchitecture(const string& targ);	///< Constructor
	~IDAArchitecture();
public:
	void addInjection(std::string functionName, std::string injection);
	void buildLoader(DocumentStorage& store) override;
private:
	std::stringstream m_err;

	std::map<std::string, std::string> m_injectionMap;
};