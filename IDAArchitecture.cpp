#include "IDAArchitecture.h"
#include "loadimage_ecat.h"

IDAArchitecture::IDAArchitecture(const string& targ):
	SleighArchitecture("ida", targ, &m_err)
{
	
}

IDAArchitecture::~IDAArchitecture()
{
	SleighArchitecture::shutdown();
}

void IDAArchitecture::addInjection(std::string functionName, std::string injection)
{
	m_injectionMap.emplace(functionName, injection);
}

void IDAArchitecture::buildLoader(DocumentStorage& store)
{
	collectSpecFiles(*errorstream);
	loader = new ECatLoadImage();
}