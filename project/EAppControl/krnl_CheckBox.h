#pragma once
#include "EAppControl.h"

class krnl_CheckBox:public EAppControl
{
protected:
	void ȡ�ؼ�Ĭ�ϸ�������(QHash<QString, QVariant>& out_data);
	void �����л��ؼ���������(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data);
	void ��ʾ�ؼ�������Ϣ(QHash<QString, QVariant>& out_data);
	qstring ȡ�¼�����(int eventIndex);
	QString ȡͼ����Դ·��();
private:
	static QStringList ȡ������뷽ʽ�б�();
	static QStringList ȡ������뷽ʽ�б�();
};