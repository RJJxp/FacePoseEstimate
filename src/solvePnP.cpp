#include "solvePnP.h"

// cpp
#include <fstream>
#include <string>
// eigen
#include <eigen3/Eigen/Geometry>
#include <eigen3/Eigen/Eigen>
// opencv
#include "opencv2/core/eigen.hpp"

CvSolvePnP::CvSolvePnP() {

}


std::vector<double> CvSolvePnP::solve(const std::vector<cv::Point2f>& face_landmarks,
                                      const std::vector<cv::Point3f>& standard_landmarks,
                                      const cv::Mat& camera_K) {
    // clear the angles
    angles.clear();
    // judge the face landmarks
    if (face_landmarks.size() == 0) {
        std::cout << "the landmard_2f has no points." << std::endl
                  << "may be there is no human face detected." << std::endl
                  << "please check. return 0,0,0 as eular angles" << std::endl;
        std::vector<double> no_value_vector = {0, 0, 0};
        return no_value_vector;
    }
    // get the rotate vectors
    cv::Mat dist_coeffs = cv::Mat::zeros(4, 1, cv::DataType<double>::type);
    cv::Mat rotate_vec, trans_vec;
    // for the calcualte speed, I do not want to use cv::slovePnPRansac
    // or maybe you could try it
    cv::solvePnP(standard_landmarks, face_landmarks, 
                 camera_K, dist_coeffs, rotate_vec, trans_vec);
    // convert the rotate vector to eular angles
    // std::cout << "rotate vec" << std::endl
    //           << rotate_vec << std::endl;
    cv::Mat rotate_mat;
    cv::Rodrigues(rotate_vec, rotate_mat);
    // std::cout << "rotata mat " << std::endl
    //           << rotate_mat << std::endl;
    Eigen::Matrix3d rotate_matrix;
    cv2eigen(rotate_mat, rotate_matrix);
    // std::cout << "rotate matrix " << std::endl
    //           << rotate_matrix << std::endl;
    // eular angles Z-Y-X
    // which means yaw-pitch-roll
    Eigen::Vector3d eular_angles = rotate_matrix.eulerAngles(2, 1, 0);
    std::vector<double> angles;
    angles.push_back(eular_angles(0));  // yaw
    angles.push_back(eular_angles(1));  // pitch
    angles.push_back(eular_angles(2));  // row
    // the eular angle is consistent with the Eigen coordiante system
    std::cout << "yaw " << angles[0] << std::endl
              << "pitch " << angles[1] << std::endl
              << "roll " << angles[2] << std::endl;
    return angles;
}