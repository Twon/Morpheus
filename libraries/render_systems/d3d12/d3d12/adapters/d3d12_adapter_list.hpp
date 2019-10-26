#pragma once


#include <core/gfx/adapters/adapter_list.hpp>
#include <wrl.h>
#include <dxgi1_6.h>

namespace morpheus::gfx::d3d12
{

/*! \using DXGIFactory
        A RAII wrapper for the IDXGIFactory4 interface.
 */
using DXGIFactory = Microsoft::WRL::ComPtr<IDXGIFactory4>;


/*! \class adapter_list

 */
class adapter_list : public morpheus::gfx::adapter_list {
public:

    /// \name Life cycle
    ///@{
    //! Constructs a d3d12 adapter list.
    adapter_list();
    ///@}

private:
    DXGIFactory mDxgiFactory;
};

} // namespace morpheus::gfx::d3d12
