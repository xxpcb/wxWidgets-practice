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

    if(img.channels()==1) //=====[�Ҷ�ͼ]
		cvtColor(img, im2, COLOR_GRAY2RGB);
	else if (img.channels() == 4) //=====[4ͨ����ͼ]
		cvtColor(img, im2, COLOR_BGRA2RGB);
    else //=====[3ͨ����ͼ]
		cvtColor(img, im2, COLOR_BGR2RGB);

	long imsize = im2.rows*im2.cols*im2.channels();//ͼ���С����*��*ͨ����
    wxImage wx(im2.cols, im2.rows,(unsigned char*)malloc(imsize), false);//����ͬ����С���ڴ�
	unsigned char* s=im2.data;//Matͼ��ָ��
	unsigned char* d=wx.GetData();//wxImageͼ��ָ��
	for (long i = 0; i < imsize; i++) 
		d[i] = s[i];//��ֵת��ͼ��

    return wx;
}

Mat mat_from_wx(wxImage &wx) 
{
    Mat im2(Size(wx.GetWidth(),wx.GetHeight()),CV_8UC3,wx.GetData());//�������ص�
    cvtColor(im2,im2,COLOR_RGB2BGR);

    return im2;
}

