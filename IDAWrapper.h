#pragma once
#include <stdint.h>

//�Լ���װ��IDA�м��,ȷ���κ���Ŀ���ܵ���IDA��API

class IDAWrapper
{
public:
	static void* create_code_viewer(void* custview, int flags = 0, void* parent = nullptr);
	static void display_widget(void* widget, unsigned int options, const char* dest_ctrl = nullptr);
	static int64_t get_bytes(void* buf, int64_t size, uint64_t ea, int gmb_flags = 0, void* mask = nullptr);
	static const char* idadir(const char* subdir);
};