#include "krnl_Tab.h"
#include "../common/public.h"

struct Tab_UnitData
{
	unsigned int version;
	unsigned int 表头方向;
	unsigned int 允许多行表头;
	unsigned int 现行子夹;
	unsigned int 隐藏自身;
	unsigned int 是否填充背景;
	unsigned int 背景颜色;
	qvector<unsigned char> 字体;
	qvector<qstring> 子夹管理;
};

QStringList krnl_Tab::QStringListFromVec(qvector<qstring>& vec_str)
{
	QStringList ret;
	for (unsigned int n = 0; n < vec_str.size(); ++n) {
		ret.push_back(QString::fromLocal8Bit(vec_str[n].c_str()));
	}
	return ret;
}

QStringList krnl_Tab::取表头方向列表()
{
	QStringList Items = {
		QStringLiteral("上"),
		QStringLiteral("下"),
		QStringLiteral("左"),
		QStringLiteral("右"),
	};
	return Items;
}

QString krnl_Tab::取图标资源路径()
{
	return QStringLiteral(":/ICO/ICO/选择夹.ico");
}

void krnl_Tab::取控件默认附加属性(QHash<QString, QVariant>& out_data)
{
	out_data[QStringLiteral("表头方向")] = 0x0;
	out_data[QStringLiteral("允许多行表头")] = 0x0;
	out_data[QStringLiteral("隐藏自身")] = 0x0;
	out_data[QStringLiteral("是否填充背景")] = 0x1;
	out_data[QStringLiteral("背景颜色")] = 0xFF000000;
}

void krnl_Tab::反序列化控件附加属性(unsigned char* pUnitDataPtr, QHash<QString, QVariant>& out_data)
{
	Tab_UnitData tmpData = {};

	tmpData.version = CDR_ReadUInt(pUnitDataPtr);
	if (tmpData.version > 3) {
		return;
	}
	
	tmpData.表头方向 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.允许多行表头 = CDR_ReadUInt(pUnitDataPtr);
	tmpData.现行子夹 = CDR_ReadUInt(pUnitDataPtr);

	if (tmpData.version >= 2) {
		tmpData.隐藏自身 = CDR_ReadUInt(pUnitDataPtr);
	}

	if (tmpData.version < 3) {
		tmpData.是否填充背景 = 0x0;
	}
	else {
		tmpData.是否填充背景 = CDR_ReadUInt(pUnitDataPtr);
		tmpData.背景颜色 = CDR_ReadUInt(pUnitDataPtr);
	}
	tmpData.字体 = CDR_ReadCFreqMem(pUnitDataPtr);
	tmpData.子夹管理 = CDR_ReadVecString(pUnitDataPtr);

	out_data[QStringLiteral("version")] = tmpData.version;
	out_data[QStringLiteral("表头方向")] = tmpData.表头方向;
	out_data[QStringLiteral("允许多行表头")] = tmpData.允许多行表头;
	out_data[QStringLiteral("现行子夹")] = tmpData.现行子夹;
	out_data[QStringLiteral("隐藏自身")] = tmpData.隐藏自身;
	out_data[QStringLiteral("隐藏自身")] = tmpData.隐藏自身;
	out_data[QStringLiteral("是否填充背景")] = tmpData.是否填充背景;
	out_data[QStringLiteral("背景颜色")] = tmpData.背景颜色;

	if (tmpData.字体.size()) {
		out_data[QStringLiteral("字体")] = QByteArray((char*)&tmpData.字体[0], tmpData.字体.size());
	}
	out_data[QStringLiteral("子夹管理")] = QStringListFromVec(tmpData.子夹管理);
	return;
}

void krnl_Tab::显示控件属性信息(QHash<QString, QVariant>& map_ControlData)
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
	EAppControl::添加列表控件(QStringLiteral("表头方向"), krnl_Tab::取表头方向列表(), map_ControlData[QStringLiteral("表头方向")].toUInt());
	EAppControl::添加布尔控件(QStringLiteral("允许多行表头"), map_ControlData[QStringLiteral("允许多行表头")].toBool());
	EAppControl::添加字体控件(QStringLiteral("字体"), map_ControlData[QStringLiteral("字体")].toByteArray());
	EAppControl::添加列表控件(QStringLiteral("子夹管理"), map_ControlData[QStringLiteral("子夹管理")].toStringList(), 0);
	EAppControl::添加文本控件(QStringLiteral("现行子夹"), QStringLiteral("** 设计时不可用 **"));
	EAppControl::添加布尔控件(QStringLiteral("隐藏自身"), map_ControlData[QStringLiteral("隐藏自身")].toBool());
	EAppControl::添加布尔控件(QStringLiteral("    是否填充背景"), map_ControlData[QStringLiteral("是否填充背景")].toBool());
	EAppControl::添加颜色控件(QStringLiteral("    背景颜色"), map_ControlData[QStringLiteral("背景颜色")].toUInt());
	return;
}

qstring krnl_Tab::取事件名称(int eventIndex)
{
	qstring ret;
	switch (eventIndex)
	{
	case 0:
		ret = "被单击";
		break;
	case 1:
		ret = "将改变子夹";
		break;
	case 2:
		ret = "子夹被改变";
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
	case -12:
		ret = "滚轮被滚动";
		break;
	default:
		ret = "未知事件";
		break;
	}
	return ret;
}