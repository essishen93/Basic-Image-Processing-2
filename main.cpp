//Name: Maoru Shen
//USC ID Number: 4946-8507-13
//USC Email: maorushe@usc.edu
//Submission Date: 10/11/2015
////////////////////////////////////////////////////////////////////
//Problem 2 : (b)
//This code is to use the Canny Edge Detection to get the edge map
/////////////////////////////////////////////////////////////////////
//main.cpp
/////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <cmath>
#include <string>
#include "functions.h"
using namespace cv;
using namespace std;

const int Size_H=321;   //the height of image
const int Size_W=481;   //the width of image
const double totalevel = 255.0;

void get_gray(char *name_rgb,char *name_gray,Mat &In_Image);

int main()
{
    int row=0,col=0;
    
    Mat In_Image_Farm(Size_H,Size_W,CV_8UC1);                 //the gray input image
    Mat In_Image_Cgar(Size_H,Size_W,CV_8UC1);                 //the gray input image
    
    Mat Edge_Image_Farm_Canny(Size_H,Size_W,CV_8UC1);                 //the edge image by Canny
    Mat Edge_Image_Cgar_Canny(Size_H,Size_W,CV_8UC1);                 //the edge image by Canny
    
    char namef_rgb[]="Farm.raw";
    char namef_gray[]="Farm_gray.raw";
    
    char namec_rgb[]="Cougar.raw";
    char namec_gray[]="Cougar_gray.raw";
    
    
    //RGB to Gray
    get_gray(namef_rgb,namef_gray,In_Image_Farm);   //rgb to gray
    get_gray(namec_rgb,namec_gray,In_Image_Cgar);   //rgb to gray
    
    //Canny edge detection
    Canny(In_Image_Farm,Edge_Image_Farm_Canny,totalevel*0.4,totalevel*0.5,3,true);
    Canny(In_Image_Cgar,Edge_Image_Cgar_Canny,totalevel*0.4,totalevel*0.5,3,true);
    
    //
    unsigned char out_pixel_10='0',out_pixel_15='0';
    ofstream ofile_fCanny("Farm_canny5.raw",ios_base::out|ios_base::binary);
    if (!ofile_fCanny)
    {
        cout<<"File CANNOT open!"<<endl;
        exit(1);
    }
    ofstream ofile_cCanny("Cougar_canny5.raw",ios_base::out|ios_base::binary);
    if (!ofile_cCanny)
    {
        cout<<"File CANNOT open!"<<endl;
        exit(1);
    }
    for (row=0;row<Size_H;row++)
        for(col=0;col<Size_W;col++)
        {
            out_pixel_10=Edge_Image_Farm_Canny.at<uchar>(row,col)+0x00;
            out_pixel_15=Edge_Image_Cgar_Canny.at<uchar>(row,col)+0x00;
            
            if (out_pixel_10==0)
                out_pixel_10=255;
            else
                out_pixel_10=0;
            if (out_pixel_15==0)
                out_pixel_15=255;
            else
                out_pixel_15=0;
            
            ofile_fCanny.write((char*)&out_pixel_10,sizeof(uchar));
            ofile_cCanny.write((char*)&out_pixel_15,sizeof(uchar));
        }
    ofile_fCanny.close();
    ofile_cCanny.close();
    
    cout<<"The end"<<endl;
    getchar();
    return 0;
    
}

