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
	//ɨ�貢ʶ��֧�ֿ⺯��
	static bool ScanLibFunction(ea_t lpLibStartAddr, uint32 dwLibCount);
	//ɨ�貢ʶ�������Ի�������
	static bool ScanBasicFunction();
private:
	//���ڼ�¼��Щ��ַ�ǿ⺯���ļ���
	static std::unordered_set<ea_t> mHash_LibFunc;
};
