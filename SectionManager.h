#pragma once
#include <string>
#include <vector>

struct SegmentInfomation
{
	unsigned int m_segStart;                   //区段起始地址
	unsigned int m_segSize;                  //区段大小
	std::string m_segName;                 //区段名称
	std::vector<unsigned char> m_segData;  //区段数据
};

class SectionManager
{
public:
	//初始化程序区段
	static bool InitSectionManager();
	//线性地址转换为虚拟地址
	static unsigned char* LinearAddrToVirtualAddr(unsigned int LinerAddr);
	//虚拟地址转换为线性地址
	static unsigned int VirtualAddrToLinearAddr(unsigned char* pVirtualAddr);
	//寻找地址,参数为十六进制特征
	static unsigned int SeachBin(std::string HexStr);
private:
	static std::vector<SegmentInfomation> mVec_segInfo;
	static std::vector<unsigned char> m_AllMemBuf;
};
