// Copyright 2018 yuzu emulator team
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include "common/assert.h"
#include "common/logging/log.h"
#include "core/core.h"
#include "core/hle/service/nvdrv/devices/nvdisp_disp0.h"
#include "core/hle/service/nvdrv/devices/nvmap.h"
#include "video_core/renderer_base.h"
#include "video_core/video_core.h"

namespace Service {
namespace Nvidia {
namespace Devices {

u32 nvdisp_disp0::ioctl(Ioctl command, const std::vector<u8>& input, std::vector<u8>& output) {
    UNIMPLEMENTED();
    return 0;
}

void nvdisp_disp0::flip(u32 buffer_handle, u32 offset, u32 format, u32 width, u32 height,
                        u32 stride, NVFlinger::BufferQueue::BufferTransformFlags transform) {
    VAddr addr = nvmap_dev->GetObjectAddress(buffer_handle);
    LOG_WARNING(Service,
                "Drawing from address %lx offset %08X Width %u Height %u Stride %u Format %u", addr,
                offset, width, height, stride, format);

    using PixelFormat = Tegra::FramebufferConfig::PixelFormat;
    const Tegra::FramebufferConfig framebuffer{
        addr, offset, width, height, stride, static_cast<PixelFormat>(format), transform};

    Core::System::GetInstance().perf_stats.EndGameFrame();

    VideoCore::g_renderer->SwapBuffers(framebuffer);
}

} // namespace Devices
} // namespace Nvidia
} // namespace Service
