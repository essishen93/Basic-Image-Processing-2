//Name: Maoru Shen
//USC ID Number: 4946-8507-13
//USC Email: maorushe@usc.edu
//Submission Date: 10/11/2015
////////////////////////////////////////////////////////////////////
//Problem 1 : (a)
//This code is texture classification by Minimum Mean Distance, PCA and LDA
/////////////////////////////////////////////////////////////////////
//get_Normalized.cpp
/////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include "functions.h"
using namespace cv;
using namespace std;

void get_normal(Mat &feature_vector25,int h)
{
    int p=0,q=0;            //the cordinate of the matrix of feature vector
    double Fmax=0,Fmin=0;   //tha MAX and MIN feature
    double temp=0;
    for (q=0;q<25;q++)
    {
        Fmax=feature_vector25.at<double>(0,q);
        Fmin=feature_vector25.at<double>(0,q);
        for(p=0;p<h;p++)
        {
            temp=feature_vector25.at<double>(p,q);
            if (temp>Fmax)
                Fmax=temp;
            if (temp<Fmin)
                Fmin=temp;
        }
        //cout<<Fmax<<"   "<<Fmin<<endl;
        for(p=0;p<h;p++)
            feature_vector25.at<double>(p,q)=(feature_vector25.at<double>(p,q)-Fmin)/(Fmax-Fmin);   //normalization
    }
    //cout<<endl;
    
}
