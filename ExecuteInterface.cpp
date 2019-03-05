#include "ExecuteInterface.h"
#include <map>
#include <memory>
#include <iostream>

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

void CExecuteInterface::Execute(int index)
{
	auto result = GetInstanceMap().find(index);
	if (result != GetInstanceMap().end())
		result->second->Execute();
	else
		std::cout << "존재하지 않는 index: " << index << std::endl;
}

void CExecuteInterface::InsertInstance(const std::string& index, const std::shared_ptr<CExecuteInterface>& executeInterface)
{
	GetInstanceMap().insert(std::make_pair(std::stoi(index), executeInterface));
}

void NUtil::PrintDivider(const std::string& title)
{
	std::cout << "\n###################################################################################\n";
	std::cout << title;
	std::cout << "\n###################################################################################\n\n";
}
