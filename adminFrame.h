#ifndef ADMINFRAME_H
#define ADMINFRAME_H

#include <wx/wx.h>
#include "sqlite/sqlite3.h"

class AdminFrame : public wxFrame
{
public:
	AdminFrame(const wxString& title, sqlite3* db, wxString* name);
private:
	void onClickAdd(wxCommandEvent& event);
	void onClickExit(wxCommandEvent& event); 
	void onClickManage(wxCommandEvent& event);
	sqlite3* m_db;
	wxStaticText* welcometxt;
	wxMenuBar* menubar;
	wxMenu* action, *option;
};


#endif // !ADMINFRAME_H

