#include "onedal/detail/common.hpp"

namespace dal {

template <typename T>
class dparray {
public:
    dparray()
        : data_(nullptr),
          size_(0) {}

    T* get_data() const {
        return data_;
    }

    std::int64_t get_size() const {
        return size_;
    }

private:
    T* data_;
    std::int64_t size_;
};

} // namespace dal
