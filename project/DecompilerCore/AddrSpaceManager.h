#pragma once
#include <string>
#include <vector>

#include "./common/Address.h"

struct SegmentInfomation;
namespace DecompilerCore
{
	struct AddressInfo
	{
		std::uint64_t addrStart;                  //������ʼ��ַ
		std::uint64_t addrSize;                   //���δ�С
		std::string addrName;                   //��������
		std::vector<unsigned char> addrData;     //��������
	};

	//��ַ������
	class AddrSpaceManager
	{
	public:
		bool InitAddressSpaceManager(std::vector<SegmentInfomation>& segInfo);
		//��ȡָ����ַ�½�
		Address getAddressLowerBound(Address addr);
		//��ȡָ����ַ�Ͻ�
		Address getAddressUpperBound(Address addr);
	public:
		std::vector<AddressInfo> mVec_segInfo;
	};

}


