#ifndef _FPC_CAMERA_HANDLE_H_
#define _FPC_CAMERA_HANDLE_H_

#include <iostream>
#include "opencv2/opencv.hpp"

class CfgHandle {
public:
    CfgHandle() {}
    ~CfgHandle() {}
    virtual void init(const std::string& config_path) = 0;
    virtual bool getCfg(std::string& model_path,
                        std::vector<cv::Point3f>& landmark_3f, 
                        cv::Mat& camera_K) = 0;
};

// ===========================
// Example of this Class
// ===========================
// ProjectCfg* pcfg = new ProjectCfg();
// pcfg->init("../cfg.yaml");
// std::string model_path;
// cv::Mat camera_K;
// std::vector<cv::Point3f> landmark;
// pcfg->getCfg(model_path, landmark, camera_K);
// ===========================
class ProjectCfg: public CfgHandle {
public:
    ProjectCfg() {}
    ~ProjectCfg() {}
    // init from YAML
    virtual void init(const std::string& config_path);
    // get config of model path, standard landmark, camera instincts
    virtual bool getCfg(std::string& model_path,
                        std::vector<cv::Point3f>& landmark_3f, 
                        cv::Mat& camera_K);
private:
    // get the standard aligned 68 points landmarks of Dlib
    bool getLandmark(const std::string& landmark_path);
    // read the Camera Matrix using YAML
    bool getCameraKMatrix(const std::string& camera_K_path);
private:
    std::string _cfg_path;
    // 3 return variables
    std::string _model_path;
    std::vector<cv::Point3f> _landmark_3f;
    cv::Mat _camera_K;
};

#endif