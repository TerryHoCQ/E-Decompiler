#pragma once
#include "EAppControl.h"

class krnl_Label:public EAppControl
{
protected:
	void ȡ�ؼ�Ĭ�ϸ�������(QHash<QString, QVariant>& out_data);
	void �����л��ؼ���������(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data);
	void ��ʾ�ؼ�������Ϣ(QHash<QString, QVariant>& map_ControlData);
	qstring ȡ�¼�����(int eventIndex);
	QString ȡͼ����Դ·��();
private:
	static void ��ӽ�����ɫ�ؼ�(QString ProperyName, unsigned int ProperyValue);
private:
	static QStringList ȡ�߿��б�();
	static QStringList ȡЧ���б�();
	static QStringList ȡ��ͼ��ʽ�б�();
	static QStringList ȡ���䱳����ʽ�б�();
	static QStringList ȡ������뷽ʽ�б�();
	static QStringList ȡ������뷽ʽ�б�();
};
