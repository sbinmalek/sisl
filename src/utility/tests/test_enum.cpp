//
// Created by Zimmerman, Bryan on 2020/12/21
//

#include <cstdint>
#include <iostream>
#include <string>
#include <type_traits>

#include <gtest/gtest.h>


#include "thread_buffer.hpp"
#include "utility/enum.hpp"

class EnumTest : public testing::Test {
public:
    EnumTest() = default;
    EnumTest(const EnumTest&) = delete;
    EnumTest(EnumTest&&) noexcept = delete;
    EnumTest& operator=(const EnumTest&) = delete;
    EnumTest& operator=(EnumTest&&) noexcept = delete;

    virtual ~EnumTest() override = default;

protected:
    void SetUp() override {}
    void TearDown() override {}
};

ENUM(signed_enum, int16_t, val1, val2)
TEST_F(EnumTest, enum_signed_test) {
    auto enum_lambda{[](const signed_enum& val) {
        switch (val) {
        case signed_enum::val1:
            return 1;
        case signed_enum::val2:
            return 2;
        default:
            return 0;
        };
    }};

    ASSERT_EQ(enum_lambda(signed_enum::val1), 1);
    ASSERT_EQ(enum_lambda(signed_enum::val2), 2);
    ASSERT_EQ(enum_name(signed_enum::val1), "val1");
    ASSERT_EQ(enum_name(signed_enum::val2), "val2");
}

ENUM(unsigned_enum, uint16_t, val1, val2)
TEST_F(EnumTest, enum_unsigned_test) {
    auto enum_lambda{[](const unsigned_enum& val) {
        switch (val) {
        case unsigned_enum::val1:
            return 1;
        case unsigned_enum::val2:
            return 2;
        default:
            return 0;
        };
    }};

    ASSERT_EQ(enum_lambda(unsigned_enum::val1), 1);
    ASSERT_EQ(enum_lambda(unsigned_enum::val2), 2);
    ASSERT_EQ(enum_name(unsigned_enum::val1), "val1");
    ASSERT_EQ(enum_name(unsigned_enum::val2), "val2");
}

ENUM(signed_enum_value, int16_t, val1=-10, val2=-20)
TEST_F(EnumTest, enum_signed_value_test) {
    auto enum_lambda{[](const signed_enum_value& val) {
        switch (val) {
        case signed_enum_value::val1:
            return static_cast< std::underlying_type_t< signed_enum_value > >(signed_enum_value::val1);
        case signed_enum_value::val2:
            return static_cast< std::underlying_type_t< signed_enum_value > >(signed_enum_value::val2);
        default:
            return std::underlying_type_t< signed_enum_value >{};
        };
    }};

    ASSERT_EQ(enum_lambda(signed_enum_value::val1), -10);
    ASSERT_EQ(enum_lambda(signed_enum_value::val2), -20);
    ASSERT_EQ(enum_name(signed_enum_value::val1), "val1");
    ASSERT_EQ(enum_name(signed_enum_value::val2), "val2");
}

ENUM(unsigned_enum_value, uint16_t, val1=10, val2=20)
TEST_F(EnumTest, enum_unsigned_value_test) {
    auto enum_lambda{[](const unsigned_enum_value& val) {
        switch (val) {
        case unsigned_enum_value::val1:
            return static_cast< std::underlying_type_t< unsigned_enum_value > >(unsigned_enum_value::val1);
        case unsigned_enum_value::val2:
            return static_cast< std::underlying_type_t< unsigned_enum_value > >(unsigned_enum_value::val2);
        default:
            return std::underlying_type_t< unsigned_enum_value >{};
        };
    }};

    ASSERT_EQ(enum_lambda(unsigned_enum_value::val1), 10);
    ASSERT_EQ(enum_lambda(unsigned_enum_value::val2), 20);
    ASSERT_EQ(enum_name(unsigned_enum_value::val1), "val1");
    ASSERT_EQ(enum_name(unsigned_enum_value::val2), "val2");
}

ENUM(signed_enum_mixed, int16_t, val1 = -10, val2)
TEST_F(EnumTest, enum_signed_mixed_test) {
    auto enum_lambda{[](const signed_enum_mixed& val) {
        switch (val) {
        case signed_enum_mixed::val1:
            return static_cast< std::underlying_type_t< signed_enum_mixed > >(signed_enum_mixed::val1);
        case signed_enum_mixed::val2:
            return static_cast< std::underlying_type_t< signed_enum_mixed > >(signed_enum_mixed::val2);
        default:
            return std::underlying_type_t< signed_enum_mixed >{};
        };
    }};

    ASSERT_EQ(enum_lambda(signed_enum_mixed::val1), -10);
    ASSERT_EQ(enum_lambda(signed_enum_mixed::val2), -9);
    ASSERT_EQ(enum_name(signed_enum_mixed::val1), "val1");
    ASSERT_EQ(enum_name(signed_enum_mixed::val2), "val2");
}

ENUM(unsigned_enum_mixed, uint16_t, val1 = 10, val2)
TEST_F(EnumTest, enum_unsigned_mixed_test) {
    auto enum_lambda{[](const unsigned_enum_mixed& val) {
        switch (val) {
        case unsigned_enum_mixed::val1:
            return static_cast< std::underlying_type_t< unsigned_enum_mixed > >(unsigned_enum_mixed::val1);
        case unsigned_enum_mixed::val2:
            return static_cast< std::underlying_type_t< unsigned_enum_mixed > >(unsigned_enum_mixed::val2);
        default:
            return std::underlying_type_t< unsigned_enum_mixed >{};
        };
    }};

    ASSERT_EQ(enum_lambda(unsigned_enum_mixed::val1), 10);
    ASSERT_EQ(enum_lambda(unsigned_enum_mixed::val2), 11);
    ASSERT_EQ(enum_name(unsigned_enum_mixed::val1), "val1");
    ASSERT_EQ(enum_name(unsigned_enum_mixed::val2), "val2");
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}