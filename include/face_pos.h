#ifndef _FPC_FACE_POS_H_
#define _FPC_FACE_POS_H_

#include <iostream>

#include "detector.h"
#include "cfg_handle.h"
#include "solvePnP.h"

class FacePoseCal {
public:
    FacePoseCal() {}
    ~FacePoseCal();
    void init(const std::string& config_path);
    bool getPose(const cv::Mat& img, 
                 double& yaw, 
                 double& pitch, 
                 double& raw);
private:
    Detector* _detector;
    CfgHandle* _cfg_handle;
    SolvePnP* _solvePnP;
    // variable need to store
    std::vector<cv::Point3f> _standard_landmarks;
    cv::Mat _camera_K;
    // result to return
    double _yaw, _pitch, _raw;
};

#endif