#include <iostream>
#include <ezn_winman.h>
#include <ezn_window.h>

int monitorCount = 0;

void OnUpdate(ezn::Window *window)
{
    ezn::Input &input = window->GetInput();

    if(input.KeyJustPressed(ezn::KEY_F))
    {
        window->SetFullscreen(-1);
    }
    else
    {
        for(int i = 0; i < monitorCount; i++)
        {
            ezn::KeyCode code = (ezn::KeyCode)(ezn::KEY_0 + i);
            if(input.KeyJustPressed(code))
            {
                window->SetFullscreen(i);
                break;
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    ezn::Winman winman;
    monitorCount = winman.GetMonitorsCount();
    {
        ezn::Window::CreateParams params = {};
        char windowTitle[] = "EZN Fullscreen Example";
        params.dimensions = {800, 600};
        params.title = windowTitle;
        params.winman = &winman;
        ezn::Window *window = new ezn::Window(params);

        window->onUpdate = OnUpdate;

        while(winman.Running())
            winman.Update();
    }
    winman.Close();
    return EXIT_SUCCESS;
}