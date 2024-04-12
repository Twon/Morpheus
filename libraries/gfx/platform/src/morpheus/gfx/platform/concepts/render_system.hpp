#pragma once

#include "morpheus/core/meta/concepts/copyable.hpp"
#include "morpheus/gfx/platform/concepts/adapter.hpp"

namespace morpheus::gfx::concepts
{

/*! \concept render_system
        A render system provides an abstraction to a platform's graphics hardware.  Such hardware
        is typically accessed via an API which abstracts direct access to the hardare in user
        space within an application.  The render system is the top level abstraction of such an
        API and supports the creation of all graphics primitives needed to access the functionality
        of the hardware.
 */
template <typename T>
concept RenderSystem = requires(T t)
{
    typename T::Window;

//    requires !meta::Copyable<T>;
//    { t.adapters() } -> AdapterRange;

//    { t.beginFrame() } -> std::same_as<void>;
//    { t.endFrame() } -> std::same_as<void>;
};

} // namespace morpheus::gfx::concepts
