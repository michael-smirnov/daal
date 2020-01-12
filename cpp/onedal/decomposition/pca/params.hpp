#pragma once
#include "service/integral_types.hpp"
#include "service/internal/pimpl.hpp"

namespace onedal {
namespace decomposition {
namespace pca {

namespace internal {
class ParamsImpl;
} // namespace internal


class Params {
public:
    Params();

    Params& set_n_components(service::int32_t value);

    service::int32_t get_n_components() const noexcept;

private:
    service::internal::Pimpl<internal::ParamsImpl> _impl;
};

} // namespace pca  
} // namespace decomposition   
} // namespace onedal
