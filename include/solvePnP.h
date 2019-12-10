#ifndef FPC_SOLOVE_PNP_H
#define FPC_SOLOVE_PNP_H

// cpp
#include <iostream>
// opencv
#include "opencv2/opencv.hpp"

class SolvePnP {
public:
    SolvePnP() {}
    virtual ~SolvePnP() {}
    virtual std::vector<double> solve(const std::vector<cv::Point2f>& face_landmarks,
                                      const std::vector<cv::Point3f>& standard_landmarks,
                                      const cv::Mat& camera_K) = 0;
protected:
    std::vector<double> angles;
};

class CvSolvePnP: public SolvePnP {
public:
    CvSolvePnP();
    virtual ~CvSolvePnP() {}
    virtual std::vector<double> solve(const std::vector<cv::Point2f>& face_landmarks,
                                      const std::vector<cv::Point3f>& standard_landmarks,
                                      const cv::Mat& camera_K);
private:
    
};
#endif