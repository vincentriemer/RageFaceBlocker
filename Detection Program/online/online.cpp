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
  //Get and store the query image
  string query_image = argv[1];
  Mat qImage = imread(query_image,CV_LOAD_IMAGE_GRAYSCALE);

  // Load the descriptors
  Mat dbDescriptors;
  FileStorage f( "descriptors.xml", FileStorage::READ);
  f["dbDescriptors"] >> dbDescriptors;

  // Load the index and Generate Matcher
  flann::Index *index;
  flann::SavedIndexParams indexParams("index.xml");
  index = new flann::Index(dbDescriptors,indexParams);

  //Get the features and descriptors for the query image
  //cout << "Getting features and descriptors for query image..." << endl;
  SiftFeatureDetector detector;
  SiftDescriptorExtractor extractor;
  vector<KeyPoint> qKey;
  Mat qDesc;
  detector.detect(qImage,qKey);
  extractor.compute(qImage, qKey, qDesc);
  //cout << "DONE!" << endl;

  //cout << "Perform search...." << endl;
  Mat indices;
  Mat dists;
  index->knnSearch( qDesc, indices, dists, 1);
  //cout << "DONE!" << endl;

  float minDistance = 99999;
  float maxDistance = 0;
  int totalDistance = 0;
  int numGoodMatches = 0;  
  for( int i = 0; i < dists.rows; i++){
    float tempDistance = dists.at<float>(i,0);
    if( tempDistance < minDistance) {
      minDistance = tempDistance;
    }
    if( tempDistance > maxDistance) {
      maxDistance = tempDistance;
    }
    if( tempDistance < 1000 ){
      numGoodMatches++;
    }
    totalDistance += tempDistance;
  }

  //Print out results for possible scoring
  cout << "Minimum distance: " << minDistance << endl;
  //cout << "Maximum distance: " << maxDistance << endl;
  //cout << "Total distance: " << totalDistance << endl;
  //cout << "Average distance: " << totalDistance/dists.rows << endl;
  cout << numGoodMatches << " good matches" << endl;
  //if( numGoodMatches == 0 ) {
  	//cout << "not_comic" << endl;
  //} else {
  	//cout << "comic" << endl;
  //}
}
