#pragma once
#include <string>
#include <vector>

#include "./common/Address.h"

struct SegmentInfomation;
namespace DecompilerCore
{
	struct AddressInfo
	{
		std::uint64_t addrStart;                  //区段起始地址
		std::uint64_t addrSize;                   //区段大小
		std::string addrName;                   //区段名称
		std::vector<unsigned char> addrData;     //区段数据
	};

	//地址管理器
	class AddrSpaceManager
	{
	public:
		bool InitAddressSpaceManager(std::vector<SegmentInfomation>& segInfo);
		//获取指定地址下界
		Address getAddressLowerBound(Address addr);
		//获取指定地址上界
		Address getAddressUpperBound(Address addr);
	public:
		std::vector<AddressInfo> mVec_segInfo;
	};

}


