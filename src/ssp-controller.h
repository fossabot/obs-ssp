//
// Created by Yibai Zhang on 2020/5/23.
//

#ifndef OBS_SSP_SSP_CONTROLLER_H
#define OBS_SSP_SSP_CONTROLLER_H

#include <functional>
#include "controller/cameracontroller.h"

typedef std::function<void()> StatusUpdateCallback;


void initCameraController();

void destroyCameraController();



struct CameraStatus {
    CameraStatus();
    void setIp(const QString& ip);
    QString getIp() {return controller->ip();}
    void getResolution(const StatusUpdateCallback&);
    void getFramerate(const StatusUpdateCallback&);
    CameraController *getController() { return controller;}
    ~CameraStatus();
    std::vector<QString> resolutions;
    std::vector<QString> framerates;

private:
    CameraController *controller;
};

#endif //OBS_SSP_SSP_CONTROLLER_H
