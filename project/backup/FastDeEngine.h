#pragma once
#include <pro.h>
#include <funcs.hpp>


//�������������������������������ڴ洢���������Ľṹ�塪������������������������������

enum PushType
{
	PUSH_Reg,
	PUSH_Addr,
};

struct StackContent
{
	PushType type;
	uint32 value;
};


//�ֲ�����
class LocalVariable
{

};

//��̬��ջ
class DynamicStack:public qstack<StackContent>
{
public:

};

class FastDeEngine
{
public:
	FastDeEngine();
	bool DoFastDecompile(func_t* pFunc);
private:
	void Handler_push();
	void Handler_sub();
	void Handler_mov();
private:
	enum DecompileState
	{
		ESTATE_Error = -1,
		ESTATE_Start,       //��ʼ����
		ESTATE_FuncHead,    //����ͷ,push ebp,mov ebp,esp
	};
private:
	DecompileState m_DecompileState;
	qlist<ea_t> m_analyzeQuene;
	int m_VarStackSize = 0;
	DynamicStack m_DynamicStack;
	LocalVariable m_LocalVarList;
};