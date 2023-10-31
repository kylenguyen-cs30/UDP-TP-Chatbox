#include "../include/GUI.h"

IMPLEMENT_APP(ChatApp)

bool ChatApp::OnInit(){
    Mode selectedMode = Mode::SERVER;
    ChatFrame* frame = new ChatFrame("Chat App" , selectedMode);
    frame->Show(true);
    return true;
}


