#ifndef GENERATOR_H
#define GENERATOR_H

#include <coroutine>
#include <cstdlib>
#include <iterator>

template<typename T>
class Generator {
public:
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    explicit Generator(handle_type h) : coro(h) {}
    Generator(const Generator&) = delete;
    Generator(Generator&& other) noexcept : coro(other.coro) { other.coro = nullptr; }
    ~Generator() { if (coro) coro.destroy(); }

    Generator& operator=(const Generator&) = delete;
    Generator& operator=(Generator&& other) noexcept {
        if (this != &other) {
            if (coro) coro.destroy();
            coro = other.coro;
            other.coro = nullptr;
        }
        return *this;
    }

    class iterator {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = const T*;
        using reference = const T&;

        iterator() : coro(nullptr), done(true) {}
        explicit iterator(handle_type h) : coro(h) { resume(); }

        iterator& operator++() { 
            resume();
            return *this;
        }

        T operator*() const { return coro.promise().current_value; }
        
        bool operator==(std::default_sentinel_t) const { return done; }
        bool operator!=(std::default_sentinel_t) const { return !done; }

    private:
        handle_type coro;
        bool done;

        void resume() {
            coro.resume();
            done = coro.done();
        }
    };

    iterator begin() {
        if (!coro)
            return iterator{};
        return iterator{coro};
    }
    
    std::default_sentinel_t end() { return {}; }

private:
    handle_type coro;
};

template<typename T>
struct Generator<T>::promise_type {
    T current_value;

    auto get_return_object() {
        return Generator{handle_type::from_promise(*this)};
    }
    
    std::suspend_always initial_suspend() { return {}; }
    std::suspend_always final_suspend() noexcept { return {}; }
    
    std::suspend_always yield_value(T value) {
        current_value = value;
        return {};
    }
    
    void return_void() {}
    void unhandled_exception() { std::exit(1); }
};

#endif
