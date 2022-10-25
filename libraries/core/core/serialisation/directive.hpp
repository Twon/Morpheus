#pragma once

#include <compare>
#include <variant>
#include <vector>

namespace morpheus::serialisation
{

using FundamentalValue = std::variant<bool, std::int8_t, std::uint8_t, std::int16_t, std::uint16_t, std::int32_t, std::uint32_t, std::int64_t, std::uint64_t, std::string>;

struct BeginValueDirective
{
    constexpr auto operator<=>(BeginValueDirective const&) const noexcept = default;
};

struct ValueDirective
{
    FundamentalValue value;
    constexpr auto operator<=>(ValueDirective const&) const noexcept = default;
};

struct EndValueDirective
{
    constexpr auto operator<=>(EndValueDirective const&) const noexcept = default;
};

struct BeginCompositeDirective
{
    constexpr auto operator<=>(BeginCompositeDirective const&) const noexcept = default;
};

struct EndCompositeDirective
{
    constexpr auto operator<=>(EndCompositeDirective const&) const noexcept = default;
};

struct BeginSequenceDirective
{
    constexpr auto operator<=>(BeginSequenceDirective const&) const noexcept = default;
};

struct EndSequenceDirective
{
    constexpr auto operator<=>(EndSequenceDirective const&) const noexcept = default;
};

struct BeginNullableDirective
{
    bool null = false;
    constexpr auto operator<=>(BeginNullableDirective const&) const noexcept = default;
};

struct EndNullableDirective
{
    constexpr auto operator<=>(EndNullableDirective const&) const noexcept = default;
};


/// \using Directive
/// 
using Directive = std::variant<
                    BeginValueDirective,
                    ValueDirective,
                    EndValueDirective,
                    BeginCompositeDirective,
                    EndCompositeDirective,
                    BeginSequenceDirective,
                    EndSequenceDirective,
                    BeginNullableDirective,
                    EndNullableDirective
                >;
    
/// \using DirectiveLog
///     
using DirectiveLog = std::vector<Directive>;


}