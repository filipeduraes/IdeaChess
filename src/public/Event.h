#pragma once
#include <functional>
#include <utility>
#include <vector>

template<typename... TArgs>
class IEvent
{
public:
    using Callback = std::function<void(TArgs...)>;

    virtual ~IEvent() = default;
    virtual void RegisterCallback(Callback callback) = 0;
};

template<typename... TArgs>
class Event final : public IEvent<TArgs...>
{
public:
    using Callback = IEvent<TArgs...>::Callback;

private:
    std::vector<Callback> callbacks;

public:
    Event() = default;

    Event(const Event&) = delete;
    Event& operator=(const Event&) = delete;

    virtual void RegisterCallback(Callback callback) override
    {
        callbacks.emplace_back(std::move(callback));
    }

    void Invoke(TArgs... args)
    {
        for (Callback& callback : callbacks)
        {
            callback(std::forward<TArgs>(args)...);
        }
    }
};