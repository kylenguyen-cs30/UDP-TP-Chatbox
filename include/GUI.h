#ifndef GUI_H
#define GUI_H

#include<wx/wx.h>
#include "../include/ChatClient.h"
#include "../include/ChatServer.h"


enum class Mode {
    SERVER,
    CLIENT
};


class ChatApp : public wxApp{
    public:
        virtual bool OnInit();
};



class ChatFrame : public wxFrame{
    public:
        ChatFrame(const wxString& titile, Mode m);

    private:
        Mode mode; // to store whether the gui is acting as SERVER or CLIENT

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