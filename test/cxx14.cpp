#include <wise_enum.h>

#include <catch2/catch.hpp>
#include <type_traits>

WISE_ENUM_CLASS((Color, int64_t), (BLACK, 1), BLUE, RED)

enum class MoreColor
{
    RED,
    GREEN,
    OLIVE
};
WISE_ENUM_ADAPT(MoreColor, RED, GREEN);