#pragma once
#include "Ghidra/type.hh"

class IDAArchitecture;

//IDA�еĵ���������
class IDATypeManager:public TypeFactory
{
public:
	explicit IDATypeManager(IDAArchitecture* architecture);

public:
	IDAArchitecture* m_archi;
};