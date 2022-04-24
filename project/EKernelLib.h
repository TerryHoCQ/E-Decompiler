#pragma once
#include <map>

enum EKernelCallType
{
	UnknownError,           
	E_MReportError,         //错误回调
	E_MCallDllCmd,          //DLL命令
	E_MCallLibCmd,          //三方支持库命令
	E_MCallKrnlLibCmd,      //核心支持库命令
	E_MReadProperty,        //读取组件属性
	E_MWriteProperty,       //设置组件属性
	E_MMalloc,              //分配内存
	E_MRealloc,             //重新分配内存
	E_MFree,               //释放内存
	E_MExitProcess,         //结束
	E_MMessageLoop,         //窗口消息循环
	E_MLoadBeginWin,        //载入启动窗口
	E_MOtherHelp            //辅助功能
};

class EKernelLib
{
public:
	EKernelLib();
public:
	EKernelCallType GetKernelCallType(unsigned int callAddr);
public:
	//地址 --> 类型
	std::map<unsigned int, EKernelCallType> map_KernelCall;
};