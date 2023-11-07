#pragma once

#if defined(MULTIFLOWLIBRARY_LIBRARY)
#  define ML_PUBLIC __declspec(dllexport)
#else
#  define ML_PUBLIC __declspec(dllimport)
#endif

#define ML_PRIVATE
