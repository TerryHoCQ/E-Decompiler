#pragma once
#include <pro.h>

//ʮ����ʮ
void HexToBin(qstring& HexCode, uchar* BinCode);

//����һΪԭ�ı�,������Ϊ����ı�,������Ϊ�ұ��ı�,������Ϊ��ʼƫ��
qstring GetMidString(qstring& src, const char* left, const char* right, int offset);

//��������������,��0x90������ģ������,����ƫ�ƴ�С
uint32 Search_Bin(unsigned char* pSrc, unsigned char* pTrait, int nSrcLen, int nTraitLen);