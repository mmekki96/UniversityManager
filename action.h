#ifndef ACTION_H
#define ACTION_H

#include <wx/wx.h>
#include "sqlite/sqlite3.h"

wxDECLARE_EVENT(EVT_TABLE_UPDATE, wxCommandEvent);

class DeleteStd : public wxFrame
{
public:
	DeleteStd(const wxString& title, sqlite3* db, wxWindow* parent);
private:
	void onDeleteClick(wxCommandEvent& event);
	wxStaticText* txt;
	wxTextCtrl* txt_ctrl;
	wxButton* submit_btn;
	wxMessageDialog* alert_msg;
	sqlite3* m_db;
	sqlite3_stmt* stmt;
	wxWindow* m_parent;
};

class DeleteUsr : public wxFrame
{
public:
	DeleteUsr(const wxString& title, sqlite3* db, wxWindow* parent);
private:
	void onDeleteClick(wxCommandEvent& event);
	wxStaticText* txt;
	wxTextCtrl* txt_ctrl;
	wxButton* submit_btn;
	wxMessageDialog* alert_msg;
	sqlite3* m_db;
	sqlite3_stmt* stmt;
	wxWindow* m_parent;
};

class DeleteTeacher : public wxFrame
{
public:
	DeleteTeacher(const wxString& title, sqlite3* db, wxWindow* parent);
private:
	void onDeleteClick(wxCommandEvent& event);
	wxStaticText* txt;
	wxTextCtrl* txt_ctrl;
	wxButton* submit_btn;
	wxMessageDialog* alert_msg;
	sqlite3* m_db;
	sqlite3_stmt* stmt;
	wxWindow* m_parent;
};

#endif // !ACTION_H
