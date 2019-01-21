/*=========================================================
* Name: serialTestApp.cpp
* Function: ���ڲ���
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

//��������(�̳�����Ƶ�MyFrame1)
class serialFrame : public MyFrame1
{
public:
	serialFrame() : MyFrame1(NULL, wxID_ANY) {};
	Serial com;
private:
	void OnSelPort(wxCommandEvent& event);//���ں�
	void OnSetBaud(wxCommandEvent& event);//������
	void OnToggle(wxCommandEvent& event);//�򿪹رմ���
	void OnClearText(wxCommandEvent& event);//������տ�
	void OnSend(wxCommandEvent& event);//����
	void OnTimer(wxTimerEvent& event);//��ʱ��
};


wxIMPLEMENT_APP(serialApp);//��ʼִ��

bool serialApp::OnInit()
{
	serialFrame *frame = new serialFrame();//��������
	frame->Show(true);//��ʾ����
	return true;
}

//���ں�
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

//������
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

//�򿪹رմ���
void serialFrame::OnToggle(wxCommandEvent& event)
{
	bool state = m_toggleBtn->GetValue();
	if (state)
	{
		m_toggleBtn->SetLabel("�رմ���");
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
		m_toggleBtn->SetLabel("�򿪴���");
		m_timer.Stop();//ֹͣ��ʱ�� 
		com.Close();
		m_txtRx->AppendText(wxString::Format(wxT("Port %s is closed.\n"), com.GetPort()));
	}
}

//������տ�
void serialFrame::OnClearText(wxCommandEvent& event)
{
	m_txtRx->Clear();
}

//����
void serialFrame::OnSend(wxCommandEvent& event)
{
	wxString str = m_txtSend->GetValue();
	wxCharBuffer buffer = str.ToUTF8();
	if (com.Write(buffer.data()))
		m_txtRx->AppendText(str);
	else
		m_txtRx->AppendText(wxT("Write error.\n"));
}

//��ʱ��
void serialFrame::OnTimer(wxTimerEvent& event)
{
	char ch; bool r;
	do
	{
		ch = com.ReadChar(r);//��ȡ����
		if (r)
			m_txtRx->AppendText(wxString::Format(wxT("%c"), ch));//��ʾ��Ϣ
	} while (r);
}
