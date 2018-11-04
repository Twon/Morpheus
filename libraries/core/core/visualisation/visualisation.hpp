#pragma once

#include <core/platform.hpp>
#include <memory>

namespace morpheus::gfx
{
    class render_system;
}

namespace morpheus::vis
{

/*! \class visualisation
        The visualisation component acts as a facade encapsuating all rendering activities of a game.

 */
class MORPHEUSCORE_EXPORT visualisation {
public:
    virtual ~visualisation();

private:
    std::unique_ptr<gfx::render_system> mRenderSystem;
};

} // namespace morpheus::vis
