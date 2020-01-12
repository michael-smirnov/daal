#pragma once
#include "service/integral_types.hpp"
#include <cstring>

namespace onedal {
namespace data_management {
namespace internal {

enum class Layout { rowmajor, colmajor };
enum class Type { heterogen, homogen_fp32 };

class TableImpl {
public:
    TableImpl(const service::float32_t* data, service::int32_t rows, service::int32_t cols)
        : _container(data, rows * cols),
          _layout(Layout::rowmajor),
          _type(Type::homogen_fp32) 
    { }

    template <typename T>
    const T* get_data(service::int32_t offset) const noexcept {
        // TODO: handle data layout and type
        _container.get_data<T>(offset);
    }

    service::int32_t get_num_rows() const noexcept {
        return _num_rows;
    }

    service::int32_t get_num_cols() const noexcept {
        return _num_cols;
    }

private:
    class DataContainer {
    public:
        template <typename T>
        DataContainer(const T* data, service::int64_t size)
            : _size_in_bytes(size * sizeof(T)) { 
            // TODO: check if size is valid value

            _data = new service::int8_t[_size_in_bytes];
            std::memcpy(_data, static_cast<const void*>(data), _size_in_bytes);
        }

        ~DataContainer() {
            delete[] _data;
            _data = nullptr;
            _size_in_bytes = 0;
        }

        template <typename T>
        T* get_data(service::int32_t offset) const {
            service::int64_t offset_in_bytes = offset * sizeof(T);

            // TODO: handle if offset_in_bytes >= _size_in_bytes
            return static_cast<T*>(_data) + offset;
        }
    
    private:
        void* _data;
        service::int64_t _size_in_bytes;
    };

private:
    DataContainer _container;
    Layout _layout;
    Type _type;

    service::int32_t _num_rows, _num_cols;
};
    
} // namespace internal
} // namespace data_management
} // namespace onedal
