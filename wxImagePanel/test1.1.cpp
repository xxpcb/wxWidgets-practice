/*=========================================================
* Name: test1.1.cpp
* Function: �򿪴�ͼƬ����ʾ���ԣ�wxImagePanel�̳��ڹ������ڣ�
* Created: 2019-01-25
* Author: xxpcb(https://github.com/xxpcb)
* �ο��ԣ�https://wiki.wxwidgets.org/An_image_panel ����wxPanel��ΪwxScrolledWindow
==========================================================*/

//====================================================================
//û�е����ߴ繦�ܵĴ���

#include <wx/wx.h>
#include <wx/sizer.h>

// �Զ����wxImagePanel�࣬���м̳��ڡ�wxPanel��
class wxImagePanel : public wxScrolledWindow//wxPanel
{
	wxBitmap image;
public:
	wxImagePanel(wxFrame* parent, wxString file, wxBitmapType format);//���캯��
	void paintEvent(wxPaintEvent & evt);//��ʾͼ�����ػ�ʱϵͳ������
	void render(wxDC& dc);//ͼ����Ⱦִ�к���
	DECLARE_EVENT_TABLE()
};


BEGIN_EVENT_TABLE(wxImagePanel, wxScrolledWindow)//wxPanel)
EVT_PAINT(wxImagePanel::paintEvent)// catch paint events
END_EVENT_TABLE()

//�Զ����wxImagePanel��Ĺ��캯�����̳��ڡ�wxPanel�����������ڼ���ͼƬ
wxImagePanel::wxImagePanel(wxFrame* parent, wxString file, wxBitmapType format) 
	: wxScrolledWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxALWAYS_SHOW_SB | wxHSCROLL | wxVSCROLL)//wxPanel(parent)
{
	// load the file... ideally add a check to see if loading was successful
	image.LoadFile(file, format);
}

void wxImagePanel::paintEvent(wxPaintEvent & evt)
{
	// depending on your system you may need to look at double-buffered dcs
	wxPaintDC dc(this);
	render(dc);
}

void wxImagePanel::render(wxDC&  dc)
{
	this->PrepareDC(dc);
	dc.DrawBitmap(image, 0, 0, false);
}


// ----------------------------------------
// how-to-use example

class MyApp : public wxApp
{
	wxFrame *frame;
	wxImagePanel * drawPane;
public:
	bool OnInit()
	{
		// make sure to call this first
		wxInitAllImageHandlers();

		// �½�һ������������
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		// �½�һ������ܡ�
		frame = new wxFrame(NULL, wxID_ANY, wxT("Hello wxDC"), wxPoint(50, 50), wxSize(800, 600));

		// then simply create like this
		// �½�һ����ͼ����塿����ӵ���������
		drawPane = new wxImagePanel(frame, wxT("../2.jpg"), wxBITMAP_TYPE_JPEG);//�˴����޸�ͼƬ·����
		drawPane->SetScrollRate(5, 5);//���ù������
		drawPane->SetVirtualSize(1920, 1080);//���û����С
		sizer->Add(drawPane, 1, wxEXPAND);

		frame->SetSizer(sizer);//�ٽ���������������
		frame->Show();

		return true;
	}

};

IMPLEMENT_APP(MyApp)