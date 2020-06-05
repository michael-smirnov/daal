/*******************************************************************************
 * Copyright 2020 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *******************************************************************************/

#pragma once

#include "onedal/array.hpp"
#include "onedal/common.hpp"

namespace dal {

enum class feature_type {
    nominal,
    ordinal,
    interval,
    ratio
};

namespace table_type {
    static constexpr std::int64_t homogen = 1;
    static constexpr std::int64_t soa = 2;
}

class table_metadata {
    table_metadata();

    table_metadata(std::int64_t features_count,
                   feature_info feature = {},
                   data_layout layout = data_layout::row_major);

    data_type get_data_type(std::int64_t feature_index) const;

    feature_type get_feature_type(std::int64_t feature_index) const;

    std::int64_t get_feature_count() const;
};

} // namespace dal
