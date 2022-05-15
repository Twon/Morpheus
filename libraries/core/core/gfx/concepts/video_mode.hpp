#pragma once


namespace morpheus::gfx::concepts
{

template <typename T>
concept VideoMode = requires(T t)
{
    { t.width() } -> std::same_as<std::uint32_t>;
    { t.height() } -> std::same_as<std::uint32_t>;
    { t.colour_depth() } -> std::same_as<std::uint32_t>;
};

template <typename T>
concept VideoModeRange = requires(T t)
{
};

} // namespace morpheus::gfx::concepts
