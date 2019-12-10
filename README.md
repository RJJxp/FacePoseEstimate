# FacePoseEstimate
Use Dlib to detect face and the landmark of the face 

Then calculate the pose using OpenCV compared with the standard one

## Dependencies

- Dlib
- Dlib model from http://dlib.net/files/shape_predictor_68_face_landmarks.dat.bz2
- OpenCV-3.4
- YAML-cpp
- Eigen



## Run

```shell
mkdir build
cd build
cmake ..
make
./face_position
```

