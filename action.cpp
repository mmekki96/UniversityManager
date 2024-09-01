#include "action.h"

wxDEFINE_EVENT(EVT_TABLE_UPDATE, wxCommandEvent);

DeleteStd::DeleteStd(const wxString& title, sqlite3* db, wxWindow* parent) :
	wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize), m_db(db), m_parent(parent)
{
	this->SetBackgroundColour(*wxWHITE);
	wxPanel* panel = new wxPanel(this, wxID_ANY);
	wxBoxSizer* box_panel = new wxBoxSizer(wxVERTICAL);
	txt = new wxStaticText(panel, wxID_ANY, "Insert the student CIN to delete");
	txt_ctrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
	submit_btn = new wxButton(panel, wxID_ANY, "Delete", wxDefaultPosition, wxDefaultSize);
	submit_btn->Bind(wxEVT_BUTTON, &DeleteStd::onDeleteClick, this);
	box_panel->Add(txt, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
	box_panel->Add(txt_ctrl, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
	box_panel->Add(submit_btn, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
	panel->SetSizerAndFit(box_panel);
	this->Fit();
}

void DeleteStd::onDeleteClick(wxCommandEvent& event)
{
	wxString cin_val = txt_ctrl->GetValue();
	const char* sql_select = "SELECT name, lastname FROM Students WHERE cin = ?";
	int rc = sqlite3_prepare_v2(m_db, sql_select, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		wxLogError("Failed to prepare statement %s", sqlite3_errmsg(m_db));
		return;
	}
	sqlite3_bind_text(stmt, 1, cin_val.c_str(), -1, SQLITE_STATIC);
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		wxString name_str = wxString::FromUTF8(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
		wxString lastname_str = wxString::FromUTF8(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
		wxString message = wxString::Format("Do you want to delete student:\nName: %s\nLast name: %s", name_str.MakeCapitalized(), lastname_str.MakeUpper());
		alert_msg = new wxMessageDialog(this, message, "Alert dialog", wxYES_NO | wxICON_QUESTION);
		int response = alert_msg->ShowModal();
		if (response == wxID_YES)
		{
			const char* sql_delete = "DELETE FROM Students WHERE cin = ?";
			sqlite3_stmt* delete_stmt;
			int del = sqlite3_prepare_v2(m_db, sql_delete, -1, &delete_stmt, NULL);
			if (del != SQLITE_OK)
			{
				wxLogError("Failed to prepare statement %s", sqlite3_errmsg(m_db));
				return;
			}
			sqlite3_bind_text(delete_stmt, 1, cin_val.c_str(), -1, SQLITE_STATIC);
			if (sqlite3_step(delete_stmt) == SQLITE_DONE)
			{
				wxCommandEvent updateEvent(EVT_TABLE_UPDATE);
				wxPostEvent(m_parent, updateEvent);
			}
			else
			{
				wxMessageBox("Failed to delete student", "Error", wxOK | wxICON_ERROR);
			}
			sqlite3_finalize(delete_stmt);
		}
		else
			alert_msg->Destroy();
	}
	else
		wxLogError("No student found with the given CIN");
	
	sqlite3_finalize(stmt);
	
}

DeleteUsr::DeleteUsr(const wxString& title, sqlite3* db, wxWindow* parent) :
	wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize), m_db(db), m_parent(parent)
{
	this->SetBackgroundColour(*wxWHITE);
	wxPanel* panel = new wxPanel(this, wxID_ANY);
	wxBoxSizer* box_panel = new wxBoxSizer(wxVERTICAL);
	txt = new wxStaticText(panel, wxID_ANY, "Insert the user ID to delete");
	txt_ctrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
	submit_btn = new wxButton(panel, wxID_ANY, "Delete", wxDefaultPosition, wxDefaultSize);
	submit_btn->Bind(wxEVT_BUTTON, &DeleteUsr::onDeleteClick, this);
	box_panel->Add(txt, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
	box_panel->Add(txt_ctrl, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
	box_panel->Add(submit_btn, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
	panel->SetSizerAndFit(box_panel);
	this->Fit();
}

void DeleteUsr::onDeleteClick(wxCommandEvent& event)
{
	wxString id_str = txt_ctrl->GetValue();
	const char* sql = "SELECT name FROM Admins WHERE id = ?";
	int rc = sqlite3_prepare_v2(m_db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		wxLogError("Failed to prepare statement %s", sqlite3_errmsg(m_db));
		return;
	}
	sqlite3_bind_text(stmt, 1, id_str.c_str(), -1, SQLITE_STATIC);
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		wxString name_str = wxString::FromUTF8(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
		wxString message = wxString::Format("Do you want to delete user ?\nName : %s", name_str.MakeCapitalized());
		alert_msg = new wxMessageDialog(m_parent, message, "Alert dialog", wxYES_NO);
		int response = alert_msg->ShowModal();
		if (response == wxID_YES)
		{
			const char* sql_del = "DELETE FROM Admins WHERE id = ?";
			sqlite3_stmt* stmt_del;
			int qr = sqlite3_prepare_v2(m_db, sql_del, -1, &stmt_del, NULL);
			if (qr != SQLITE_OK)
			{
				wxLogError("Failed to prepare statement %s", sqlite3_errmsg(m_db));
				return;
			}
			sqlite3_bind_text(stmt_del, 1, id_str.c_str(), -1, SQLITE_STATIC);
			if (sqlite3_step(stmt_del) != SQLITE_DONE)
			{
				wxLogError("Failed to delete user %s", sqlite3_errmsg(m_db));
				return;
			}
			else
			{
				wxCommandEvent updateEvent(EVT_TABLE_UPDATE);
				wxPostEvent(m_parent, updateEvent);
			}
			sqlite3_finalize(stmt_del);
		}
		
		else
		{
			alert_msg->Destroy();
		}
	}
	else
	{
		wxLogError("Cannot found user by ID given, try again!");
		return;
	}
	sqlite3_finalize(stmt);
}

DeleteTeacher::DeleteTeacher(const wxString& title, sqlite3* db, wxWindow* parent) :
	wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxDefaultSize), m_db(db), m_parent(parent)
{
	this->SetBackgroundColour(*wxWHITE);
	wxPanel* panel = new wxPanel(this, wxID_ANY);
	wxBoxSizer* box_panel = new wxBoxSizer(wxVERTICAL);
	txt = new wxStaticText(panel, wxID_ANY, "Insert the user CIN to delete");
	txt_ctrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
	submit_btn = new wxButton(panel, wxID_ANY, "Delete", wxDefaultPosition, wxDefaultSize);
	submit_btn->Bind(wxEVT_BUTTON, &DeleteTeacher::onDeleteClick, this);
	box_panel->Add(txt, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
	box_panel->Add(txt_ctrl, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
	box_panel->Add(submit_btn, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 10);
	panel->SetSizerAndFit(box_panel);
	this->Fit();
}

void DeleteTeacher::onDeleteClick(wxCommandEvent& event)
{
	wxString cin_str = txt_ctrl->GetValue();
	const char* sql = "SELECT name, lastname FROM Teachers WHERE cin = ?";
	int rc = sqlite3_prepare_v2(m_db, sql, -1, &stmt, NULL);
	if (rc != SQLITE_OK)
	{
		wxLogError("Failed to prepare statement %s", sqlite3_errmsg(m_db));
		return;
	}
	sqlite3_bind_text(stmt, 1, cin_str.c_str(), -1, SQLITE_STATIC);
	if (sqlite3_step(stmt) == SQLITE_ROW)
	{
		this->Close();
		wxString name_str = wxString::FromUTF8(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0)));
		wxString lastname_str = wxString::FromUTF8(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
		wxString message = wxString::Format("Do you want to delete user ?\nName : %s\nLast name : %s", name_str.MakeCapitalized(), lastname_str.MakeUpper());
		alert_msg = new wxMessageDialog(m_parent, message, "Alert dialog", wxYES_NO);
		int response = alert_msg->ShowModal();
		if (response == wxID_YES)
		{
			const char* sql_del = "DELETE FROM Teachers WHERE cin = ?";
			sqlite3_stmt* stmt_del;
			int qr = sqlite3_prepare_v2(m_db, sql_del, -1, &stmt_del, NULL);
			if (qr != SQLITE_OK)
			{
				wxLogError("Failed to prepare statement %s", sqlite3_errmsg(m_db));
				return;
			}
			sqlite3_bind_text(stmt_del, 1, cin_str.c_str(), -1, SQLITE_STATIC);
			if (sqlite3_step(stmt_del) != SQLITE_DONE)
			{
				wxLogError("Failed to delete user %s", sqlite3_errmsg(m_db));
				return;
			}
			else
			{
				wxCommandEvent updateEvent(EVT_TABLE_UPDATE);
				wxPostEvent(m_parent, updateEvent);
			}
			sqlite3_finalize(stmt_del);
		}

		else
		{
			alert_msg->Destroy();
		}
	}
	else
	{
		wxLogError("Cannot found user by CIN given, try again!");
		return;
	}
	sqlite3_finalize(stmt);

}