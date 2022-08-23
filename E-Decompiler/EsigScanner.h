#pragma once
#include <pro.h>
#include <unordered_set>

struct LibScanResult
{
	qstring LibName;
	qstring Guid;
	struct FuncScanResult
	{
		ea_t FuncAddr;
		qstring FuncName;
	};
	qvector<FuncScanResult> Vec_Funcs;
};

class ESigScanner
{
public:
	
	
private:
	//���ڼ�¼��Щ��ַ�ǿ⺯���ļ���
	static std::unordered_set<ea_t> mHash_LibFunc;
};
