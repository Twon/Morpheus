#pragma once

#include "morpheus/core/conformance/expected.hpp"
#include "morpheus/gfx/d3d12/prerequisites.hpp"

#include <d3d12.h>

#include <wrl/client.h>

namespace morpheus::gfx::d3d12
{

/// \using DXGIExpected
///     An alias for an expected which take any value type, but returns an unexpected HRESULT type.
///
template <typename T>
using DXGIExpected = exp_ns::expected<T, HRESULT>;

/// \using DXGIFactory
///     A RAII wrapper for the IDXGIFactory6 interface.
using DXGIFactory = Microsoft::WRL::ComPtr<IDXGIFactory6>;

/// \using DXGIOutput
///     A RAII wrapper for the IDXGIOutput interface.
using DXGIOutput = Microsoft::WRL::ComPtr<IDXGIOutput>;

/*! \typedef DXGIAdapter
        A RAII wrapper for the IDXGIAdapter1 interface.
 */
using DXGIAdapter = Microsoft::WRL::ComPtr<IDXGIAdapter1>;

/// \using D3D12Device
///     A RAII wrapper for the ID3D12Device interface.
using D3D12Device = Microsoft::WRL::ComPtr<ID3D12Device>;

} // namespace morpheus::gfx::d3d12
