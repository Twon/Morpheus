#pragma once

#include <core/base/assert.hpp>

/// \def MORPHEUS_VERIFY
///     Helper macro to verify an expression succeeds.
/// \param[in] expr
///     Expression to verify
#define MORPHEUS_VERIFY(expr) \
    MORPHEUS_ASSERT_HANDLER(AssertType::Verify, expr, {})

/// \def MORPHEUS_VERIFY_MSG
///     Helper macro to verify an expression succeeds and print a message on failure.
/// \param[in] expr
///     Expression to verify
/// \param[in] msg
///     Message to print on error.
#define MORPHEUS_VERIFY_MSG(expr, msg) \
    MORPHEUS_ASSERT_HANDLER(AssertType::Verify, expr, (msg))
