// basic file operations
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <sstream>
#include "DataPoint.hpp"
using namespace std;


int main () {
  int totalTT = 0;
  int totalTF = 0;
  int totalFT = 0;
  int totalFF = 0;
  ifstream myfile;
  vector<DataPoint> allData;
  myfile.open ("C:\\Users\\aliso\\Documents\\CIS663\\Results\\Mini_unmaskTrain_maskTest.txt");
  DataPoint tempDataPoint;
  string inputLine;
  //std::getline(myfile, inputLine); // toss the first line because it's just the headers -> not true anymore
  std::getline(myfile, inputLine);
  while(myfile)
  {
    std::stringstream ss;
    ss << inputLine;
    ss >> tempDataPoint.truth;
    ss >> tempDataPoint.predicted;
    ss >> tempDataPoint.distance;
    ss.get();
    allData.push_back(tempDataPoint);
    std::getline(myfile, inputLine);
  }
  myfile.close();
  int beginningOfFalseData = 500; // 0 -> 499 is trained, 500 -> 999 is not
  double threshold = 1000.00;
  std::string::size_type sz;
  for (DataPoint instance : allData)
  {

      //instance.performEvaluation(instance.truth);
      instance.performThresholdEvaluation(beginningOfFalseData, threshold, instance.truth);
      instance.printMe();
      if(instance.trueVal == 1 && instance.predictionVal == 1)
      {
          totalTT++;
      }
      if(instance.trueVal == 1 && instance.predictionVal == 0)
      {
          totalTF++;
      }
      if(instance.trueVal == 0 && instance.predictionVal == 1)
      {
          totalFT++;
      }
      if(instance.trueVal == 0 && instance.predictionVal == 0)
      {
          totalFF++;
      }
  }

  std::cout << std::endl;
  std::cout << "------------------------" << std::endl;
  std::cout << "Confusion Matrix" << std::endl;
  std::cout << "------------------------" << std::endl;
  //Output confusion matrix in nice printed format
  std::cout << "     True --1--  --0--" << std::endl;;
  std::cout << "Pred|                " << std::endl;;
  std::cout << "    1      " << totalTT << "  | " << totalFT << "   " << std::endl;
  std::cout << "    |      ----------  " << std::endl;
  std::cout << "    0       " << totalTF << "  | " << totalFF << "   " << std::endl;
  std::cout << "    |      ----------  " << std::endl;
  std::cout << std::endl;

  std::cout << "------------------------" << std::endl;
  std::cout << "Machine Learning Metrics" << std::endl;
  std::cout << "------------------------" << std::endl;

  //Calculate model accuracy
  float accuracy = float(totalTT + totalFF) / float(allData.size());
  std::cout << "Model accuracy = " << accuracy << std::endl;

  //Calculate FMR
  float fmr = float(totalFT) / float(totalFT + totalFF);
  std::cout << "FMR(FPR) = " << fmr << std::endl;

  //Calculate FNMR 
  float fnmr = float(totalTF) / float(totalTT + totalTF);
  std::cout << "FNMR(FNR) = " << fnmr << std::endl;

  //Calculate Precision PPV = TP / (TP + FP)
  float precision = float(totalTT) / float(totalTT + totalFT);
  std::cout << "Precision(PPV) = " << precision << std::endl;

  //Calculate Recall (TPR = TP / P = TP/ (TP + FN) = 1 - FNR)
  float recall = float(totalTT) / float(totalTT + totalTF);
  std::cout << "Recall = " << recall << std::endl;

  return 0;
}