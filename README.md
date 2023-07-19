[English](./README_en.md) | 简体中文

# Tuya嵌入式多媒体SDK


## 介绍
Tuya嵌入式多媒体SDK是在涂鸦IoTOS体系中针对具备音视频能力的嵌入式设备，如网络摄像机（IPC）、录像机（NVR/DVR）、可视门铃（doorbell）、摄像头灯（Floodlight）等推出的软件开发包。

## 下载IPC SDK

* **[Release Note](./release_note.md)**

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

* **[产测SDK](./dowload_fac.md)**

* 6.x系列的SDK发布，将统一通过涂鸦VS CODE Wind IDE插件发布，[跳转参考文档](https://developer.tuya.com/cn/docs/iot-device-dev/IPC-Product-Sofrware-Development-Kit?id=Kbfjuvhlyu2wr)。不同系列的版本差异如下：

 版本周期 | 版本号 | 版本说明 |
| --- | --- | --- |
| TuyaOS版本 | 6.x | 支持IPV6<br>支持蓝牙配网/AP配网时在APP端显示有效wifi列表<br>支持流媒体安全分级<br>支持新AI检测<br>升级Mbed TLS版本至3.1.0<br>升级CJSON版本至1.7.15<br>*即将发布：对Homekit的支持|
| 服务版本 | 5.3.36 | 能力更新迭代：<br>蓝牙配网<br>本地录像支持倍速回放、事件封面、录像删除<br>附属固件版本上报<br>自定义语音<br>4G iccid信息上报<br>设备主动取消呼叫<br>升级局域网通信安全等级<br>注：服务版本不再提供新功能迭代  |
| 维护版本 | 4.11.2 | 提供IPC产品的基础能力：<br>IOT平台接入<br>U-RTC实时视频传输<br>本地录像与回放<br>云存储录像<br>事件告警<br>门铃呼叫<br>注：维护版本除修复致命/严重Bug外，不再提供版本更新 |



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
