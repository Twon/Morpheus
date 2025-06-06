#pragma once

#include <catch2/catch_all.hpp>

#include <optional>

namespace Catch {
template <typename T>
struct StringMaker<std::optional<T>> {
    static auto convert(std::optional<T> const& o) -> std::string {
        ReusableStringStream rss;
        if (o) {
            rss << "Some(" << Detail::stringify(*o) << ')';
        } else {
            rss << "None";
        }
        return rss.str();
    }
};
}