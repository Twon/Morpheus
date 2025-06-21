#pragma once

#include <morpheus/gfx/gl4/prerequisites.hpp>

namespace morpheus::gfx::gl4::xgl
{

/// \class Context
///     The context class represents a rendering context for the OpenGL 4.x API on Linux.
class Context {
public:
    explicit Context();
    explicit Context(Context const&) = delete;
    Context& operator=(Context const&) = delete;

    explicit Context(Context&&) noexcept = default;
    Context& operator=(Context&&) noexcept = default;

private:
};

} // namespace morpheus::gfx::gl4::xgl
