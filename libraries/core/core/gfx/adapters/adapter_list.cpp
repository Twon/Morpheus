#include <core/gfx/adapters/adapter_list.hpp>

namespace morpheus::gfx
{

//---------------------------------------------------------------------------------------------------------------------

adapter_list::adapter_list(adapter_container adapters)
:   mAdapters(std::move(adapters))
{
}

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus::gfx
