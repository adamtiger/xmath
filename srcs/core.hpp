#ifndef __CORE__
#define __CORE__

// common includes
#include <iostream>
#include <random>

// function prefix
#if defined(_WIN64) && defined(EXPORT_DLL)
#define XMATH_API extern __declspec(dllexport);
#elif defined(__linux__) && defined(EXPORT_DLL)
#define XMATH_API extern;
# else
#define XMATH_API ;
#endif

// data types
using f64 = double;
using f32 = float;
using i64 = long long;
using i32 = int;
using i16 = short int;
using i8 = char;
using u64 = unsigned long long;
using u32 = unsigned int;
using u16 = unsigned short int;
using u8 = unsigned char;

static_assert(sizeof(f64) == 8, "f64 expected to be 8 bytes");
static_assert(sizeof(f32) == 4, "f32 expected to be 4 bytes");
static_assert(sizeof(i64) == 8, "i64 expected to be 8 bytes");
static_assert(sizeof(i32) == 4, "i32 expected to be 4 bytes");
static_assert(sizeof(i16) == 2, "i16 expected to be 2 bytes");
static_assert(sizeof(i8) == 1, "i8 expected to be 1 bytes");
static_assert(sizeof(u64) == 8, "u64 expected to be 8 bytes");
static_assert(sizeof(u32) == 4, "u32 expected to be 4 bytes");
static_assert(sizeof(u16) == 2, "u16 expected to be 2 bytes");
static_assert(sizeof(u8) == 1, "u8 expected to be 1 bytes");

// helper structures for alignment
struct alignas(64) f512 { f32 data[16]; };

// frequent contants
constexpr f32 C_LOG2_E = 1.44269504f;
constexpr f32 C_LN_2 = 0.69314718f;
constexpr i32 C_F32_BIAS = 127;

#endif  // __CORE__
