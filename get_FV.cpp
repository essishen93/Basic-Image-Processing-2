//Name: Maoru Shen
//USC ID Number: 4946-8507-13
//USC Email: maorushe@usc.edu
//Submission Date: 10/11/2015
////////////////////////////////////////////////////////////////////
//Problem 1 : (a)
//This code is texture classification by Minimum Mean Distance, PCA and LDA
/////////////////////////////////////////////////////////////////////
//get_FV.cpp
/////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include "functions.h"
using namespace cv;
using namespace std;


double get_FV(char *name,Mat &laws_filter,int Size_H,int Size_W,int R)
{
    int row=0,col=0;
    
    Mat In_Image(128,128,CV_8UC1);                 //the input image
    Mat Lg_Image(128+2*R,128+2*R,CV_8UC1);    // the enlarged input image
    Mat Filtered_Image(128,128,CV_64FC1);          //the filtered image

    //input the oringinal image
    uchar in_pixel='0';
    ifstream ifile(name,ios_base::in|ios_base::binary);
    if (!ifile)
    {
        cout<<"File CANNOT open!"<<endl;
        exit(1);
    }
    for (int row=0;row<Size_H;row++)
        for(int col=0;col<Size_W;col++)
        {
            ifile.read((char*)&in_pixel,sizeof(uchar));
            In_Image.at<uchar>(row,col)=in_pixel;
        }
    ifile.close();
  
    //enlarge the input image
    //the center 128X128
    for (row=0;row<Size_H;row++)
        for (col=0;col<Size_W;col++)
            Lg_Image.at<uchar>(row+R,col+R)=In_Image.at<uchar>(row,col);
    //upper boundary
    for (row=1;row<R+1;row++)
        for (col=0;col<Size_W;col++)
            Lg_Image.at<uchar>(R-row,col+R)=In_Image.at<uchar>(row,col);
    //right boundary
    for (row=0;row<Size_H+R;row++)
        for (col=Size_W-1;col<Size_W+R-1;col++)
            Lg_Image.at<uchar>(row,2*Size_W+2*R-2-col)=Lg_Image.at<uchar>(row,col);
    //lower boundary
    for (row=Size_H-1;row<Size_H+R-1;row++)
        for (col=R;col<Size_W+2*R;col++)
            Lg_Image.at<uchar>(2*Size_H+2*R-2-row,col)=Lg_Image.at<uchar>(row,col);
    //left boundary
    for (int row=0;row<Size_H+2*R;row++)
        for (int col=R+1;col<2*R+1;col++)
            Lg_Image.at<uchar>(row,2*R-col)=Lg_Image.at<uchar>(row,col);
    
    //filtering image
    int i=0,j=0;
    //the variables of copputation
    double sum_mean=0,mean=0;
    double sum_conv=0;
    //filtering window
    Mat window(2*R+1,2*R+1,CV_64FC1);
    
    for (row=R;row<Size_H+R;row++)
        for (col=R;col<Size_W+R;col++)
        {
            //put the pixels in the filtering window
            for (i=-R;i<1+R;i++)
                for (j=-R;j<1+R;j++)
                    window.at<double>(i+R,j+R)=Lg_Image.at<uchar>(row+i,col+j);
            //compute the local mean
            sum_mean=0;
            for (i=0;i<(2*R+1);i++)
                for (j=0;j<(2*R+1);j++)
                    sum_mean+=window.at<double>(i,j);
            mean=sum_mean/((2*R+1)*(2*R+1));
            //subtract the local mean and convolve with the filter
            sum_conv=0;
            for (i=0;i<(2*R+1);i++)
                for (j=0;j<(2*R+1);j++)
                {
                    window.at<double>(i,j)=window.at<double>(i,j)-mean;
                    sum_conv=sum_conv+(window.at<double>(i,j)*laws_filter.at<double>(i,j));
                }
            //replace the central pixel with the covolution sum
            Filtered_Image.at<double>(row-R,col-R)=sum_conv*sum_conv;
        }
    
    double en=0,sum_en=0;
    for (row=0;row<Size_H;row++)
        for (col=0;col<Size_W;col++)
            sum_en+=Filtered_Image.at<double>(row,col);
    
    //average sum of local energy
    en=sum_en/(Size_H*Size_W);
    return en;
}
