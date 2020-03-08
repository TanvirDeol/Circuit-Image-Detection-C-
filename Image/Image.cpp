//#include "stdafx.h"
#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;
Mat image;
void similar(Mat &srcImage, Mat &imageBlock) {
    //iterate through main image, create array of the number of black pixels in a row
    // do the same with the image block
    vector<int> firstGraph; vector<int> secondGraph;
    Size size = srcImage.size(); Size size2 = imageBlock.size();
    for (int i = 0; i < size.height; i++) {
        int sum = 0;
        for (int j = 0; j < size.width; j++) {
            Vec3b pix = srcImage.at<Vec3b>(i, j);
            if (pix[0] < 255) {
                sum++;
            }
        }
        firstGraph.push_back(sum);
    }
   
    for (int i = 0; i < size2.height; i++) {
        int sum = 0;
        for (int j = 0; j < size2.width; j++) {
            Vec3b pix = imageBlock.at<Vec3b>(i, j);
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
    cout << difference / (size.height * 1.00) *100 << endl;
    
    return;
}
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
  Mat blockImg[5];
  blockImg[0] = imread("C:\\Users\\Roxy\\Desktop\\Circuit Project\\Circuit Images\\Lightbulb.png");
  blockImg[1] = imread("C:\\Users\\Roxy\\Desktop\\Circuit Project\\Circuit Images\\Resistor.png");
  blockImg[2] = imread("C:\\Users\\Roxy\\Desktop\\Circuit Project\\Circuit Images\\Switch.png");
  blockImg[3] = imread("C:\\Users\\Roxy\\Desktop\\Circuit Project\\Circuit Images\\Battery.png");
  blockImg[4] = imread("C:\\Users\\Roxy\\Desktop\\Circuit Project\\Circuit Images\\img.jpg");

  if (image.empty()) // Check for failure
  {
   cout << "Could not open or find the image" << endl;
   system("pause"); //wait for any key press
   return -1;
  }

 
// double d = imgRatio(75, 213, 60.0, 51.0);
 // double e = imgRatio(619, 80, 151.0, 136.0);


  //create subimage from main image
  //resize subimage to match blockImage in method
  //run method
  Range cols(565, 822);
  Range rows(70, 218);
  Mat res = image(rows, cols); //crops image

  for (int i =0;i<5;i++){
      Size size = blockImg[i].size(); //gets size of image to compare
      Mat dst; 
      resize(res, dst, size); //resizes original image to it, for equal comparison
      similar(dst, blockImg[i]); //runs method to see percent difference
  }
  /*
  namedWindow("Cropped"); 
  imshow("Cropped", dst); 
  namedWindow("Block");
  imshow("Block", blockImg);
  waitKey(0); 
  destroyWindow("Cropped"); 
  destroyWindow("Block");*/
  
 
  return 0;
}