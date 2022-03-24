English | [简体中文](./release_note_zh-CN.md)
## release note for 2.0.4 20220324
### [optimization version]
- Support 0.5*speed playback
- Add api to stop cloud storage immediately
- Optimize the logic of sub device binding

## release note for 2.0.2 20220127
### [optimization version]
- Add cloud storage audio channel configuration API.
- Optimize memory usage of cloud storage, malloc buf when the camera have an order. 
- Add asynchronous API to stop cloud.
- Fix bug that the cloud storage could not stop due to the probabilistic endless loop of ringbuffer.
- Change the limit of the bitrate to 10Mbps.
- Fix bug that the streaming gateway only uses the first camera stream.
- Fix probabilistic memory leak when p2p exit.
- Support the audio channel setting corresponding to the sub-stream preview, the default main audio channel can be set to other audio channels.
- Support multi-unbind and multi-rebind.
- Fixed bug that the APP cannot show the picture when multiple cameras upload event at the same time.
