#pragma once

#include <stdlib.h>

#define EXPECT(expr, msg) ASSERT(expr)

#define ASSERT_NOT_NULL(expr) ASSERT((expr) != NULL)
#define ASSERT_NEQ(expr1, expr2) ASSERT((expr1) != (expr2))
#define ASSERT(expr) do  {if (!(expr)) { __debugbreak(); __builtin_unreachable(); }} while(0)
