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