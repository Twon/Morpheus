#ifndef MORPHEUS_VULKAN_INSTANCE_HPP
#define MORPHEUS_VULKAN_INSTANCE_HPP

#include <vulkan/vulkan.h>
#include <string>

namespace morpheus::gfx::vulkan::primitives
{
    uint32_t get_highest_supported_instance_version();


    /*! \class instance
            A video mode describes a mode of available settings for an graphics adapter.
     */
    class instance {
    public:

        class application_info {
        public:
            /*!
                \param[in] name
                    The application name
             */
            application_info(std::string name) noexcept;
            explicit operator const VkApplicationInfo& () const noexcept { return mInfo; }

        private:
            std::string mName;
            VkApplicationInfo mInfo;
        };

        class create_info {
        public:
            create_info() noexcept;
            explicit operator const VkInstanceCreateInfo& () const noexcept { return mInfo; }

        private:
            VkInstanceCreateInfo mInfo;
        };
    private:

    };

} // namespace morpheus::gfx::vulkan


#endif //MORPHEUS_VULKAN_INSTANCE_HPP
