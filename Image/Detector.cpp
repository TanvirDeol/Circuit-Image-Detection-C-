#include "Detector.h"
#include "Header.h"
#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace cv;
using namespace std;
Detector::Detector(Mat &srcImage) {
    image = srcImage;
}

double Detector::similar(Mat& subImage, Mat& stockImage) {
    //iterate through main image, create array of the number of black pixels in a row
    // do the same with the image block
    vector<int> firstGraph; vector<int> secondGraph;
    Size size = subImage.size(); Size size2 = stockImage.size();
    for (int i = 0; i < size.height; i++) {
        int sum = 0;
        for (int j = 0; j < size.width; j++) {
            Vec3b pix = subImage.at<Vec3b>(i, j);
            if (pix[0] < 255) {
                sum++;
            }
        }
        firstGraph.push_back(sum);
    }

    for (int i = 0; i < size2.height; i++) {
        int sum = 0;
        for (int j = 0; j < size2.width; j++) {
            Vec3b pix = stockImage.at<Vec3b>(i, j);
            if (pix[0] < 255) {
                sum++;
            }
        }
        secondGraph.push_back(sum);
    }

    //100% difference is 787 rows that are different
    double difference = 0; //max value is 787
    for (int i = 0; i < size.height; i++) {
        int one = firstGraph[i], two = secondGraph[i];
        //cout << one << " " << two << endl;
        if (abs(two - one) > 30) {
            difference++;
        }
    }
    double answer = difference / (size.height * 1.00) * 100;
    return answer;
}

pair<int, int> Detector::findImageBounds(pair<int, int>& begin, pair<int, int>& finish) {
    int start = begin.first;
    int end = finish.first;
    int height = begin.second;
    bool whiteLine = false; int j = height;
    int topLimit = 0, bottomLimit = 0;
    while (!whiteLine) {
        int blackCount = 0;
        for (int k = start; k < end; k++) {
            Vec3b pix = image.at<Vec3b>(j, k);
            if (pix[0] < 250) {
                blackCount++; break;
            }
        } j++;
        if (blackCount == 0) {
            bottomLimit = j; whiteLine = true;
        }
    }
    whiteLine = false; j = height;
    while (!whiteLine) {
        int blackCount = 0;
        for (int k = start; k < end; k++) {
            Vec3b pix = image.at<Vec3b>(j, k);
            if (pix[0] < 250) {
                blackCount++; break;
            }
        } j--;
        if (blackCount == 0) {
            topLimit = j; whiteLine = true;
        }
    }

    return make_pair(topLimit, bottomLimit);
}

string Detector::identifyFeature (pair<int, int> startX, pair<int, int> endX, vector<Mat>& stockImage, vector<string> names) {
    vector<pair<double, string> >decisionList;
    topBot = findImageBounds(startX, endX);

    //create subimage from main image
    //resize subimage to match blockImage in method
    Range cols(startX.first, endX.first);
    Range rows(topBot.first, topBot.second);
    Mat croppedSubImage = image(rows, cols); //crops image


    for (int i = 0; i < stockImage.size(); i++) {
        Size size = stockImage[i].size(); //gets size of image to compare
        Mat resultImage;
        resize(croppedSubImage, resultImage, size); //resizes original image to it, for equal comparison
      /*  namedWindow("Cropped");
        imshow("Cropped", resultImage);
        waitKey(0);
        destroyWindow("Cropped");*/
        //runs method to see percent difference
        double imageDifference = similar(resultImage, stockImage[i]);
        cout << "Feature match with " << names[i] << ": " << imageDifference << endl;
        decisionList.push_back(make_pair(imageDifference, names[i]));
    }

    sort(decisionList.begin(), decisionList.end());
    cout << endl << "This must be a " << decisionList[0].second << endl;
    cout << "-----------------------------------------" << endl;

    return decisionList[0].second;
}

