#pragma once
#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

class Scanner {
public:
	vector<Mat> collectFeatureData();
	vector<Mat> collectCornerData();
	vector<String> initFeatureNames();
	vector<String> initCornerNames();  
	vector<pair<int, int> > scanCoordinates(string directory);
};
