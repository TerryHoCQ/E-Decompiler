#pragma once
#include <ida.hpp>
#include <windows.h>
#include <funcs.hpp>

enum NodeType_t
{
	NODE_NORMAL = 0,
	NODE_LONGJMP = 1,	       //      -->
	NODE_CALL = 2,	           //      <>
	NODE_JMPAPI = 3,	       //      []
	NODE_CALLAPI = 4,	       //      <[]>
	NODE_CONSTANT = 6,	       //      !!
	NODE_LEFTPASS = 11,        //      ?
	NODE_RIGHTPASS = 12,       //       ?
	NODE_ALLPASS = 13          //      ??
};


class TrieTreeNode
{
public:
	TrieTreeNode();
	qvector<TrieTreeNode*> SpecialNodes;
	TrieTreeNode** ChildNodes;

	uint32 SpecialType;	//һ�����ִ�������
	char* EsigText;		//һ�����ִ�������
	char* FuncName;		//��������

	bool IsMatched;     //�Ƿ��Ѿ�ƥ���
};

class TrieTree
{
public:
	TrieTree();
	~TrieTree();

	void Log_PrintSubFunc();
	bool LoadSig(const char* lpMapPath);

	//char* MatchSig(UCHAR*);					//����ƥ��
	//
	//������ͨ�ڵ�
	TrieTreeNode* AddNode(TrieTreeNode* p, qstring Txt);
	//��������ڵ�
	TrieTreeNode* AddSpecialNode(TrieTreeNode* p, uint type, qstring Txt);

public:
	qvector<char*>  MemAllocSave;

	//�޸ĺ���������
	bool m_IsSetName;
	bool m_IsAligned;
	bool m_IsAllMem;
	bool m_MatchSubName;
protected:
	bool Insert(qstring& FuncTxt, const qstring& FuncName);
	bool CmpCode(uchar* FuncSrc, qstring& FuncTxt);
private:
	//���ڵ�
	TrieTreeNode* root;
	//func_t* func;

	//char* Match(TrieTreeNode* p, UCHAR* FuncSrc);			 //����һΪƥ��ڵ�,������Ϊƥ���ַ,����ƥ��ɹ��ĺ����ı�
	//BOOL CheckNode(TrieTreeNode* p, UCHAR*& FuncSrc);		//��ǰ����ڵ��Ƿ�ƥ��

	//�Ӻ���,�������ƺͺ����ı�һһӳ��
	std::map<qstring, qstring> m_subFunc;	

	 //R����Runtime,����ʱ��¼ʵ�ʵ�ַ��Ӧ����,��Ҫ��ͼһ����ַ����������� ,����һΪʵ���ڴ��ַ,������Ϊ��Ӧ����
	std::map<uint32, qstring> m_RFunc; 
};