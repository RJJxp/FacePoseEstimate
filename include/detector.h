#ifndef _FPC_DETECTOR_H_
#define _FPC_DETECTOR_H_

#include <iostream>
#include <opencv2/opencv.hpp>
// dlib
#include "dlib/opencv.h"
#include "dlib/image_processing.h"
#include "dlib/image_processing/frontal_face_detector.h"
#include "dlib/image_processing/render_face_detections.h"

class Detector {
public:
    Detector() {}
    virtual ~Detector() {};
    virtual bool init(const std::string& model_path) = 0;
    virtual std::vector<cv::Point2f> detect(const cv::Mat& pic) = 0;
protected:
    std::string _model_path;
    
};

// return the 68 feature points of the largest human face detected.
// =====================
// Example:
// =====================
// std::string model_path;
// Detector* d = new DlidDetector()
// d->init(model_path);
// cv::Mat img = cv::imread("../pic.jpg");
// std::vector<cv::Point2f> result;
// result = d->detect(img);
class DlibDetector: public Detector {
public: 
    DlibDetector() {}
    virtual ~DlibDetector() {}
    virtual bool init(const std::string& model_path);
    virtual std::vector<cv::Point2f> detect(const cv::Mat& pic);
private:
    bool loadModel();
private:
    dlib::shape_predictor _landmark_predictor;
};  

#endif