#include "Utility.h"
#pragma once
#include "Header.h"
#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace cv;
using namespace std;

void Utility::testVisibility(Mat& image) {
    namedWindow("Visible");
    imshow("Visible", image);
    waitKey(0);
    destroyWindow("Visible");
}
void Utility::eraseSections(Mat& image, pair<int, int>topLeft, pair<int, int>botRight) {
    for (int i = topLeft.second; i < botRight.second; i++) {
        for (int j = topLeft.first; j < botRight.first; j++) {
            image.at<Vec3b>(i, j)[0] = 255;
            image.at<Vec3b>(i, j)[1] = 255;
            image.at<Vec3b>(i, j)[2] = 255;
        }
    }
}