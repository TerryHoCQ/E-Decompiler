#pragma once
#include <pro.h>
#include "EAppControl.h"

class krnl_EditBox :public EAppControl
{
protected:
	void ȡ�ؼ�Ĭ�ϸ�������(QHash<QString, QVariant>& out_data);
	void �����л��ؼ���������(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data);
	void ��ʾ�ؼ�������Ϣ(QHash<QString, QVariant>& out_data);
	qstring ȡ�¼�����(int eventIndex);
private:
	QStringList ȡ�߿��б�();
	QStringList ȡ�������б�();
	QStringList ȡ���뷽ʽ�б�();
	QStringList ȡ���뷽ʽ�б�();
	QStringList ȡת����ʽ�б�();
	QStringList ȡ��������ʽ�б�();
};