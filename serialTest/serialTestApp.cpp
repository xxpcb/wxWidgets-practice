/*=========================================================
* Name: serialTestApp.cpp
* Function: 串口测试
* Created: 2019-01-21
* Author: xxpcb(https://github.com/xxpcb)
==========================================================*/

// For compilers that support precompilation, includes "wx/wx.h".  
#include <wx/wxprec.h>  
#ifndef WX_PRECOMP  
#include <wx/wx.h>  
#endif  
#include "serialtest.h"   

#include <wx/numdlg.h>
#include "ce_serial.h"
using namespace std;

bool falg_OnPaintPannel = FALSE;

class serialApp : public wxApp
{
public:
	virtual bool OnInit();
};

//主窗口类(继承于设计的MyFrame1)
class serialFrame : public MyFrame1
{
public:
	serialFrame() : MyFrame1(NULL, wxID_ANY) {};
	Serial com;
private:
	void OnSelPort(wxCommandEvent& event);//串口号
	void OnSetBaud(wxCommandEvent& event);//波特率
	void OnToggle(wxCommandEvent& event);//打开关闭串口
	void OnClearText(wxCommandEvent& event);//清除接收框
	void OnSend(wxCommandEvent& event);//发送
	void OnTimer(wxTimerEvent& event);//定时器
};


wxIMPLEMENT_APP(serialApp);//开始执行

bool serialApp::OnInit()
{
	serialFrame *frame = new serialFrame();//窗口名称
	frame->Show(true);//显示窗口
	return true;
}

//串口号
void serialFrame::OnSelPort(wxCommandEvent& event)
{
	if (com.IsOpened())
		m_txtRx->AppendText(wxString::Format(wxT("Close Port %s first.\n"), com.GetPort()));
	else
	{
		wxString cdev = wxString::Format(wxT("%s"), com.GetPort());
		wxString device = wxGetTextFromUser(wxT("Enter the port"), wxT("Set Port"), cdev);
		string str = device.ToStdString();
		if (str.length() > 0)
			com.SetPort(str);

		m_txtRx->AppendText(wxString::Format(wxT("Port: %s\n"), com.GetPort()));
	}
}

//波特率
void serialFrame::OnSetBaud(wxCommandEvent& event)
{
	if (com.IsOpened())
		m_txtRx->AppendText(wxString::Format(wxT("Close port %s first.\n"), com.GetPort()));
	else
	{
		long n = wxGetNumberFromUser(wxT("Enter the baud rate"), wxT("Baud rate"), wxT("Set Baud Rate"), com.GetBaudRate(), 0, 1000000);
		if (n >= 0)
			com.SetBaudRate(n);

		m_txtRx->AppendText(wxString::Format(wxT("Baud rate: %ld\n"), com.GetBaudRate()));
	}
}

//打开关闭串口
void serialFrame::OnToggle(wxCommandEvent& event)
{
	bool state = m_toggleBtn->GetValue();
	if (state)
	{
		m_toggleBtn->SetLabel("关闭串口");
		if (com.Open())
			m_txtRx->AppendText(wxString::Format(wxT("Error opening port %s.\n"), com.GetPort()));
		else
		{
			m_txtRx->AppendText(wxString::Format(wxT("Port %s is opened.\n"), com.GetPort()));
			m_timer.Start(100);
		}
	}
	else
	{
		m_toggleBtn->SetLabel("打开串口");
		m_timer.Stop();//停止定时器 
		com.Close();
		m_txtRx->AppendText(wxString::Format(wxT("Port %s is closed.\n"), com.GetPort()));
	}
}

//清除接收框
void serialFrame::OnClearText(wxCommandEvent& event)
{
	m_txtRx->Clear();
}

//发送
void serialFrame::OnSend(wxCommandEvent& event)
{
	wxString str = m_txtSend->GetValue();
	wxCharBuffer buffer = str.ToUTF8();
	if (com.Write(buffer.data()))
		m_txtRx->AppendText(str);
	else
		m_txtRx->AppendText(wxT("Write error.\n"));
}

//定时器
void serialFrame::OnTimer(wxTimerEvent& event)
{
	char ch; bool r;
	do
	{
		ch = com.ReadChar(r);//读取串口
		if (r)
			m_txtRx->AppendText(wxString::Format(wxT("%c"), ch));//显示信息
	} while (r);
}
