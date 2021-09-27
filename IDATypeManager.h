#pragma once
#include "Ghidra/type.hh"

class IDAArchitecture;

//IDA中的的数据类型
class IDATypeManager:public TypeFactory
{
public:
	explicit IDATypeManager(IDAArchitecture* architecture);

public:
	IDAArchitecture* m_archi;
};