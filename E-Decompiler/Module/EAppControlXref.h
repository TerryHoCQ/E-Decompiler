#pragma once
#include <pro.h>
#include <kernwin.hpp>
#include <vector>

//�����Կؼ���������

class ESymbol;
struct EAppControl;

class EAppControlXref:public action_handler_t
{
	//������������
	enum eAppControlXrefType
	{
		XrefWriteProperty = 0x0,
		XrefReadProperty = 0x1,
		XrefExecute = 0x2,
	};

	struct eAppControlXrefData
	{
		eAppControlXrefType type;
		unsigned int xRefAddr;
		std::string text;
	};
public:
	EAppControlXref(ESymbol& symbol);
	//ע��Handler
	void RegisterAction(void* owner);
	//��Ӳ˵���
	void AttachToPopupMenu(TWidget* view, TPopupMenu* p);
private:
	//��ʼ��������������
	bool initXrefData(unsigned int callAddr);
	int activate(action_activation_ctx_t* ctx)override;
	action_state_t idaapi update(action_update_ctx_t* ctx) override;
	//��ȡ��д�������õ�ַ�Ŀؼ���Ϣ,����false��ʾʧ��
	bool getRWXrefAddrText(unsigned int XrefAddr, std::string& outText);
	//��ȡִ�н������õ�ַ�Ŀؼ���Ϣ,����false��ʾʧ��
	bool getExecuteXrefAddrText(unsigned int XrefAddr, std::string& outText);
	void showXrefList();
private:
	ESymbol& symbolTable;
	std::vector<eAppControlXrefData> allXrefData;
	EAppControl* currentAppControl;
	unsigned int currentAddr;
	unsigned int windowID;
	unsigned int controlID;
};