#pragma once

#include "morpheus/core/conformance/expected.hpp"
#include "morpheus/gfx/gl4/prerequisites.hpp"

#include <functional>
#include <memory>
#include <optional>
#include <string>

namespace morpheus::gfx::gl4::wgl
{

/// \class Context
///     The Context type stores all of the required Windows resources for the OpenGL context via rule of zero types.
class Context
{
public:
    /// Expected result type for the Context creation function.
    using Expected = conf::exp::expected<Context, std::string>;

    /// Creates a new OpenGL context using the global default device context.
    /// \param window The window to create the OpenGL context for.
    /// \param pfd The pixel format descriptor to use for the OpenGL context.
    /// \return Returns an expected containing the new OpenGL context or an error message.
    static Expected create(HWND const window, PIXELFORMATDESCRIPTOR const& pfd);

    Context(Context const&) = delete;
    Context& operator=(Context const&) = delete;

    Context(Context&&) = default;
    Context& operator=(Context&&) = default;

    Expected enable();
    void disable();

    /// Gets the current OpenGL device context handle.
    auto getDC() const noexcept { return mDeviceContext.get(); }

    /// Gets the current OpenGL context handle.
    auto getGL() const noexcept { return mGLContext.get(); }

private:
    /// Context initialised from the global default.
    Context();

    explicit Context(HWND const window, HDC const hdc, HGLRC const hglrc);

    /// \struct ReleaseResources
    ///     Allows std::unique_ptr handles to override the expect pointer type and to define a lambda to execute
    ///     clean-up.
    template <typename T>
    struct ReleaseResources
    {
        using pointer = T;
        std::function<void()> releaser;
        void operator()(pointer) { releaser(); }
    };

    /// \typedef ResourceWrapper
    ///     Defines a type for wrapping a resource an calling clean up.
    /// \note
    ///     Depending on the resource definition operator*() and operator->() may not make sense for the type and fail
    ///     to compile. In such cases default to using the get() method instead.
    template <typename T>
    using ResourceWrapper = std::unique_ptr<T, ReleaseResources<T>>;

    /// \typedef DeviceContext
    ///     Rule of zero managed device context.
    using DeviceContext = ResourceWrapper<HDC>;

    /// \typedef DeviceContext
    ///     Rule of zero managed OpenGL context.
    using GLContext = ResourceWrapper<HGLRC>;

    std::optional<HWND> mOwningWindow; /// Window owning the context.
    DeviceContext mDeviceContext;      /// The windows device context handle.
    GLContext mGLContext;              /// The OpenGL context handle.
};

} // namespace morpheus::gfx::gl4::wgl
