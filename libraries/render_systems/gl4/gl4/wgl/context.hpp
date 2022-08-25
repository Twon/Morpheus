#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <optional>

namespace morpheus::gfx::gl4::wgl
{

/// \class Context
///     
class Context 
{
public:
    explicit Context(HWND const window, PIXELFORMATDESCRIPTOR const& pfd);
    ~Context();

    Context(Context const&) = delete;
    Context& operator=(Context const&) = delete;

    Context(Context&&) noexcept = default;
    Context& operator=(Context&&) noexcept = default;

    Context enable();
    void disable();

    auto getDC() const noexcept { return mDeviceContext; }
    auto getGL() const noexcept { return mGLContext; }
private:
    /// Context initialised from the global default.
    Context();

    std::optional<HWND> mOwningWindow; /// Window owning the context
    HDC mDeviceContext; /// The windows device context handle.
    HGLRC mGLContext; /// The OpenGL context handle.
    bool mOwningContext; /// Does the context require destorying.
};


} // namespace morpheus::gfx::gl4::wgl
