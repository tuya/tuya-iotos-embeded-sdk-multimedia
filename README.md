[English](./README_en.md) | 简体中文

# Tuya嵌入式多媒体SDK


## 介绍
Tuya嵌入式多媒体SDK是在涂鸦IoTOS体系中针对具备音视频能力的嵌入式设备，如网络摄像机（IPC）、录像机（NVR/DVR）、可视门铃（doorbell）、摄像头灯（Floodlight）等推出的软件开发包。

## 下载IPC SDK

* **[Release Note](./release_note.md)**

Vendor | Chip| Toolchain| Gcc Version|Mainline| Longterm
---|---|---|---|---|---
NA | Linux X86 | linux-ubuntu-6.2.0_64Bit | 16.04 | [5.3.34](https://images.tuyacn.com/rms-static/210cf150-e318-11ed-80aa-ef6f378e8a54-1682392829157.rar?tyName=tuya_ipc_sdk_5.3.34_linux-ubuntu-6.2.0_64Bit.rar) | [4.11.0](https://images.tuyacn.com/rms-static/ae1d8f90-e274-11ed-80aa-ef6f378e8a54-1682322628361.tar.gz?tyName=tuya_ipc_sdk_4.11.0_linux-ubuntu-6.2.0_64Bit.tar.gz)
Realtek | RTS3903 | mips-linux-uclibc-gcc-4.8.5 | 4.8.5 | [5.3.34](https://images.tuyacn.com/rms-static/210c06f0-e318-11ed-ace1-c7bc07059f9e-1682392829151.rar?tyName=tuya_ipc_sdk_5.3.34_mips-linux-uclibc-gcc-4.8.5.rar) | [4.11.0](https://images.tuyacn.com/rms-static/ae1c5710-e274-11ed-ace1-c7bc07059f9e-1682322628353.tar.gz?tyName=tuya_ipc_sdk_4.11.0_mips-linux-uclibc-gcc-4.8.5.tar.gz)
Realtek | RTS3906 | rsdk-6.4.1-linux | 6.4.1 | [5.3.34](https://images.tuyacn.com/rms-static/210b6ab0-e318-11ed-ace1-c7bc07059f9e-1682392829147.rar?tyName=tuya_ipc_sdk_5.3.34_rsdk-6.4.1.rar) | [4.11.0](https://images.tuyacn.com/rms-static/ae1d4170-e274-11ed-ace1-c7bc07059f9e-1682322628359.tar.gz?tyName=tuya_ipc_sdk_4.11.0_rsdk-6.4.1-linux.tar.gz)
Realtek | RTS3903/3906 | rsdk-6.5.0 | 6.5.0 | [5.3.34](https://images.tuyacn.com/rms-static/210e50e0-e318-11ed-ace1-c7bc07059f9e-1682392829166.rar?tyName=tuya_ipc_sdk_5.3.34_rsdk-6.5.0.rar) | [4.11.0](https://images.tuyacn.com/rms-static/ae1d6880-e274-11ed-80aa-ef6f378e8a54-1682322628360.tar.gz?tyName=tuya_ipc_sdk_4.11.0_rsdk-6.5.0.tar.gz)
Anyka | AK3918/3916ev100 | arm-none-linux-4.4.1 | 4.4.1 | [5.3.34](https://images.tuyacn.com/rms-static/210f6250-e318-11ed-80aa-ef6f378e8a54-1682392829173.rar?tyName=tuya_ipc_sdk_5.3.34_arm-none-linux-4.4.1.rar) | [4.11.0](https://images.tuyacn.com/rms-static/ae1ccc40-e274-11ed-ace1-c7bc07059f9e-1682322628356.tar.gz?tyName=tuya_ipc_sdk_4.11.0_arm-none-linux-4.4.1.tar.gz)
Anyka | AK3918/3916ev200 | arm-anykav200-linux-uclibc-4.8.5 | 4.8.5 | [5.3.34](https://images.tuyacn.com/rms-static/210f3b40-e318-11ed-ace1-c7bc07059f9e-1682392829172.rar?tyName=tuya_ipc_sdk_5.3.34_arm-anykav200-linux-uclibc-4.8.5.rar) | [4.11.0](https://images.tuyacn.com/rms-static/ae1d6881-e274-11ed-80aa-ef6f378e8a54-1682322628360.tar.gz?tyName=tuya_ipc_sdk_4.11.0_arm-anykav200-linux-uclibc-4.8.5.tar.gz)
Anyka | AK3918 | arm-anykav500-linux-uclibcgnueabi-gcc-4.9.4 | 4.9.4 | [5.3.34](https://images.tuyacn.com/rms-static/210c2e00-e318-11ed-80aa-ef6f378e8a54-1682392829152.rar?tyName=tuya_ipc_sdk_5.3.34_arm-anykav500-linux-uclibcgnueabi-gcc-4.9.4.rar) | [4.11.0](https://images.tuyacn.com/rms-static/ae1c7e20-e274-11ed-80aa-ef6f378e8a54-1682322628354.tar.gz?tyName=tuya_ipc_sdk_4.11.0_arm-anykav500-linux-uclibcgnueabi-gcc-4.9.4.tar.gz)
Fullhan | FH8626V100 | arm-fullhanv2-linux-uclibcgnueabi-b2 | 5.5.0 | [5.3.34](https://images.tuyacn.com/rms-static/210c06f0-e318-11ed-80aa-ef6f378e8a54-1682392829151.rar?tyName=tuya_ipc_sdk_5.3.34_arm-fullhanv2-linux-uclibcgnueabi-b2.rar) | [4.11.0](https://images.tuyacn.com/rms-static/ae1e52e0-e274-11ed-80aa-ef6f378e8a54-1682322628366.tar.gz?tyName=tuya_ipc_sdk_4.11.0_arm-fullhanv2-linux-uclibcgnueabi-b2.tar.gz)
Fullhan | FH8626 | arm-fullhanv3-linux-uclibcgnueabi-b6.2 | 6.5.0 | [5.3.34](https://images.tuyacn.com/rms-static/210d1860-e318-11ed-80aa-ef6f378e8a54-1682392829158.rar?tyName=tuya_ipc_sdk_5.3.34_arm-fullhanv3-linux-uclibcgnueabi-b6.2.rar) | [4.11.0](https://images.tuyacn.com/rms-static/ae1e2bd0-e274-11ed-ace1-c7bc07059f9e-1682322628365.tar.gz?tyName=tuya_ipc_sdk_4.11.0_arm-fullhanv3-linux-uclibcgnueabi-b6.2.tar.gz)
Fullhan | FH8636 | arm-fullhanv3-linux-uclibcgnueabi-b6 | 6.5.0 | [5.3.34](https://images.tuyacn.com/rms-static/210e77f0-e318-11ed-ace1-c7bc07059f9e-1682392829167.rar?tyName=tuya_ipc_sdk_5.3.34_arm-fullhanv3-linux-uclibcgnueabi-b6.rar) | [4.11.0](https://images.tuyacn.com/rms-static/1dda7930-e3e0-11ed-80aa-ef6f378e8a54-1682478723139.tar.gz?tyName=tuya_ipc_sdk_4.11.0_arm-fullhanv3-linux-uclibcgnueabi-b6.tar.gz) 

* **[产测SDK](./dowload_fac.md)**

## 快速上手

* [涂鸦开发者平台创建产品](https://developer.tuya.com/cn/docs/iot/configure-in-platform/create-product/create-product?id=K914jp1ijtsfe) 获取 PID 信息([What's this?](https://github.com/tuya/tuya-iotos-embeded-sdk-multimedia/wiki/What-is#what-is-pid))<br> 
注：产品类型选择智能摄像机

* 获取 UUID&AUTHKEY 信息.([What's this?](https://github.com/tuya/tuya-iotos-embeded-sdk-multimedia/wiki/What-is#what-is-uuid--authkey))

* 使用Tuya [demo代码](https://github.com/tuya/tuya-iotos-embeded-multimedia-demo), 参考[快速上手说明](https://github.com/tuya/tuya-iotos-embeded-multimedia-demo#get-started)进行demo开发


## 技术支持

[开发者论坛](https://www.tuyaos.com/viewforum.php?f=14) <br>
[开发者中心](https://developer.tuya.com/cn/) <br>
[帮助中心](https://support.tuya.com/cn/help) <br>
[技术支持工单中心](https://iot.tuya.com/council/) 

## License
[MIT License](./LICENSE)