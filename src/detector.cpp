#include "detector.h"
// cpp
#include <chrono>
#include <time.h>
// opencv
#include "opencv2/opencv.hpp"

bool DlibDetector::init(const std::string& model_path) {
    _model_path = model_path;
    if (!loadModel()) {
        std::cout << "load model failed." << std::endl;
        return false;
    }
    return true;
}

bool DlibDetector::loadModel() {
    // initialize the landmard predictor
    dlib::deserialize(_model_path) >> _landmark_predictor;
    std::cout << "load model successfully." << std::endl;
    return true;
}

std::vector<cv::Point2f> DlibDetector::detect(const cv::Mat& pic) {
    // defined face_detector and landmark predictor
    dlib::frontal_face_detector face_detector = dlib::get_frontal_face_detector();
    // convert to dlib_cv_image, shadow copy
    dlib::cv_image<dlib::bgr_pixel> pic_dlib(pic);
    // get the detected faces
    std::vector<dlib::rectangle> faces = face_detector(pic_dlib);
    // if there is no face detected
    if (faces.size() == 0) {
        std::cout << "no face detected." << std::endl;
        std::vector<cv::Point2f> no_value_vector;
        return no_value_vector;
    }
    // find the largest face
    auto largest_face_ptr = std::max_element(faces.begin(), faces.end(), 
                                [](dlib::rectangle r01, dlib::rectangle r02) {
                                    return r01.area() < r02.area();
                                }
                                );
    // convert to dlib::full_object_detection to get the coordinates
    clock_t start_time = clock();
    dlib::full_object_detection shape = _landmark_predictor(pic_dlib, *largest_face_ptr);    
    clock_t end_time = clock();
    std::cout << "landmarks used time is " 
              << (double)(end_time - start_time) / CLOCKS_PER_SEC 
              << "seconds."
              << std::endl;
    // std::cout << "part num " << shape.num_parts() << std::endl;
    // construct the cv::Point2f vector
    std::vector<cv::Point2f> landmarks;
    for (int i = 0; i < shape.num_parts(); ++i) {
        landmarks.push_back(cv::Point2f(shape.part(i).x(), shape.part(i).y()));
        // std::cout << landmarks[i] << std::endl;
    }
    return landmarks;
}