#include "decomposition/pca/params.hpp"
#include "decomposition/pca/internal/params_impl.hpp"

#include <iostream>

namespace onedal {
namespace decomposition {
namespace pca {

Params::Params()
    : _impl()
{ }

Params& Params::set_n_components(service::int32_t value) {
    _impl->num_components = value;
    return *this;
}

service::int32_t Params::get_n_components() const noexcept {
    return _impl->num_components;
}

} // namespace pca
} // namespace decomposition
} // namespace onedal
