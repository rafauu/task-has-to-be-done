#include <boost/algorithm/cxx11/all_of.hpp>
#include <boost/range/adaptor/map.hpp>
#include <unordered_map>

template <typename Type>
class MultipleActionsHandler
{
public:
    template <typename... Args>
    constexpr explicit MultipleActionsHandler(Args&&... args)
    {
        (holder.emplace(std::forward<Args>(args), false), ...);
    }

    void markAsDone(const Type& id)
    {
        holder.insert_or_assign(id, true);
    }

    void markAllAsDone()
    {
        for(auto& id : holder)
            holder[id] = true;
    }

    bool isHandlingFinished() const
    {
        return boost::algorithm::all_of_equal(holder | boost::adaptors::map_values, true);
    }

private:
    std::unordered_map<Type, bool> holder;
};
