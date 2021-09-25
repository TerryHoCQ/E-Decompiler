#pragma once
#include <vector>
#include <windows.h>

struct rich_entry
{
	std::uint16_t ProductId;
	std::uint16_t BuildNumber;
	std::uint32_t Count;
};

struct RICH_HEADER
{
	std::vector<rich_entry> Entries;
	std::uint32_t xorKey;
	uint32_t Checksum;
	bool isPresent;
	bool isValid;
};

struct SECTION_HEADER
{
	BYTE    Name[IMAGE_SIZEOF_SHORT_NAME];
	union {
		DWORD   PhysicalAddress;
		DWORD   VirtualSize;
	} Misc;
	DWORD   VirtualAddress;
	DWORD   SizeOfRawData;
	DWORD   PointerToRawData;
	DWORD   PointerToRelocations;
	DWORD   PointerToLinenumbers;
	WORD    NumberOfRelocations;
	WORD    NumberOfLinenumbers;
	DWORD   Characteristics;

	DWORD	VirtualAlignSize;		//个人定义,VirtualSize内存对齐后的大小
};

struct NT_HEADER
{
	DWORD Signature;
	PIMAGE_FILE_HEADER pFileHeader;
	PIMAGE_OPTIONAL_HEADER32 pOptionalHeader32;
	PIMAGE_OPTIONAL_HEADER64 pOptionalHeader64;

	bool isAlignEqual;      //文件对齐与内存对齐是否相等
	bool isPE64;			//个人定义的,用来标记32位PE还是64位PE
};

struct RawPE
{
	PIMAGE_DOS_HEADER pDosHeader;
	RICH_HEADER RichHeader;
	NT_HEADER NtHeader;
	std::vector<SECTION_HEADER> vec_SECTION;
};

class LazyPE
{
public:
	~LazyPE()
	{
		FreeAll();
	}
	void FreeAll()
	{
		if (m_FileBuffer) {
			delete m_FileBuffer;
			m_FileBuffer = nullptr;
		}
		if (no_FileHandle != INVALID_HANDLE_VALUE) {
			CloseHandle(no_FileHandle);
		}
	}
	bool LoadFile(const char* filePath)
	{
		FreeAll();

		no_FileHandle = CreateFileA(filePath,
			GENERIC_READ,
			FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
			nullptr,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			nullptr);
		if (no_FileHandle == INVALID_HANDLE_VALUE) {
			return false;
		}

		DWORD fileSize = GetFileSize(no_FileHandle, nullptr);
		if (fileSize == INVALID_FILE_SIZE) {
			CloseHandle(no_FileHandle);
			no_FileHandle = INVALID_HANDLE_VALUE;
			return false;
		}

		m_FileBuffer = new unsigned char[fileSize];
		if (m_FileBuffer == nullptr) {
			CloseHandle(no_FileHandle);
			no_FileHandle = INVALID_HANDLE_VALUE;
			return false;
		}
		memset(m_FileBuffer, 0x0, fileSize);
		DWORD dwReadLen = 0;
		if (!ReadFile(no_FileHandle, m_FileBuffer, fileSize, &dwReadLen, nullptr) || fileSize != dwReadLen) {
			CloseHandle(no_FileHandle);
			no_FileHandle = INVALID_HANDLE_VALUE;
			return false;
		}

		if (!ParsePEFromBuffer(m_FileBuffer)) {
			CloseHandle(no_FileHandle);
			no_FileHandle = INVALID_HANDLE_VALUE;
			return false;
		}

		CloseHandle(no_FileHandle);
		no_FileHandle = INVALID_HANDLE_VALUE;
		return true;
	}
private:
	bool ParsePEFromBuffer(unsigned char* fileBuf)
	{
		if (nullptr == fileBuf) {
			return false;
		}

		ReadDosHeader(fileBuf);
		if (rawData.pDosHeader->e_magic != 0x5A4D) {
			return false;
		}

		fileBuf += rawData.pDosHeader->e_lfanew;
		if (!ReadNtHeader(fileBuf)) {
			return false;
		}

		if (!ReadSections(fileBuf)) {
			return false;
		}

		return true;
	}

	//————————————————
	void ReadDosHeader(unsigned char* pHeader)
	{
		rawData.pDosHeader = (PIMAGE_DOS_HEADER)pHeader;
	}
	bool ReadNtHeader(unsigned char*& pHeader)
	{
		rawData.NtHeader.Signature = ReadDword(pHeader);
		if (rawData.NtHeader.Signature != 0x00004550) {
			return false;
		}
		pHeader += 4;

		ReadFileHeader(pHeader);
		pHeader += sizeof(IMAGE_FILE_HEADER);

		if (!ReadOptionalHeader(pHeader)) {
			return false;
		}
		pHeader += rawData.NtHeader.pFileHeader->SizeOfOptionalHeader;
		return true;
	}
	void ReadFileHeader(unsigned char* pHeader)
	{
		rawData.NtHeader.pFileHeader = (PIMAGE_FILE_HEADER)pHeader;;
		return;
	}
	bool ReadOptionalHeader(unsigned char* pHeader)
	{
		std::uint16_t OptionMagic = ReadWord(pHeader);
		if (OptionMagic == 0x10B) {
			rawData.NtHeader.pOptionalHeader32 = (PIMAGE_OPTIONAL_HEADER32)pHeader;
			rawData.NtHeader.isPE64 = false;
			if (rawData.NtHeader.pOptionalHeader32->FileAlignment == rawData.NtHeader.pOptionalHeader32->SectionAlignment) {
				rawData.NtHeader.isAlignEqual = true;
			}
		}
		else if (OptionMagic == 0x20B) {
			rawData.NtHeader.pOptionalHeader64 = (PIMAGE_OPTIONAL_HEADER64)pHeader;
			rawData.NtHeader.isPE64 = true;
			if (rawData.NtHeader.pOptionalHeader64->FileAlignment == rawData.NtHeader.pOptionalHeader64->SectionAlignment) {
				rawData.NtHeader.isAlignEqual = true;
			}
		}
		else {
			return false;
		}

		return true;
	}
	bool ReadSections(unsigned char* pBuf)
	{
		for (std::uint32_t i = 0; i < rawData.NtHeader.pFileHeader->NumberOfSections; ++i) {
			PIMAGE_SECTION_HEADER pSECHeader = (PIMAGE_SECTION_HEADER)pBuf;
			SECTION_HEADER tmpHeader = { 0 };
			memcpy(&tmpHeader, pSECHeader, sizeof(IMAGE_SECTION_HEADER));
			tmpHeader.VirtualAlignSize = AlignByMemory(tmpHeader.Misc.VirtualSize);
			rawData.vec_SECTION.push_back(tmpHeader);
			pBuf += sizeof(IMAGE_SECTION_HEADER);
		}

		return true;
	}
	//————————————————
	std::uint32_t ReadDword(unsigned char* pBuf)
	{
		return *(std::uint32_t*)(pBuf);
	}
	std::uint16_t ReadWord(unsigned char* pBuf)
	{
		return *(std::uint16_t*)(pBuf);
	}

	DWORD AlignByMemory(DWORD originValue)
	{
		DWORD Alignment = 0;
		if (!rawData.NtHeader.isPE64) {
			Alignment = rawData.NtHeader.pOptionalHeader32->SectionAlignment;
		}
		else {
			Alignment = rawData.NtHeader.pOptionalHeader64->SectionAlignment;
		}

		DWORD reminder = originValue / Alignment;
		DWORD mod = originValue % Alignment;

		if (mod != 0) {
			reminder += 1;
		}
		return reminder * Alignment;
	}
public:
	RawPE rawData;
private:
	//seems to be no use
	HANDLE no_FileHandle = INVALID_HANDLE_VALUE;


	unsigned char* m_FileBuffer = nullptr;
};