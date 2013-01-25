#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d/features2d.hpp"
#include <opencv2/nonfree/nonfree.hpp>
#include "opencv2/core/core.hpp"
#include <opencv/cv.h>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

using namespace std;
using namespace cv;

int main( int argc, char** argv )
{
  //Get all the database images
  cout << "Loading database images...." << endl;
  string STRING;
  ifstream infile;
  vector<Mat> images;
  infile.open("files.txt");
  int a = 0;
  string previousLine = "";
  while (!infile.eof())
  {
    getline(infile,STRING);
    Mat image = imread(STRING, CV_LOAD_IMAGE_GRAYSCALE);
    images.push_back( image );
    //add flipped image too
    Mat flippedImage;
    flip(image, flippedImage, 1);
    images.push_back( flippedImage);
  }
  infile.close();
  cout << "DONE!" << endl;

  //Get all the features and descriptors for the database images
  cout << "Dectecting features and extracting descriptors from database images..." << endl;
  SiftFeatureDetector detector;
  SiftDescriptorExtractor extractor;
  vector<vector<KeyPoint> > dbKeypoints;
  Mat dbDescriptors;
  for(int i = 0; i < images.size(); i++)
  {
    vector<KeyPoint> tmpKey;
    Mat tmpDesc;
    detector.detect(images[i], tmpKey);
    extractor.compute(images[i], tmpKey, tmpDesc);
    dbKeypoints.push_back(tmpKey);
    dbDescriptors.push_back(tmpDesc);
  }
  FileStorage f;
  f.open("descriptors.xml", FileStorage::WRITE);
  f << "dbDescriptors" << dbDescriptors;
  f.release();
  cout << "DONE!" << endl;
  cout << "DBdescriptors has " << dbDescriptors.rows << " rows and " << dbDescriptors.cols << "columns!" << endl;

  //Generate a matcher to be queried
  cout << "Configuring matcher...." << endl;
  flann::Index *index;
  cout << "Creating a new index..." << endl;
  flann::AutotunedIndexParams indexParams;
  index = new flann::Index(dbDescriptors,indexParams);
  index->save("index.xml");
  cout << "DONE!" << endl;
}