#pragma once

#include "core/serialisation/directive.hpp"

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <span>
#include <string_view>
#include <string>
#include <variant>

namespace morpheus::serialisation
{

/// \class DirectiveReader
/// 
class DirectiveReader
{
public:
    static constexpr bool isTextual() { return false; }

    explicit DirectiveReader() = default;

    void beginComposite();
    void endComposite();
    void beginValue(std::string_view const key);
    void endValue();
    void beginSequence(std::optional<std::size_t> = std::nullopt);
    void endSequence();

    template<typename T> requires std::is_arithmetic_v<T, bool> or std::is_same_v<T, std::string>
    T read()
    {
        return T;
    }
    
    constexpr auto const& getLog() const noexcept { return mDirectiveLog; }
private:
    DirectiveLog mDirectiveLog;
};


}