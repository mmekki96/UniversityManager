#ifndef MANAGEUSR_H
#define MANAGEUSR_H

#include <wx/wx.h>
#include <wx/grid.h>
#include "sqlite/sqlite3.h"

class ManageUsr : public wxFrame
{
public:
	ManageUsr(const wxString& title, sqlite3* db);
private:
	void onClickClose(wxCommandEvent& event);
	void onClickDelete(wxCommandEvent& event);
	void onTableUpdate(wxCommandEvent& event);
	void loadData();
	wxMenuBar* menu;
	wxMenu* file_menu;
	sqlite3* m_db;
	wxButton* close_btn;
	wxGrid* grid;
	sqlite3_stmt* stmt;
};

#endif // !MANAGEUSR_H
