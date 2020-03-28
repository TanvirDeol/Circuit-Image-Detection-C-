#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "Header.h"
#include "Detector.h"
#include "Utility.h"
typedef pair<int, int> pi;
#define mp make_pair 
#define pb push_back 
#define f first 
#define s second 
using namespace cv;
using namespace std;


Mat srcImage;
Mat erasedImage;

int main() {
    srcImage = imread("C:\\Users\\Roxy\\Desktop\\Circuit Project\\Circuit Images\\edit.png");
    Scanner scanner;
    Detector detector(srcImage);
    Utility util;
    
    vector<Mat> featureImages = scanner.collectFeatureData();
    vector<Mat> cornerImages = scanner.collectCornerData();
    vector<string> featureNames = scanner.initFeatureNames();
    vector<string> cornerNames = scanner.initCornerNames();
    vector<pi> featureCoordinates = scanner.scanCoordinates("Features");
    vector<pi> cornerCoordinates = scanner.scanCoordinates("Corners");

    vector<pi> topBotCoordinates;
    vector<pair<pi, pi>> boundingCoordinates;

    for (int i = 0; i < featureCoordinates.size() - 1; i += 2) {
        //tells you what the feature is
        string featureType = detector.identifyFeature(featureCoordinates[i], featureCoordinates[i + 1], featureImages, featureNames); 
        topBotCoordinates.pb(detector.topBot); //adds top and bottom coords for further reference
        //makes 2 pairs of coords that tell all the dimensions of the image
        boundingCoordinates.pb(mp(mp(featureCoordinates[i].f, detector.topBot.f), mp(featureCoordinates[i + 1].f, detector.topBot.s))); 
    }

    erasedImage = srcImage;
    //This block of code whitens out circuit features, so only wires are left to scan
    for (int i = 0; i < boundingCoordinates.size(); i++) {
        util.eraseSections(erasedImage, boundingCoordinates[i].f, boundingCoordinates[i].s);
    }

    //for every given corner coordinate, the program tries to detect what type of corner it is
    for (int i = 0; i < cornerCoordinates.size(); i++) {
        string cornerType = detector.identifyCorner(cornerCoordinates[i], cornerImages, cornerNames);
    }

    return 0;
}