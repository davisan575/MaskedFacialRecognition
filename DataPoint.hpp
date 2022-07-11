#include <iostream>
#include <string.h>

class DataPoint {
    public:
        DataPoint() {};
        ~DataPoint() {};
        std::string truth;
        std::string predicted;
        int trueVal;
        int predictionVal;
        int truePredictionVal;
        double distance;
        void printMe()
        {
            std::cout << truth << "   " << predicted << "  ->  " << trueVal << ", " << predictionVal << std::endl;
        }   
        
        void performEvaluation(std::string trueString)
        {
            if(truth == trueString) {
                trueVal = 1;
            } else {
                trueVal = 0;
            }

            if(predicted == trueString) {
                predictionVal = 1;
            } else {
                predictionVal = 0;
            }
        }

        void performThresholdEvaluation(int cutoff, double threshold, std::string trueString)
        {
            if (std::stoi(truth) >= cutoff)
            {
                trueVal = 0;
            }
            else{
                trueVal = 1;
            }

            if (distance >= threshold)
            {
                predictionVal = 0;
            }
            else
            {
                predictionVal = 1;
                if(predicted != trueString)
                {
                    truePredictionVal = 0;
                }
                else{
                    truePredictionVal = 1;
                }
            }
        }
};