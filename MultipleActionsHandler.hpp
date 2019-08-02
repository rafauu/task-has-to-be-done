#include <boost/algorithm/cxx11/all_of.hpp>
#include <boost/range/adaptor/map.hpp>
#include <unordered_map>
#include <iostream>

template <auto... Args>
class MultipleActionsHandler
{
using Type = std::decay_t<std::common_type_t<decltype(Args)...>>;

public:
    constexpr explicit MultipleActionsHandler()
    {
        (holder.emplace(std::forward<Type>(Args), false), ...);
    }

    void markAsDone(Type id)
    {
        holder.insert_or_assign(id, true);
        std::cout << id << " marked as done" << std::endl;
    }

    void markAllAsDone()
    {
        for(auto&& [id, isDone] : holder)
        {
            isDone = true;
            std::cout << id << " marked as done" << std::endl;
        }
    }

    bool isHandlingFinished() const
    {
        return boost::algorithm::all_of_equal(holder | boost::adaptors::map_values, true);
    }

private:
    std::unordered_map<Type, bool> holder;
};
