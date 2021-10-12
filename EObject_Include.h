#pragma once

#pragma pack(push,1)

// 用作定义窗口单元属性
struct UNIT_PROPERTY
{
	unsigned int m_lpszName;      //属性名称
	unsigned int m_lpszEGName;    //英文名称
	unsigned int m_lpszExplain;   //属性解释
	short  m_shtType;             //属性的数据类型
	unsigned short m_wState;      //属性的特殊标记
	unsigned int m_lpszzPickStr;  //备选文本
};

//库定义数据类型结构
struct LIB_DATA_TYPE_INFO   
{
	unsigned int m_lpszName;     //名称
	unsigned int m_lpszEGName;   //英文名称,可为空
	unsigned int m_szExplain;    //详细解释,可为空
	int  m_nCmdCount;    //本数据类型成员方法的数目(可为0)
	unsigned int m_lpnCmdsIndex; //指向所有成员方法命令在支持库命令表中的索引值指针,编译后数据被抹除
	unsigned int m_dwState;      //数据类型的特殊属性

	 ////////////////////////////////////////////
	// 以下成员只有在为窗口单元、菜单时才有效。

	unsigned int m_dwUnitBmpID;     //指定在支持库中的单元图像资源ID
	int  m_nEventCount;     //本单元的事件数目
	unsigned int m_lpEventBegin;    //指向单元的所有事件的指针,EVENT_INFO,编译后数据被抹除
	int m_nPropertyCount;   //本单元的属性数目
	unsigned int m_lpPropertyBegin; //指向单元的所有属性的指针,UNIT_PROPERTY

	unsigned int m_lpfnGetInterface; //用作提供本窗口单元的所有接口。

	////////////////////////////////////////////
	// 以下成员只有在不为窗口单元、菜单时才有效。

	int m_nElementCount;    //本数据类型中子成员的数目(可为0)
	unsigned int m_lpElementBegin;   //指向子成员数组的首地址,LIB_DATA_TYPE_ELEMENT
};

struct LIB_INFO
{
	unsigned int m_dwLibFormatVer;    //支持库格式版本号,应该为0x1312D65
	unsigned int m_lpGuid;            //对应支持库的GUID指针。
	int  m_nMajorVersion;     //支持库的主版本号，必须大于0。
	int  m_nMinorVersion;     //支持库的次版本号。
	int  m_nBuildNumber;      //构建版本号
	int  m_nRqSysMajorVer;    //所需要易语言系统的主版本号
	int  m_nRqSysMinorVer;    //所需要易语言系统的次版本号
	int  m_nRqSysKrnlLibMajorVer;   //所需要的系统核心支持库的主版本号
	int  m_nRqSysKrnlLibMinorVer;   //所需要的系统核心支持库的次版本号
	unsigned int m_lpName;            //支持库名称指针
	int  m_nLanguage;         //支持库所支持的语言,应该是1
	unsigned int m_lpExplain;         //支持库解释内容指针,可为空
	unsigned int m_dwState;           //支持库特殊状态说明
	unsigned int m_lpszAuthor;        //作者相关信息
	unsigned int m_lpszZipCode;       //作者相关信息
	unsigned int m_lpszAddress;       //作者相关信息
	unsigned int m_lpszPhone;         //作者相关信息
	unsigned int m_lpszFax;           //作者相关信息
	unsigned int m_lpszEmail;         //作者相关信息
	unsigned int m_lpszHomePage;      //作者相关信息
	unsigned int m_lpszOther;         //作者相关信息

//////////////////
	int m_nDataTypeCount;     //支持库全部的数据类型个数
	unsigned int m_lpDataType;        //指向程序用到的数据类型信息的指针,LIB_DATA_TYPE_INFO

	int m_nCategoryCount;     //全局命令类别数目
	unsigned int m_lpszzCategory;     //全局命令类别说明表，每项为一字符串，前四位数字表示图象索引号（从1开始，0表示无）。
								// 减一后的值为指向支持库中名为"LIB_BITMAP"的BITMAP资源中某一部分16X13位图的索引

	int m_nCmdCount;          //本库中提供的所有命令(全局命令及对象方法)的数目(如无则为0)。
	unsigned int m_lpBeginCmdInfo;    //指向所有命令及方法的定义信息数组(如m_nCmdCount为0,则为NULL),CMD_INFO
	unsigned int m_lpCmdsFunc;        //指向每个命令的实现代码首地址，(如m_nCmdCount为0, 则为NULL)。

	unsigned int m_lpfnRunAddInFn;    //可为NULL，用作为易语言IDE提供附加功能
	unsigned int m_szzAddInFnInfo;    //有关AddIn功能的说明，两个字符串说明一个功能

	unsigned int m_lpfnNotify;        //不能为NULL，提供接收来自易语言IDE或运行环境通知信息的函数。

	// 超级模板暂时保留不用。
	unsigned int m_lpfnSuperTemplate;       //为空
	unsigned int m_lpszzSuperTemplateInfo;  //为空

	// 本库定义的所有常量。
	int m_nLibConstCount;   //常量数据
	unsigned int m_lpLibConst;      //指向常量定义数组的指针

	unsigned int m_lpszzDependFiles; //本库正常运行所需要依赖的其他文件，在制作安装软件时将会自动带上这些文件,可为空
};

#pragma pack(pop)

enum ControlType_t
{
	UnknownControl = 0,
	krnl_window,     //窗口
	krnl_menu,       //菜单
	krnl_EditBox,    //编辑框
	krnl_PicBox,     //图片框
	krnl_ShapeBox,   //外形框
	krnl_DrawPanel,  //画板
	krnl_GroupBox,   //分组框
	krnl_Label,      //标签
	krnl_Button,     //按钮
	krnl_CheckBox,   //选择框
	krnl_RadioBox,   //单选框
	krnl_ComboBox,   //组合框
	krnl_ListBox,    //列表框
	krnl_ChkListBox, //选择列表框
	krnl_HScrollBar, //横向滚动条
	krnl_VScrollBar, //纵向滚动条
	krnl_ProcessBar, //进度条
	krnl_SliderBar,  //滑块条
	krnl_Tab,        //选择夹
	krnl_AnimateBox, //影像框
	krnl_DatePicker, //日期框
	krnl_MonthCalendar,  //月历
	krnl_DriverBox,  //驱动器框
	krnl_DirBox,     //目录框
	krnl_FileBox,    //文件框
	krnl_ColorPicker, //颜色选择器
	krnl_HyperLinker, //超级链接器
	krnl_Spin,        //调节器
	krnl_CommonDlg,   //通用对话框
	krnl_Timer,       //时钟
	krnl_printer,     //打印机
	krnl_UDP,         //数据报
	krnl_Client,      //客户
	krnl_Server,      //服务器
	krnl_SerialPort,  //端口
	krnl_Grid,        //表格
	krnl_DataSrc,     //数据源
	krnl_NProvider,   //通用提供者
	krnl_DBProvider,  //数据库提供者
	krnl_PicBtn,      //图形按钮
	krnl_ODBCDB,      //外部数据库
	krnl_ODBCProvider,//外部数据提供者
	krnl_DropTarget,  //拖放对象
};

struct EStaticHead
{
	unsigned int dwMagic;  //未知,值固定为3
	unsigned int szNone2;  //未知,值固定为0
	unsigned int szNone3;  //未知,好像是个随机数,修改不影响程序
	unsigned int lpStartCode;   //起始用户代码地址,不可修改
	unsigned int lpEString;     //字符串资源,如果没有字符串资源,则为0
	unsigned int dwEStringSize; //字符串资源大小,如果没有字符串资源,则为0
	unsigned int lpEWindow;     //创建组件信息
	unsigned int dwEWindowSize; //创建组件信息大小
	unsigned int dwLibNum;      //支持库数量
	unsigned int lpLibEntry;    //支持库信息入口
	unsigned int dwApiCount;    //Api数量
	unsigned int lpModuleName;  //指向模块名称
	unsigned int lpApiName;     //指向Api名称
};
