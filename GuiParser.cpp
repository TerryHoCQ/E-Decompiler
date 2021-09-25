#include "GuiParser.h"
#include <bytes.hpp>
#include <kernwin.hpp>
#include <name.hpp>
#include "EDecompiler.h"
#include "ControlInfoWidget.h"
#include "common/public.h"
#include <QMap>
#include "EAppControl/EAppControlFactory.h"

qvector<GuiParser::mid_GuiInfo> mVec_GuiInfo;               //�ؼ���Ϣ
ea_t m_UserCodeStartAddr = 0;
unsigned int m_EventSum = 0;
ControlInfoWidget* GuiParser::g_ControlInfoWindow = nullptr;

//����,���ݿؼ�IDֱ�Ӷ�λ���ؼ�����
QMap<unsigned int, GuiParser::ControlIndex> mMap_ControlIndex;
//����,���ݿؼ�����ID���ٶ�λ���ؼ�����
QMap<unsigned int, ControlType_t> mMap_ControlTypeIndex;

unsigned int krnln_GetIDSubType(unsigned int ID)
{
	return ID & 0xF0000000;
}

unsigned int krnln_GetIDGroupType(unsigned int ID)
{
	return ID & 0xF000000;
}

bool krnln_IsMenuItemID(unsigned int ID)
{
	return krnln_GetIDGroupType(ID) == 0x6000000 && krnln_GetIDSubType(ID) == 0x20000000;
}

unsigned int GuiParser::GetEventCount()
{
	return m_EventSum;
}

void GuiParser::InitUserCodeStartAddr(ea_t addr)
{
	m_UserCodeStartAddr = addr;
}

void GuiParser::ClearControlTypeMap()
{
	mMap_ControlTypeIndex.clear();
}

void GuiParser::AddControlType(unsigned int controlTypeId, ControlType_t type)
{
	mMap_ControlTypeIndex[controlTypeId] = type;
}

bool GuiParser::GetControlInfo(unsigned int controlId, mid_ControlInfo& out_ControlInfo)
{
	QMap<unsigned int, ControlIndex>::iterator it = mMap_ControlIndex.find(controlId);
	if (it != mMap_ControlIndex.end()) {
		out_ControlInfo = mVec_GuiInfo[it->nWindowIndex].mVec_ControlInfo[it->nControlIndex];
		return true;
	}
	return false;
}

ControlType_t GuiParser::GetControlType(unsigned int controlTypeId)
{
	QMap<unsigned int, ControlType_t>::iterator it = mMap_ControlTypeIndex.find(controlTypeId);
	if (it != mMap_ControlTypeIndex.end()) {
		return *it;
	}
	return UnknownControl;
}

int GuiParser::MenuHandle_ShowEventInfo()
{
	struct eventInfo
	{
		ea_t EventAddr;
		qstring ControlName;
		qstring EventName;
	};

	struct chooser_EventInfo :public chooser_multi_t
	{
	public:
		qvector<eventInfo> vec_EventInfo;
	protected:
		const int widths_[3] = { 10,10,50 };
		const char* header_[3] = { "Address","ControlType","EventName" };
	public:
		chooser_EventInfo(const char* title) :chooser_multi_t(0, qnumber(widths_), widths_, header_, title) {}
	private:
		~chooser_EventInfo() {}
		const void* get_obj_id(size_t* len) const
		{
			*len = strlen(title);
			return title;
		}
		size_t idaapi get_count(void) const
		{
			return vec_EventInfo.size();
		}
		cbres_t idaapi enter(sizevec_t* sel)
		{
			if (sel->size()) {
				jumpto(vec_EventInfo[sel->at(0)].EventAddr);
			}
			return cbres_t();
		}
		void idaapi get_row(qstrvec_t* cols_, int* icon_, chooser_item_attrs_t* attrs, size_t n) const
		{
			qstrvec_t& cols = *cols_;
			cols[0].sprnt("%08a", vec_EventInfo[n].EventAddr);
			acp_utf8(&cols[1], vec_EventInfo[n].ControlName.c_str());
			acp_utf8(&cols[2], vec_EventInfo[n].EventName.c_str());
		}
	};

	qstring title = getUTF8String("�ؼ��¼���Ϣ");
	chooser_EventInfo* pEventWindow = new chooser_EventInfo(title.c_str());
	for (unsigned int nWindowIndex = 0; nWindowIndex < mVec_GuiInfo.size(); ++nWindowIndex) {
		for (unsigned int nControlIndex = 0; nControlIndex < mVec_GuiInfo[nWindowIndex].mVec_ControlInfo.size(); ++nControlIndex) {
			ControlType_t type = GuiParser::GetControlType(mVec_GuiInfo[nWindowIndex].mVec_ControlInfo[nControlIndex].m_controlTypeId);
			EAppControl* pEAppControl = EAppControlFactory::getEAppControl(type);
			if (pEAppControl) {
				for (unsigned int nEventIndex = 0; nEventIndex < mVec_GuiInfo[nWindowIndex].mVec_ControlInfo[nControlIndex].mVec_eventInfo.size(); ++nEventIndex) {
					eventInfo eEventInfo;
					eEventInfo.EventAddr = mVec_GuiInfo[nWindowIndex].mVec_ControlInfo[nControlIndex].mVec_eventInfo[nEventIndex].m_EventAddr;
					eEventInfo.ControlName = mVec_GuiInfo[nWindowIndex].mVec_ControlInfo[nControlIndex].m_controlTypeName;
					unsigned int index = mVec_GuiInfo[nWindowIndex].mVec_ControlInfo[nControlIndex].mVec_eventInfo[nEventIndex].m_nEventIndex;
					eEventInfo.EventName.sprnt("_%s_%s", mVec_GuiInfo[nWindowIndex].mVec_ControlInfo[nControlIndex].m_controlName.c_str(), pEAppControl->ȡ�¼�����(index).c_str());
					qstring utf8Name;
					acp_utf8(&utf8Name, eEventInfo.EventName.c_str());
					set_name(eEventInfo.EventAddr, utf8Name.c_str(), SN_NOWARN);
					pEventWindow->vec_EventInfo.push_back(eEventInfo);
				}
			}
		}
	}

	pEventWindow->choose();
	return 0;
}

int GuiParser::MenuHandle_ShowGuiInfo()
{
	TWidget* widget = find_widget(getUTF8String("���ڿؼ���Ϣ").c_str());

	if (widget == nullptr) {
		g_ControlInfoWindow = new ControlInfoWidget();
		widget = (TWidget*)g_ControlInfoWindow;

		g_ControlInfoWindow->ui.treeWidget->setHeaderLabel(QStringLiteral("�����Դ���"));
		for (unsigned int nWindowIndex = 0; nWindowIndex < mVec_GuiInfo.size(); ++nWindowIndex) {
			QTreeWidgetItem* pWindowItem = new QTreeWidgetItem(g_ControlInfoWindow->ui.treeWidget);
			pWindowItem->setData(0, Qt::UserRole, mVec_GuiInfo[nWindowIndex].m_windowId);
			pWindowItem->setText(0, QString::asprintf("0x%08X", mVec_GuiInfo[nWindowIndex].m_windowId));
			qvector<mid_ControlInfo>& vec_ControlInfo = mVec_GuiInfo[nWindowIndex].mVec_ControlInfo;
			for (unsigned int nControlIndex = 0; nControlIndex < vec_ControlInfo.size(); ++nControlIndex) {
				QTreeWidgetItem* pControlItem = new QTreeWidgetItem(pWindowItem);
				EAppControl* pControl= EAppControlFactory::getEAppControl(GuiParser::GetControlType(vec_ControlInfo[nControlIndex].m_controlTypeId));
				if (pControl) {
					pControlItem->setIcon(0, QIcon(pControl->ȡͼ����Դ·��()));
				}
				pControlItem->setData(0, Qt::UserRole, vec_ControlInfo[nControlIndex].m_controlId);
				pControlItem->setText(0, QString::asprintf("0x%08X", vec_ControlInfo[nControlIndex].m_controlId));
			}
		}
		display_widget(widget, WOPN_DP_TAB | WOPN_RESTORE);
	}
	else {
		activate_widget(widget, true);
	}
	return 0;
}

void GuiParser::ParseControlBasciProperty(unsigned char* lpControlInfo, GuiParser::mid_ControlInfo& out_Property)
{
	//�����ַ���1?
	ReadStr(lpControlInfo);
	lpControlInfo += qstrlen(lpControlInfo) + 1;

	//�洢����?
	ReadUInt(lpControlInfo);
	lpControlInfo += 4;

	unsigned int m_left = ReadUInt(lpControlInfo);
	lpControlInfo += 4;

	unsigned int m_top = ReadUInt(lpControlInfo);
	lpControlInfo += 4;

	unsigned int m_width = ReadUInt(lpControlInfo);
	lpControlInfo += 4;

	unsigned int m_height = ReadUInt(lpControlInfo);
	lpControlInfo += 4;

	//ֵΪ0,�����洢LoadCursorA���صľ��ֵ��
	unsigned int hCURSOR = ReadUInt(lpControlInfo);
	lpControlInfo += 4;

	//���ؼ�ID
	unsigned int fatherControlId = ReadUInt(lpControlInfo);
	lpControlInfo += 4;

	//�ӿؼ���Ŀ
	unsigned int childControlCount = ReadUInt(lpControlInfo);
	lpControlInfo += 4;

	for (unsigned int n = 0; n < childControlCount; ++n) {
		unsigned int tmpChildControlId = ReadUInt(lpControlInfo);
		lpControlInfo += 4;
		//out_Property.mVec_childControl.push_back(tmpChildControlId);
	}

	//δ֪ƫ��
	unsigned int offset2 = ReadUInt(lpControlInfo);
	lpControlInfo += offset2 + 4;

	//���
	qstring m_tag = ReadStr(lpControlInfo);
	lpControlInfo += qstrlen(lpControlInfo) + 1;

	//δ֪��ֵ
	lpControlInfo += 12;

	int dwEventCount = ReadInt(lpControlInfo);
	lpControlInfo += 4;
	m_EventSum += dwEventCount;
	for (int nIndexEvent = 0; nIndexEvent < dwEventCount; ++nIndexEvent) {
		mid_EventInfo tmpEvent;
		tmpEvent.m_nEventIndex = ReadInt(lpControlInfo);
		lpControlInfo += 4;
		tmpEvent.m_EventAddr = ReadUInt(lpControlInfo) + m_UserCodeStartAddr;
		lpControlInfo += 4;
		out_Property.mVec_eventInfo.push_back(tmpEvent);
	}
	return;
}



bool GuiParser::ParseGUIResource(ea_t lpGUIStart, uint32 infoSize)
{
	m_EventSum = 0;
	mVec_GuiInfo.clear();
	mMap_ControlIndex.clear();

	qvector<unsigned char> tmpGuiBuf;
	tmpGuiBuf.resize(infoSize);
	get_bytes(&tmpGuiBuf[0], infoSize, lpGUIStart);

	//��ǰ������ַ
	unsigned char* lpCurrentParseAddr = &tmpGuiBuf[0];

	qvector<uint32> vec_WindowId;
	uint32 dwTotalWindowCount = ReadUInt(&tmpGuiBuf[0]) >> 3;
	lpCurrentParseAddr += 4;

	for (unsigned int n = 0; n < dwTotalWindowCount; ++n) {
		vec_WindowId.push_back(ReadUInt(lpCurrentParseAddr));
		lpCurrentParseAddr += 4;
	}

	//����������ֵ?
	for (unsigned int n = 0; n < dwTotalWindowCount; ++n) {
		//uint32 unknowId = ReadUInt(lpCurrentParseAddr);
		lpCurrentParseAddr += 4;
	}

	for (unsigned int nIndexWindow = 0; nIndexWindow < dwTotalWindowCount; ++nIndexWindow) {
		unsigned char* lpWindowInfo = lpCurrentParseAddr;

		mid_GuiInfo eGuiInfo;
		eGuiInfo.m_windowId = vec_WindowId[nIndexWindow];

		//��ʱδ֪
		uint32 unKnownFieldA = ReadUInt(lpWindowInfo);
		lpWindowInfo += 4;
		uint32 unKnownFieldB = ReadUInt(lpWindowInfo);
		lpWindowInfo += 4;

		//��������������CString,��Ϊ��
		lpWindowInfo += 8;

		//���������еĿؼ��ܸ���
		uint32 dwTotalControlCount = ReadUInt(lpWindowInfo);
		lpWindowInfo += 4;

		//���������еĿؼ���ռ�ô�С
		uint32 dwTotalControlSize = ReadUInt(lpWindowInfo);
		lpWindowInfo += 4;

		//��ʼ�����ؼ�
		unsigned char* lpControlArray = lpWindowInfo;
		{
			//�����ؼ�ID,����0x160612BC
			qvector<uint32> vec_ControlId;
			for (unsigned int j = 0; j < dwTotalControlCount; ++j) {
				vec_ControlId.push_back(ReadUInt(lpControlArray));
				lpControlArray += 4;
			}

			//�����ؼ�ƫ��
			qvector<uint32> vec_ControlOffset;
			for (unsigned int j = 0; j < dwTotalControlCount; ++j) {
				vec_ControlOffset.push_back(ReadUInt(lpControlArray));
				lpControlArray += 4;
			}

			//�����ؼ�����
			for (unsigned int nIndexControl = 0; nIndexControl < dwTotalControlCount; ++nIndexControl) {
				unsigned char* lpControlInfo = lpControlArray + vec_ControlOffset[nIndexControl];

				mid_ControlInfo eControlInfo;

				//�ؼ�ռ�õĴ�С
				int32 dwControlSize = ReadInt(lpControlInfo);
				lpControlInfo += 4;

				eControlInfo.m_propertyAddr = lpGUIStart + (lpControlInfo - &tmpGuiBuf[0]);
				eControlInfo.m_propertySize = dwControlSize;

				//�ؼ�����ID
				uint32 dwControlTypeId = ReadUInt(lpControlInfo);
				lpControlInfo += 4;

				//�̶���20�����ֽ�,����ʹ��?
				lpControlInfo += 20;

				if (dwControlTypeId == 0x10001) {
					eControlInfo.m_controlName = ReadStr(lpControlInfo);
					lpControlInfo += qstrlen(lpControlInfo) + 1;
					if (eControlInfo.m_controlName.empty()) {
						eControlInfo.m_controlName.sprnt("����0x%08X", eGuiInfo.m_windowId);
					}

					//����������
					ParseControlBasciProperty(lpControlInfo, eControlInfo);
				}
				else if (krnln_IsMenuItemID(vec_ControlId[nIndexControl])) {
					lpControlInfo += 14;
					eControlInfo.m_controlName = ReadStr(lpControlInfo);
				}
				else {
					eControlInfo.m_controlName = ReadStr(lpControlInfo);
					lpControlInfo += qstrlen(lpControlInfo) + 1;

					ParseControlBasciProperty(lpControlInfo, eControlInfo);
				}

				ControlIndex eControlIndex;
				eControlIndex.nWindowIndex = nIndexWindow;
				eControlIndex.nControlIndex = nIndexControl;
				mMap_ControlIndex[vec_ControlId[nIndexControl]] = eControlIndex;

				eControlInfo.m_controlId = vec_ControlId[nIndexControl];
				eControlInfo.m_controlTypeId = dwControlTypeId;
				eControlInfo.m_controlTypeName = EDecompilerEngine::GetControlTypeName(dwControlTypeId);
				eGuiInfo.mVec_ControlInfo.push_back(eControlInfo);
			}
		}

		mVec_GuiInfo.push_back(eGuiInfo);
		lpCurrentParseAddr = lpWindowInfo + dwTotalControlSize;
	}

	return true;
}