#include "IDATypeManager.h"
#include "IDAArchitecture.h"

IDATypeManager::IDATypeManager(IDAArchitecture* architecture)
	:TypeFactory(architecture), m_archi(architecture)
{

}