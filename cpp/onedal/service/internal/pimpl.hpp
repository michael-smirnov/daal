#pragma once

#include <memory>

namespace onedal {
namespace service {
namespace internal {

template <typename T>
class Pimpl {
public:
    template <typename... Args>
    Pimpl(Args&&... args) {
        _impl = std::make_unique<T>(std::forward<Args>(args)...);
    }

    T* operator ->() const noexcept {
        return _impl.get();
    }

private:
    std::shared_ptr<T> _impl;
};
    
} // namespace internal 
} // namespace service
} // namespace onedal
