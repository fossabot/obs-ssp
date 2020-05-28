//
// Created by Yibai Zhang on 2020/5/23.
//

#include <QThread>
#include "ssp-controller.h"

static QThread *ccThread = nullptr;

void initCameraController()  {
    ccThread = new QThread();
    ccThread->start(QThread::TimeCriticalPriority);
}

void destroyCameraController() {
    ccThread->quit();
    ccThread->wait();
    delete ccThread;
}

CameraStatus::CameraStatus(){
    controller = new CameraController();
    controller->moveToThread(ccThread);
};

void CameraStatus::setIp(const QString &ip) {
    controller->setIp(ip);
}

void CameraStatus::getResolution(const StatusUpdateCallback& callback) {
    controller->getCameraConfig(CONFIG_KEY_MOVIE_RESOLUTION,[=](HttpResponse *rsp) {
        if(rsp->choices.count() > 0) {
            resolutions.clear();
        }
        for (const auto& i: rsp->choices) {
            resolutions.push_back(i);
        }
        callback();
    });
}

void CameraStatus::getFramerate(const StatusUpdateCallback& callback) {
    controller->getCameraConfig(CONFIG_KEY_PROJECT_FPS, 3,[=](HttpResponse *rsp) {
        if(rsp->choices.count() > 0) {
            framerates.clear();
        }
        for (const auto& i: rsp->choices) {
            framerates.push_back(i);
        }
        callback();
    });
}

CameraStatus::~CameraStatus() {
    controller->cancelAllReqs();
    delete controller;
}