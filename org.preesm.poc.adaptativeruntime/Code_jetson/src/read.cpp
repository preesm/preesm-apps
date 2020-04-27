#include <ctime>
#include <cstdio>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "read.h"

using namespace cv;

static std::unique_ptr<VideoCapture> cap{ new VideoCapture() };

void initRead(int width, int height) {
    char gst[300];
    snprintf(gst, 300, "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)%d, height=(int)%d, format=(string)NV12, framerate=(fraction)30/1  ! nvvidconv ! video/x-raw,format=(string)BGRx ! videoconvert ! appsink", width, height);
    cap->open(gst, CV_CAP_GSTREAMER);
    if (!cap->isOpened()) {
        fprintf(stderr, "ERROR: failed to open the camera.\n");
        exit(1);
    }
}

void read(int width, int height, unsigned char *y, unsigned char *u, unsigned char *v) {
    Mat inputFrame;
    *(cap.get()) >> inputFrame;
    if (inputFrame.empty()) {
        fprintf(stderr, "ERROR: failed to read image from camera.\n");
    } else {
        /* == Ensure the image is in the proper size == */
        cv::resize(inputFrame, inputFrame, Size(width, height), INTER_LINEAR);
        /* == Convert the BGR image to YUV == */
        cv::cvtColor(inputFrame, inputFrame, COLOR_BGR2YUV);
        /* == Extract the different planes of the YUV image == */
        std::vector<cv::Mat> yuvPlanes;
        cv::split(inputFrame, yuvPlanes);
        /* == Getting the y component == */
        for (auto j = 0; j < height; ++j) {
            for (auto i = 0; i < width; ++i) {
                y[j * width + i] = yuvPlanes[0].at<uint8_t>(j, i);
            }
        }
        /* == Getting the u / v components with sub-sampling for 4:2:0 format == */
        for (auto j = 0; j < height / 2; ++j) {
            for (auto i = 0; i < width / 2; ++i) {
                u[j * width / 2 + i] = yuvPlanes[1].at<uint8_t>(j*2, i*2);
                v[j * width / 2 + i] = yuvPlanes[2].at<uint8_t>(j*2, i*2);
            }
        }
        inputFrame.release();
    }
}

void generateNothing(int height, int width, int value, unsigned char *out) {
    memset(out, value, static_cast<size_t>(height * width) * sizeof(unsigned char));
}
