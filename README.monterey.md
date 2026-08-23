# KWin VR for Oculus Quest 1 (Monterey)

This repository preserves KDE's draft KWin VR Mode work and carries the small,
reviewable changes needed for the Quest 1 postmarketOS port.

## Source and status

- Upstream project: <https://invent.kde.org/plasma/kwin>
- Upstream merge request: <https://invent.kde.org/plasma/kwin/-/merge_requests/8671>
- Branch: `oculus-vr-desktop`
- Imported revision: `ccdd46eadbd705c6ea2efb9c5de03e2fe5ec148a`
- Imported project version: `6.6.80`

The imported plugin provides floating Wayland windows, head-gaze input,
controller bindings, virtual screens, and a Qt Quick 3D XR scene. It requires
Qt Quick 3D XR and a working OpenXR runtime. The Monterey Monado fork now finds
the live headset and creates a two-view HMD from its SyncBoss IMU stream, but
its compositor cannot initialize Vulkan on the stock kernel. The plugin has
therefore not rendered on the headset and is not described as functional yet.

KWin is the VR compositor, not the base desktop. The Monterey session runs
labwc normally and starts this KWin build as a nested Wayland compositor only
when VR is requested. KWin listens for VR applications on `oculus-vr-0` while
its windowed backend connects to labwc's socket. The VR plugin remains inside
KWin because it depends on KWin-private scene, window, and input APIs; it is not
a plugin that labwc can load.

## Dependency versions

The plugin requires Qt 6.10.2 or newer; Qt 6.11 is preferred. Alpine edge has
Qt 6.11 with `Qt6Quick3DXr`, OpenXR, Monado, and KWin packages for aarch64.
The upstream VR author also maintains companion Qt Quick 3D and Xwayland
patches at <https://invent.kde.org/lightofmysoul/vr-patches>. Those patches
will be pinned in the postmarketOS package rather than copied without source
history.

## Monterey hardware boundary

The Quest 1 v50 downstream kernel exposes KGSL and the Android framebuffer,
not DRM/KMS; `CONFIG_DRM` is disabled and no `/dev/dri` render node exists.
The stock firmware contains the matching Qualcomm Adreno EGL, GLES, Vulkan,
gralloc, hardware-composer, and Oculus-composer libraries, but those modules
target Android/Bionic and cannot be loaded directly by Alpine/Musl. Those
proprietary files are never committed here. A working port needs an isolated
Android graphics compatibility process or a DRM/MSM kernel path before Monado
and Qt Quick 3D XR can present the VR scene.

A framebuffer/software-rendered desktop is useful as an early diagnostic, but
it cannot prove VR performance. The VR milestone requires stereo presentation,
OpenXR frame timing, and measured 72/90 Hz output on the headset.

## Repository scope

labwc owns the normal desktop. Nested KWin owns VR window composition and
interaction. Device-specific code belongs elsewhere:

- Monterey HMD, pose, and Touch action devices: Monado driver.
- SyncBoss/Pulsar pairing and reconnect: privileged controller bridge.
- Qualcomm Android graphics loading: device compatibility service.
- labwc session startup, nested-KWin launcher, refresh selector, and USB
  recovery: pmaports packages.

Keeping these boundaries separate makes upstream review possible and prevents
controller pairing data or proprietary firmware from entering this repository.
