#include "cfg_handle.h"

// yaml-cpp
#include <yaml-cpp/yaml.h>

void ProjectCfg::init(const std::string& config_path) {
    _cfg_path = config_path;
}

bool ProjectCfg::getLandmark(const std::string& landmark_path) {
    std::ifstream infile;
    infile.open(landmark_path, std::ios::in);
    if (!infile.is_open()) {
        std::cout << "can not open file in function getLandmark()"
                  << std::endl;
        return false;
    }
    cv::Point3f tmp_pt;
    std::string s;
    std::size_t pos;
    // the structure of each line is 
    // x, y, z
    while(!infile.eof()) { 
        getline(infile, s);
        // get the x
        pos = s.find(",");        
        std::string sx = s.substr(0, pos);
        tmp_pt.x = atof(sx.c_str());
        // get the y
        s = s.substr(pos + 1);
        pos = s.find(",");        
        std::string sy = s.substr(0, pos);
        tmp_pt.y = atof(sy.c_str());
        // get the z
        s = s.substr(pos + 1);
        pos = s.find(",");        
        std::string sz = s.substr(0, pos);
        tmp_pt.z = atof(sz.c_str());
        // add the cvpt
        _landmark_3f.push_back(tmp_pt);
    }
    infile.close();
    std::cout << "finished read standard 68 landmarks from file."
              << std::endl;
    return true;
}

bool ProjectCfg::getCameraKMatrix(const std::string& camera_K_path) {
    YAML::Node config = YAML::LoadFile(camera_K_path);
    // the focal_length should be normalized
    // f_x = f_x / dx, f_y = f_y / dy;
    double f_x = config["focal_length_x"].as<double>();
    double f_y = config["focal_length_y"].as<double>();
    double c_x = config["center_x"].as<double>();
    double c_y = config["center_y"].as<double>();
    _camera_K = (cv::Mat_<double>(3, 3) << f_x, 0, c_x,
                                           0, f_y, c_y,
                                           0, 0, 1);
    std::cout << "finished reading camera K matrix" << std::endl;
    return true;
}

bool ProjectCfg::getCfg(std::string& model_path,
                        std::vector<cv::Point3f>& landmark_3f, 
                        cv::Mat& camera_K) {
    // use YAML to read yaml file
    YAML::Node config = YAML::LoadFile(_cfg_path);
    // get the model path
    _model_path = config["ModelPath"].as<std::string>();
    std::cout << "get the model path " << std::endl;
    std::string landmark_path = config["LandmarkPath"].as<std::string>();
    std::string camera_K_path = config["CameraKPath"].as<std::string>();
    // get the landmark
    if (!getLandmark(landmark_path)) {
        std::cout << "get landmark failed." << std::endl;
        return false;
    } 
    // get the camera K matrix
    if (!getCameraKMatrix(camera_K_path)) {
        std::cout << "get camera K matrix failed." << std::endl;
        return false;
    }
    // return the 3 variables
    model_path = _model_path;
    landmark_3f = _landmark_3f;
    camera_K = _camera_K;
    std::cout << "get all the 3 configs " << std::endl;
    return true;
}
