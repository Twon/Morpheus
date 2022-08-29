#include <metal/adapter.hpp>

namespace morpheus::gfx::metal
{

struct Adapter::Implementation
{
//    implementation() = default;
};

Adapter::Adapter() = default;
Adapter::Adapter(Adapter&& rhs) noexcept = default;
Adapter::Adapter(const Adapter& rhs) = default;
Adapter& Adapter::operator=(Adapter&& rhs) noexcept = default;
Adapter& Adapter::operator=(const Adapter& rhs) = default;
Adapter::~Adapter() = default;

//---------------------------------------------------------------------------------------------------------------------

Adapter::Adapter(
    const std::uint32_t width,
    const std::uint32_t height,
    const std::uint32_t colourDepth
)
{
}

//---------------------------------------------------------------------------------------------------------------------

} // namespace morpheus::gfx::metal
