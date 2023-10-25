#include "../include/GUI.h"



ChatFrame::ChatFrame(const wxString& title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400,300)){
    wxPanel* panel = new wxPanel(this, wxID_ANY);

    conversationCtrl= new wxTextCtrl(panel,wxID_ANY, "",wxDefaultPosition, wxSize(-1,200), wxTE_MULTILINE | wxTE_READONLY);
    inputCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    sendButton = new wxButton(panel, wxID_ANY, "Send");
    closeButton = new wxButton(panel, wxID_ANY, "Close");

    wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);
    
    vbox->Add(conversationCtrl,1,wxEXPAND | wxALL, 10);
    vbox->Add(inputCtrl,0,wxEXPAND | wxLEFT | wxRIGHT, 10);
    vbox->Add(sendButton,0,wxALL, 10);
    vbox->Add(closeButton,0,wxALL, 10);

    panel->SetSizer(vbox);

    //Bind events
    Bind(wxEVT_BUTTON, &ChatFrame::OnSend, this, sendButton->GetId());
    Bind(wxEVT_BUTTON, &ChatFrame::OnClose, this, closeButton->GetId());


}

void ChatFrame::OnSend(wxCommandEvent& e){
    // handle send logic
}

void ChatFrame::OnClose(wxCommandEvent& e){
    Close(true);
}
