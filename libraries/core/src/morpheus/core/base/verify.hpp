#pragma once

#include <morpheus/core/base/assert_handler.hpp>

#define MORPHEUS_VERIFY_HANDLER(type, expr, msg)                                                                                                               \
    do {                                                                                                                                                       \
        if ((!static_cast<bool>(expr))) [[unlikely]]                                                                                                           \
            assertHandler(type, MORPHEUS_CURRENT_LOCATION, #expr, msg);                                                                                        \
    }                                                                                                                                                          \
    while (0)

/// \def MORPHEUS_VERIFY
///     Helper macro to verify an expression succeeds.
/// \param[in] expr
///     Expression to verify
#define MORPHEUS_VERIFY(expr)          MORPHEUS_VERIFY_HANDLER(AssertType::Verify, expr, {})

/// \def MORPHEUS_VERIFY_MSG
///     Helper macro to verify an expression succeeds and print a message on failure.
/// \param[in] expr
///     Expression to verify
/// \param[in] msg
///     Message to print on error.
#define MORPHEUS_VERIFY_MSG(expr, msg) MORPHEUS_VERIFY_HANDLER(AssertType::Verify, expr, (msg))
