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
#include "onedal/detail/common.hpp"
#include "onedal/common_helpers.hpp"

namespace dal {

enum class feature_type {
    nominal,
    ordinal,
    interval,
    ratio
};

enum class data_layout {
    row_major,
    column_major
};

namespace table_type {
    static constexpr std::int64_t empty = 0;
    static constexpr std::int64_t homogen = 1;
    static constexpr std::int64_t soa = 2;
} // namespace table_type

namespace detail {
    class table_feature_impl;
    class table_metadata_impl;
} // namespace detail

class table_feature {
public:
    table_feature();
    table_feature(data_type);
    table_feature(data_type, feature_type);


    data_type get_data_type() const;
    table_feature& set_data_type(data_type);

    feature_type get_type() const;
    table_feature& set_type(feature_type);

private:
    detail::pimpl<detail::table_feature_impl> impl_;
};

template <typename T>
table_feature make_table_feature() {
    return table_feature { make_data_type<T>() };
}

class table_metadata {
    friend detail::pimpl_accessor;

public:
    table_metadata();

    table_metadata(std::int64_t table_type,
                   const table_feature&,
                   std::int64_t row_count,
                   std::int64_t column_count = 1);

    table_metadata(std::int64_t table_type,
                   array<table_feature> features,
                   std::int64_t rows_count);

    std::int64_t get_row_count() const;
    std::int64_t get_column_count() const;
    std::int64_t get_table_type() const;
    const table_feature& get_feature(std::int64_t column_index) const;

protected:
    table_metadata(const detail::pimpl<detail::table_metadata_impl>& impl)
        : impl_(impl) {}

private:
    detail::pimpl<detail::table_metadata_impl> impl_;
};

class homogen_table_metadata : public table_metadata {
public:
    homogen_table_metadata();

    homogen_table_metadata(const table_feature&,
                           data_layout,
                           std::int64_t row_count,
                           std::int64_t column_count = 1);

    data_layout get_data_layout() const;
    homogen_table_metadata& set_data_layout(data_layout);

    const table_feature& get_feature_type() const;
    homogen_table_metadata& set_feature_type(const table_feature&);

    homogen_table_metadata& set_row_count(std::int64_t);
    homogen_table_metadata& set_column_count(std::int64_t);
};

} // namespace dal
