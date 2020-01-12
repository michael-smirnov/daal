#include "data_management/table.hpp"
#include "data_management/internal/table_impl.hpp"

namespace onedal {
namespace data_management {

Table::Table(const service::float32_t* data, 
             service::int32_t rows,
             service::int32_t cols) 
    : _impl(data, rows, cols)
{ }

service::int32_t Table::get_rows() const noexcept {
    return _impl->get_num_rows();
}

service::int32_t Table::get_cols() const noexcept {
    return _impl->get_num_cols();
}

const service::float32_t* Table::get_data() const noexcept {
    return _impl->get_data<service::float32_t>(0);
}

} // namespace data_management
} // namespace onedal