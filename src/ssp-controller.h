//
// Created by Yibai Zhang on 2020/5/23.
//

#ifndef OBS_SSP_SSP_CONTROLLER_H
#define OBS_SSP_SSP_CONTROLLER_H

#include <functional>
#include "controller/cameracontroller.h"

#define E2C_MODEL_CODE "noteclipse"

typedef std::function<void(bool ok)> StatusUpdateCallback;


struct CameraStatus {
    CameraStatus();
    void setIp(const QString& ip);
    QString getIp() {return controller->ip();}
    void getResolution(const StatusUpdateCallback&);
    void getFramerate(const StatusUpdateCallback&);
    void getCurrentStream(const StatusUpdateCallback&);
    void getInfo(const StatusUpdateCallback&);
    void refreshAll(const StatusUpdateCallback&);
    CameraController *getController() { return controller;}
    ~CameraStatus();

    void setStream(int stream_index, QString resolution, QString fps, int bitrate, StatusUpdateCallback cb);
    void setLed(bool isOn);

    QString model;
    std::vector<QString> resolutions;
    QString current_resolution;
    std::vector<QString> framerates;
    QString current_framerate;
    StreamInfo current_streamInfo;

private:
    CameraController *controller;
};

#endif //OBS_SSP_SSP_CONTROLLER_H
