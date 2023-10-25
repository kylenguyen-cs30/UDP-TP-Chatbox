#ifndef GUI_H
#define GUI_H

#include<wx/wx.h>

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
};


#endif // GUI_H