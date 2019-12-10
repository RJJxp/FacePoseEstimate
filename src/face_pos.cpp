#include "face_pos.h"


FacePoseCal::~FacePoseCal() {
    if (_detector != NULL) {
        delete _detector;
        _detector = NULL;
    }
    if (_cfg_handle != NULL) {
        delete _cfg_handle;
        _cfg_handle = NULL;
    }
    if (_solvePnP != NULL) {
        delete _solvePnP;
        _solvePnP = NULL;
    }
}

void FacePoseCal::init(const std::string& config_path) {
    // load config using ConfigHandle
    _cfg_handle = new ProjectCfg();
    _cfg_handle->init(config_path);
    std::string model_path;
    _cfg_handle->getCfg(model_path, _standard_landmarks, _camera_K);
    // load shape predictor model
    _detector = new DlibDetector();
    _detector->init(model_path);
    // initialize the solvePnP
    _solvePnP = new CvSolvePnP();
}

bool FacePoseCal::getPose(const cv::Mat& img, 
                          double& yaw, 
                          double& pitch, 
                          double& roll) {
    std::vector<cv::Point2f> face_landmarks;
    face_landmarks = _detector->detect(img);
    std::vector<double> eular_angles;
    eular_angles = _solvePnP->solve(face_landmarks, _standard_landmarks, _camera_K);
    yaw = eular_angles[0];
    pitch = eular_angles[1];
    roll = eular_angles[2];
    return true;
}