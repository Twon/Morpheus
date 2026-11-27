#pragma once

#include <morpheus/gfx/platform/concepts/adapter.hpp>
#include <morpheus/gfx/platform/vendor.hpp>
#include <morpheus/gfx/platform/video_mode.hpp>

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace morpheus::gfx::metal
{

/// \class Adapter
///     Describes an available Metal graphics hardware device on the target platform.
class Adapter
{
public:
    /// Constructs an empty adapter.
    Adapter() = default;

    /// Constructs an adapter with device properties.
    /// \param[in] name
    ///     Device name (e.g. "Apple M5 Pro").
    /// \param[in] id
    ///     Unique registry ID for the device.
    /// \param[in] isLowPower
    ///     True if this device is low-power / integrated.
    /// \param[in] isRemovable
    ///     True if this device is an external eGPU.
    /// \param[in] memory
    ///     Recommended max working set size in bytes.
    Adapter(std::string name, std::uint64_t id, bool isLowPower, bool isRemovable, std::uint64_t memory);

    /// Access the adapter ID.
    [[nodiscard]] auto id() const noexcept -> std::uint64_t { return mId; }

    /// Access the adapter display name.
    [[nodiscard]] auto name() const noexcept -> std::string_view { return mName; }

    /// Access the hardware vendor.
    [[nodiscard]] auto vendor() const noexcept -> Vendor { return Vendor::Apple; }

    /// Check if the adapter is a low-power GPU.
    [[nodiscard]] auto isLowPower() const noexcept -> bool { return mIsLowPower; }

    /// Check if the adapter is an external removable GPU.
    [[nodiscard]] auto isRemovable() const noexcept -> bool { return mIsRemovable; }

    /// Get the maximum working set memory size in bytes.
    [[nodiscard]] auto memory() const noexcept -> std::uint64_t { return mMemory; }

    /// Query available video modes supported by the displays attached to this adapter.
    [[nodiscard]] auto getVideoModes() const -> std::vector<VideoMode>;

    [[nodiscard]] auto operator<=>(Adapter const& rhs) const noexcept = default;

private:
    struct Implementation;

    std::string mName = "Apple Metal Device";
    std::uint64_t mId = 0;
    bool mIsLowPower = false;
    bool mIsRemovable = false;
    std::uint64_t mMemory = 0;
};

using AdapterList = std::vector<Adapter>;

/// Enumerate all available Metal graphic adapters on the system.
/// \return List of detected Metal adapters.
[[nodiscard]] auto enumerateAdapters() -> std::vector<Adapter>;

} // namespace morpheus::gfx::metal
