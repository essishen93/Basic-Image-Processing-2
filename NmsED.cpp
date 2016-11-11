//Name: Maoru Shen
//USC ID Number: 4946-8507-13
//USC Email: maorushe@usc.edu
//Submission Date: 10/11/2015
////////////////////////////////////////////////////////////////////
//Problem 2 : (a)
//This code is to use the Sobel Edge Detection and Non Maximum Supression to get the edge map
/////////////////////////////////////////////////////////////////////
//NmsED.cpp
/////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <cmath>
#include "functions.h"
using namespace cv;
using namespace std;

const int Size_H=321;   //the height of image
const int Size_W=481;   //the width of image
const int R=1;         //the radius of filtering window

void nms_ed(Mat &In_Image,char *name_nms_10,char *name_nms_15,Mat &sobel_x,Mat &sobel_y)
{
    int row=0,col=0;
    Mat Lg_Image(Size_H+2*R,Size_W+2*R,CV_8UC1);    // the enlarged input image
    Mat grad_mag(Size_H,Size_W,CV_8UC1);            // the gradient map
    Mat angle(Size_H,Size_W,CV_8UC1);    // the enlarged input image
    Mat Grad_Map_10(Size_H,Size_W,CV_8UC1);                 //the gradient map of  input image (10%)
    Mat Grad_Map_15(Size_H,Size_W,CV_8UC1);
    
    //enlarge the input image
    //the center 321X481
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
    
    //get the gradient
    int i=0,j=0;int count1=0;
    double grad_x=0,grad_y=0;
    Mat window(2*R+1,2*R+1,CV_64FC1);
    Mat Temp_Grad_Map(Size_H,Size_W,CV_64FC1);
    for (row=R;row<Size_H+R;row++)
    {
        count1++;
        //cout<<count1<<endl;
        for (col=R;col<Size_W+R;col++)
        {
            //put the pixels in the filtering window
            for (i=-R;i<1+R;i++)
                for (j=-R;j<1+R;j++)
                    window.at<double>(i+R,j+R)=Lg_Image.at<uchar>(row+i,col+j);
            grad_x=0;grad_y=0;
            for (i=0;i<2*R+1;i++)
                for (j=0;j<2*R+1;j++)
                {
                    grad_x+=window.at<double>(i,j)*sobel_x.at<double>(i,j);
                    grad_y+=window.at<double>(i,j)*sobel_y.at<double>(i,j);
                }
            //cout<<grad_x<<endl;
            //cout<<grad_y<<endl;
            //cout<<endl;
            if (abs((int)grad_x)>abs((int)grad_y))
                angle.at<uchar>(row-R,col-R)='x';
            else
                angle.at<uchar>(row-R,col-R)='y';
            Temp_Grad_Map.at<double>(row-R,col-R)=sqrt(grad_x*grad_x+grad_y*grad_y)/4;
            
        }
    }
    

    
    //find maximum and minimum gray level
    double Fmax=0,Fmin=0;
    double temp=0;
    int grad=0,temp_grad=0;
    int count=0;
    int threshold_10=(int)(Size_H*Size_W*0.9);    //%10
    int threshold_15=(int)(Size_H*Size_W*0.85);   //%15
    //int Int_Grad_Map[Size_H][Size_W];
    for (row=0;row<Size_H;row++)
        for (col=0;col<Size_W;col++)
        {
            temp=Temp_Grad_Map.at<double>(row,col);
            if (temp>Fmax)
                Fmax=temp;
            if (temp<Fmin)
                Fmin=temp;
        }
    
    //scaling to 0-255
    for (row=0;row<Size_H;row++)
        for (col=0;col<Size_W;col++)
            grad_mag.at<uchar>(row,col)=(uchar)(255*(Temp_Grad_Map.at<double>(row,col)-Fmin)/(Fmax-Fmin));
    
    //thresholding with 10% and 15%
    for (grad=0;grad<256;grad++)
        for (row=0;row<Size_H;row++)
            for (col=0;col<Size_W;col++)
            {
                temp_grad=(int)grad_mag.at<uchar>(row,col);
                //cout<<temp_grad<<endl;
                if (temp_grad==grad)
                {
                    count++;
                    if (count<threshold_15)
                    {
                        Grad_Map_10.at<uchar>(row,col)=0;
                        Grad_Map_15.at<uchar>(row,col)=0;
                    }
                    else if (count>threshold_15 && count<threshold_10+1)
                    {
                        Grad_Map_10.at<uchar>(row,col)=0;
                        Grad_Map_15.at<uchar>(row,col)=grad_mag.at<uchar>(row,col);
                    }
                    else
                    {
                        Grad_Map_10.at<uchar>(row,col)=grad_mag.at<uchar>(row,col);
                        Grad_Map_15.at<uchar>(row,col)=grad_mag.at<uchar>(row,col);
                    }
                }
            }
    
    //Non maximum suppress (10%)
    for (row=1;row<Size_H-1;row++)
        for (col=1;col<Size_W-1;col++)
        {
            if ((int)Grad_Map_10.at<uchar>(row,col)!=0)
            {
                if (angle.at<uchar>(row,col)=='x')
                {
                    if (Grad_Map_10.at<uchar>(row,col)>=Grad_Map_10.at<uchar>(row,col-1) && Grad_Map_10.at<uchar>(row,col)>=Grad_Map_10.at<uchar>(row,col+1))
                        Grad_Map_10.at<uchar>(row,col)=255;
                    else
                        Grad_Map_10.at<uchar>(row,col)=0;
                }
                
                else
                {
                    if (Grad_Map_10.at<uchar>(row,col)>=Grad_Map_10.at<uchar>(row-1,col) && Grad_Map_10.at<uchar>(row,col)>=Grad_Map_10.at<uchar>(row+1,col))
                        Grad_Map_10.at<uchar>(row,col)=255;
                    else
                        Grad_Map_10.at<uchar>(row,col)=0;
                }
            }
        }
    
    //Non maximum suppress (15%)
    for (row=1;row<Size_H-1;row++)
        for (col=1;col<Size_W-1;col++)
        {
            if ((int)Grad_Map_15.at<uchar>(row,col)!=0)
            {
                if (angle.at<uchar>(row,col)=='x')
                {
                    if (Grad_Map_15.at<uchar>(row,col)>=Grad_Map_15.at<uchar>(row,col-1) && Grad_Map_15.at<uchar>(row,col)>=Grad_Map_15.at<uchar>(row,col+1))
                        Grad_Map_15.at<uchar>(row,col)=255;
                    else
                        Grad_Map_15.at<uchar>(row,col)=0;
                }
                
                else
                {
                    if (Grad_Map_15.at<uchar>(row,col)>=Grad_Map_15.at<uchar>(row-1,col) && Grad_Map_15.at<uchar>(row,col)>=Grad_Map_15.at<uchar>(row+1,col))
                        Grad_Map_15.at<uchar>(row,col)=255;
                    else
                        Grad_Map_15.at<uchar>(row,col)=0;
                }
            }
        }
    
    
    //output the gray image
    unsigned char out_pixel_10='0',out_pixel_15='0';
    ofstream ofile_10(name_nms_10,ios_base::out|ios_base::binary);
    if (!ofile_10)
    {
        cout<<"File CANNOT open!"<<endl;
        exit(1);
    }
    ofstream ofile_15(name_nms_15,ios_base::out|ios_base::binary);
    if (!ofile_15)
    {
        cout<<"File CANNOT open!"<<endl;
        exit(1);
    }
    for (row=0;row<Size_H;row++)
        for(col=0;col<Size_W;col++)
        {
            
            out_pixel_10=Grad_Map_10.at<uchar>(row,col)+0x00;
            out_pixel_15=Grad_Map_15.at<uchar>(row,col)+0x00;
            
            if (out_pixel_10==0)
                out_pixel_10=255;
            else
                out_pixel_10=0;
            if (out_pixel_15==0)
                out_pixel_15=255;
            else
                out_pixel_15=0;
            
            ofile_10.write((char*)&out_pixel_10,sizeof(uchar));
            ofile_15.write((char*)&out_pixel_15,sizeof(uchar));
        }
    ofile_10.close();
    ofile_15.close();
}
