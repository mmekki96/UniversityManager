#ifndef USER_H
#define USER_H

#include <wx/wx.h>
#include "sqlite/sqlite3.h"

class User : public wxPanel
{
public:
	User(wxWindow* parent, sqlite3* db);
private:
	void onAddClick(wxCommandEvent& event);
	void onResetClick(wxCommandEvent& event);
	void onCancelClick(wxCommandEvent& event);
	void clearData();
	wxGridSizer* grid;
	wxButton* add_btn, * reset_btn, * cancel_btn;
	wxStaticText* name_txt, * psd_txt, *psd_ver_txt;
	wxTextCtrl* name, * password, *psd_ver;
	sqlite3* m_db;
	sqlite3_stmt* stmt;
};

#endif // !USER_H
