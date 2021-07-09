#include "krnl_SliderBar.h"
#include "../common/public.h"

struct SliderBar_UnitData
{
	unsigned int version;
	unsigned int 边框;
	unsigned int 方向;
	unsigned int 刻度类型;
	unsigned int 单位刻度值;
	unsigned int 允许选择;
	unsigned int 首选择位置;
	unsigned int 选择长度;
	unsigned int 页改变值;
	unsigned int 行改变值;
	unsigned int 最小位置;
	unsigned int 最大位置;
	unsigned int 位置;
};

QStringList krnl_SliderBar::取边框列表()
{
	QStringList Items = {
		QStringLiteral("无边框"),
		QStringLiteral("凹入式"),
		QStringLiteral("凸出式"),
		QStringLiteral("浅凹入式"),
		QStringLiteral("镜框式"),
		QStringLiteral("单线边框式"),
	};
	return Items;
}

QStringList krnl_SliderBar::取方向列表()
{
	QStringList Items = {
		QStringLiteral("横向"),
		QStringLiteral("纵向"),
	};
	return Items;
}

QStringList krnl_SliderBar::取刻度类型列表()
{
	QStringList Items = {
		QStringLiteral("无"),
		QStringLiteral("上/左"),
		QStringLiteral("下/右"),
		QStringLiteral("双向"),
	};
	return Items;
}

void krnl_SliderBar::取控件默认附加属性(QHash<QString, QVariant>& out_data)
{
	out_data[QStringLiteral("边框")] = 0x0;
	out_data[QStringLiteral("方向")] = 0x0;
	out_data[QStringLiteral("刻度类型")] = 0x2;
	out_data[QStringLiteral("单位刻度值")] = 0x1;
	out_data[QStringLiteral("允许选择")] = 0x0;
	out_data[QStringLiteral("首选择位置")] = 0x0;
	out_data[QStringLiteral("选择长度")] = 0x0;
	out_data[QStringLiteral("页改变值")] = 0x5;
	out_data[QStringLiteral("行改变值")] = 0x1;
	out_data[QStringLiteral("最小位置")] = 1;
	out_data[QStringLiteral("最大位置")] = 10;
	out_data[QStringLiteral("位置")] = 0x1;
}

void krnl_SliderBar::反序列化控件附加属性(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data)
{
	SliderBar_UnitData tmpData;

	tmpData.version = CDR_ReadUInt(pUnitDataPtr);
	if (tmpData.version > 1) {
		return;
	}

	tmpData.边框 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.方向 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.刻度类型 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.单位刻度值 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.允许选择 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.首选择位置 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.选择长度 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.页改变值 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.行改变值 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.最小位置 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.最大位置 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.位置 = CDR_ReadUInt(pUnitDataPtr);
	
	out_data[QStringLiteral("边框")] = tmpData.边框;
	out_data[QStringLiteral("方向")] = tmpData.方向;
	out_data[QStringLiteral("刻度类型")] = tmpData.刻度类型;
	out_data[QStringLiteral("单位刻度值")] = tmpData.单位刻度值;
	out_data[QStringLiteral("允许选择")] = tmpData.允许选择;
	out_data[QStringLiteral("首选择位置")] = tmpData.首选择位置;
	out_data[QStringLiteral("选择长度")] = tmpData.选择长度;
	out_data[QStringLiteral("页改变值")] = tmpData.页改变值;
	out_data[QStringLiteral("行改变值")] = tmpData.行改变值;
	out_data[QStringLiteral("最小位置")] = tmpData.最小位置;
	out_data[QStringLiteral("最大位置")] = tmpData.最大位置;
	out_data[QStringLiteral("位置")] = tmpData.位置;
	return;
}

void krnl_SliderBar::显示控件属性信息(QHash<QString, QVariant>& map_ControlData)
{
	EAppControl::添加文本控件(QStringLiteral("名称"), map_ControlData[QStringLiteral("名称")].toString());
	EAppControl::添加文本控件(QStringLiteral("左边"), map_ControlData[QStringLiteral("左边")].toString());
	EAppControl::添加文本控件(QStringLiteral("顶边"), map_ControlData[QStringLiteral("顶边")].toString());
	EAppControl::添加文本控件(QStringLiteral("宽度"), map_ControlData[QStringLiteral("宽度")].toString());
	EAppControl::添加文本控件(QStringLiteral("高度"), map_ControlData[QStringLiteral("高度")].toString());
	EAppControl::添加文本控件(QStringLiteral("标记"), map_ControlData[QStringLiteral("标记")].toString());
	EAppControl::添加布尔控件(QStringLiteral("可视"), map_ControlData[QStringLiteral("可视")].toBool());
	EAppControl::添加布尔控件(QStringLiteral("禁止"), map_ControlData[QStringLiteral("禁止")].toBool());
	EAppControl::添加鼠标控件(map_ControlData[QStringLiteral("鼠标指针")].toUInt());
	EAppControl::添加布尔控件(QStringLiteral("可停留焦点"), map_ControlData[QStringLiteral("可停留焦点")].toBool());
	EAppControl::添加文本控件(QStringLiteral("    停留顺序"), map_ControlData[QStringLiteral("停留顺序")].toString());

	EAppControl::添加列表控件(QStringLiteral("边框"), krnl_SliderBar::取边框列表(), map_ControlData[QStringLiteral("边框")].toUInt());
	EAppControl::添加列表控件(QStringLiteral("方向"), krnl_SliderBar::取方向列表(), map_ControlData[QStringLiteral("方向")].toUInt());
	EAppControl::添加列表控件(QStringLiteral("刻度类型"), krnl_SliderBar::取刻度类型列表(), map_ControlData[QStringLiteral("刻度类型")].toUInt());
	EAppControl::添加文本控件(QStringLiteral("    单位刻度值"), map_ControlData[QStringLiteral("单位刻度值")].toString());
	EAppControl::添加布尔控件(QStringLiteral("允许选择"), map_ControlData[QStringLiteral("允许选择")].toBool());
	EAppControl::添加文本控件(QStringLiteral("    首选择位置"), map_ControlData[QStringLiteral("首选择位置")].toString());
	EAppControl::添加文本控件(QStringLiteral("    选择长度"), map_ControlData[QStringLiteral("选择长度")].toString());
	EAppControl::添加文本控件(QStringLiteral("页改变值"), map_ControlData[QStringLiteral("页改变值")].toString());
	EAppControl::添加文本控件(QStringLiteral("行改变值"), map_ControlData[QStringLiteral("行改变值")].toString());
	EAppControl::添加文本控件(QStringLiteral("最小位置"), map_ControlData[QStringLiteral("最小位置")].toString());
	EAppControl::添加文本控件(QStringLiteral("最大位置"), map_ControlData[QStringLiteral("最大位置")].toString());
	EAppControl::添加文本控件(QStringLiteral("位置"), map_ControlData[QStringLiteral("位置")].toString());
}

qstring krnl_SliderBar::取事件名称(int eventIndex)
{
	qstring ret;
	switch (eventIndex)
	{
	case 0:
		ret = "创建完毕";
		break;
	case 1:
		ret = "可否被关闭";
		break;
	case 2:
		ret = "将被销毁";
		break;
	case 3:
		ret = "位置被改变";
		break;
	case 4:
		ret = "尺寸被改变";
		break;
	case 5:
		ret = "被激活";
		break;
	case 6:
		ret = "被取消激活";
		break;
	case 7:
		ret = "空闲";
		break;
	case 8:
		ret = "首次激活";
		break;
	case 9:
		ret = "托盘事件";
		break;
	case 10:
		ret = "被显示";
		break;
	case 11:
		ret = "被隐藏";
		break;
	case 12:
		ret = "窗口可否被关闭";
		break;
	case -1:
		ret = "鼠标左键被按下";
		break;
	case -2:
		ret = "鼠标左键被放开";
		break;
	case -3:
		ret = "被双击";
		break;
	case -4:
		ret = "鼠标右键被按下";
		break;
	case -5:
		ret = "鼠标右键被放开";
		break;
	case -6:
		ret = "鼠标位置被移动";
		break;
	case -7:
		ret = "获得焦点";
		break;
	case -8:
		ret = "失去焦点";
		break;
	case -9:
		ret = "按下某键";
		break;
	case -10:
		ret = "放开某键";
		break;
	case -11:
		ret = "字符输入";
		break;
	case -12:
		ret = "滚轮被滚动";
		break;
	default:
		ret = "未知事件";
		break;
	}

	return ret;
}

QString krnl_SliderBar::取图标资源路径()
{
	return QStringLiteral(":/ICO/ICO/滑块条.ico");
}
