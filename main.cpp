#include "initFrame.h"
#include "sqlite/sqlite3.h"

class myApp : public wxApp
{
public:
	virtual bool OnInit();
	int OnExit();
private:
	sqlite3* db;
};


bool myApp::OnInit()
{
	int exit = sqlite3_open("university.db", &db);
	if (exit)
	{
		wxLogError("Can't open Database %s", sqlite3_errmsg(db));
		return false;
	}
	InitFrame* init = new InitFrame("My new App", db);
	init->Show(true);
	return true;
}

int myApp::OnExit()
{
	sqlite3_close(db);
	return 0;
}


IMPLEMENT_APP(myApp);