#pragma once

// 如果是 MSVC 编译器，使用 __declspec
#if defined(_MSC_VER)
    #if defined(MULTIFLOWLIBRARY_LIBRARY)
    #  define ML_PUBLIC __declspec(dllexport)
    #else
    #  define ML_PUBLIC __declspec(dllimport)
    #endif
// 否则，如果是 GCC 或 Clang 编译器，使用 __attribute__
#elif defined(__GNUC__) || defined(__clang__)
    #define ML_PUBLIC __attribute__((visibility("default")))
    #define ML_PRIVATE __attribute__((visibility("hidden")))
#else
    #define ML_PUBLIC
    #define ML_PRIVATE
#endif
