#include <vector>
#include <algorithm>

template <typename Type>
class MultipleActionsHandler
{
public:
    template <typename... Args>
    constexpr explicit MultipleActionsHandler(Args&&... args)
    {
        (holder.emplace_back(Action{std::forward<Args>(args), false}), ...);
    }

    void markAsDone(const Type& id)
    {
        auto it = std::find_if(holder.begin(),
                               holder.end(),
                               [&](auto&& action){ return action.id == id; });
        if (it != holder.end())
        {
            it->isDone = true;
        }
    }

    bool isHandlingFinished() const
    {
        return std::all_of(holder.cbegin(),
                           holder.cend(),
                           [](auto&& action){ return action.isDone; });
    }

private:
    struct Action
    {
        Type id;
        bool isDone;
    };
    std::vector<Action> holder;
};
