#include "EAppControlFactory.h"
#include "krnl_window.h"
#include "krnl_EditBox.h"
#include "krnl_Label.h"
#include "krnl_Button.h"
#include "krnl_Timer.h"
#include "krnl_PicBox.h"
#include "krnl_ShapeBox.h"
#include "krnl_DrawPanel.h"
#include "krnl_GroupBox.h"
#include "krnl_CheckBox.h"
#include "krnl_RadioBox.h"
#include "krnl_ComboBox.h"
#include "krnl_ListBox.h"
#include "krnl_ChkListBox.h"
#include "krnl_HScrollBar.h"
#include "krnl_VScrollBar.h"

class krnl_window gkrnl_window;
class krnl_EditBox gkrnl_EditBox;
class krnl_PicBox gkrnl_PicBox;
class krnl_Label gkrnl_Label;
class krnl_Button gkrnl_Button;
class krnl_Timer gkrnl_Timer;
class krnl_ShapeBox gkrnl_ShapeBox;
class krnl_DrawPanel gkrnl_DrawPanel;
class krnl_GroupBox gkrnl_GroupBox;
class krnl_CheckBox gkrnl_CheckBox;
class krnl_RadioBox gkrnl_RadioBox;
class krnl_ComboBox gkrnl_ComboBox;
class krnl_ListBox gkrnl_ListBox;
class krnl_ChkListBox gkrnl_ChkListBox;
class krnl_HScrollBar gkrnl_HScrollBar;
class krnl_VScrollBar gkrnl_VScrollBar;

QHash<ControlType_t, EAppControl*> g_classMap = {
	{krnl_window, &gkrnl_window},
	{krnl_EditBox,&gkrnl_EditBox},
	{krnl_PicBox,&gkrnl_PicBox},
	{krnl_Label,&gkrnl_Label},
	{krnl_Button,&gkrnl_Button},
	{krnl_Timer,&gkrnl_Timer},
	{krnl_ShapeBox,&gkrnl_ShapeBox},
	{krnl_DrawPanel,&gkrnl_DrawPanel},
	{krnl_GroupBox,&gkrnl_GroupBox},
	{krnl_CheckBox,&gkrnl_CheckBox},
	{krnl_RadioBox,&gkrnl_RadioBox},
	{krnl_ComboBox,&gkrnl_ComboBox},
	{krnl_ListBox,&gkrnl_ListBox},
	{krnl_ChkListBox,&gkrnl_ChkListBox},
	{krnl_HScrollBar,&gkrnl_HScrollBar},
	{krnl_VScrollBar,&gkrnl_VScrollBar}
};

EAppControl* EAppControlFactory::getEAppControl(ControlType_t type)
{
	EAppControl* ret = nullptr;
	return g_classMap[type];
}