#pragma once
#include <string>

unsigned int ReadUInt(unsigned char* pBuf);
int ReadInt(unsigned char* pBuf);
unsigned char ReadUChar(unsigned char* pBuf);
unsigned char ReadUChar(char* pBuf);
std::string ReadStr(unsigned char* pBuf);


//ʮ����ʮ,a -> 10
unsigned char HexToBin(unsigned char HexCode);

