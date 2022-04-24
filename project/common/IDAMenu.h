#pragma once
#include <pro.h>
#include <kernwin.hpp>

class IDAMenu :public action_handler_t
{
public:
	static IDAMenu* CreateMenu(const char* menuPath, int (*callback)(), const char* shortcut = nullptr, const char* tooltip = nullptr, int icon = -1)
	{
		return new IDAMenu(menuPath, callback, shortcut, tooltip, icon);
	}
	void DestroyMenu()
	{
		delete this;
	}
private:
	IDAMenu(const char* menuPath, int (*callback)(), const char* shortcut, const char* tooltip, int icon);
	~IDAMenu();
	int activate(action_activation_ctx_t* ctx);
	action_state_t update(action_update_ctx_t* ctx);
private:
	int (*m_callback)();
	//�������ڲ�����
	qstring m_actionName;
	//�����ı�ǩ����
	qstring m_actionLabel;

	//�˵����ڲ�����
	qstring m_menuName;
	//�˵��ı�ǩ����
	qstring m_menuLabel;
};