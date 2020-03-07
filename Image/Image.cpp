//#include "stdafx.h"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;
Mat image;

double imgRatio(int x, int y, double width, double height) {
    int blackSum = 0;
    double totalSum = width * height;
    for (int i = y; i < y+height; i++) {
        for (int j = x; j < x+width; j++) {
            Vec3b c = image.at<Vec3b>(i, j);
            if (c[0] < 255) {
                blackSum++;
            }
        }
    }
    return blackSum / totalSum * 100.0;
}
int main()
{
 // Read the image file
  image = imread("C:\\Users\\Roxy\\Desktop\\Circuit Project\\Circuit Images\\edit.png");

  if (image.empty()) // Check for failure
  {
   cout << "Could not open or find the image" << endl;
   system("pause"); //wait for any key press
   return -1;
  }

  String windowName = "My HelloWorld Window"; //Name of the window

  
  double d = imgRatio(75, 213, 60.0, 51.0);
  double e = imgRatio(619, 80, 151.0, 136.0);
  cout <<d<<endl;
  cout << e << endl;
 
  
 
  return 0;
}