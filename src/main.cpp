#include "../include/GUI.h"

IMPLEMENT_APP(ChatApp)

bool ChatApp::OnInit(){
    ChatFrame* frame = new ChatFrame("Chat App");
    frame->Show(true);
    return true;
}


