//#include "stdafx.h"
#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <fstream>
using namespace cv;
using namespace std;
Mat image;

class imageBounds 
{
public:
    pair<int, int> findBounds(pair<int, int> &begin, pair<int, int> &finish ) {
        int start = begin.first;
        int end = finish.first;
        int height = begin.second;
            bool whiteLine = false; int j = height;
            int topH = 0, bottomH = 0;
            while (!whiteLine) {
                int blackCount = 0;
                for (int k = start; k < end; k++) {
                    Vec3b pix = image.at<Vec3b>(j, k);
                    if (pix[0] < 250) {
                        blackCount++; break;
                    }
                } j++;
                if (blackCount == 0) {
                    bottomH = j; whiteLine = true;
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
                    topH = j; whiteLine = true;
                }
            }
        
        return make_pair(topH, bottomH);
    }
public:
    void eraseSections(Mat& image, pair<int, int>topLeft, pair<int, int>botRight) {
        for (int i = topLeft.second; i < botRight.second; i++) {
            for (int j = topLeft.first; j < botRight.first; j++) {
                image.at<Vec3b>(i, j)[0] = 255;
                image.at<Vec3b>(i, j)[1] = 255;
                image.at<Vec3b>(i, j)[2] = 255;
            }
        }
    }
};

class Scanner
{
public:
    vector<Mat> prepareImgData() {
        vector<Mat> blockImg;
        blockImg.push_back(imread("C:\\Users\\Roxy\\Desktop\\Circuit Project\\Circuit Images\\Lightbulb.png"));
        blockImg.push_back(imread("C:\\Users\\Roxy\\Desktop\\Circuit Project\\Circuit Images\\Resistor.png"));
        blockImg.push_back(imread("C:\\Users\\Roxy\\Desktop\\Circuit Project\\Circuit Images\\Switch.png"));
        blockImg.push_back(imread("C:\\Users\\Roxy\\Desktop\\Circuit Project\\Circuit Images\\Battery.png"));
        if (blockImg[0].empty()) // Check for failure
        {
            cout << "Could not open or find the image" << endl;
            system("pause"); //wait for any key press
            exit(1);
        }
        return blockImg;
    }
};

class featureScanner {
public:
    vector<pair<int, int> > scanFile() {
        string s;
        vector<pair<int, int> >featureCoords;
        ifstream inFile;
        inFile.open("C:\\Users\\Roxy\\Desktop\\Circuit Project\\input\\Coordinates.txt");
        if (!inFile) {
            cerr << "Unable to open file datafile.txt";
            exit(1);   // call system to stop
        }
        while (getline(inFile, s)) {
            int x = 0, y = 0;
            istringstream ss(s);
            ss >> x >> y;
            featureCoords.push_back(make_pair(x, y));
        }
        inFile.close();
        return featureCoords;
    }
};

double similar(Mat &srcImage, Mat &imageBlock) {
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
    double ans = difference / (size.height * 1.00) * 100;
    return ans;
}

class Detector {
public:
    pair<int, int> topBot;
public:
    string identifyFeature(pair<int, int> beginX, pair<int, int> endX, vector<Mat> blockImg, string* names) {
        imageBounds imgB;
        vector<pair<double, string> >decision;

       
        topBot = imgB.findBounds(beginX, endX);


        //create subimage from main image
        //resize subimage to match blockImage in method
        Range cols(beginX.first, endX.first);
        Range rows(topBot.first, topBot.second);
        Mat res = image(rows, cols); //crops image
        

        for (int i = 0; i < blockImg.size(); i++) {
            Size size = blockImg[i].size(); //gets size of image to compare
            Mat dst;
            resize(res, dst, size); //resizes original image to it, for equal comparison
          /*  namedWindow("Cropped");
            imshow("Cropped", dst);
            waitKey(0);
            destroyWindow("Cropped");*/
            //runs method to see percent difference
            double diff = similar(dst, blockImg[i]);
            cout << "Feature match with " << names[i] << ": " << diff << endl;
            decision.push_back(make_pair(diff, names[i]));
        }
        sort(decision.begin(), decision.end());
        cout << endl << "This must be a " << decision[0].second << endl;
        cout << "-----------------------------------------" << endl;

        return decision[0].second;
    }
};


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


int main(){

 // Read the image file
  image = imread("C:\\Users\\Roxy\\Desktop\\Circuit Project\\Circuit Images\\edit.png");
  Scanner sc; 
  vector<Mat> blockImg;
  blockImg = sc.prepareImgData();
  string* names = new string[4];
  names[0] = "Lightbulb"; names[1] = "Resistor"; names[2] = "Switch"; names[3] = "Battery";
  featureScanner fScan;
  vector<pair<int, int> > featureCoords;
  featureCoords = fScan.scanFile();
  vector<pair<int, int> > topBotCoords;
  vector <pair<pair<int, int>, pair<int, int> > > boundingCoords;
  //Using the coordinates given, find the exact dimensions 
  //that will contain the feature with as little whitespace as possible
  Detector detect;
  for (int i = 0; i < featureCoords.size() - 1; i += 2) {
      string s= detect.identifyFeature(featureCoords[i], featureCoords[i+1], blockImg, names);
      topBotCoords.push_back(detect.topBot);
      boundingCoords.push_back(make_pair(make_pair(featureCoords[i].first, detect.topBot.first),
                                  make_pair(featureCoords[i+1].first, detect.topBot.second)));
  }

  Mat imageCopy = image;
  imageBounds imgBound;

  for (int i = 0; i < boundingCoords.size(); i++) {
      imgBound.eraseSections(imageCopy,boundingCoords[i].first,boundingCoords[i].second);
      namedWindow("Whitened");
      imshow("Whitened", imageCopy);
      waitKey(0);
      destroyWindow("Whitened");
  }
  

    


  



   /*
   namedWindow("Cropped");
   imshow("Cropped", dst);
   waitKey(0);
   destroyWindow("Cropped");
   destroyWindow("Block");*/
 
      return 0;
  }