#include <morpheus/gfx/metal/adapter.hpp>

namespace morpheus::gfx::metal
{

struct Adapter::Implementation
{
//    implementation() = default;
};

Adapter::Adapter() = default;
Adapter::Adapter(Adapter&& rhs) noexcept = default;
Adapter::Adapter(Adapter const& rhs) = default;
Adapter& Adapter::operator=(Adapter&& rhs) noexcept = default;
Adapter& Adapter::operator=(Adapter const& rhs) = default;
Adapter::~Adapter() = default;

//---------------------------------------------------------------------------------------------------------------------

Adapter::Adapter(
    std::uint32_t const /*width*/,
    std::uint32_t const /*height*/,
    std::uint32_t const /*colourDepth*/
)
{
}

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus::gfx::metal
