#pragma once

#include "core/serialisation/directive.hpp"

#include <cstddef>
#include <cstdint>
#include <ostream>
#include <optional>
#include <span>
#include <string_view>

namespace morpheus::serialisation
{

/// \class DirectiveWriter
///     Captures a serialisation directive log dictating the order of operations for a recorded stream of objects.
class DirectiveWriter
{
public:
    static constexpr bool isTextual() { return false; }

    explicit DirectiveWriter() = default;

    void beginComposite() { return mDirectiveLog.emplace_back( BeginCompositeDirective{} ); }
    void endComposite() { return mDirectiveLog.emplace_back( EndCompositeDirective{} ); }
    void beginValue(std::string_view const key) { return mDirectiveLog.emplace_back( BeginValueDirective{ key } ); }
    void endValue() { return mDirectiveLog.emplace_back( EndValueDirective{} ); }
    void beginSequence(std::optional<std::size_t> = std::nullopt) { return mDirectiveLog.emplace_back( BeginSequenceDirective{ value } ); }
    void endSequence() { return mDirectiveLog.emplace_back( EndSequenceDirective{} ); }
    void beginNullable(bool const null) { return mDirectiveLog.emplace_back( BeginNullableDirective{ null } ); }
    void endNullable() { return mDirectiveLog.emplace_back( EndNullableDirective{} ); }

    void write(auto const value) requires std::is_arithmetic_v<T> { return mDirectiveLog.emplace_back( ValueDirective{value} ); }
    void write(std::string_view const value) { return mDirectiveLog.emplace_back(ValueDirective{ std::string(value) }); }
//    void write(std::span<std::byte> const value);

    template <std::size_t N> void write(const char(&str)[N]) { write(std::string_view(str, N-1)); }

    constexpr auto const& getLog() const noexcept { return mDirectiveLog; }
private:
    DirectiveLog mDirectiveLog;
};


}