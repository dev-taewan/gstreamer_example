#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>
#include <string.h>

void start_rtsp_server(const char *device, const char *width_str, const char *height_str, const char *port_str, const char *fps_str);

int main(int argc, char *argv[]) {
    gst_init(&argc, &argv);

    // 기본값 설정
    const char *device = "/dev/video0";
    const char *width_str = "1920";
    const char *height_str = "1080";
    const char *port_str = "8554";
    const char *fps_str = "30";

    if (argc >= 5) {
        device = argv[1];
        width_str = argv[2];
        height_str = argv[3];
        port_str = argv[4];
        fps_str = argv[5];
    }
    start_rtsp_server(device, width_str,height_str, port_str, fps_str);
    return 0;
}

void start_rtsp_server(const char *device,const char *width_str, const char *height_str, const char *port_str, const char *fps_str) {
    int port = atoi(port_str);
    int fps = atoi(fps_str);
    int width = atoi(width_str);
    int height = atoi(height_str);
    GstRTSPServer *server = gst_rtsp_server_new();
    gst_rtsp_server_set_service(server, port_str);

    GstRTSPMountPoints *mounts = gst_rtsp_server_get_mount_points(server);
    GstRTSPMediaFactory *factory = gst_rtsp_media_factory_new();
    gchar *pipeline_str;

    pipeline_str = g_strdup_printf("v4l2src device=%s ! image/jpeg,width=%d,height=%d, framerate=%d/1 ! jpegdec ! x264enc key-int-max=30 bitrate=8192 speed-preset=ultrafast tune=zerolatency ! rtph264pay name=pay0 pt=96", device, width,height, fps);
    gst_rtsp_media_factory_set_launch(factory, pipeline_str);
    g_free(pipeline_str);
    gst_rtsp_mount_points_add_factory(mounts, "/test", factory);
    gst_rtsp_server_attach(server, NULL);
    g_print("Stream ready at rtsp://127.0.0.1:%d/test\n", port);
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);
}
