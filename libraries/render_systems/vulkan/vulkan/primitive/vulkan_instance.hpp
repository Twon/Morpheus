#pragma once

#include <vulkan/vulkan_core.h>

#include <string>
#include <optional>
#include <vector>

namespace morpheus::gfx::vulkan::primitives
{
    /*! Queries the highest support version of Vulkan available on the target host
        \return
            Vulkan API version.
     */
    uint32_t get_highest_supported_instance_version();

    std::vector<VkLayerProperties> enumerate_instance_layer_properties();

    std::vector<VkExtensionProperties> enumerate_instance_extension_properties(const std::optional<std::string>& layer);

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

            //! Access the address of the underlying Vulkan structure.
            const VkApplicationInfo* operator&() const noexcept { return &mInfo; }

            //! Access the underlying Vulkan structure.
            explicit operator const VkApplicationInfo& () const noexcept { return mInfo; }

        private:
            std::string mName; //! The application name.
            VkApplicationInfo mInfo; //! The underlying Vulkan application structure.
        };

        class create_info {
        public:
            /*!

               \param[in] app_info
               \param[in] layers
             */
            create_info(
                const std::optional<std::vector<VkLayerProperties>>& layers = std::optional<std::vector<VkLayerProperties>>()
            ) noexcept;

            /*!

               \param[in] app_info
               \param[in] layers
             */
            create_info(
                const application_info& app_info,
                const std::optional<std::vector<VkLayerProperties>>& layers = std::optional<std::vector<VkLayerProperties>>()
            ) noexcept;


            //! Access the address of the underlying Vulkan structure.
            const VkInstanceCreateInfo* operator&() const noexcept { return &mInfo; }

            //! Access the underlying Vulkan structure.
            explicit operator const VkInstanceCreateInfo& () const noexcept { return mInfo; }

        private:
            std::vector<char const *> mLayerNames;
            VkInstanceCreateInfo mInfo; //! The underlying Vulkan create info structure.
        };

        instance(const create_info& info);
        ~instance();

        instance(const instance&)=delete;
        instance(instance&&)=delete;

        instance& operator=(const instance&)=delete;
        instance& operator=(instance&&)=delete;

    private:
        VkInstance mInstance;
    };

} // namespace morpheus::gfx::vulkan
