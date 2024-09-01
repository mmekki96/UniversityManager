#include "adminFrame.h"
#include "form.h"
#include "manage.h"
#include <string>

AdminFrame::AdminFrame(const wxString& title, sqlite3* db, wxString* name) :
	wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 400)), m_db(db)
{
	this->SetBackgroundColour(*wxWHITE);
	wxPanel* panel = new wxPanel(this, wxID_ANY);
	wxBoxSizer* boxsizer = new wxBoxSizer(wxVERTICAL);
	wxString welcomeMessage = wxString::Format("Welcome to our application, " + *name + "!");
	welcometxt = new wxStaticText(panel, wxID_ANY, welcomeMessage, wxDefaultPosition, wxDefaultSize);
	boxsizer->Add(panel, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 40);
	this->SetSizer(boxsizer);

	menubar = new wxMenuBar();
	action = new wxMenu();
	option = new wxMenu();
	
	action->Append(wxID_ADD, "&New");
	action->Append(wxID_EDIT, "&Manage");

	option->Append(wxID_EDIT, "&Help");
	option->AppendSeparator();
	option->Append(wxID_EXIT, "&Exit");

	menubar->Append(action, "&File");
	menubar->Append(option, "&Options");
	
	SetMenuBar(menubar);
	action->Bind(wxEVT_MENU, &AdminFrame::onClickAdd, this, wxID_ADD);
	action->Bind(wxEVT_MENU, &AdminFrame::onClickManage, this, wxID_EDIT);
	option->Bind(wxEVT_MENU, &AdminFrame::onClickExit, this, wxID_EXIT);
}

void AdminFrame::onClickAdd(wxCommandEvent& event)
{
	std::string createTableStudent = "CREATE TABLE IF NOT EXISTS Students ("
		"id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"name TEXT NOT NULL, "
		"lastname TEXT NOT NULL, "
		"cin TEXT UNIQUE NOT NULL, "
		"email TEXT UNIQUE NOT NULL, "
		"gender TEXT CHECK(gender IN ('Male', 'Female')), "
		"birthdate TEXT, "
		"phone TEXT);";
	char* errormsg;
	int exit = sqlite3_exec(m_db, createTableStudent.c_str(), NULL, 0, &errormsg);
	if (exit != SQLITE_OK)
	{
		wxLogError("SQL error %s", errormsg);
		sqlite3_free(errormsg);
	}
	const char* createTableUser = "CREATE TABLE IF NOT EXISTS Admins (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT NOT NULL, password TEXT NOT NULL);";
	exit = sqlite3_exec(m_db, createTableUser, NULL, 0, &errormsg);
	if (exit != SQLITE_OK)
	{
		wxLogError("SQL error %s", errormsg);
		sqlite3_free(errormsg);
	}

	const char* createTabelSubject = "CREATE TABLE IF NOT EXISTS Subjects (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT UNIQUE NOT NULL);";
	exit = sqlite3_exec(m_db, createTabelSubject, NULL, 0, &errormsg);
	if (exit != SQLITE_OK)
	{
		wxLogError("SQL error %s", errormsg);
		sqlite3_free(errormsg);
	}

	std::string createTableTeacher = "CREATE TABLE IF NOT EXISTS Teachers("
		"id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"name TEXT NOT NULL, "
		"lastname TEXT NOT NULL, "
		"subject TEXT NOT NULL, "
		"cin TEXT UNIQUE NOT NULL, "
		"email TEXT UNIQUE NOT NULL, "
		"gender TEXT CHECK(gender IN ('Male', 'Female')), "
		"birthdate TEXT, "
		"phone TEXT);";
	exit = sqlite3_exec(m_db, createTableTeacher.c_str(), NULL, 0, &errormsg);
	if (exit != SQLITE_OK)
	{
		wxLogError("SQL error %s", errormsg);
		sqlite3_free(errormsg);
	}

	Form* form = new Form("Add new users", m_db);
	form->Show(true);
}

void AdminFrame::onClickExit(wxCommandEvent& event)
{
	this->Close();
}

void AdminFrame::onClickManage(wxCommandEvent& event)
{
	Manage* manage = new Manage("Frame manager", m_db);
	manage->Show(true);
}