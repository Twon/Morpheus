#pragma once

#include <d3d12/prerequisites.hpp>
#include <d3d12/video_mode_list.hpp>
#include <core/base/platform.hpp>
#include <core/concurrency/generator.hpp>
#include <core/gfx/adapter.hpp>
#include <core/gfx/vendor.hpp>

#include <string_view>

namespace morpheus::gfx::d3d12
{

/*! \using DXGIAdapter
        A RAII wrapper for the IDXGIAdapter4 interface.
 */
using DXGIAdapter = Microsoft::WRL::ComPtr<IDXGIAdapter1>;


/// \class adapter
///     Describes an available graphic devices on the target platform.
///
class Adapter {
public:
    /// \name Life cycle
    ///@{
    // Constructs an adapter with the specified parameters.
    //    \param[in] dxgiAdapter The DXGI adapter object.
    constexpr Adapter() noexcept = default;
    Adapter(DXGIAdapter dxgiAdapter);
    ///@}

    //! The DXGI adapter interface.
    [[nodiscard]] DXGIAdapter const& dxgiAdapter() const noexcept { return mDxgiAdapter; }

    //! The DXGI adapter description.
    [[nodiscard]] DXGI_ADAPTER_DESC1 const& dxgDescription() const noexcept { return mDescription; }

    [[nodiscard]] auto getId() const noexcept { return mDescription.DeviceId; }
    [[nodiscard]] std::wstring_view getName() const noexcept { return mDescription.Description; }
    [[nodiscard]] Vendor getVendor() const noexcept;
    [[nodiscard]] constexpr auto operator<=>(Adapter const& rhs) const noexcept = default;
private:
    /// \name Data Members
    ///@{
    //! The interface to the DXGI object.
    DXGIAdapter mDxgiAdapter;
    //! The DXGI adapter description.
    DXGI_ADAPTER_DESC1 mDescription = {};
    ///@}
};

concurrency::Generator<Adapter> enumerateAdapters();

} // namespace morpheus::gfx::d3d12
