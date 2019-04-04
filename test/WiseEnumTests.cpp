#include <wise_enum.h>

#include <boost/optional.hpp>
#include <gtest/gtest.h>

WISE_ENUM(Color, (RED, -1), GREEN, (OLIVE, 5))
WISE_ENUM_CLASS(ColorClass, (RED, -1), GREEN, (OLIVE, 5))
struct ColorAggregator {
    WISE_ENUM_MEMBER(Color, (RED, -1), GREEN, (OLIVE, 5))
    WISE_ENUM_CLASS_MEMBER(ColorClass, (RED, -1), GREEN, (OLIVE, 5))
};

enum class ColorClassAdapted
{
    RED = -1,
    GREEN,
    OLIVE = 5
};
WISE_ENUM_ADAPT(ColorClassAdapted, RED, GREEN, OLIVE);

enum class ColorAdapted
{
    RED = -1,
    GREEN,
    OLIVE = 5
};
WISE_ENUM_ADAPT(ColorAdapted, RED, GREEN, OLIVE);

template <typename T>
class WiseEnumTest : public ::testing::Test {
public:
    using EnumType = T;
};

using MyTypes = ::testing::Types<Color, ColorClass, ColorAggregator::Color,  ColorAggregator::ColorClass, ColorAdapted, ColorClassAdapted>;
TYPED_TEST_CASE(WiseEnumTest, MyTypes);

TYPED_TEST(WiseEnumTest, FromNumberCreation) {
    using EnumType = typename TestFixture::EnumType;
    ASSERT_EQ(wise_enum::from_number<EnumType>(-1), EnumType::RED);
    ASSERT_EQ(wise_enum::from_number<EnumType>(0), EnumType::GREEN);
    ASSERT_EQ(wise_enum::from_number<EnumType>(5), EnumType::OLIVE);
}

TYPED_TEST(WiseEnumTest, FromStringCreation) {
    using EnumType = typename TestFixture::EnumType;
    ASSERT_EQ(wise_enum::from_string<EnumType>("RED"), EnumType::RED);
    ASSERT_EQ(wise_enum::from_string<EnumType>("GREEN"), EnumType::GREEN);
    ASSERT_EQ(wise_enum::from_string<EnumType>("OLIVE"), EnumType::OLIVE);
}

TYPED_TEST(WiseEnumTest, FromStandardStringCreation) {
    using EnumType = typename TestFixture::EnumType;
    const std::string RED = "RED";
    ASSERT_EQ(wise_enum::from_string<EnumType>(RED), EnumType::RED);
}

TYPED_TEST(WiseEnumTest, ToString) {
    using EnumType = typename TestFixture::EnumType;
    ASSERT_EQ(wise_enum::to_string(EnumType::RED), "RED");
    ASSERT_EQ(wise_enum::to_string(EnumType::GREEN), "GREEN");
    ASSERT_EQ(wise_enum::to_string(EnumType::OLIVE), "OLIVE");
}


TYPED_TEST(WiseEnumTest, TestOstreamOperator) {
    using EnumType = typename TestFixture::EnumType;
    std::ostringstream stream;
    stream << EnumType::RED << " " << EnumType::GREEN << " " << EnumType::OLIVE;
    ASSERT_EQ(stream.str(), "RED(-1) GREEN(0) OLIVE(5)");
}