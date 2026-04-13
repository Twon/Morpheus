#pragma once

#include <cstddef>
#include <cstdint>
#include <gmock/gmock.h>
#include <optional>
#include <span>
#include <string>
#include <string_view>
#include <vector>

namespace morpheus::gfx::platform::mock
{

/// \class RenderSystem
///     Provides a mocks adhering to the concept morpheus::gfx::platform::concepts::RenderSystem.
class RenderSystem
{
public:
    /// \defgroup MockFunctions Mock Functions
    ///@{
    /// \copydoc morpheus::gfx::concepts::RenderSystem::beginFrame()
    MOCK_METHOD(void, beginFrame, (), ());

    /// \copydoc morpheus::gfx::concepts::RenderSystem::endFrame()
    MOCK_METHOD(void, endFrame, (), ());
    ///@}
};

} // namespace morpheus::gfx::platform::mock
