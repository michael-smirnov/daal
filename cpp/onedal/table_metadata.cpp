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

    virtual int64_t get_column_count() const = 0;
    virtual const table_feature& get_feature(int64_t column_index) const = 0;
};

class empty_metadata_impl : public table_metadata_impl {
public:
    int64_t get_column_count() const override {
        return 0;
    }

    const table_feature& get_feature(int64_t column_index) const {
        throw std::runtime_error("no columns in empty table");
    }
};

class simple_metadata_impl : public table_metadata_impl {
public:
    simple_metadata_impl(array<table_feature> features)
        : features_(features) {}

    int64_t get_column_count() const override {
        return features_.get_size();
    }

    const table_feature& get_feature(int64_t column_index) const override {
        return features_[column_index];
    }

private:
    array<table_feature> features_;
};

class homogen_table_metadata_impl : public table_metadata_impl {
public:
    homogen_table_metadata_impl()
        : col_count_(0) {}

    homogen_table_metadata_impl(const table_feature& feature,
                                homogen_data_layout layout,
                                std::int64_t column_count)
        : feature_(feature),
          layout_(layout),
          col_count_(column_count) {}

    homogen_data_layout get_data_layout() const {
        return layout_;
    }

    void set_data_layout(homogen_data_layout dl) {
        layout_ = dl;
    }

    int64_t get_column_count() const override {
        return col_count_;
    }

    void set_column_count(int64_t value) {
        col_count_ = value;
    }

    const table_feature& get_feature(int64_t column_index) const override {
        return this->get_feature();
    }

    const table_feature& get_feature() const {
        return feature_;
    }

    void set_feature(const table_feature& f) {
        feature_ = f;
    }

private:
    table_feature feature_;
    homogen_data_layout layout_;
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

table_metadata::table_metadata(const table_feature& feature,
                               int64_t column_count)
    : impl_(new detail::simple_metadata_impl {
        array<table_feature>(column_count, feature)
    }) {}

table_metadata::table_metadata(array<table_feature> features)
    : impl_(new detail::simple_metadata_impl {
        features
    }) {}

int64_t table_metadata::get_column_count() const {
    return impl_->get_column_count();
}

const table_feature& table_metadata::get_feature(int64_t column_index) const {
    return impl_->get_feature(column_index);
}

using hm_impl = detail::homogen_table_metadata_impl;

homogen_table_metadata::homogen_table_metadata()
    : table_metadata(detail::pimpl<detail::table_metadata_impl>{
        new detail::homogen_table_metadata_impl()
    }) {}

homogen_table_metadata::homogen_table_metadata(const table_feature& feature,
                                               homogen_data_layout layout,
                                               int64_t column_count)
    : table_metadata(detail::pimpl<detail::table_metadata_impl>{
        new detail::homogen_table_metadata_impl(feature, layout, column_count)
    }) {}

homogen_data_layout homogen_table_metadata::get_data_layout() const {
    auto& impl = detail::get_impl<hm_impl>(*this);
    return impl.get_data_layout();
}

homogen_table_metadata& homogen_table_metadata::set_data_layout(homogen_data_layout dl) {
    auto& impl = detail::get_impl<hm_impl>(*this);
    impl.set_data_layout(dl);
    return *this;
}

const table_feature& homogen_table_metadata::get_feature_type() const {
    auto& impl = detail::get_impl<hm_impl>(*this);
    return impl.get_feature();
}

homogen_table_metadata& homogen_table_metadata::set_feature_type(const table_feature& f) {
    auto& impl = detail::get_impl<hm_impl>(*this);
    impl.set_feature(f);
    return *this;
}

homogen_table_metadata& homogen_table_metadata::set_column_count(int64_t value) {
    auto& impl = detail::get_impl<hm_impl>(*this);
    impl.set_column_count(value);
    return *this;
}

} // namespace dal
