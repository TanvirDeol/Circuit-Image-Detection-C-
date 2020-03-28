#pragma once
#include "Header.h"
#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace cv;
using namespace std;


class Utility
{
public:
	void testVisibility(Mat& image);
	void eraseSections(Mat& image, pair<int, int>topLeft, pair<int, int>botRight);
};

