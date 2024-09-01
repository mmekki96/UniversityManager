#ifndef FRAME_H
#define	FRAME_H

#include <wx/wx.h>
#include <vector>
#include "sqlite/sqlite3.h"

class myFrame : public wxFrame
{
public:
	myFrame(const wxString& title, sqlite3 *db);
private:
	void onSignClick(wxCommandEvent& event);
	wxStaticText* user_id_label, * user_psd_label;
	wxTextCtrl *user_id, *user_psd;
	wxButton* sign_btn;
	std::string data_user_id, data_user_psd;
	sqlite3* m_db;
	sqlite3_stmt* stmt;
	DECLARE_EVENT_TABLE()
};


#endif 

