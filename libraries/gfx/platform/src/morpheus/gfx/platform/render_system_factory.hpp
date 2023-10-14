#pragma once

namespace morpheus::gfx
{

/// \class render_system_factory
///     The render system factory manages the available render systems for a target system.
///     Supported render systems can be queried and specfic type can be instantiated to
///     render visualalisation with.
class render_system_factory {
public:
    /// \name Life cycle
    ///@{
    /*!

     */
    render_system_factory();

    //! Destructor
    virtual ~render_system_factory();
    ///@}

private:
};

} // namespace morpheus::gfx
