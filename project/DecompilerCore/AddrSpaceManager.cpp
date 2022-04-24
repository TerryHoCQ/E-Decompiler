#include "AddrSpaceManager.h"
#include <segment.hpp>
#include <bytes.hpp>
#include "..\SectionManager.h"

bool DecompilerCore::AddrSpaceManager::InitAddressSpaceManager(std::vector<SegmentInfomation>& vec_segInfo)
{
	for (unsigned int n = 0; n < vec_segInfo.size(); ++n) {
		AddressInfo tmpInfo;
		tmpInfo.addrStart = vec_segInfo[n].m_segStart;
		tmpInfo.addrSize = vec_segInfo[n].m_segSize;
		tmpInfo.addrName = vec_segInfo[n].m_segName;
		tmpInfo.addrData = vec_segInfo[n].m_segData;
		this->mVec_segInfo.push_back(tmpInfo);
	}
	return true;
}

DecompilerCore::Address DecompilerCore::AddrSpaceManager::getAddressLowerBound(Address addr)
{
	for (unsigned int n = 0; n < mVec_segInfo.size(); ++n) {
		auto bound = mVec_segInfo[n].addrStart + mVec_segInfo[n].addrSize;
		if (addr.offset >= mVec_segInfo[n].addrStart && addr.offset < bound) {
			return mVec_segInfo[n].addrStart;
		}
	}
	return 0;
}

DecompilerCore::Address DecompilerCore::AddrSpaceManager::getAddressUpperBound(Address addr)
{
	for (unsigned int n = 0; n < mVec_segInfo.size(); ++n) {
		auto bound = mVec_segInfo[n].addrStart + mVec_segInfo[n].addrSize;
		if (addr.offset >= mVec_segInfo[n].addrStart && addr.offset < bound) {
			return bound;
		}
	}
	return 0;
}
