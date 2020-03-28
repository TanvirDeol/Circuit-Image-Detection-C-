#pragma once
#include "Header.h"
#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace cv;
using namespace std;


class Detector
{

public:
	pair<int, int> topBot;
	Mat image;
	Detector(Mat &srcImage);
	double similar(Mat& srcImage, Mat& imageBlock);
	string identifyFeature(pair<int, int> startX, pair<int, int> endX, vector<Mat>& blockImg, vector<string> names);
	pair<int, int> findImageBounds(pair<int, int>& begin, pair<int, int>& finish);
};

