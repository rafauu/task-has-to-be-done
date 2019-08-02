#include <boost/algorithm/cxx11/all_of.hpp>
#include <boost/range/adaptor/map.hpp>
#include <unordered_map>
#include <iostream>


template <auto... Args>
class MultipleActionsHandler
{
private:
    using Type = std::decay_t<std::common_type_t<decltype(Args)...>>;

public:
    constexpr MultipleActionsHandler();
    void markAsDone(Type id);
    void markAllAsDone();
    bool isHandlingFinished() const;

private:
    std::unordered_map<Type, bool> holder;
};


template <auto... Args>
constexpr MultipleActionsHandler<Args...>::MultipleActionsHandler()
{
    (holder.emplace(std::forward<Type>(Args), false), ...);
}

template <auto... Args>
void MultipleActionsHandler<Args...>::markAsDone(Type id)
{
    holder.insert_or_assign(id, true);
    std::cout << id << " marked as done" << std::endl;
}

template <auto... Args>
void MultipleActionsHandler<Args...>::markAllAsDone()
{
    for(auto&& [id, isDone] : holder)
    {
        isDone = true;
        std::cout << id << " marked as done" << std::endl;
    }
}

template <auto... Args>
bool MultipleActionsHandler<Args...>::isHandlingFinished() const
{
    return boost::algorithm::all_of_equal(holder | boost::adaptors::map_values, true);
}

