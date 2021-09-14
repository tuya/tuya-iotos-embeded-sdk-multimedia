[English](./README.md) | 简体中文

# Tuya嵌入式多媒体SDK


## 介绍
Tuya嵌入式多媒体SDK是在涂鸦IoTOS体系中针对具备音视频能力的嵌入式设备，如网络摄像机（IPC）、录像机（NVR/DVR）、可视门铃（doorbell）、摄像头灯（Floodlight）等推出的软件开发包。提供标准C语言静态库、头文件以及对应的说明文档，覆盖Linux、LiteOS以及部分特定的RTOS系统。

## 下载中心

mainline指代包含最新功能的SDK版本，经过涂鸦内部SDK级别测试后发布的版本；<br>
stable指代已经经过涂鸦内部特定硬件平台产品级别测试后发布的版本；<br>
longterm指代已经经过多个涂鸦客户硬件平台产品级别验证的版本。

### 标准Linux版本
* **[下载SDK](./Linux/download.md)**
* **[Release Note](./Linux/release_note.md)**

### RTOS系统版本
* Mainline:&emsp;**[1.0.1](./RTOS/dowload_list_rtos.md)**
* **[新SoC接入](./RTOS/For_New_SoC)**

### LiteOS系统版
* longterm (for liteos):&emsp;**[4.8.8](./LiteOS/dowload_list_liteos_4.8.8.md)**
* version info:&emsp;**[releaseNote](./LiteOS/release_note_zh-CN.md)**

### 基站-相机套装版本
* mainline:&emsp;**[1.0.4](./Base-station&Camera-Suit/download_list_kit.md)**

### XVR(NRV&DVR)版本
* mainline:&emsp;**[1.5.4](./XVR/download_list_1.5.4.md)**
* stable:&emsp;**[1.4.6](./XVR/download_list_1.4.6.md)**

### 行车记录仪版本


### 门锁版本
* mainline:&emsp;**[1.0.0](./Door-Lock/doorlock_sdk_release.md)**

### 产测专用
* longterm:&emsp;**[1.1.0](./fac/dowload_list_fac_1.1.0.md)**

## 快速上手

* **[涂鸦开发者平台创建产品](https://developer.tuya.com/cn/docs/iot/configure-in-platform/create-product/create-product?id=K914jp1ijtsfe)** 获取 PID 信息([What's this?](https://github.com/tuya/tuya-iotos-embeded-sdk-multimedia/wiki/What-is#what-is-pid))<br> 
注：产品类型选择智能摄像机

* 获取 UUID&AUTHKEY 信息.([What's this?](https://github.com/tuya/tuya-iotos-embeded-sdk-multimedia/wiki/What-is#what-is-uuid--authkey))

* 使用[Tuya官方标准demo代码](https://github.com/tuya/tuya-iotos-embeded-multimedia-demo), 参考[快速上手说明](https://github.com/tuya/tuya-iotos-embeded-multimedia-demo#get-started)进行demo开发


## 技术支持

开发者中心：https://developer.tuya.com/cn/ <br>
帮助中心: https://support.tuya.com/cn/help <br>
技术支持工单中心:    https://iot.tuya.com/council/

## License
[MIT License](./LICENSE)