#include "ExecuteInterface.h"
#include <map>
#include <memory>

static std::map<int, std::shared_ptr<CExecuteInterface>> g_instanceMap;

CExecuteInterface::~CExecuteInterface()
{
}

void CExecuteInterface::ExecuteLatestInstance()
{
	auto iter = g_instanceMap.rbegin();
	if (iter != g_instanceMap.rend())
		iter->second->Execute();
}

void CExecuteInterface::InsertInstance(int index, const std::shared_ptr<CExecuteInterface>& executeInterface)
{
	g_instanceMap.insert(std::make_pair(index, executeInterface));
}
