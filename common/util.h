//File: util.h
//Description: Functions to convert wxImage and OpenCV Mat
//Author: Yan Naing Aye
//MIT License - Copyright (c) 2017 Yan Naing Aye

#include <wx/wx.h>
#include <opencv2/opencv.hpp>
using namespace cv;

wxImage wx_from_mat(Mat &img) 
{
    Mat im2;

    if(img.channels()==1) //=====[灰度图]
		cvtColor(img, im2, COLOR_GRAY2RGB);
	else if (img.channels() == 4) //=====[4通道彩图]
		cvtColor(img, im2, COLOR_BGRA2RGB);
    else //=====[3通道彩图]
		cvtColor(img, im2, COLOR_BGR2RGB);

	long imsize = im2.rows*im2.cols*im2.channels();//图像大小（行*列*通道）
    wxImage wx(im2.cols, im2.rows,(unsigned char*)malloc(imsize), false);//创建同样大小的内存
	unsigned char* s=im2.data;//Mat图像指针
	unsigned char* d=wx.GetData();//wxImage图像指针
	for (long i = 0; i < imsize; i++) 
		d[i] = s[i];//赋值转移图像

    return wx;
}

Mat mat_from_wx(wxImage &wx) 
{
    Mat im2(Size(wx.GetWidth(),wx.GetHeight()),CV_8UC3,wx.GetData());//重排像素点
    cvtColor(im2,im2,COLOR_RGB2BGR);

    return im2;
}

