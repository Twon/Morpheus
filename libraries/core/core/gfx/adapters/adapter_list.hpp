#pragma once

#include <vector>
#include <core/platform.hpp>
#include <core/gfx/adapters/adapter.hpp>

#if defined (MORPHEUSCORE_COMPILER_IS_MSVC)
#pragma warning( push )  
#pragma warning( disable : 4251 ) // 'foo' needs to have dll-interface to be used by clients of class 'bar'
#endif

namespace morpheus::gfx
{

//template class MORPHEUSCORE_EXPORT std::allocator<adapter>;
//template class MORPHEUSCORE_EXPORT std::vector<adapter>;


/*! \class adapter_list


class MORPHEUSCORE_EXPORT adapter_list {
public:

    using adapter_container = std::vector<adapter>;

    using const_iterator = adapter_container::const_iterator;

    //! Destructor.
    virtual ~adapter_list() = default;

    adapter_list(const adapter_list& rhs) = delete;
    adapter_list& operator=(const adapter_list& rhs) = delete;

/*    class iterator {
    public:
        iterator() {}
//        iterator(const iterator&);
//        ~iterator();
//        iterator& operator=(const iterator&);
//        iterator& operator++(); //prefix increment
//        reference operator*() const;
//        friend void swap(iterator& lhs, iterator& rhs); //C++11 I think
    };

    //adapter_list() {}

    size_t size() const { return mAdapters.size(); };
    const_iterator begin() const { return mAdapters.begin(); }
    const_iterator end() const { return mAdapters.end(); }

protected:
    /// \name Life cycle
    ///@{
    /*! Constructs an adapter list from a container of adapters.
        \param[in] adapters
             A container of all availalbe adapters.
     
    adapter_list(adapter_container adapters);
    ///@}

private:
    /// \name Data Members
    ///@{
    //! The available adapters on the system.
    adapter_container mAdapters;
    ///@}
};
*/

} // namespace morpheus::gfx

#if (MORPHEUSCORE_COMPILER_IS_MSVC)
#pragma warning( pop )   
#endif