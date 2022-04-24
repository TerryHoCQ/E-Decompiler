#pragma once
#include "BasicBlock.h"
#include <unordered_map>
#include <unordered_set>

class ControlFlowGraph
{
public:
	ControlFlowGraph(ea_t entry);
private:
	//�洢��ȫ���Ļ�����,     BasicBlock entry -> BasicBlock
	std::unordered_map<ea_t, BasicBlock> m_nodes;

	//�洢�����л�����ĸ��ڵ�����  BasicBlock entry -> its Parants
	std::unordered_map<ea_t, std::unordered_set<ea_t>> m_parents;
};