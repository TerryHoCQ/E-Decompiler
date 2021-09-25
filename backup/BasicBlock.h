#pragma once
#include <pro.h>
#include <set>

class BasicBlock
{
public:
	BasicBlock(ea_t entry);	
	~BasicBlock();
public:
	//���ָ��
	void AppendInstruction(ea_t instAddr);
public:
	ea_t m_entry;  //���������
	ea_t m_end;    //���������
private:
	std::set<ea_t> m_SaveInstructionAddr;
};