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
	//获取控件的附加单元数据
	static unsigned char* GetUnitDataPtr(unsigned char* propertyAddr);
	//解析每个控件都有的基础属性
	static void 解析控件基础属性(unsigned char* lpControlInfo, QHash<QString, QVariant>& out_data);

	static void 显示控件信息(ControlType_t type, unsigned int propertyAddr, int propertySize);
	static void 添加文本控件(QString PropertyName, QString PropertyValue);
	static void 添加布尔控件(QString PropertyName, bool ProperyValue);
	static void 添加列表控件(QString PropertyName, QStringList& PropertyList, unsigned int PropertyValue);
	static void 添加鼠标控件(unsigned int ProperyValue);
	static void 添加图片控件(QString PropertyName, QByteArray& PropertyValue);
	static void 添加颜色控件(QString PropertyName, unsigned int PropertyValue);
	static void 添加字体控件(QString PropertyName, QByteArray& PropertyValue);
	static void 添加无效控件(QString PropertyName, QString PropertyValue);

	static void 添加底色控件(QString propertyName, unsigned int ProperyValue);
public:
	virtual void 取控件默认附加属性(QHash<QString, QVariant>& out_data) = 0;
	virtual void 反序列化控件附加属性(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data) = 0;
	virtual void 显示控件属性信息(QHash<QString, QVariant>& out_data) = 0;
	virtual qstring 取事件名称(int eventIndex) = 0;
	virtual QString 取图标资源路径();
};