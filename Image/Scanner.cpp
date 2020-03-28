#include "Header.h"
#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace cv;
using namespace std;

vector<Mat> Scanner:: collectFeatureData() {
    vector<Mat> imageList;
    //Note that this list could be added to as there could be more types of features
    imageList.push_back(imread("C:\\Users\\Roxy\\Desktop\\Circuit Project\\Circuit Images\\Lightbulb.png"));
    imageList.push_back(imread("C:\\Users\\Roxy\\Desktop\\Circuit Project\\Circuit Images\\Resistor.png"));
    imageList.push_back(imread("C:\\Users\\Roxy\\Desktop\\Circuit Project\\Circuit Images\\Switch.png"));
    imageList.push_back(imread("C:\\Users\\Roxy\\Desktop\\Circuit Project\\Circuit Images\\Battery.png"));
        if (imageList[0].empty()) // Check for failure
        {
            cout << "Could not open or find the image" << endl;
            system("pause"); //wait for any key press
            exit(1);
        }
        return imageList;
    }

vector<Mat> Scanner::collectCornerData() {
        vector<Mat> cornerImg;
        cornerImg.push_back(imread("C:\\Users\\Roxy\\Desktop\\Circuit Project\\Circuit Images\\cornerBotLeft.png"));
        cornerImg.push_back(imread("C:\\Users\\Roxy\\Desktop\\Circuit Project\\Circuit Images\\cornerBotRight.png"));
        cornerImg.push_back(imread("C:\\Users\\Roxy\\Desktop\\Circuit Project\\Circuit Images\\cornerTopRight.png"));
        cornerImg.push_back(imread("C:\\Users\\Roxy\\Desktop\\Circuit Project\\Circuit Images\\cornerTopLeft.png"));
        cornerImg.push_back(imread("C:\\Users\\Roxy\\Desktop\\Circuit Project\\Circuit Images\\interLeft.png"));
        cornerImg.push_back(imread("C:\\Users\\Roxy\\Desktop\\Circuit Project\\Circuit Images\\interRight.png"));
        cornerImg.push_back(imread("C:\\Users\\Roxy\\Desktop\\Circuit Project\\Circuit Images\\interTop.png"));
        cornerImg.push_back(imread("C:\\Users\\Roxy\\Desktop\\Circuit Project\\Circuit Images\\interBottom.png"));
        if (cornerImg[0].empty()) // Check for failure
        {
            cout << "Could not open or find the image" << endl;
            system("pause"); //wait for any key press
            exit(1);
        }
        return cornerImg;
    }

vector<string> Scanner::initFeatureNames() {
    vector<string> names;
    names.push_back("Lightbulb");
    names.push_back("Resistor");
    names.push_back("Switch");
    names.push_back("Battery");
    return names;
}

vector<string> Scanner::initCornerNames() {
    vector<string> names;
    names.push_back("corBotLeft");
    names.push_back("corBotRight");
    names.push_back("corTopRight");
    names.push_back("corTopLeft");
    names.push_back("interLeft");
    names.push_back("interRight");
    names.push_back("interTop");
    names.push_back("interBottom");
    return names;
}

vector<pair<int, int> > Scanner:: scanCoordinates(string directory) {
    if (directory == "Features") {
        directory = "C:\\Users\\Roxy\\Desktop\\Circuit Project\\input\\Feature Coordinates.txt";
    }
    else{
        directory = "C:\\Users\\Roxy\\Desktop\\Circuit Project\\input\\Corner Coordinates.txt";
    }
    string input;
    vector<pair<int, int> > coordinates;
    ifstream inFile;
    inFile.open(directory);

    if (!inFile) {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }

    while (getline(inFile, input)) {
        int x = 0, y = 0;
        istringstream ss(input);
        ss >> x >> y;
        coordinates.push_back(make_pair(x, y));
    }
    inFile.close();

    return coordinates;
}
