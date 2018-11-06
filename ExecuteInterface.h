#pragma once
#include <type_traits>
#include <memory>

class CExecuteInterface
{
public:
	virtual ~CExecuteInterface() = 0;
	virtual void Execute() = 0;

	template <class T>
	static std::shared_ptr<T> MakeInstance(int index)
	{
		static_assert(std::is_base_of<CExecuteInterface, T>::value, "the base class must be of type CExecuteInterface.");
		std::shared_ptr<T> t(new T);
		InsertInstance(index, t);
		return t; 
	}

	static void ExecuteLatestInstance();

private:
	static void InsertInstance(int index, const std::shared_ptr<CExecuteInterface>& executeInterface);
};

#define DECLARE_INTERFACE(prefix, index) \
class prefix##index : public CExecuteInterface \
{ \
public: \
	void Execute() override; \
}; \
static std::shared_ptr<prefix##index> instance = CExecuteInterface::MakeInstance<prefix##index>(index);