#pragma once

#include <wrl.h>
#include <dxgi1_6.h>
#include <core/platform.hpp>
#include <d3d12/adapters/video_mode_list.hpp>

namespace morpheus::gfx::d3d12
{

/*! \using DXGIAdapter
        A RAII wrapper for the IDXGIAdapter4 interface.
 */
using DXGIAdapter = Microsoft::WRL::ComPtr<IDXGIAdapter1>;


/*! \class adapter
        Describes an available graphic devices on the target platform.
 */
class adapter {
public:
    /// \name Life cycle
    ///@{
    /*! Constructs an adapter with the specified parameters.
        \param[in] dxgiAdapter
             The DXGI adapter object.
     */
    adapter(
        DXGIAdapter dxgiAdapter
    );
    ///@}

    //! The DXGI adapter interface.
    DXGIAdapter const& dxgi_adapter() const noexcept { return mDxgiAdapter; }

    //! The DXGI adapter description.
    DXGI_ADAPTER_DESC1 const& dxgi_description() const noexcept { return mDescription; }

private:
    /// \name Data Members
    ///@{
    //! The interface to the DXGI object.
    DXGIAdapter mDxgiAdapter;
    //! The DXGI adapter description.
    DXGI_ADAPTER_DESC1 mDescription;
    ///@}
};

} // namespace morpheus::gfx::d3d12
