#include "IDAWrapper.h"
#include <pro.h>
#include <kernwin.hpp>
#include <bytes.hpp>
#include <diskio.hpp>
#include <funcs.hpp>
#include <ua.hpp>

void* IDAWrapper::create_code_viewer(void* custview, int flags, void* parent)
{
	return ::create_code_viewer((TWidget*)custview, flags, (TWidget*)parent);
}

void IDAWrapper::display_widget(void* widget, unsigned int options, const char* dest_ctrl)
{
	::display_widget((TWidget*)widget, options, dest_ctrl);
}

int64_t IDAWrapper::get_bytes(void* buf, int64_t size, uint64_t ea, int gmb_flags, void* mask)
{
	return ::get_bytes(buf, size, ea, gmb_flags, mask);
}

const char* IDAWrapper::idadir(const char* subdir)
{
	return ::idadir(subdir);
}

unsigned short IDAWrapper::get_word(uint64_t addr)
{
	return ::get_word(addr);
}

unsigned int IDAWrapper::get_dword(uint64_t addr)
{
	return ::get_dword(addr);
}

func_t* IDAWrapper::get_func(uint64_t addr)
{
	return ::get_func(addr);
}

uint64_t IDAWrapper::get_screen_ea()
{
	return ::get_screen_ea();
}

std::string IDAWrapper::get_shortstring(uint64_t addr)
{
	if (addr <= 0)
	{
		return "";
	}
	char buffer[255] = { 0 };
	if (::get_bytes(buffer, sizeof(buffer), addr, GMB_READALL, NULL) != sizeof(buffer))			//û��ȡ���������ֽ�Ӧ�����Ǵ�����
	{
		return "";
	}
	return buffer;
}

