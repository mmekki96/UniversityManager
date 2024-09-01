#ifndef INITFRAME_H
#define INITFRAME_H

#include <wx/wx.h>
#include <string>
#include "sqlite/sqlite3.h"

class InitFrame : public wxFrame
{
public:
	InitFrame(const wxString &title, sqlite3* db);
private:
	wxStaticText* initTxt;
	wxTextCtrl* initPsd;
	wxButton* connect_btn;
	std::string m_psd;
	sqlite3* db;
	void onConnectClick(wxCommandEvent& event);
};


#endif // !INITFRAME_H

