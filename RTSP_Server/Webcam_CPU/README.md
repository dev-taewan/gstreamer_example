# gstreamer_example
Webcam-Rtsp_Server Example

## Caution
 We have configured the system to achieve the highest frame rate in an environment without a GPU. My webcam provides the highest frame rate when using JPEG. If your webcam supports H.264 or H.265, you can transmit directly to RTSP without additional processes such as JPEG decoding or encoding. Alternatively, if it is USB 3.0 or higher, even raw data can achieve 30fps.

In such cases, you need to modify the pipeline. Please check with gst-device-monitor-1.0.

## Excution Example   
```shell
mkdir build
cd build
cmake ..
make
#rtsp_server [webcam-device] [width] [height] [rtsp-port] [fps]
./rtsp_server /dev/video2 1920 1080 8554 30
```

