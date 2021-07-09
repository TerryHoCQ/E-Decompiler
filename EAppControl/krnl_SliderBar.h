#pragma once
#include "EAppControl.h"

class krnl_SliderBar:public EAppControl
{
protected:
	void 取控件默认附加属性(QHash<QString, QVariant>& out_data);
	void 反序列化控件附加属性(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data);
	void 显示控件属性信息(QHash<QString, QVariant>& out_data);
	qstring 取事件名称(int eventIndex);
	QString 取图标资源路径();
private:
	QStringList 取边框列表();
	QStringList 取方向列表();
	QStringList 取刻度类型列表();
};