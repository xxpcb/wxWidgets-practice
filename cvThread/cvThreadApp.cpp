/*=========================================================
* Name: cvThreadApp.cpp
* Function: OpenCV+Camera+Thread+wxWidgets 多线程OpenCV图像处理测试
* Created: 2019-05-26
* Author: xxpcb(https://github.com/xxpcb)
* Bug: 打开摄像头后，若没有关闭摄像头，直接点窗口右上角的叉号退出会报错，目前不知如何解决
==========================================================*/

// For compilers that support precompilation, includes "wx/wx.h".  
#include <wx/wxprec.h>  
#ifndef WX_PRECOMP  
#include <wx/wx.h>  
#endif  
#include "gui.h"

#include "../common/util.h"
#include <opencv2/opencv.hpp>
#include "opencv2/xfeatures2d.hpp"
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>
using namespace cv;
using namespace cv::xfeatures2d;
using namespace std;

Mat srcImg;
list<Mat> frameSeq;//帧序列
VideoCapture cap;
mutex mutex_frame, mutex_process;
condition_variable cond_process;
bool stop = false;
vector<thread> mythreads;

//主窗口类(继承于设计的MyFrame1)
class myframe : public MyFrame1
{
public:
	myframe() : MyFrame1(NULL, wxID_ANY) {};

private:
	void OnButton(wxCommandEvent& event);
	void capture();
	void control();
	void Proce_gray();
	void Proce_contours();
	void Proce_surf();
};

myframe *frame;
class calcApp : public wxApp
{
public:
	virtual bool OnInit();
};

wxIMPLEMENT_APP(calcApp);//开始执行

bool calcApp::OnInit()
{
	frame = new myframe();//窗口名称
	frame->Show(true);//显示窗口
	return true;
}

void myframe::OnButton(wxCommandEvent& event)
{
	bool state = m_toggleBtn->GetValue();
	if (state)
	{
		cap.set(CAP_PROP_FRAME_WIDTH, 480);
		cap.set(CAP_PROP_FRAME_HEIGHT, 360);
		cap.open(0);//0：笔记本自带摄像头 1：外部USB摄像头
		if (!cap.isOpened())//检查是否成功打开
		{
			return;
		}

		m_toggleBtn->SetLabel("关闭摄像头");

		stop = false;
		mythreads.push_back(thread(&myframe::capture, frame));
		mythreads.push_back(thread(&myframe::control, frame));
		mythreads.push_back(thread(&myframe::Proce_gray, frame));
		mythreads.push_back(thread(&myframe::Proce_contours, frame));
		mythreads.push_back(thread(&myframe::Proce_surf, frame));//surf算法特别消耗CPU,可注释掉该条语句
	}
	else
	{
		m_toggleBtn->SetLabel("打开摄像头");

		stop = true;
		cond_process.notify_all();
		for (auto& thread : mythreads)
		{
			thread.join();
		}
		cap.release();
		mythreads.clear();
	}
}


//摄像头捕获子线程
void myframe::capture()
{
	Mat capframe;
	while (!stop)
	{
		cap >> capframe;
		mutex_frame.lock();//保护frameSeq
		frameSeq.push_front(capframe);
		mutex_frame.unlock();
		this_thread::sleep_for(chrono::milliseconds(100));//减慢拍照速度
	}
}

void myframe::control()
{
	unsigned int i = 0;
	char temp[16];
	while (!stop)
	{
		if (!frameSeq.empty())
		{
			this_thread::sleep_for(chrono::milliseconds(10));
			mutex_frame.lock();//保护frameSeq
			mutex_process.lock();//保护frame
			srcImg = frameSeq.back();//队列中读数据
			sprintf(temp, "frame:%05d", i++);//【帧计数值加一】
			putText(srcImg, temp, Point(10, 40), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(155), 2, 8);
			mutex_process.unlock();
			cond_process.notify_all();//激活所有处理线程
			//这个notify_all()好像用的不是非常合适，虽然是通知所有等待的子线程，但子线程之间还是互斥，不能同时获取帧？

			frameSeq.pop_back();//队列中删除数据（队尾删除）
			mutex_frame.unlock();
			wxBitmap imwx = wx_from_mat(srcImg);//Mat 转 wxBitmap
			wxClientDC dc(m_panel1);
			dc.DrawBitmap(imwx, 0, 0);
		}
	}
	wxClientDC dc(m_panel1);
	dc.Clear();
}

//灰度化处理子线程
void myframe::Proce_gray()
{
	Mat grayImg;
	while (!stop)
	{
		unique_lock<mutex> locker_gray(mutex_process);
		cond_process.wait(locker_gray);//保护frame
		Mat src = srcImg.clone();
		locker_gray.unlock();//提前解锁

		cvtColor(src, grayImg, COLOR_RGB2GRAY);
		wxBitmap imwx = wx_from_mat(grayImg);//Mat 转 wxBitmap
		wxClientDC dc(m_panel2);
		dc.DrawBitmap(imwx, 0, 0);
	}
	wxClientDC dc(m_panel2);
	dc.Clear();
}

//轮廓查找子线程
void myframe::Proce_contours()
{
	Mat contoursImg;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	while (!stop)
	{
		unique_lock<mutex> locker_contours(mutex_process);
		cond_process.wait(locker_contours);//保护frame
		Mat src = srcImg.clone();
		locker_contours.unlock();//提前解锁

		cvtColor(src, src, COLOR_RGB2GRAY);
		blur(src, src, Size(3, 3));
		Canny(src, src, 40, 100);
		findContours(src, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
		contoursImg = Mat::zeros(src.size(), CV_8UC3);
		for (int i = 0; i < contours.size(); i++)
		{
			Scalar color(rand() & 255, rand() & 255, rand() & 255);
			drawContours(contoursImg, contours, i, color, 2, 8);
		}

		wxBitmap imwx = wx_from_mat(contoursImg);//Mat 转 wxBitmap
		wxClientDC dc(m_panel3);
		dc.DrawBitmap(imwx, 0, 0);
	}
	wxClientDC dc(m_panel3);
	dc.Clear();
}

//SURF特征点子线程
void myframe::Proce_surf()
{
	int minHessian = 400;//SURF算法中hessian阈值
	Ptr<SURF> detector = SURF::create(minHessian);//定义一个Ptr<SURF> detector 指针对象
	vector<KeyPoint> keypoints;//vector模板类，存放动态数组
	Mat img_keypoints;
	while (!stop)
	{
		unique_lock<mutex> locker_surf(mutex_process);
		cond_process.wait(locker_surf);//保护frame
		Mat src = srcImg.clone();
		locker_surf.unlock();//提前解锁

		detector->detect(src, keypoints);
		drawKeypoints(src, keypoints, img_keypoints, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
		wxBitmap imwx = wx_from_mat(img_keypoints);//Mat 转 wxBitmap
		wxClientDC dc(m_panel4);
		dc.DrawBitmap(imwx, 0, 0);
	}
	wxClientDC dc(m_panel4);
	dc.Clear();
}