#include "IDAWrapper.h"
#include <pro.h>
#include <kernwin.hpp>
#include <bytes.hpp>
#include <diskio.hpp>

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

std::string IDAWrapper::get_shortstring(uint64_t addr)
{
	if (addr <= 0)
	{
		return "";
	}
	char buffer[255] = { 0 };
	if (::get_bytes(buffer, sizeof(buffer), addr, GMB_READALL, NULL) != sizeof(buffer))			//没读取到完整的字节应该算是错误了
	{
		return "";
	}
	return buffer;
}