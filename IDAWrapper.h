#pragma once
#include <stdint.h>
#include <string>

//自己封装的IDA中间件,确保其它项目都能调用IDA的API

class IDAWrapper
{
public:
	static void* create_code_viewer(void* custview, int flags = 0, void* parent = nullptr);
	static void display_widget(void* widget, unsigned int options, const char* dest_ctrl = nullptr);
	static int64_t get_bytes(void* buf, int64_t size, uint64_t ea, int gmb_flags = 0, void* mask = nullptr);
	static const char* idadir(const char* subdir);
	static unsigned short get_word(uint64_t addr);
	static unsigned int get_dword(uint64_t addr);
	//适用于一般场景
	static std::string get_shortstring(uint64_t addr);
};