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

#include "onedal/table_metadata.hpp"

using std::int64_t;

namespace dal {
namespace detail {

struct table_feature_impl {
    data_type dtype;
    feature_type ftype;

    table_feature_impl(data_type dt, feature_type ft)
        : dtype(dt),
          ftype(ft) {}
};

class table_metadata_impl {
public:
    virtual ~table_metadata_impl() {}

    virtual int64_t get_table_type() const = 0;
    virtual int64_t get_row_count() const = 0;
    virtual int64_t get_column_count() const = 0;
    virtual const table_feature& get_feature(int64_t column_index) const = 0;
};

class empty_metadata_impl : public table_metadata_impl {
public:
    int64_t get_table_type() const override {
        return table_type::empty;
    }

    int64_t get_row_count() const override {
        return 0;
    }

    int64_t get_column_count() const override {
        return 0;
    }

    const table_feature& get_feature(int64_t column_index) const {
        throw std::runtime_error("no columns in empty table");
    }
};

class simple_metadata_impl : public table_metadata_impl {
public:
    simple_metadata_impl(int64_t table_type,
                         array<table_feature> features,
                         int64_t row_count)
        : table_type_(table_type),
          features_(features),
          row_count_(row_count) {}

    int64_t get_table_type() const override {
        return table_type_;
    }

    int64_t get_row_count() const override {
        return row_count_;
    }

    int64_t get_column_count() const override {
        return features_.get_size();
    }

    const table_feature& get_feature(int64_t column_index) const override {
        return features_[column_index];
    }

private:
    int64_t table_type_;
    array<table_feature> features_;
    int64_t row_count_;
};

class homogen_table_metadata_impl : public table_metadata_impl {
public:
    homogen_table_metadata_impl()
        : row_count_(0),
          col_count_(0) {}

    homogen_table_metadata_impl(const table_feature& feature,
                                data_layout& layout,
                                std::int64_t row_count,
                                std::int64_t column_count)
        : feature_(feature),
          layout_(layout),
          row_count_(row_count),
          col_count_(column_count) {}

    data_layout get_data_layout() const {
        return layout_;
    }

    int64_t get_table_type() const override {
        return table_type::homogen;
    }

    int64_t get_row_count() const override {
        return row_count_;
    }

    int64_t get_column_count() const override {
        return col_count_;
    }

    const table_feature& get_feature(int64_t column_index) const override {
        return feature_;
    }

private:
    table_feature feature_;
    data_layout layout_;
    int64_t row_count_;
    int64_t col_count_;
};

} // namespace detail

table_feature::table_feature()
    : table_feature(data_type::float32) {}

table_feature::table_feature(data_type dtype)
    : table_feature(dtype,
                    is_floating_point(dtype) ? feature_type::ratio
                                             : feature_type::ordinal) {}

table_feature::table_feature(data_type dtype, feature_type ftype)
    : impl_(new detail::table_feature_impl{ dtype, ftype }) {}

data_type table_feature::get_data_type() const {
    return impl_->dtype;
}

table_feature& table_feature::set_data_type(data_type dt) {
    impl_->dtype = dt;
    return *this;
}

feature_type table_feature::get_type() const {
    return impl_->ftype;
}

table_feature& table_feature::set_type(feature_type ft) {
    impl_->ftype = ft;
    return *this;
}

table_metadata::table_metadata()
    : impl_(new detail::empty_metadata_impl()) {}

table_metadata::table_metadata(int64_t table_type,
                               const table_feature& feature,
                               int64_t row_count,
                               int64_t column_count)
    : impl_(new detail::simple_metadata_impl {
        table_type,
        array<table_feature>(column_count, feature),
        row_count
    }) {}

table_metadata::table_metadata(int64_t table_type,
                               array<table_feature> features,
                               int64_t row_count)
    : impl_(new detail::simple_metadata_impl {
        table_type,
        features,
        row_count
    }) {}

int64_t table_metadata::get_row_count() const {
    return impl_->get_row_count();
}

int64_t table_metadata::get_column_count() const {
    return impl_->get_column_count();
}

int64_t table_metadata::get_table_type() const {
    return impl_->get_table_type();
}

const table_feature& table_metadata::get_feature(int64_t column_index) const {
    return impl_->get_feature(column_index);
}

homogen_table_metadata::homogen_table_metadata()
    : table_metadata() {}

homogen_table_metadata::homogen_table_metadata(const table_feature& feature,
                                               data_layout layout,
                                               int64_t row_count,
                                               int64_t column_count)
    : table_metadata(detail::pimpl<detail::table_metadata_impl>{
        new detail::homogen_table_metadata_impl(feature, layout, row_count, column_count)
    }) {}

data_layout homogen_table_metadata::get_data_layout() const {
    auto& impl = detail::get_impl<detail::homogen_table_metadata_impl>(*this);
    return impl.get_data_layout();
}

} // namespace dal
