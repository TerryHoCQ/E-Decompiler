#include "EKernelLib.h"

EKernelLib::EKernelLib()
{

}

EKernelCallType EKernelLib::GetKernelCallType(unsigned int callAddr)
{
	return map_KernelCall[callAddr];
}
