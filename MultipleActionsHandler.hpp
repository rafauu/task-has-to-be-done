#include <any>
#include <vector>
#include <algorithm>

class MultipleActionsHandler
{
public:
    template <typename... Args>
    constexpr explicit MultipleActionsHandler(Args&&... args)
    {
        (holder.emplace_back(Action{std::forward<Args>(args), false}), ...);
    }

    template <typename T>
    void markAsDone(const T& id)
    {
        auto it = std::find_if(holder.begin(),
                               holder.end(),
                               [&](auto&& action){ return std::any_cast<T>(action.id) == std::any_cast<T>(id); });
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
        std::any id;
        bool isDone;
    };
    std::vector<Action> holder;
};
