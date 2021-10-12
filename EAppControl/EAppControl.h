#pragma once
#include <pro.h>
#include <QVariant>
#include "..\EObject_Include.h"

#define COLUMN_PropertyName  0
#define COLUMN_PropertyValue 1

class ControlInfoWidget;
class EAppControl
{
public:
	//��ȡ�ؼ��ĸ��ӵ�Ԫ����
	static unsigned char* GetUnitDataPtr(unsigned char* propertyAddr);
	//����ÿ���ؼ����еĻ�������
	static void �����ؼ���������(unsigned char* lpControlInfo, QHash<QString, QVariant>& out_data);

	static void ��ʾ�ؼ���Ϣ(ControlType_t type, unsigned int propertyAddr, int propertySize);
	static void ����ı��ؼ�(QString PropertyName, QString PropertyValue);
	static void ��Ӳ����ؼ�(QString PropertyName, bool ProperyValue);
	static void ����б�ؼ�(QString PropertyName, QStringList& PropertyList, unsigned int PropertyValue);
	static void ������ؼ�(unsigned int ProperyValue);
	static void ���ͼƬ�ؼ�(QString PropertyName, QByteArray& PropertyValue);
	static void �����ɫ�ؼ�(QString PropertyName, unsigned int PropertyValue);
	static void �������ؼ�(QString PropertyName, QByteArray& PropertyValue);
	static void �����Ч�ؼ�(QString PropertyName, QString PropertyValue);

	static void ��ӵ�ɫ�ؼ�(QString propertyName, unsigned int ProperyValue);
public:
	virtual void ȡ�ؼ�Ĭ�ϸ�������(QHash<QString, QVariant>& out_data) = 0;
	virtual void �����л��ؼ���������(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data) = 0;
	virtual void ��ʾ�ؼ�������Ϣ(QHash<QString, QVariant>& out_data) = 0;
	virtual qstring ȡ�¼�����(int eventIndex) = 0;
	virtual QString ȡͼ����Դ·��();
};