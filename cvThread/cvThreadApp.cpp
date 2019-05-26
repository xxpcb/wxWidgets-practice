/*=========================================================
* Name: cvThreadApp.cpp
* Function: OpenCV+Camera+Thread+wxWidgets ���߳�OpenCVͼ�������
* Created: 2019-05-26
* Author: xxpcb(https://github.com/xxpcb)
* Bug: ������ͷ����û�йر�����ͷ��ֱ�ӵ㴰�����ϽǵĲ���˳��ᱨ��Ŀǰ��֪��ν��
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
list<Mat> frameSeq;//֡����
VideoCapture cap;
mutex mutex_frame, mutex_process;
condition_variable cond_process;
bool stop = false;
vector<thread> mythreads;

//��������(�̳�����Ƶ�MyFrame1)
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

wxIMPLEMENT_APP(calcApp);//��ʼִ��

bool calcApp::OnInit()
{
	frame = new myframe();//��������
	frame->Show(true);//��ʾ����
	return true;
}

void myframe::OnButton(wxCommandEvent& event)
{
	bool state = m_toggleBtn->GetValue();
	if (state)
	{
		cap.set(CAP_PROP_FRAME_WIDTH, 480);
		cap.set(CAP_PROP_FRAME_HEIGHT, 360);
		cap.open(0);//0���ʼǱ��Դ�����ͷ 1���ⲿUSB����ͷ
		if (!cap.isOpened())//����Ƿ�ɹ���
		{
			return;
		}

		m_toggleBtn->SetLabel("�ر�����ͷ");

		stop = false;
		mythreads.push_back(thread(&myframe::capture, frame));
		mythreads.push_back(thread(&myframe::control, frame));
		mythreads.push_back(thread(&myframe::Proce_gray, frame));
		mythreads.push_back(thread(&myframe::Proce_contours, frame));
		mythreads.push_back(thread(&myframe::Proce_surf, frame));//surf�㷨�ر�����CPU,��ע�͵��������
	}
	else
	{
		m_toggleBtn->SetLabel("������ͷ");

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


//����ͷ�������߳�
void myframe::capture()
{
	Mat capframe;
	while (!stop)
	{
		cap >> capframe;
		mutex_frame.lock();//����frameSeq
		frameSeq.push_front(capframe);
		mutex_frame.unlock();
		this_thread::sleep_for(chrono::milliseconds(100));//���������ٶ�
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
			mutex_frame.lock();//����frameSeq
			mutex_process.lock();//����frame
			srcImg = frameSeq.back();//�����ж�����
			sprintf(temp, "frame:%05d", i++);//��֡����ֵ��һ��
			putText(srcImg, temp, Point(10, 40), FONT_HERSHEY_SIMPLEX, 1.5, Scalar(155), 2, 8);
			mutex_process.unlock();
			cond_process.notify_all();//�������д����߳�
			//���notify_all()�����õĲ��Ƿǳ����ʣ���Ȼ��֪ͨ���еȴ������̣߳������߳�֮�仹�ǻ��⣬����ͬʱ��ȡ֡��

			frameSeq.pop_back();//������ɾ�����ݣ���βɾ����
			mutex_frame.unlock();
			wxBitmap imwx = wx_from_mat(srcImg);//Mat ת wxBitmap
			wxClientDC dc(m_panel1);
			dc.DrawBitmap(imwx, 0, 0);
		}
	}
	wxClientDC dc(m_panel1);
	dc.Clear();
}

//�ҶȻ��������߳�
void myframe::Proce_gray()
{
	Mat grayImg;
	while (!stop)
	{
		unique_lock<mutex> locker_gray(mutex_process);
		cond_process.wait(locker_gray);//����frame
		Mat src = srcImg.clone();
		locker_gray.unlock();//��ǰ����

		cvtColor(src, grayImg, COLOR_RGB2GRAY);
		wxBitmap imwx = wx_from_mat(grayImg);//Mat ת wxBitmap
		wxClientDC dc(m_panel2);
		dc.DrawBitmap(imwx, 0, 0);
	}
	wxClientDC dc(m_panel2);
	dc.Clear();
}

//�����������߳�
void myframe::Proce_contours()
{
	Mat contoursImg;
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	while (!stop)
	{
		unique_lock<mutex> locker_contours(mutex_process);
		cond_process.wait(locker_contours);//����frame
		Mat src = srcImg.clone();
		locker_contours.unlock();//��ǰ����

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

		wxBitmap imwx = wx_from_mat(contoursImg);//Mat ת wxBitmap
		wxClientDC dc(m_panel3);
		dc.DrawBitmap(imwx, 0, 0);
	}
	wxClientDC dc(m_panel3);
	dc.Clear();
}

//SURF���������߳�
void myframe::Proce_surf()
{
	int minHessian = 400;//SURF�㷨��hessian��ֵ
	Ptr<SURF> detector = SURF::create(minHessian);//����һ��Ptr<SURF> detector ָ�����
	vector<KeyPoint> keypoints;//vectorģ���࣬��Ŷ�̬����
	Mat img_keypoints;
	while (!stop)
	{
		unique_lock<mutex> locker_surf(mutex_process);
		cond_process.wait(locker_surf);//����frame
		Mat src = srcImg.clone();
		locker_surf.unlock();//��ǰ����

		detector->detect(src, keypoints);
		drawKeypoints(src, keypoints, img_keypoints, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
		wxBitmap imwx = wx_from_mat(img_keypoints);//Mat ת wxBitmap
		wxClientDC dc(m_panel4);
		dc.DrawBitmap(imwx, 0, 0);
	}
	wxClientDC dc(m_panel4);
	dc.Clear();
}