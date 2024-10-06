#pragma once

#include <morpheus/gfx/d3d12/prerequisites.hpp>
#include <morpheus/gfx/d3d12/video_mode_list.hpp>
#include <morpheus/core/base/platform.hpp>
#include <morpheus/core/concurrency/generator.hpp>
#include <morpheus/gfx/platform/adapter.hpp>
#include <morpheus/gfx/platform/vendor.hpp>

#include <string_view>

namespace morpheus::gfx::d3d12
{

/*! \typedef DXGIAdapter
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

    /// Default construction an empty adapter.
    constexpr Adapter() noexcept = default;
    /// Constructs an adapter with the specified parameters.
    /// \param[in] dxgiAdapter The DXGI adapter object.
    Adapter(DXGIAdapter dxgiAdapter);

    ///@}

    /// The DXGI adapter interface.
    [[nodiscard]] DXGIAdapter const& dxgiAdapter() const noexcept { return mDxgiAdapter; }

    /// The DXGI adapter description.
    [[nodiscard]] DXGI_ADAPTER_DESC1 const& dxgDescription() const noexcept { return mDescription; }

    /// \copydoc morpheus::gfx::Adapter::id()
    [[nodiscard]] auto id() const noexcept { return mDescription.DeviceId; }

    /// \copydoc morpheus::gfx::Adapter::name()
    [[nodiscard]] std::wstring_view name() const noexcept { return mDescription.Description; }

    /// \copydoc morpheus::gfx::Adapter::vendor()
    [[nodiscard]] Vendor vendor() const noexcept;

    /// \copydoc morpheus::gfx::Adapter::operator<=>()
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
