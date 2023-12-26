#pragma once

#define ENABLE_ASSERTS
#ifdef ENABLE_ASSERTS
#define CORE_ASSERT(x, ...)                                                    \
    {                                                                          \
        if (!(x)) {                                                            \
            SD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);               \
        }                                                                      \
    }
#define ASSERT(x, ...)                                                         \
    {                                                                          \
        if (!(x)) {                                                            \
            SD_ERROR("Assertion Failed: {0}", __VA_ARGS__);                    \
        }                                                                      \
    }
#else
#define CORE_ASSERT(x, ...)
#define ASSERT(x, ...)
#endif
