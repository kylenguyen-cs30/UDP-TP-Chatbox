#ifndef GUI_H
#define GUI_H

#include<wx/wx.h>
#include "../include/ChatClient.h"
#include "../include/ChatServer.h"


class ChatApp : public wxApp{
    public:
        virtual bool OnInit();
};

class ChatFrame : public wxFrame{
    public:
        ChatFrame(const wxString& titile);

    private:
        wxTextCtrl* conversationCtrl;
        wxTextCtrl* inputCtrl;
        wxButton* sendButton;
        wxButton* closeButton;

        void OnSend(wxCommandEvent& e);
        void OnClose(wxCommandEvent& e);
        void OnCheckMessages(wxTimerEvent& e);

        //instance from ChatServer and ChatClient
        ChatServer server;
        ChatClient client;
        wxTimer* checkMessagesTimer; // time periodacally check for messages
};


#endif // GUI_H