#pragma once
#include "EKernelLib.h"
#include "EObject_Include.h"
#include "IDAArchitecture.h"
#include <vector>
#include <string>

//易语言静态编译架构

struct mid_ELibInfo
{
	std::string m_Name;     //支持库名称
	std::string m_Guid;     //支持库的GUID
	int  m_nMajorVersion;   //支持库的主版本号，必须大于0。
	int  m_nMinorVersion;   //支持库的次版本号。
};

struct mid_EAppInfo
{
	unsigned int m_UserCodeStartAddr;                //用户起始地址
	unsigned int m_UserCodeEndAddr;                  //用户结束地址,目前暂时还没有什么好办法获取这个地址,如果有好的想法欢迎提issue

	std::vector<mid_ELibInfo>  mVec_LibInfo;         //支持库信息
	//mid_KrnlApp m_KrnlApp;
	//mid_KrnlJmp m_KrnlJmp;
	bool b_IsWindowProgram;                          //是否是窗体程序
};

class EStaticArchitecture:public IDAArchitecture
{
public:
	EStaticArchitecture();
	~EStaticArchitecture();
	//解析静态类型的易语言程序
	bool Parse_EStatic(unsigned int eHeadAddr);

	//执行反编译动作
	void performActions() override;
private:
	//解析支持库信息
	bool ParseLibInfomation(unsigned int lpLibStartAddr, unsigned int dwLibCount);

	//解析系统接口函数
	bool ParseKrnlInterface(unsigned int);

	//void buildAction(DocumentStorage& store) override;
public:
	//核心函数
	EKernelLib m_KernelLib;

	//易语言中的所有信息
	mid_EAppInfo m_eAppInfo;
	//控件ID -> 控件类型
	std::map<unsigned int, ControlType_t> m_ControlMapping;

	std::map<unsigned int, std::string> map_KernelFunc;
};