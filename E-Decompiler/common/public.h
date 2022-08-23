#pragma once
#include <pro.h>



//UTF-8תascii
bool acp_ascii(qstring* out, const char* in);

//����MD5�ı�
qstring CalculateMD5(qstring& md5);

//��ʮ������
const char* UCharToStr(unsigned char c);


//����һΪԭ�ı�,������Ϊ����ı�,������Ϊ�ұ��ı�,������Ϊ��ʼƫ��
qstring GetMidString(qstring& src, const char* left, const char* right, int offset);

//��������������,��0x90������ģ������,����ƫ�ƴ�С
uint32 Search_Bin(unsigned char* pSrc, unsigned char* pTrait, int nSrcLen, int nTraitLen);

qstring �ֽڼ�_�ֽڼ���ʮ������(qvector<unsigned char>& ԭʼ�ֽڼ�);

//��ȡ���е����ݽ�������
qvector<ea_t> GetAllDataRef(ea_t addr);

//�Ƿ������ݽ�������
bool HasDataRef(ea_t addr);


qstring getUTF8String(const char* data);

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

qvector<unsigned int> CDR_ReadVecInt(unsigned char*& currentPoint);

