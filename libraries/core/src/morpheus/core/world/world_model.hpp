#pragma once

#include "morpheus/core/base/platform.hpp"

namespace morpheus::world
{

/*! \class world_model
        The world model is the component of the game abstracting the representation of the game
        world.
 */
class MORPHEUSCORE_EXPORT world_model {
public:
    virtual ~world_model() noexcept;

private:
};

} // namespace morpheus::world
