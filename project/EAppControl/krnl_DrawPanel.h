#pragma once
#include "EAppControl.h"

class krnl_DrawPanel :public EAppControl
{
protected:
	void ȡ�ؼ�Ĭ�ϸ�������(QHash<QString, QVariant>& out_data);
	void �����л��ؼ���������(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data);
	void ��ʾ�ؼ�������Ϣ(QHash<QString, QVariant>& out_data);
	qstring ȡ�¼�����(int eventIndex);
	QString ȡͼ����Դ·��();
private:
	static QStringList ȡ�߿��б�();
	static QStringList ȡ��ͼ��ʽ�б�();
	static QStringList ȡ�滭��λ�б�();
	static QStringList ȡ���������б�();
	static QStringList ȡ������ʽ�б�();
	static QStringList ȡˢ�������б�();
};


