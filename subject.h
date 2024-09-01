#ifndef SUBJECT_H
#define SUBJECT_H

#include <wx/wx.h>
#include "sqlite/sqlite3.h"

class Subject : public wxPanel
{
public:
	Subject(wxWindow* parent, sqlite3* db);
private:
	wxStaticText* txt;
	wxTextCtrl* txt_ctrl;
	wxButton* submit_btn, *close_btn;
	wxGridSizer* grid;
	sqlite3* m_db;
	sqlite3_stmt* stmt;

	void onClickSubmit(wxCommandEvent& event);
};


#endif // !SUBJECT_H
