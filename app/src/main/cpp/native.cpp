#include <jni.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/features2d.hpp>
#include <vector>
#include <string>
#include <opencv2/objdetect.hpp>

using namespace cv;


extern "C"
JNIEXPORT void JNICALL
Java_com_example_facesfinal_MainActivity_FindFeatures(JNIEnv* jniEvn, jobject MainActivity, jlong addrGray, jlong addrRGBA){

    Mat* mGray = (Mat*)addrGray;
    Mat* mRGBA = (Mat*)addrRGBA;

    std::vector<Point2f> corners;

    goodFeaturesToTrack(*mGray, corners, 20, 0.01, 10, Mat(), 3, false, 0.04);

    for(int i = 0; i < corners.size(); i++){
        circle(*mRGBA, corners[i], 10, Scalar(0, 255, 0), 2);
    }
    // TODO: implement FindFeatures()
}

CascadeClassifier face_cascade;
extern "C"
JNIEXPORT void JNICALL
Java_com_example_facesfinal_MainActivity_InitFaceDetector(JNIEnv* jniEvn, jobject MainActivity, jstring jFilePath) {
    // TODO: implement InitFaceDetector()
    const char * jnamestr = jniEvn->GetStringUTFChars(jFilePath, NULL);
    std::string filePath(jnamestr);
    face_cascade.load(filePath);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_facesfinal_MainActivity_DetectFaces(JNIEnv* jniEvn, jobject MainActivity, jlong addrGray, jlong addrRGBA){

    Mat* mGray = (Mat*)addrGray;
    Mat* mRGBA = (Mat*)addrRGBA;

    std::vector<Rect> faces;

    face_cascade.detectMultiScale(*mGray, faces);

    for (int i = 0; i < faces.size(); ++i) {
        rectangle(*mRGBA, Point(faces[i].x, faces[i].y), Point(faces[i].x+faces[i].width, faces[i].y+faces[i].height), Scalar(0, 255, 0), 2);
    }
    // TODO: implement FindFeatures()
}