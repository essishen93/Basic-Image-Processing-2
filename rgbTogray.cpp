//Name: Maoru Shen
//USC ID Number: 4946-8507-13
//USC Email: maorushe@usc.edu
//Submission Date: 10/11/2015
////////////////////////////////////////////////////////////////////
//Problem 2 : (b)
//This code is to use the Canny Edge Detection to get the edge map
/////////////////////////////////////////////////////////////////////
//rgbTogray.cpp
/////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include "functions.h"
using namespace cv;
using namespace std;

const int BytesPerPixel=3;   //24-bit
const int Size_H=321;   //the height of image
const int Size_W=481;   //the width of image

void get_gray(char *name_rgb,char *name_gray,Mat &In_Image)
{
    int row=0,col=0;
    int pI=0,qI=0;                                               //coordinate of input
    int c=0;                                                     //channels. 0, RED channel;1,GREEN channel;2,BLUE channel;
    double sum_gray=0;
    unsigned char In_Image_RGB[Size_H][Size_W][BytesPerPixel];   //the color input image
    
    ifstream ifile(name_rgb,ios_base::in | ios_base::binary);
    if (!ifile)
    {
        cout<<"File CANNOT open!"<<endl;
        exit(1);
    }
    for (pI=0;pI<Size_H;pI++)
        for (qI=0;qI<Size_W;qI++)
        {
            sum_gray=0;
            for (c=0;c<BytesPerPixel;c++)
            {
                ifile.read((char*)&In_Image_RGB[pI][qI][c],sizeof(In_Image_RGB[pI][qI][c]));
                if (c==0)
                    sum_gray+=0.21*(float)In_Image_RGB[pI][qI][c];
                else if (c==1)
                    sum_gray+=0.72*(float)In_Image_RGB[pI][qI][c];
                else
                    sum_gray+=0.07*(float)In_Image_RGB[pI][qI][c];
            }
            In_Image.at<uchar>(pI,qI)=(uchar)sum_gray;
        }
    
    //output the gray image
    uchar out_pixel='0';
    ofstream ofile(name_gray,ios_base::out|ios_base::binary);
    if (!ofile)
    {
        cout<<"File CANNOT open!"<<endl;
        exit(1);
    }
    for (row=0;row<Size_H;row++)
        for(col=0;col<Size_W;col++)
        {
            
            out_pixel=In_Image.at<uchar>(row,col)+0x00;
            ofile.write((char*)&out_pixel,sizeof(uchar));
        }
    ifile.close();
    ofile.close();
    
    
}
