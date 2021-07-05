#pragma once
#include <pro.h>

void setFuncName(ea_t addr, const char* funcName, int flags = 0);

//UTF-8תascii
bool acp_ascii(qstring* out, const char* in);

//����MD5�ı�
qstring CalculateMD5(qstring& md5);

//��ʮ������
const char* UCharToStr(unsigned char c);

//ʮ����ʮ
unsigned char HexToBin(unsigned char HexCode);

//ʮ����ʮ
void HexToBin(qstring& HexCode, uchar* BinCode);

//����һΪԭ�ı�,������Ϊ����ı�,������Ϊ�ұ��ı�,������Ϊ��ʼƫ��
qstring GetMidString(qstring& src, const char* left, const char* right, int offset);

//��������������,��0x90������ģ������,����ƫ�ƴ�С
uint32 Search_Bin(unsigned char* pSrc, unsigned char* pTrait, int nSrcLen, int nTraitLen);

qstring �ֽڼ�_�ֽڼ���ʮ������(qvector<unsigned char>& ԭʼ�ֽڼ�);

//��ȡ���е����ݽ�������
qvector<ea_t> GetAllDataRef(ea_t addr);

//�Ƿ������ݽ�������
bool HasDataRef(ea_t addr);

qstring get_shortstring(int32 addr);

qstring getUTF8String(const char*);

uint32 ReadUInt(unsigned char* pBuf);

int32 ReadInt(unsigned char* pBuf);

unsigned char ReadUChar(unsigned char* pBuf);
unsigned char ReadUChar(char* pBuf);

qstring ReadStr(unsigned char* pBuf);

//���л�_��ȡInt
int CDR_ReadInt(unsigned char*& currentPoint);

//���л�_��ȡUint
unsigned int CDR_ReadUInt(unsigned char*& currentPoint);

//���л�_��ȡ�ַ�������
qvector<qstring> CDR_ReadVecString(unsigned char*& currentPoint);

//���л�_��ȡUshort
unsigned short CDR_ReadUShort(unsigned char*& currentPoint);

//���л�_��ȡchar
char CDR_ReadChar(unsigned char*& currentPoint);

//���л�_��ȡ�ַ���
qstring CDR_ReadCString(unsigned char*& currentPoint);

//���л�_��ȡ����
qvector<unsigned char> CDR_ReadCFreqMem(unsigned char*& currentPoint);