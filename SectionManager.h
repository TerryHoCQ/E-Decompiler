#pragma once
#include <string>
#include <vector>

struct SegmentInfomation
{
	unsigned int m_segStart;                   //������ʼ��ַ
	unsigned int m_segSize;                  //���δ�С
	std::string m_segName;                 //��������
	std::vector<unsigned char> m_segData;  //��������
};

class SectionManager
{
public:
	//��ʼ����������
	static bool InitSectionManager();
	//���Ե�ַת��Ϊ�����ַ
	static unsigned char* LinearAddrToVirtualAddr(unsigned int LinerAddr);
	//�����ַת��Ϊ���Ե�ַ
	static unsigned int VirtualAddrToLinearAddr(unsigned char* pVirtualAddr);
	//Ѱ�ҵ�ַ,����Ϊʮ����������
	static unsigned int SeachBin(std::string HexStr);
private:
	static std::vector<SegmentInfomation> mVec_segInfo;
	static std::vector<unsigned char> m_AllMemBuf;
};
