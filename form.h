#ifndef FORM_H
#define FORM_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include "sqlite/sqlite3.h"

class Form : public wxFrame
{
public:
	Form(const wxString& title, sqlite3* db);
private:
	sqlite3* m_db;
	wxNotebook* notebook;
};

#endif // !FORM_H

