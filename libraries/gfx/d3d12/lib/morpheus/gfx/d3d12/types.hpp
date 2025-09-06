#pragma once

#include "morpheus/core/conformance/expected.hpp"
#include "morpheus/gfx/d3d12/prerequisites.hpp"

#include <d3d12.h>

#include <memory>

namespace morpheus::gfx::d3d12
{

struct ComDeleter
{
    template <typename T>
    void operator()(T* p) const noexcept
    {
        if (p)
        {
            p->Release();
        }
    }
};

/// \using DXGIExpected
///     An alias for an expected which take any value type, but returns an unexpected HRESULT type.
///
template <typename T>
using DXGIExpected = conf::exp::expected<T, HRESULT>;

/// \using DXGIFactory
///     A RAII wrapper for the IDXGIFactory6 interface.
using DXGIFactory = std::unique_ptr<IDXGIFactory6, ComDeleter>;

/// \using DXGIOutput
///     A RAII wrapper for the IDXGIOutput interface.
using DXGIOutput = std::unique_ptr<IDXGIOutput, ComDeleter>;

/*! \typedef DXGIAdapter
        A RAII wrapper for the IDXGIAdapter1 interface.
 */
using DXGIAdapter = std::unique_ptr<IDXGIAdapter1, ComDeleter>;

/// \using D3D12Device
///     A RAII wrapper for the ID3D12Device interface.
using D3D12Device = std::unique_ptr<ID3D12Device, ComDeleter>;

} // namespace morpheus::gfx::d3d12
