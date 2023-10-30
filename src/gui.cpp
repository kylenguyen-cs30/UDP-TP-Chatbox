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

    // initialize chatserver
    server.initialize(3515);
    // initialize chatclient
    client.initialize("127.0.0.1" , 3515, 3514);

    // initialize the timer to check for the messages
    checkMessagesTimer = new wxTimer(this, wxID_ANY);
    Bind(wxEVT_TIMER, &ChatFrame::OnCheckMessages, this, checkMessagesTimer->getId());
    checkMessagesTimer->Start(1000); //check every second


}

void ChatFrame::OnCheckMessages(wxTimerEvent& event){}

void ChatFrame::OnSend(wxCommandEvent& e){
    // handle send logic
}

void ChatFrame::OnClose(wxCommandEvent& e){
    checkMessagesTimer->stop();
    server.shutdown();
    client.shutdown();
    Close(true);
}
