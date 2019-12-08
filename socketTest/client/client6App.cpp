/*=========================================================
* Name: server6App.cpp
* Function: wxSocket Test, Client-Side
* Created: 2019-12-6
* Author: xxpcb(https://github.com/xxpcb)
* Reference: wxWidgets official samples(sockets:client.cpp)
==========================================================*/

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#  pragma hdrstop
#endif

// for all others, include the necessary headers
#ifndef WX_PRECOMP
#  include "wx/wx.h"
#endif

#include "wx/socket.h"
#include "wx/url.h"
#include "wx/sstream.h"
#include "wx/thread.h"
#include <memory>

#include "gui_c.h"
#define BUFSIZE 4096

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};

class MyFrame : public MyFrame1
{
public:
	MyFrame();
	~MyFrame();

	void OnAbout(wxCommandEvent& event);
	void OnQuit(wxCommandEvent& event);

	void OnOpenConnection(wxCommandEvent& event);
	void OnTest1(wxCommandEvent& event);
	void OnTest2(wxCommandEvent& event);
	void OnTest3(wxCommandEvent& event);
	void OnTest4(wxCommandEvent& event);
	void OnTest5(wxCommandEvent& event);
	void OnCloseConnection(wxCommandEvent& event);

	void OnDatagram(wxCommandEvent& event);
	void OnTestURL(wxCommandEvent& event);

	void OnSocketEvent(wxSocketEvent& event);
	void UpdateStatusBar();

	void TestFile();//only for file test

private:
	wxSocketClient *m_sock;
	bool            m_busy;
	wxFile file1;
	wxFile file2;
	wxString dirpath = "./file";

	// any class wishing to process wxWidgets events must use this macro
	wxDECLARE_EVENT_TABLE();
};

// simple helper class to log start and end of each test
class TestLogger
{
public:
	TestLogger(const wxString& name) : m_name(name)
	{
		wxLogMessage("=== %s begins ===", m_name);
	}

	~TestLogger()
	{
		wxLogMessage("=== %s ends ===", m_name);
	}

private:
	const wxString m_name;
};

// id for sockets
enum
{
	// id for socket
	SOCKET_ID = 100
};

// event tables and other macros for wxWidgets
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
	EVT_SOCKET(SOCKET_ID, MyFrame::OnSocketEvent) // OnSocketEvent()
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	if (!wxApp::OnInit())
		return false;

	MyFrame *frame = new MyFrame();
	frame->Show(true);
	return true;
}

MyFrame::MyFrame() : MyFrame1(NULL, wxID_ANY)
{
	wxLog::SetActiveTarget(new wxLogTextCtrl(m_text));

	// Create the socket
	m_sock = new wxSocketClient();

	//  [Setup the event handler] and subscribe to most events
	m_sock->SetEventHandler(*this, SOCKET_ID); // OnSocketEvent()
	m_sock->SetNotify(wxSOCKET_CONNECTION_FLAG | // connect
						wxSOCKET_INPUT_FLAG |    // input
						wxSOCKET_LOST_FLAG);     // lose
	m_sock->Notify(true);

	// Set the dirpath
	if (!wxDirExists(dirpath))
	{
		wxMkDir(dirpath, 0);
		m_text->AppendText("mkdir: " + dirpath + "\n");
	}
	wxSetWorkingDirectory(dirpath);
	m_text->AppendText("[Current directoy path]: " + dirpath + "\n");

	m_busy = false;
	UpdateStatusBar();

	//TestFile();
}

MyFrame::~MyFrame()
{
	// No delayed deletion here, as the frame is dying anyway
	delete m_sock;
}

//==============================================================
void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	// true is to force the frame to close
	Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
	wxMessageBox("wxSocket demo: Client\n(c) 1999 Guillermo Rodriguez Garcia\n\nModify by xxpcb (Add File Transfer Function)",
					"About Client",
					wxOK | wxICON_INFORMATION, this);
}

// we use OnOpenConnection() to open and connect to the server
void MyFrame::OnOpenConnection(wxCommandEvent& WXUNUSED(event))
{
	wxUnusedVar(wxSockAddress::IPV4); // unused in !wxUSE_IPV6 case

	wxIPV4address addr;

	// Ask user for server address
	wxString hostname = wxGetTextFromUser(
		"Enter the address of the wxSocket demo server:",
		"Connect ...",
		"localhost");
	if (hostname.empty())
		return;

	addr.Hostname(hostname);
	addr.Service(3000);

	// we connect asynchronously and will get a wxSOCKET_CONNECTION event when the connection is really established
	// if you want to make sure that connection is established right here you could call WaitOnConnect(timeout) instead
	wxLogMessage("Trying to connect to %s:%d", hostname, addr.Service());

	m_sock->Connect(addr, false);
}

void MyFrame::OnTest1(wxCommandEvent& event)
{
	// Disable socket menu entries (exception: Close Session)
	m_busy = true;
	UpdateStatusBar();

	m_text->AppendText("\n=== Test 1 begins ===\n");

	// Tell the server which test we are running
	unsigned char c = 0xBE;
	m_sock->Write(&c, 1);

	// Send some data and read it back. We know the size of the buffer, so we can specify the exact number of bytes
	// to be sent or received and use the wxSOCKET_WAITALL flag. Also, we have disabled menu entries which could 
	// interfere with the test, so we can safely avoid the wxSOCKET_BLOCK flag.

	// First we send a byte with the length of the string, then we send the string itself (do NOT try to send any integral value 
	// larger than a byte "as is" across the network, or you might be in trouble! Ever heard about big and little endian computers?)

	m_sock->SetFlags(wxSOCKET_WAITALL);

	const char *buf1 = "Test  [string] (less than 256 chars!)";
	unsigned char len = (unsigned char)(wxStrlen(buf1) + 1);
	wxCharBuffer buf2(wxStrlen(buf1));

	m_text->AppendText("Sending a test buffer with [Write]to the server ...");
	m_sock->Write(&len, 1); // send size
	m_sock->Write(buf1, len); // send data
	m_text->AppendText(m_sock->Error() ? "failed !\n" : "done\n");

	m_text->AppendText("Receiving the buffer with [Read]back from server ...");
	m_sock->Read(buf2.data(), len);
	m_text->AppendText(m_sock->Error() ? "failed !\n" : "done\n");

	m_text->AppendText("Comparing the two buffers ...");
	if (memcmp(buf1, buf2, len) != 0)
	{
		m_text->AppendText("failed!\n");
		m_text->AppendText("Test 1 failed !\n");
	}
	else
	{
		m_text->AppendText("done\n");
		m_text->AppendText("Test 1 passed !\n");
	}
	m_text->AppendText("=== Test 1 ends ===\n");

	m_busy = false;
	UpdateStatusBar();
}

void MyFrame::OnTest2(wxCommandEvent& event)
{
	// Disable socket menu entries (exception: Close Session)
	m_busy = true;
	UpdateStatusBar();

	m_text->AppendText("\n=== Test 2 begins ===\n");

	// Tell the server which test we are running
	unsigned char c = 0xCE;
	m_sock->Write(&c, 1);

	// Here we use ReadMsg and WriteMsg to send messages with a header with size information. 
	// Also, the reception is event triggered, so we test input events as well.
	// We need to set no flags here (ReadMsg and WriteMsg are not affected by flags)

	m_sock->SetFlags(wxSOCKET_WAITALL);

	wxString s = wxGetTextFromUser(
		"Enter an  [arbitrary string] to send to the server:",
		"Test 2 ...",
		"Yes I like wxWidgets!");

	const wxScopedCharBuffer msg1(s.utf8_str());
	size_t len = wxStrlen(msg1) + 1;
	wxCharBuffer msg2(wxStrlen(msg1));

	m_text->AppendText("Sending the string with [WriteMsg]...");
	m_sock->WriteMsg(msg1, len); // send data
	m_text->AppendText(m_sock->Error() ? "failed !\n" : "done\n");
	m_text->AppendText("Waiting for an event (timeout = 2 sec)\n");

	// Wait until data available (will also return if the connection is lost)
	m_sock->WaitForRead(2);

	if (m_sock->IsData())
	{
		m_text->AppendText("Reading the string with [ReadMsg]back with ReadMsg ...");
		m_sock->ReadMsg(msg2.data(), len);
		m_text->AppendText(m_sock->Error() ? "failed !\n" : "done\n");
		m_text->AppendText("Comparing the two buffers ...");
		if (memcmp(msg1, msg2, len) != 0)
		{
			m_text->AppendText("failed!\n");
			m_text->AppendText("Test 2 failed !\n");
		}
		else
		{
			m_text->AppendText("done\n");
			m_text->AppendText("Test 2 passed !\n");
		}
	}
	else
		m_text->AppendText("Timeout ! Test 2 failed.\n");

	m_text->AppendText("=== Test 2 ends ===\n");

	m_busy = false;
	UpdateStatusBar();
}

void MyFrame::OnTest3(wxCommandEvent& event)
{
	// Disable socket menu entries (exception: Close Session)
	m_busy = true;
	UpdateStatusBar();

	m_text->AppendText("\n=== Test 3 begins ===\n");

	// Tell the server which test we are running
	unsigned char c = 0xDE;
	m_sock->Write(&c, 1);

	// This test also is similar to the first one but it sends a large buffer so that wxSocket is actually 
	// forced to split it into pieces and take care of sending everything before returning.

	m_sock->SetFlags(wxSOCKET_WAITALL);

	// Note that len is in kbytes here!
	const unsigned char len = 32;
	wxCharBuffer buf1(len * BUFSIZE),
		buf2(len * BUFSIZE);

	for (size_t i = 0; i < len * BUFSIZE; i++)
		buf1.data()[i] = (char)(i % 256);

	m_text->AppendText("Sending a [large buffer](32K) to the server ...");
	m_sock->Write(&len, 1); // send size
	m_sock->Write(buf1, len * BUFSIZE); // send data
	m_text->AppendText(m_sock->Error() ? "failed !\n" : "done\n");

	m_text->AppendText("Receiving the buffer back from server ...");
	m_sock->Read(buf2.data(), len * BUFSIZE); //receive data
	m_text->AppendText(m_sock->Error() ? "failed !\n" : "done\n");

	m_text->AppendText("Comparing the two buffers ...");
	if (memcmp(buf1, buf2, len) != 0)
	{
		m_text->AppendText("failed!\n");
		m_text->AppendText("Test 3 failed !\n");
	}
	else
	{
		m_text->AppendText("done\n");
		m_text->AppendText("Test 3 passed !\n");
	}
	m_text->AppendText("=== Test 3 ends ===\n");

	m_busy = false;
	UpdateStatusBar();
}

// Send File
void MyFrame::OnTest4(wxCommandEvent& event)
{
	// Disable socket menu entries (exception: Close Session)
	m_busy = true;
	UpdateStatusBar();

	m_text->AppendText("\n=== Test 4 (Send File) begins ===\n");

	// Tell the server which test we are running
	unsigned char c = 0xEE;
	m_sock->Write(&c, 1);

	// This test also is send a File to the Service

	//m_sock->SetFlags(wxSOCKET_WAITALL); // Wait or not wait on here is not important ?

	// ------------------- Select a file 
	wxFileDialog openFileDialog(this, "Open a file", "", "", "All Files (*.*)|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	openFileDialog.ShowModal();

	wxString file1path = (const char*)openFileDialog.GetPath().mb_str();
	m_text->AppendText("[filepath]: " + file1path + "\n");
	wxString file1name = file1path.SubString(file1path.find_last_of("\\") + 1, file1path.Last());
	m_text->AppendText("[filename]: " + file1name + "\n");

	// -------------------- Send fimename to server
	m_text->AppendText("Sending the file name...");
	const wxScopedCharBuffer file1name_utf8(file1name.utf8_str());
	m_sock->WriteMsg(file1name_utf8, wxStrlen(file1name_utf8) + 1); // send file name, attention "wxStrlen(file1name) + 1" !!!
	m_text->AppendText(m_sock->Error() ? "failed !\n" : "done\n");
	m_text->AppendText("Waiting for an event (timeout = 2 sec)\n");
	// Wait until data available (will also return if the connection is lost)
	m_sock->WaitForRead(2);

	// ------------------- Open the file and check the file size
	file1.Open(file1path);
	//if (file1.IsOpened())
	//	m_text->AppendText("Open file1 ok\n");

	file1.Seek(0);
	wxFileOffset filesize = file1.Length();
	if (wxInvalidOffset == filesize) return;
	wxString str = wxString::Format("[File size]: %lld byte (%lld KB)(%lld M)\n", filesize, filesize >> 10, filesize >> 20);
	m_text->AppendText(str);

	// ------------------- send file to server
	wxUint8 * data = new wxUint8[BUFSIZE];
	int len = 0;
	while(1)
	{
		if ((len = file1.Read(data, (size_t)BUFSIZE)) && len > 0)
		{
			//wxLogMessage("%d", len);
			m_sock->Write(data, len); // send data, len !!!(not BUFSIZE)
		}
		else
			break;
	}
	delete[] data;
	file1.Close();

	m_text->AppendText("=== Test 4 ends ===\n");
	m_busy = false;
	UpdateStatusBar();
}

// Receive File
void MyFrame::OnTest5(wxCommandEvent& event)
{
	// Disable socket menu entries (exception: Close Session)
	m_busy = true;
	UpdateStatusBar();

	m_text->AppendText("\n=== Test 5 (Receive File) begins ===\n");

	// Tell the server which test we are running
	unsigned char c = 0xFE;
	m_sock->Write(&c, 1);

	// -------------------- Send fimename to server
	m_sock->SetFlags(wxSOCKET_WAITALL);
	wxString s = wxGetTextFromUser(
		"Enter the filename to get from server:",
		"Test 2 ...",
		"1.jpg");

	const wxScopedCharBuffer filename(s.utf8_str());
	size_t lens = wxStrlen(filename) + 1;

	m_text->AppendText("Sending the filename ...");
	m_sock->WriteMsg(filename, lens); // send data
	m_text->AppendText(m_sock->Error() ? "failed !\n" : "done\n");
	m_sock->WaitForRead(2);

	// ---------------------- Receive file information
	char buf[BUFSIZE];
	wxUint32 len = 0;
	len = m_sock->ReadMsg(buf, sizeof(buf)).LastCount();
	if (!len)
	{
		wxLogError("Failed to read file name.");
		return;
	}
	wxString fileinfo = wxString::FromUTF8(buf, len);
	m_text->AppendText("[receive fileinfo]: " + fileinfo);

	if (!strstr(fileinfo, "not"))
	{
		// ------------------------ Receive file
		m_sock->SetFlags(wxSOCKET_NONE); // Must use wxSOCKET_NONE !!!

		file2.Create(s, wxFile::write);
		if (file2.IsOpened())
			m_text->AppendText("Create file2 ok\n");

		wxUint8 *data = new wxUint8[BUFSIZE];
		len = 0;
		while ((len = m_sock->Read(data, BUFSIZE).LastCount()) && len > 0)
		{
			//wxLogMessage("%d", len);
			file2.Write(data, (size_t)len);

			if (len != BUFSIZE) break;
		}
		delete[] data;
		file2.Close();
		wxLogMessage("Receive the File ok");
	}


	// ------------------
	m_text->AppendText("=== Test 5 ends ===\n");
	m_busy = false;
	UpdateStatusBar();
}

// File Transport Test
void MyFrame::TestFile()
{
	// --------- Open file dialog test
	wxFileDialog openFileDialog(this, "Open a file", "", "", "All Files (*.*)|*.*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	openFileDialog.ShowModal();

	wxString file1path = (const char*)openFileDialog.GetPath().mb_str();
	m_text->AppendText("[filepath]: " + file1path + "\n");
	wxString file1name = file1path.SubString(file1path.find_last_of("\\")+1, file1path.Last());
	m_text->AppendText("[filename]: " + file1name + "\n");

	// --------- Select save path dialog test
	wxDirDialog selectDirDialog(this, "Select a direction for save file");
	selectDirDialog.ShowModal();

	wxString dirpath = (const char*)selectDirDialog.GetPath().mb_str();
	m_text->AppendText("[savepath]: " + dirpath + "\n");

	// ---------- Open file test
	file1.Open("1.jpg");
	if (file1.IsOpened())
		m_text->AppendText("Open file1 ok\n");

	file1.Seek(0);
	wxFileOffset filesize = file1.Length();
	if (wxInvalidOffset == filesize) return;
	wxString str = wxString::Format("File length : %lld\n", filesize);
	m_text->AppendText(str);

	// --------- File Read and Write Test
	file2.Create("2.jpg", wxFile::write);
	if (file2.IsOpened())
		m_text->AppendText("Create file2 ok\n");

	wxUint8 * data = new wxUint8[BUFSIZE];
	wxUint32 len = 0;
	while (1)
	{
		if ((len = file1.Read(data, (size_t)BUFSIZE)) && len > 0)
		{
			file2.Write(data, (size_t)len);
		}
		else
			break;
	}
	delete[] data;
	file1.Close();
	file2.Close();
}

void MyFrame::OnCloseConnection(wxCommandEvent& WXUNUSED(event))
{
	m_sock->Close();
	UpdateStatusBar();
}

// UDP Test
void MyFrame::OnDatagram(wxCommandEvent& WXUNUSED(event))
{
	wxString hostname = wxGetTextFromUser
		(
			"Enter the address of the wxSocket demo server:",
			"UDP peer",
			"localhost"
			);
	if (hostname.empty())
		return;

	TestLogger logtest("UDP");

	wxIPV4address addrLocal;
	addrLocal.Hostname();
	wxDatagramSocket sock(addrLocal);
	if (!sock.IsOk())
	{
		wxLogMessage("ERROR: failed to create UDP socket");
		return;
	}

	wxLogMessage("Created UDP socket at %s:%u", addrLocal.IPAddress(), addrLocal.Service());

	wxIPV4address addrPeer;
	addrPeer.Hostname(hostname);
	addrPeer.Service(3000);

	wxLogMessage("Testing UDP with peer at %s:%u", addrPeer.IPAddress(), addrPeer.Service());

	char buf[] = "Uryyb sebz pyvrag!";
	if (sock.SendTo(addrPeer, buf, sizeof(buf)).LastCount() != sizeof(buf))
	{
		wxLogMessage("ERROR: failed to send data");
		return;
	}

	if (sock.RecvFrom(addrPeer, buf, sizeof(buf)).LastCount() != sizeof(buf))
	{
		wxLogMessage("ERROR: failed to receive data");
		return;
	}

	wxLogMessage("Received \"%s\" from %s:%u.",
		wxString::From8BitData(buf, sock.LastCount()),
		addrPeer.IPAddress(), addrPeer.Service());
}

#if wxUSE_URL
// URL Test
void DoDownload(const wxString& urlname)
{
	wxString testname("URL");
	if (!wxIsMainThread())
		testname += " in worker thread";
	else
		testname += " in main thread";

	TestLogger logtest(testname);

	// Parse the URL
	wxURL url(urlname);
	if (url.GetError() != wxURL_NOERR)
	{
		wxLogError("Failed to parse URL \"%s\"", urlname);
		return;
	}

	// Try to get the input stream (connects to the given URL)
	wxLogMessage("Establishing connection to \"%s\"...", urlname);
	const std::auto_ptr<wxInputStream> data(url.GetInputStream());
	if (!data.get())
	{
		wxLogError("Failed to retrieve URL \"%s\"", urlname);
		return;
	}

	// Print the contents type and file size
	wxLogMessage("Contents type: %s\nFile size: %lu\nStarting to download...",
		url.GetProtocol().GetContentType(),
		static_cast<unsigned long>(data->GetSize()));

	// Get the data
	wxStringOutputStream sout;
	if (data->Read(sout).GetLastError() != wxSTREAM_EOF)
	{
		wxLogError("Error reading the input stream.");
	}

	wxLogMessage("Text retrieved from URL \"%s\" follows:\n%s", urlname, sout.GetString());
}

void MyFrame::OnTestURL(wxCommandEvent& WXUNUSED(event))
{
	// Ask for the URL
	static wxString s_urlname("http://www.baidu.com/");
	wxString urlname = wxGetTextFromUser
		(
			"Enter an URL to get",
			"URL:",
			s_urlname
			);
	if (urlname.empty())
		return; // cancelled by user

	s_urlname = urlname;

	// First do it in this (main) thread.
	DoDownload(urlname);

	// And then also in a worker thread.
#if wxUSE_THREADS
	class DownloadThread : public wxThread
	{
	public:
		explicit DownloadThread(const wxString& url) : m_url(url)
		{
			Run();
		}

		virtual void* Entry()
		{
			DoDownload(m_url);
			return NULL;
		}

	private:
		const wxString m_url;
	};

	// NB: there is a race condition here, we don't check for this thread
	// termination before exiting the application, don't do this in real code!
	new DownloadThread(urlname);
#endif // wxUSE_THREADS
}

#endif // wxUSE_URL

// we use OnSocketEvent() to show socket event type
void MyFrame::OnSocketEvent(wxSocketEvent& event)
{
	switch (event.GetSocketEvent())
	{
	case wxSOCKET_INPUT:
		wxLogMessage("Input available on the socket");
		break;

	case wxSOCKET_LOST:
		wxLogMessage("Socket connection was unexpectedly lost.");
		UpdateStatusBar();
		break;

	case wxSOCKET_CONNECTION:
		wxLogMessage("... socket is now connected.");
		UpdateStatusBar();
		break;

	default:
		wxLogMessage("Unknown socket event!!!");
		break;
	}
}

// convenience functions
void MyFrame::UpdateStatusBar()
{
	wxString s;

	if (!m_sock->IsConnected())
	{
		s = "Not connected";
	}
	else
	{
		wxIPV4address addr;
		// we use GetPeer() to get the opposite info
		m_sock->GetPeer(addr);
		s.Printf("%s : %d", addr.Hostname(), addr.Service());
	}
	SetStatusText(s, 1);

	m_menuTCP->Enable(wxID_Open, !m_sock->IsConnected() && !m_busy);
	m_menuTCP->Enable(wxID_Test1, m_sock->IsConnected() && !m_busy);
	m_menuTCP->Enable(wxID_Test2, m_sock->IsConnected() && !m_busy);
	m_menuTCP->Enable(wxID_Test3, m_sock->IsConnected() && !m_busy);
	m_menuTCP->Enable(wxID_Test4, m_sock->IsConnected() && !m_busy);
	m_menuTCP->Enable(wxID_Test5, m_sock->IsConnected() && !m_busy);
	m_menuTCP->Enable(wxID_Close, m_sock->IsConnected());
}