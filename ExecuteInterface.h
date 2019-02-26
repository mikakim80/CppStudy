#pragma once
#include <type_traits>
#include <memory>
#include <string>

class CExecuteInterface
{
public:
	virtual ~CExecuteInterface() = 0;
	virtual void Execute() = 0;

	template <class T>
	static std::shared_ptr<CExecuteInterface> MakeInstance(const std::string& index)
	{
		static_assert(std::is_base_of<CExecuteInterface, T>::value, "the base class must be of type CExecuteInterface.");
		std::shared_ptr<CExecuteInterface> t(new T);
		InsertInstance(index, t);
		return t; 
	}

	static void ExecuteLatestInstance();

private:
	static void InsertInstance(const std::string& index, const std::shared_ptr<CExecuteInterface>& executeInterface);
};

#define DECLARE_INTERFACE(prefix, index) \
class prefix##index : public CExecuteInterface \
{ \
public: \
	void Execute() override; \
}; \
using ClassName = prefix##index; \
static std::shared_ptr<CExecuteInterface> instance = CExecuteInterface::MakeInstance<ClassName>(#index);