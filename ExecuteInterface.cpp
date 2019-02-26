#include "ExecuteInterface.h"
#include <map>
#include <memory>

using InterfaceMap = std::map<int, std::shared_ptr<CExecuteInterface>>;

InterfaceMap& GetInstanceMap()
{
	static InterfaceMap g_instanceMap;
	return g_instanceMap;
}

CExecuteInterface::~CExecuteInterface()
{
}

void CExecuteInterface::ExecuteLatestInstance()
{
	auto iter = GetInstanceMap().rbegin();
	if (iter != GetInstanceMap().rend())
		iter->second->Execute();
}

void CExecuteInterface::InsertInstance(const std::string& index, const std::shared_ptr<CExecuteInterface>& executeInterface)
{
	GetInstanceMap().insert(std::make_pair(std::stoi(index), executeInterface));
}
