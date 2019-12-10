#include <chrono>

#include "detector.h"
#include "solvePnP.h"
#include "cfg_handle.h"
#include "face_pos.h"

int main(int argc, char* argv[]) {
  
/*
    std::cout << "it's ok now" << std::endl;
    CfgHandle* cfg = new ProjectCfg();
    cfg->init("../cfg/cfg.yaml");
    std::string model_path;
    std::vector<cv::Point3f> landmarks;
    cv::Mat camera_K;
    cfg->getCfg(model_path, landmarks, camera_K);
    Detector* d = new DlibDetector();
    d->init(model_path);
    cv::Mat img = cv::imread("/home/rjp/Downloads/rjp_04.jpeg");
    std::vector<cv::Point2f> face_landmarks;
    face_landmarks = d->detect(img);

    SolvePnP* spnp = new CvSolvePnP();
    spnp->solve(face_landmarks, landmarks, camera_K);
*/

    FacePoseCal* fpc = new FacePoseCal();
    fpc->init("/home/rjp/rjp_code/face/face_pos_cal/cfg/cfg.yaml");
    double yaw, pitch, roll;
    cv::Mat img = cv::imread("/home/rjp/Downloads/rjp_04.jpeg");
    fpc->getPose(img, yaw, pitch, roll);

    return 0;
}