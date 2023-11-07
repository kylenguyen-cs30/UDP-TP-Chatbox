#include "../include/GUI.h"

ChatFrame::ChatFrame(const wxString &title, Mode m) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(400, 300)), mode(m)
{
    wxPanel *panel = new wxPanel(this, wxID_ANY);

    conversationCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(-1, 200), wxTE_MULTILINE | wxTE_READONLY);
    inputCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    sendButton = new wxButton(panel, wxID_ANY, "Send");
    closeButton = new wxButton(panel, wxID_ANY, "Close");

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    vbox->Add(conversationCtrl, 1, wxEXPAND | wxALL, 10);
    vbox->Add(inputCtrl, 0, wxEXPAND | wxLEFT | wxRIGHT, 10);
    vbox->Add(sendButton, 0, wxALL, 10);
    vbox->Add(closeButton, 0, wxALL, 10);

    panel->SetSizer(vbox);

    // Bind events
    Bind(wxEVT_BUTTON, &ChatFrame::OnSend, this, sendButton->GetId());
    Bind(wxEVT_BUTTON, &ChatFrame::OnClose, this, closeButton->GetId());

    //set title for window
    if (mode == Mode::SERVER)
    {
        this->SetTitle("Chat App - Server Mode");
    }else{
        this->SetTitle("Chat App - Client Mode");
    }
    

    // initalize server and client via conditional logic
    if (mode == Mode::SERVER)
    {
        server.initialize(3515);
    }
    else
    {
        client.initialize("127.0.0.1", 3515, 3514);
    }

    // initialize the timer to check for the messages
    checkMessagesTimer = new wxTimer(this, wxID_ANY);
    Bind(wxEVT_TIMER, &ChatFrame::OnCheckMessages, this, checkMessagesTimer->GetId());
    checkMessagesTimer->Start(6000); // check every second
}

void ChatFrame::OnCheckMessages(wxTimerEvent &event)
{
    std::string receivedMessage;
    if (mode == Mode::SERVER)
    {
        receivedMessage = server.listenForMessages();
    }
    else
    {
        receivedMessage = client.listenForMessages();
    }

    if (!receivedMessage.empty())
    {
        conversationCtrl->AppendText(receivedMessage + "\n");
    }
    
    


    // Check for the server message

    // check for the client message
}

void ChatFrame::OnSend(wxCommandEvent &e)
{
    // handle send logic
    wxString message = inputCtrl->GetValue();
    conversationCtrl->AppendText(message + "\n");

    if (mode == Mode::SERVER)
    {
        server.sendMessage(message.c_str());
    }
    else
    {
        client.sendMessage(message.c_str());
    }
}

void ChatFrame::OnClose(wxCommandEvent &e)
{
    checkMessagesTimer->Stop();

    if (mode == Mode::SERVER)
    {
        server.shutdown();
    }
    else if (mode == Mode::CLIENT)
    {
        client.shutdown();
    }

    Close(true);
}


/*
ISSUE :
- the application is still very slow 

*/