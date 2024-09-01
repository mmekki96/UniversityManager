#ifndef MANAGESTD_H
#define MANAGESTD_H

#include <wx/wx.h>
#include "sqlite/sqlite3.h"
#include <wx/grid.h>

class ManageStd : public wxFrame
{
public:
	ManageStd(const wxString& title, sqlite3* db);
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



#endif // !MANAGESTD_H

