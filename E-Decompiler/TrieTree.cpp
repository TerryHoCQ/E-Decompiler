#include "TrieTree.h"
#include <ida.hpp>
#include <kernwin.hpp>
#include <diskio.hpp>
#include <fpro.h>
#include <name.hpp>
#include "SectionManager.h"
#include "./Utils/Common.h"

bool FastMatch_CmpApi(unsigned char* pSrc, qstring IATEAT)
{
	qstring IATCom;
	qstring EATCom;

	int EATpos = IATEAT.find("||");
	if (EATpos != -1) {            //�����Զ���EAT
		IATCom = IATEAT.substr(0, EATpos);
		EATCom = IATEAT.substr(EATpos + 2);
	}
	else
	{
		IATCom = IATEAT;
		EATCom = IATEAT.substr(IATEAT.find('.') + 1);
	}

	size_t nDllPos = IATCom.find('.');
	if (nDllPos != qstring::npos) {
		IATCom = IATCom.substr(nDllPos + 1);
	}

	ea_t oaddr = ReadUInt(pSrc);
	qstring funcName = get_name(oaddr);
	if (funcName.find("__imp_") == 0) {
		funcName = funcName.substr(6);
	}

	if (!qstrcmp(funcName.c_str(), EATCom.c_str()) || !qstrcmp(funcName.c_str(), IATCom.c_str())) {
		return true;
	}
	return false;
}

qstring GetMidString(qstring& src, const char* left, const char* right, int offset) {
	int start = src.find(left, offset);
	if (start == -1) {
		return "";
	}

	int end = src.find(right, start);
	if (end == -1) {
		return "";
	}
	qstring ret = src.substr(start + qstrlen(left), end);
	return ret;
}

bool TrieTree::SlowMatch_CmpCall(unsigned char* pSrc, qstring FuncName)
{
	if (*pSrc != 0xE8) {
		return false;
	}
	ea_t oaddr = SectionManager::VirtualAddrToLinearAddr(pSrc + ReadInt(pSrc + 1) + 5);
	if (m_RFunc[oaddr] == FuncName) {
		return true;
	}
	m_RFunc[oaddr] = FuncName;
	if (SlowMatch(SectionManager::LinearAddrToVirtualAddr(oaddr), m_subFunc[FuncName])) {
		return true;
	}
	m_RFunc[oaddr] = "";
	return false;
}

bool TrieTree::SlowMatch_CmpCallApi(unsigned char* pSrc,qstring IATEAT)
{
	if (*pSrc != 0xFF) {
		return false;
	}
	if ((*(pSrc + 1) != 0x15) && (*(pSrc + 1) != 0x25)) {
		return false;
	}
	qstring IATCom;
	qstring EATCom;

	int EATpos = IATEAT.find("||");
	if (EATpos != -1) {            //�����Զ���EAT
		IATCom = IATEAT.substr(0, EATpos);
		EATCom = IATEAT.substr(EATpos + 2);
	}
	else
	{
		IATCom = IATEAT;
		EATCom = IATEAT.substr(IATEAT.find('.') + 1);
	}

	size_t nDllPos = IATCom.find('.');
	if (nDllPos != qstring::npos) {
		IATCom = IATCom.substr(nDllPos + 1);
	}

	ea_t oaddr = ReadUInt(pSrc + 2);
	qstring funcName = get_name(oaddr);

	if (funcName.find("__imp_") == 0) {
		funcName = funcName.substr(6);
	}

	if (!qstrcmp(funcName.c_str(), EATCom.c_str()) || !qstrcmp(funcName.c_str(), IATCom.c_str())) {
		return true;
	}
	return false;
}

TrieTreeNode::TrieTreeNode() {
	ChildNodes = new TrieTreeNode * [256];
	for (int i = 0; i < 256; i++) {
		ChildNodes[i] = NULL;
	}
	EsigText = NULL;
	FuncName = NULL;
	IsMatched = false;
}

TrieTree::TrieTree()
{
	root = new TrieTreeNode();
	root->SpecialType = NODE_NORMAL;

	//Ĭ������
	m_IsAligned = false;
	m_IsSetName = true;
	m_MatchSubName = false;
}

//ʮ����ʮ
void HexStrToBin(qstring& HexCode, unsigned char* BinCode)
{
	for (uint n = 0; n < HexCode.length() / 2; n++) {
		BinCode[n] = HexToBin(HexCode[2 * n]) * 16 + HexToBin(HexCode[2 * n + 1]);
	}
}

TrieTreeNode* TrieTree::AddNode(TrieTreeNode* p, qstring Txt) {
	uchar index = 0;
	HexStrToBin(Txt, &index);
	if (p->ChildNodes[index]) {
		return p->ChildNodes[index];
	}

	TrieTreeNode* NewNode = new TrieTreeNode(); //������еĽڵ��ж�û��,�򴴽�һ���½ڵ�
	p->ChildNodes[index] = NewNode;      //��ǰ�ڵ�������ӽڵ�

	NewNode->EsigText = new char[Txt.length() + 1]; qstrncpy(NewNode->EsigText, Txt.c_str(), MAXSTR);//��ֵEsigTxt
	MemAllocSave.push_back(NewNode->EsigText);
	NewNode->SpecialType = NODE_NORMAL;
	return NewNode;
}

TrieTreeNode* TrieTree::AddSpecialNode(TrieTreeNode* p, uint type, qstring Txt) {
	for (int i = 0; i < p->SpecialNodes.size(); i++) {		//������ǰ�ӽڵ�
		if (p->SpecialNodes[i]->SpecialType == type && Txt == p->SpecialNodes[i]->EsigText) {
			return p->SpecialNodes[i];
		}
	}
	TrieTreeNode* NewNode = new TrieTreeNode(); //������еĽڵ��ж�û��,�򴴽�һ���½ڵ�
	p->SpecialNodes.push_back(NewNode);      //��ǰ�ڵ�������ӽڵ�
	NewNode->EsigText = new char[Txt.length() + 1]; qstrncpy(NewNode->EsigText, Txt.c_str(), MAXSTR);//��ֵEsigTxt
	MemAllocSave.push_back(NewNode->EsigText);
	NewNode->SpecialType = type;
	return NewNode;
}

bool TrieTree::Insert(qstring& FuncTxt, const qstring& FuncName) {		//����һΪ�������ı���ʽ,������Ϊ����������
	TrieTreeNode* p = root;		//����ǰ�ڵ�ָ��ָ��ROOT�ڵ�

	qstring BasicTxt;
	qstring SpecialTxt;

	MemAllocSave.clear();
	for (UINT n = 0; n < FuncTxt.length(); n++) {
		char test = FuncTxt[n];
		switch (FuncTxt[n])
		{
		case '-':	//Check 1��
			if (FuncTxt[n + 1] == '-' && FuncTxt[n + 2] == '>')
			{
				BasicTxt = "E9";
				p = AddNode(p, BasicTxt);
				p = AddSpecialNode(p, NODE_LONGJMP, "");
				n = n + 2;
				continue;		//��continue�����ⲿѭ��
			}
			return false;
		case '<':
			if (FuncTxt[n + 1] == '[') {						//CALLAPI
				int post = FuncTxt.find("]>", n);
				if (post == -1) {
					return false;
				}
				BasicTxt = "FF";
				p = AddNode(p, BasicTxt);
				BasicTxt = "15";
				p = AddNode(p, BasicTxt);
				SpecialTxt = FuncTxt.substr(n + 2, post);   //�õ��ı��е�IAT����
				p = AddSpecialNode(p, NODE_CALLAPI, SpecialTxt);
				n = post + 1;
				continue;
			}
			else {											//��ͨ�ĺ���CALL
				int post = FuncTxt.find('>', n);
				if (post == -1) {
					return false;
				}
				SpecialTxt = FuncTxt.substr(n + 1, post);
				BasicTxt = "E8";
				p = AddNode(p, BasicTxt);
				p = AddSpecialNode(p, NODE_CALL, SpecialTxt);
				n = post;
				continue;
			}
		case '[':
			if (FuncTxt[n + 1] == ']' && FuncTxt[n + 2] == '>') {
				//To Do
			}
			else
			{
				int post = FuncTxt.find(']', n);
				if (post == -1) {
					return false;
				}
				BasicTxt = "FF";
				p = AddNode(p, BasicTxt);
				BasicTxt = "25";
				p = AddNode(p, BasicTxt);
				SpecialTxt = FuncTxt.substr(n + 1, post);
				p = AddSpecialNode(p, NODE_JMPAPI, SpecialTxt);
				n = post;
				continue;
			}
		case '?':
			if (FuncTxt[n + 1] == '?') {
				p = AddSpecialNode(p, NODE_ALLPASS, FuncTxt.substr(n, n + 2));	//ȫͨ���
				n = n + 1;
				continue;
			}
			else
			{
				p = AddSpecialNode(p, NODE_LEFTPASS, FuncTxt.substr(n, n + 2));	//��ͨ���
				n = n + 1;
				continue;
			}
		case '!':
		{
			int post = FuncTxt.find('!', n + 1);	//��!����һ���ַ���ʼѰ��!
			if (post == -1) {
				return false;
			}
			SpecialTxt = FuncTxt.substr(n + 1, post);
			p = AddSpecialNode(p, NODE_CONSTANT, SpecialTxt);
			n = post;	//����ǰָ��ָ���ұߵ�!��
			continue;
		}
		default:
			if (FuncTxt[n + 1] == '?') {
				p = AddSpecialNode(p, NODE_RIGHTPASS, FuncTxt.substr(n, n + 2));	//��ͨ���
				n = n + 1;
				continue;
			}
			else {
				BasicTxt = FuncTxt.substr(n, n + 2);
				p = AddNode(p, BasicTxt);
				n = n + 1;
				continue;
			}
		}
	}

	if (p->FuncName) {		//ȷ����������Ψһ�ԣ�����
		msg("Find The same Function--%s", p->FuncName);
		for (uint i = 0; i < MemAllocSave.size(); i++)
		{
			delete MemAllocSave[i];
		}
		return false;
	}

	p->FuncName = new char[FuncName.length() + 1]; qstrncpy(p->FuncName, FuncName.c_str(), MAXSTR);
	return true;
}

TrieTree::~TrieTree()
{
	TrieTreeNode* p = root;
	if (!p)
	{
		return;
	}

	qstack<TrieTreeNode*> StackNode;	//�ڵ�
	StackNode.push(p);

	while (!StackNode.empty()) {
		p = StackNode.top();
		StackNode.pop();
		//ȡ�ض�ջ���˽ڵ�
		if (p)
		{
			for (uint i = 0; i < 256; i++)
			{
				StackNode.push(p->ChildNodes[i]);
			}
			for (uint j = 0; j < p->SpecialNodes.size(); j++)
			{
				StackNode.push(p->SpecialNodes[j]);
			}
			if (p->EsigText)
			{
				delete p->EsigText;
				p->EsigText = NULL;
			}
			if (p->FuncName)
			{
				delete p->FuncName;
				p->FuncName = NULL;
			}
			if (p->ChildNodes)
			{
				delete p->ChildNodes;
				p->ChildNodes = NULL;
			}
			p->SpecialNodes.clear();
		}
		delete p;
		p = NULL;
	}
}

bool TrieTree::FastMatch(TrieTreeNode* p, unsigned char*& FuncSrc)
{
#ifdef _DEBUG
	if (p->SpecialType != NODE_NORMAL) {
		int a = 0;
	}
#endif
	switch (p->SpecialType)
	{
	case NODE_NORMAL:
	{
		return true;
	}
	case NODE_LONGJMP:
	{
		ea_t oaddr = SectionManager::VirtualAddrToLinearAddr(FuncSrc - 1 + ReadInt(FuncSrc) + 5);
		FuncSrc = SectionManager::LinearAddrToVirtualAddr(oaddr);
		return true;
	}
	case NODE_CALL:
	{
		unsigned char* pCallSrc = FuncSrc - 1 + ReadInt(FuncSrc) + 5;
		uint32 oaddr = SectionManager::VirtualAddrToLinearAddr(pCallSrc);
		if (m_RFunc[oaddr] == p->EsigText)	//�˺����Ѿ�ƥ���һ��
		{
			FuncSrc = FuncSrc + 4;
			return true;
		}
		if (!SlowMatch(SectionManager::LinearAddrToVirtualAddr(oaddr), m_subFunc[p->EsigText])) {
			return false;
		}
		m_RFunc[oaddr] = p->EsigText;
		FuncSrc = FuncSrc + 4;
		return true;
	}
	case NODE_JMPAPI:
	case NODE_CALLAPI:
	{
		if (!FastMatch_CmpApi(FuncSrc, p->EsigText)) {
			return false;
		}
		FuncSrc = FuncSrc + 4;
		return true;
	}
	case NODE_CONSTANT:
	{
		ea_t oaddr = ReadUInt(FuncSrc);
		if (m_RFunc[oaddr] == p->EsigText) {
			FuncSrc = FuncSrc + 4;
			return true;
		}
		if (!SlowMatch(SectionManager::LinearAddrToVirtualAddr(oaddr), m_subFunc[p->EsigText])) {
			return false;
		}
		m_RFunc[oaddr] = p->EsigText;
		FuncSrc = FuncSrc + 4;
		return true;
	}
	case NODE_LEFTPASS:
	{
		if ((ReadUChar(FuncSrc) & 0xF) == HexToBin(p->EsigText[1])) {
			FuncSrc = FuncSrc + 1;
			return true;
		}
		return false;
	}
	case NODE_RIGHTPASS:
	{
		if ((ReadUChar(FuncSrc) >> 4) == HexToBin(p->EsigText[0])) {
			FuncSrc = FuncSrc + 1;
			return true;
		}
		return false;
	}
	case NODE_ALLPASS:
	{
		FuncSrc = FuncSrc + 1;
		return true;
	}
	default:
		break;
	}

	return false;
}


bool TrieTree::SlowMatch(unsigned char* FuncSrc, qstring& FuncTxt)
{
	unsigned char* pSrc = FuncSrc;  //��ʼ����������ָ��
	if (FuncTxt == "")
	{
		return false;
	}

	unsigned int MaxLength = FuncTxt.length();
	unsigned int n = 0;
	while (n < MaxLength) {
		switch (FuncTxt[n]) {
		case '-':
		{
			if (FuncTxt[n + 1] == '-' && FuncTxt[n + 2] == '>') {		//����ת
				if (*pSrc != 0xE9) {
					return false;
				}
				ea_t oaddr = SectionManager::VirtualAddrToLinearAddr(pSrc + ReadInt(pSrc + 1) + 5);
				pSrc = SectionManager::LinearAddrToVirtualAddr(oaddr);
				n = n + 3;
				continue;
			}
			return false;
		}
		case '<':
		{
			if (FuncTxt[n + 1] == '[') {						//CALLAPI
				int post = FuncTxt.find("]>", n);
				if (post == -1) {
					return false;
				}
				if (!SlowMatch_CmpCallApi(pSrc, FuncTxt.substr(n + 2, post))) {
					return false;
				}
				pSrc = pSrc + 6;
				n = post + 2;
				continue;
			}
			else {
				int post = FuncTxt.find('>', n);
				if (post == -1) {
					return false;
				}
				if (SlowMatch_CmpCall(pSrc, FuncTxt.substr(n + 1, post))) {
					pSrc = pSrc + 5;
					n = post + 1;
					continue;
				}
				return false;
			}
		}
		case '[':
		{
			int post = FuncTxt.find(']', n);
			if (post == -1) {
				return false;
			}
			if (!SlowMatch_CmpCallApi(pSrc, FuncTxt.substr(n + 1, post))) {
				return false;
			}
			pSrc = pSrc + 6;
			n = post + 1;
			continue;
		}
		case '!':
		{
			int post = FuncTxt.find('!', n + 1);
			if (post == -1) {
				return false;
			}
			qstring constantName = FuncTxt.substr(n + 1, post);
			ea_t oaddr = ReadUInt(pSrc);
			if (m_RFunc[oaddr] == constantName || SlowMatch(SectionManager::LinearAddrToVirtualAddr(oaddr), m_subFunc[constantName])) {
				pSrc = pSrc + 4;
				n = post + 1;
				continue;
			}
			return false;
		}
		case '?':
		{
			if (FuncTxt[n + 1] == '?') {	                                  //ȫͨ���
				pSrc = pSrc + 1;
				n = n + 2;
				continue;
			}
			else if ((ReadUChar(pSrc) & 0xF) == HexToBin(FuncTxt[n + 1])) {   //��ͨ���
				pSrc = pSrc + 1;
				n = n + 2;
				continue;
			}
			return false;
		}
		default:
		{
			if (FuncTxt[n + 1] == '?') {                                      //��ͨ���
				if ((ReadUChar(pSrc) >> 4) == HexToBin(FuncTxt[n])) {
					pSrc = pSrc + 1;
					n = n + 2;
					continue;
				}
			}
			else{    
				unsigned char ByteCode;
				HexStrToBin(FuncTxt.substr(n, n + 2), &ByteCode);
				if (*pSrc != ByteCode) {
					return false;
				}
				pSrc = pSrc + 1;
				n = n + 2;
				continue;
			}
		}
		}
	}
	return true;
}

char* TrieTree::MatchFunc(unsigned char* FuncSrc)
{
	TrieTreeNode* p = root;		                //��ǰָ��ָ��root

	qstack<TrieTreeNode*> StackNode;	        //�ڵ�
	qstack<unsigned char*> StackFuncSrc;        //�ڵ��ַ

	StackNode.push(p);
	StackFuncSrc.push(FuncSrc);
	//����ѭ����ʼ����

	while (!StackNode.empty()) {
		p = StackNode.top();
		StackNode.pop();
		FuncSrc = StackFuncSrc.top();
		StackFuncSrc.pop();
		//ȡ�ض�ջ���˽ڵ�
		if (!FastMatch(p, FuncSrc)) {		//��鵱ǰ�ڵ�Ϸ������ȼ������ж��սڵ�
			continue;
		}
		if (p->FuncName) {
			return p->FuncName;
		}
		for (UINT i = 0; i < p->SpecialNodes.size(); i++) {
			StackNode.push(p->SpecialNodes[i]);
			StackFuncSrc.push(FuncSrc);
		}
		if (p->ChildNodes[*FuncSrc]) {
			StackNode.push(p->ChildNodes[*FuncSrc]);
			StackFuncSrc.push(FuncSrc + 1);
		}
	}

	return NULL;
}

bool TrieTree::LoadSig(const char* lpMapPath)
{
	qstring str_MapPath;
	acp_utf8(&str_MapPath, lpMapPath);
	
	FILE* hFile = fopenRB(str_MapPath.c_str());
	if (!hFile)
	{
		return false;
	}

	uint64 dwSize = qfsize(hFile);
	char* pMapBuffer = (char*)qalloc(dwSize);
	qfread(hFile, pMapBuffer, dwSize);

	qstring str_Map = pMapBuffer;

	qstring SubFunc = GetMidString(str_Map, "*****SubFunc*****\r\n", "*****SubFunc_End*****", 0);

	int pos = SubFunc.find("\r\n");     //�Ӻ���
	while (pos != -1) {
		qstring temp = SubFunc.substr(0, pos);  //�����Ӻ���
		if (temp == "")
		{
			SubFunc = SubFunc.substr(SubFunc.find("\r\n") + 2);
			pos = SubFunc.find("\r\n");
			continue;
		}
		int tempos = temp.find(':');
		if (tempos == -1) {
			break;
		}
		while (SubFunc[tempos + 1] == ':')
		{
			tempos = temp.find(':', tempos + 2);
		}
		m_subFunc[temp.substr(0, tempos)] = temp.substr(tempos + 1);
		SubFunc = SubFunc.substr(pos + 2);
		pos = SubFunc.find("\r\n");
	}

	qstring Func = GetMidString(str_Map, "***Func***\r\n", "***Func_End***", 0);

	pos = Func.find("\r\n");//�ָ��ı�
	while (pos != -1) {
		qstring temp = Func.substr(0, pos);    //ȡ�����������ı�
		if (temp == "")		//�õ�����
		{
			Func = Func.substr(Func.find("\r\n") + 2);
			pos = Func.find("\r\n");
			continue;
		}
		int tempos = temp.find(':');
		if (tempos == -1) {
			break;
		}
		while (Func[tempos + 1] == ':')
		{
			tempos = temp.find(':', tempos + 2);
		}
		if (!Insert(temp.substr(tempos + 1), temp.substr(0, tempos))) {
			msg("���뺯��ʧ��\r\n");
		}
		Func = Func.substr(pos + 2);
		pos = Func.find("\r\n");
	}

	qfree(pMapBuffer);
	qfclose(hFile);
	return true;
}

void TrieTree::Log_PrintSubFunc()
{
	std::map<qstring, qstring>::iterator it;
	for (it = m_subFunc.begin(); it != m_subFunc.end(); it++)
	{
		msg("%s----%s\r\n", it->first.c_str(), it->second.c_str());
	}
}