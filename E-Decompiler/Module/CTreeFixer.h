#pragma once

//�޸������Է�������

class ESymbol;
class CTreeFixer
{
public:
	CTreeFixer(ESymbol& symbol);
	~CTreeFixer();
private:
	ESymbol& eSymbol;
};