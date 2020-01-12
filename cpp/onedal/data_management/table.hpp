#pragma once

#include "service/integral_types.hpp"
#include "service/internal/pimpl.hpp"

namespace onedal {
namespace data_management {

namespace internal {
class TableImpl;
} // namespace internal


class Table {
public:
    Table(const service::float32_t* data, 
          service::int32_t rows,
          service::int32_t cols);

    service::int32_t get_rows() const noexcept;
    service::int32_t get_cols() const noexcept;
    const service::float32_t* get_data() const noexcept;

private:
    service::internal::Pimpl<internal::TableImpl> _impl;
};
    
} // namespace data_management
} // namespace onedal
