English | [简体中文](./README.md)

# Tuya Embedded SDK for Multimedia Devices

## Overview
Multimedia SDK is part of Tuya IoTOS and used to develop embedded devices, such as IP cameras (IPCs), network video recorders (NVRs), digital video recorders (DVRs), doorbells, and floodlights.

## Download
* **[Release Note](./release_note_en.md)**

Vendor | Chip| Toolchain| Gcc Version|Mainline| Longterm
---|---|---|---|---|---
NA | Linux X86 | linux-ubuntu-6.2.0_64Bit | 16.04 | [5.3.36](https://images.tuyacn.com/rms-static/3f7aa8c0-f070-11ed-8585-0943ff8b8030-1683860041036.rar?tyName=tuya_ipc_sdk_5.3.36_linux-ubuntu-6.2.0_64Bit.rar) | [4.11.2](https://images.tuyacn.com/rms-static/f7a99fe0-f067-11ed-8b07-418e300fdfb3-1683856484575.tar.gz?tyName=tuya_ipc_sdk_4.11.2_linux-ubuntu-6.2.0_64Bit.tar.gz)
Realtek | RTS3903 | mips-linux-uclibc-gcc-4.8.5 | 4.8.5 | [5.3.36](https://images.tuyacn.com/rms-static/3f779b80-f070-11ed-8b07-418e300fdfb3-1683860041016.rar?tyName=tuya_ipc_sdk_5.3.36_mips-linux-uclibc-gcc-4.8.5.rar) | [4.11.2](https://images.tuyacn.com/rms-static/f7ac10e0-f067-11ed-8585-0943ff8b8030-1683856484590.tar.gz?tyName=tuya_ipc_sdk_4.11.2_mips-linux-uclibc-gcc-4.8.5.tar.gz)
Realtek | RTS3906 | rsdk-6.4.1-linux | 6.4.1 | [5.3.36](https://images.tuyacn.com/rms-static/3f76b120-f070-11ed-8b07-418e300fdfb3-1683860041010.rar?tyName=tuya_ipc_sdk_5.3.36_rsdk-6.4.1.rar) | [4.11.2](https://images.tuyacn.com/rms-static/f7b3d910-f067-11ed-8585-0943ff8b8030-1683856484641.tar.gz?tyName=tuya_ipc_sdk_4.11.2_rsdk-6.4.1-linux.tar.gz)
Realtek | RTS3903/3906 | rsdk-6.5.0 | 6.5.0 | [5.3.36](https://images.tuyacn.com/rms-static/3f7a5aa0-f070-11ed-8585-0943ff8b8030-1683860041034.rar?tyName=tuya_ipc_sdk_5.3.36_rsdk-6.5.0.rar) | [4.11.2](https://images.tuyacn.com/rms-static/f7e74520-f067-11ed-8585-0943ff8b8030-1683856484978.tar.gz?tyName=tuya_ipc_sdk_4.11.2_rsdk-6.5.0.tar.gz)
Anyka | AK3918/3916ev100 | arm-none-linux-4.4.1 | 4.4.1 | [5.3.36](https://images.tuyacn.com/rms-static/3f768a10-f070-11ed-8b07-418e300fdfb3-1683860041009.rar?tyName=tuya_ipc_sdk_5.3.36_arm-none-linux-4.4.1.rar) | [4.11.2](https://images.tuyacn.com/rms-static/f7e6a8e0-f067-11ed-8b07-418e300fdfb3-1683856484974.tar.gz?tyName=tuya_ipc_sdk_4.11.2_arm-none-linux-4.4.1.tar.gz)
Anyka | AK3918/3916ev200 | arm-anykav200-linux-uclibc-4.8.5 | 4.8.5 | [5.3.36](https://images.tuyacn.com/rms-static/3f818690-f070-11ed-8b07-418e300fdfb3-1683860041081.rar?tyName=tuya_ipc_sdk_5.3.36_arm-anykav200-linux-uclibc-4.8.5.rar) | [4.11.2](https://images.tuyacn.com/rms-static/f7b3d911-f067-11ed-8585-0943ff8b8030-1683856484641.tar.gz?tyName=tuya_ipc_sdk_4.11.2_arm-anykav200-linux-uclibc-4.8.5.tar.gz)
Anyka | AK3918 | arm-anykav500-linux-uclibcgnueabi-gcc-4.9.4 | 4.9.4 | [5.3.36](https://images.tuyacn.com/rms-static/3f7b6c10-f070-11ed-8585-0943ff8b8030-1683860041041.rar?tyName=tuya_ipc_sdk_5.3.36_arm-anykav500-linux-uclibcgnueabi-gcc-4.9.4.rar) | [4.11.2](https://images.tuyacn.com/rms-static/f7abe9d0-f067-11ed-8585-0943ff8b8030-1683856484589.tar.gz?tyName=tuya_ipc_sdk_4.11.2_arm-anykav500-linux-uclibcgnueabi-gcc-4.9.4.tar.gz)
Fullhan | FH8626V100 | arm-fullhanv2-linux-uclibcgnueabi-b2 | 5.5.0 | [5.3.36](https://images.tuyacn.com/rms-static/3f7307a0-f070-11ed-8585-0943ff8b8030-1683860040986.rar?tyName=tuya_ipc_sdk_5.3.36_arm-fullhanv2-linux-uclibcgnueabi-b2.rar) | [4.11.2](https://images.tuyacn.com/rms-static/f7aad860-f067-11ed-8b07-418e300fdfb3-1683856484582.tar.gz?tyName=tuya_ipc_sdk_4.11.2_arm-fullhanv2-linux-uclibcgnueabi-b2.tar.gz)
Fullhan | FH8626 | arm-fullhanv3-linux-uclibcgnueabi-b6.2 | 6.5.0 | [5.3.36](https://images.tuyacn.com/rms-static/3f7a81b0-f070-11ed-8585-0943ff8b8030-1683860041035.rar?tyName=tuya_ipc_sdk_5.3.36_arm-fullhanv3-linux-uclibcgnueabi-b6.2.rar) | [4.11.2](https://images.tuyacn.com/rms-static/f7abc2c0-f067-11ed-8b07-418e300fdfb3-1683856484588.tar.gz?tyName=tuya_ipc_sdk_4.11.2_arm-fullhanv3-linux-uclibcgnueabi-b6.2.tar.gz)
Fullhan | FH8636 | arm-fullhanv3-linux-uclibcgnueabi-b6 | 6.5.0 | [5.3.36](https://images.tuyacn.com/rms-static/3f772650-f070-11ed-8b07-418e300fdfb3-1683860041013.rar?tyName=tuya_ipc_sdk_5.3.36_arm-fullhanv3-linux-uclibcgnueabi-b6.rar) | [4.11.2](https://images.tuyacn.com/rms-static/f7aad860-f067-11ed-8585-0943ff8b8030-1683856484582.tar.gz?tyName=tuya_ipc_sdk_4.11.2_arm-fullhanv3-linux-uclibcgnueabi-b6.tar.gz)

* **[Production SDK](./dowload_fac.md)**

## Get started

* [Create a product](https://developer.tuya.com/en/docs/iot/configure-in-platform/create-product/create-product?id=K914jp1ijtsfe) on the Tuya IoT Platform.<br>
**Note**: Select the \<Video Surveillance\> category and \<Smart Camera\> product, and specify \<Custom Solution\> as the plan. Get PID info. ([What's this?](https://github.com/tuya/tuya-iotos-embeded-sdk-multimedia/wiki/What-is#what-is-pid))

* Get free licenses for developing, including UUID&AUTHKEY. ([What's this?](https://github.com/tuya/tuya-iotos-embeded-sdk-multimedia/wiki/What-is#what-is-uuid--authkey))

* Clone [demo code](https://github.com/tuya/tuya-iotos-embeded-multimedia-demo). For more information, see [Get started](https://github.com/tuya/tuya-iotos-embeded-multimedia-demo#get-started).

## Support

[Tuya IoT Developer Forum](https://www.tuyaos.com/viewforum.php?f=14) <br>
[Tuya IoT Developer Platform](https://developer.tuya.com/cn/) <br>
[Tuya Smart Help Center](https://support.tuya.com/cn/help) <br>
[Technical Support Console](https://iot.tuya.com/council/) 

## License
[MIT License](./LICENSE)
