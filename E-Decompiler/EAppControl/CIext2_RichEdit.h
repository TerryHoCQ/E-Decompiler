#pragma once
#include "EAppControl.h"

//�����༭��

struct CIext2_RichEdit :public EAppControl
{
public:
	CIext2_RichEdit();
	static CIext2_RichEdit* create();
public:
	std::string GetEventName(int eventIndex)override;
	bool InitControlExtraData(unsigned int propertyAddr, unsigned int propertySize) override;
	std::string GetPropertyName(unsigned int propertyIndex) override;
};