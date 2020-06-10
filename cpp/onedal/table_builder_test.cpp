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

#include "gtest/gtest.h"
#include "onedal/table_builder.hpp"
#include "onedal/accessor.hpp"

using namespace dal;

TEST(table_builder_test, can_modify_table) {
    float data[] = {
        1.f, 2.f,
        3.f, 4.f,
        5.f, 6.f
    };

    float data2[] = {
        1.f, 2.f,
        3.f, 4.f,
        -5.f, -6.f
    };

    table t = homogen_table { 3, 2, data };

    {
        table_builder b { std::move(t) };
        row_accessor<float> acc { b };

        auto arr = acc.pull({2, -1});
        ASSERT_EQ(arr.get_size(), 2);
        arr.unique();
        arr[0] = data2[2*2];
        arr[1] = data2[2*2+1];
        acc.push(arr, {2, -1});

        t = b.build();
    }

    row_accessor<const float> acc { t };
    auto arr = acc.pull();

    for(std::int64_t i = 0; i < arr.get_size(); i++) {
        ASSERT_FLOAT_EQ(arr.get_data()[i], data2[i]);
    }
}

TEST(homogen_table_builder_test, can_construct_table) {
    float data[] = {
        1.f, 2.f,
        3.f, 4.f,
        5.f, 6.f
    };

    auto t = homogen_table_builder(3, 2, data)
        .build();

    ASSERT_TRUE(t.has_data());
    ASSERT_EQ(3, t.get_row_count());
    ASSERT_EQ(2, t.get_column_count());

    auto meta = t.get_metadata();

    ASSERT_EQ(homogen_data_layout::row_major, meta.get_data_layout());

    for (std::int64_t i = 0; i < t.get_column_count(); i++) {
        ASSERT_EQ(data_type::float32, meta.get_feature(i).get_data_type());
        ASSERT_EQ(feature_type::ratio, meta.get_feature(i).get_type());
    }

    ASSERT_EQ(data, t.get_data<float>());
}
