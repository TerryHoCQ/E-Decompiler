#pragma once
#include <pro.h>

struct SegmentInfomation
{
	ea_t m_segStart;                   //������ʼ��ַ
	uint32 m_segSize;                  //���δ�С
	qstring m_segName;                 //��������
	qvector<unsigned char> m_segData;  //��������
};

class SectionManager
{
public:
	//��ʼ����������
	static bool InitSectionManager();
	//���Ե�ַת��Ϊ�����ַ
	static uint8* LinearAddrToVirtualAddr(ea_t LinerAddr);
	//�����ַת��Ϊ���Ե�ַ
	static ea_t VirtualAddrToLinearAddr(uint8* pVirtualAddr);
	//Ѱ�ҵ�ַ,����Ϊʮ����������
	static ea_t SeachBin(qstring HexStr);
private:
	static qvector<SegmentInfomation> mVec_segInfo;
	static qvector<unsigned char> m_AllMemBuf;
};
