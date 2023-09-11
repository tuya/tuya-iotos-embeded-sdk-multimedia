[English](./README_en.md) | 简体中文

# Tuya嵌入式多媒体SDK


## 介绍
Tuya嵌入式多媒体SDK是在涂鸦IoTOS体系中针对具备音视频能力的嵌入式设备，如网络摄像机（IPC）、录像机（NVR/DVR）、可视门铃（doorbell）、摄像头灯（Floodlight）等推出的软件开发包。

## 下载IPC SDK

* 6.x系列的SDK发布，将统一通过涂鸦VS Code Wind IDE插件发布，[跳转参考文档](https://developer.tuya.com/cn/docs/iot-device-dev/TuyaOS-Overview?id=Kbfjtwjcpn1gc)。不同系列的版本差异如下：

 SDK版本周期 | SDK版本系列 | 版本说明 |
| --- | --- | --- |
| 全新TuyaOS版本 | 6.x | 支持IPV6<br>支持蓝牙配网/AP配网时在APP端显示有效wifi列表<br>支持高倍速8x 16x 32x回放<br>支持缩时录像（延时摄影）<br>支持流媒体安全分级<br>支持端云结合动态调度算法仓的AI检测<br>升级Mbed TLS版本至3.1.0<br>升级CJSON版本至1.7.15<br>即将发布：支持Homekit<br>即将发布：支持双向视频通话|
| 服务版本 | 5.x | 最新版本5.3.38。相比4.x系列新增：<br>蓝牙配网<br>本地录像支持倍速回放、事件封面、录像删除<br>附属固件版本上报<br>自定义语音<br>4G iccid等信息上报<br>设备主动取消呼叫<br>升级局域网通信安全等级<br>注：服务版本不再提供新功能迭代  |
| 维护版本 | 4.x | 最新版本4.11.2。提供IPC产品的基础能力：<br>IOT平台接入<br>U-RTC实时视频传输<br>本地录像与回放<br>云存储录像<br>事件告警<br>门铃呼叫<br>注：维护版本除修复致命/严重Bug外，不再提供版本更新 |

* **[Release Note](./release_note.md)**

厂商 | 芯片型号| Toolchain | 服务版本下载 | 维护版本下载
---|---|---|---|---
NA | Linux X86 | linux-ubuntu-6.2.0_64Bit | [5.3.40](https://images.tuyacn.com/rms-static/fc43be60-5083-11ee-b879-5585a458b469-1694423829830.rar?tyName=5.3.40_linux-ubuntu-6.2.0_64Bit.rar) | [4.11.2](https://images.tuyacn.com/rms-static/f7a99fe0-f067-11ed-8b07-418e300fdfb3-1683856484575.tar.gz?tyName=tuya_ipc_sdk_4.11.2_linux-ubuntu-6.2.0_64Bit.tar.gz)
Realtek | RTS3903 | mips-linux-uclibc-gcc-4.8.5 | [5.3.40](https://images.tuyacn.com/rms-static/1da28780-5084-11ee-beb1-377a1535f238-1694423885816.rar?tyName=5.3.40_mips-linux-uclibc-gcc-4.8.5.rar) | [4.11.2](https://images.tuyacn.com/rms-static/f7ac10e0-f067-11ed-8585-0943ff8b8030-1683856484590.tar.gz?tyName=tuya_ipc_sdk_4.11.2_mips-linux-uclibc-gcc-4.8.5.tar.gz)
Realtek | RTS3906 | rsdk-6.4.1-linux | [5.3.40](https://images.tuyacn.com/rms-static/40adc820-5084-11ee-b879-5585a458b469-1694423944610.rar?tyName=5.3.40_rsdk-6.4.1-linux.rar) | [4.11.2](https://images.tuyacn.com/rms-static/f7b3d910-f067-11ed-8585-0943ff8b8030-1683856484641.tar.gz?tyName=tuya_ipc_sdk_4.11.2_rsdk-6.4.1-linux.tar.gz)
Realtek | RTS3903/3906 | rsdk-6.5.0 | [5.3.40](https://images.tuyacn.com/rms-static/655b4710-5084-11ee-beb1-377a1535f238-1694424006145.rar?tyName=5.3.40_rsdk-6.5.0.rar) | [4.11.2](https://images.tuyacn.com/rms-static/f7e74520-f067-11ed-8585-0943ff8b8030-1683856484978.tar.gz?tyName=tuya_ipc_sdk_4.11.2_rsdk-6.5.0.tar.gz)
Anyka | AK3918/3916ev100 | arm-none-linux-4.4.1 | [5.3.40](https://images.tuyacn.com/rms-static/893c0020-5084-11ee-b879-5585a458b469-1694424066338.rar?tyName=5.3.40_arm-none-linux-4.4.1.rar) | [4.11.2](https://images.tuyacn.com/rms-static/f7e6a8e0-f067-11ed-8b07-418e300fdfb3-1683856484974.tar.gz?tyName=tuya_ipc_sdk_4.11.2_arm-none-linux-4.4.1.tar.gz)
Anyka | AK3918/3916ev200 | arm-anykav200-linux-uclibc-4.8.5 | [5.3.40](https://images.tuyacn.com/rms-static/c2543df0-5084-11ee-b879-5585a458b469-1694424162127.rar?tyName=5.3.40_arm-anykav200-linux-uclibc-4.8.5.rar) | [4.11.2](https://images.tuyacn.com/rms-static/f7b3d911-f067-11ed-8585-0943ff8b8030-1683856484641.tar.gz?tyName=tuya_ipc_sdk_4.11.2_arm-anykav200-linux-uclibc-4.8.5.tar.gz)
Anyka | AK3918ev300/33x | arm-anykav500-linux-uclibcgnueabi-gcc-4.9.4 | [5.3.40](https://images.tuyacn.com/rms-static/e0f8c910-5084-11ee-beb1-377a1535f238-1694424213537.rar?tyName=5.3.40_arm-anykav500-linux-uclibcgnueabi-gcc-4.9.4.rar) | [4.11.2](https://images.tuyacn.com/rms-static/f7abe9d0-f067-11ed-8585-0943ff8b8030-1683856484589.tar.gz?tyName=tuya_ipc_sdk_4.11.2_arm-anykav500-linux-uclibcgnueabi-gcc-4.9.4.tar.gz)
Anyka | AnyCloud39AV100 | arm-anycloud-linux-uclibcgnueabi | [5.3.40](https://images.tuyacn.com/rms-static/cae04fa0-5083-11ee-beb1-377a1535f238-1694423746971.rar?tyName=5.3.40_arm-anycloud-linux-uclibcgnueabi.rar) | 
Anyka | AnyCloud39AV100 | arm-anycloud-linux-uclibcgnueabi_V1_0_04 | [5.3.40](https://images.tuyacn.com/rms-static/0e9ac300-5085-11ee-b879-5585a458b469-1694424290096.rar?tyName=5.3.40_arm-anycloud-linux-uclibcgnueabi_V1_0_04.rar) | 
Anyka | AnyCloud39AV100 | arm-anycloud-linux-uclibcgnueabi_V1_0_05 | [5.3.40](https://images.tuyacn.com/rms-static/2e187010-5085-11ee-beb1-377a1535f238-1694424342929.rar?tyName=5.3.40_arm-anycloud-linux-uclibcgnueabi_V1_0_05.rar) | 
Fullhan | FH8626V100 | arm-fullhanv2-linux-uclibcgnueabi-b2 | [5.3.40](https://images.tuyacn.com/rms-static/59005310-5085-11ee-b879-5585a458b469-1694424414913.rar?tyName=5.3.40_arm-fullhanv2-linux-uclibcgnueabi-b2.rar) | [4.11.2](https://images.tuyacn.com/rms-static/f7aad860-f067-11ed-8b07-418e300fdfb3-1683856484582.tar.gz?tyName=tuya_ipc_sdk_4.11.2_arm-fullhanv2-linux-uclibcgnueabi-b2.tar.gz)
Fullhan | FH8626 | arm-fullhanv3-linux-uclibcgnueabi-b6.2(硬浮点) | [5.3.40](https://images.tuyacn.com/rms-static/7d602730-5085-11ee-beb1-377a1535f238-1694424475939.rar?tyName=5.3.40_arm-fullhanv3-linux-uclibcgnueabi-b6.2.rar) | [4.11.2](https://images.tuyacn.com/rms-static/f7abc2c0-f067-11ed-8b07-418e300fdfb3-1683856484588.tar.gz?tyName=tuya_ipc_sdk_4.11.2_arm-fullhanv3-linux-uclibcgnueabi-b6.2.tar.gz)
Fullhan | FH8626 | arm-fullhanv3-linux-uclibcgnueabi-b6.2(软浮点) | [5.3.40](https://images.tuyacn.com/rms-static/9dd26d70-5085-11ee-b879-5585a458b469-1694424530375.rar?tyName=5.3.40_arm-fullhanv3-linux-uclibcgnueabi-b6-2-soft.rar) | 
Fullhan | FH8636 | arm-fullhanv3-linux-uclibcgnueabi-b6 | [5.3.40](https://images.tuyacn.com/rms-static/c5fa9430-5085-11ee-beb1-377a1535f238-1694424597747.rar?tyName=5.3.40_arm-fullhanv3-linux-uclibcgnueabi-b6.rar) | [4.11.2](https://images.tuyacn.com/rms-static/f7aad860-f067-11ed-8585-0943ff8b8030-1683856484582.tar.gz?tyName=tuya_ipc_sdk_4.11.2_arm-fullhanv3-linux-uclibcgnueabi-b6.tar.gz) 

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
