#include <iostream>

#include <ezn_winman.h>
#include <ezn_window.h>

int main(int argc, char *argv[])
{
    ezn::Winman winman;
    winman.ToggleVSync(true);
    {
        ezn::Window::CreateParams windowParams = {};
        char windowTitle[] = "easy native window";
        windowParams.dimensions = {1280, 720};
        windowParams.title = windowTitle;
        windowParams.winman = &winman;
        std::shared_ptr<ezn::Window> window = std::make_shared<ezn::Window>(windowParams);

        window->SetFullscreen(0);

        window->onUpdate = [](ezn::Window *window)
        {
            ezn::Input &input = window->GetInput();
            if(input.IsKeyPressed(ezn::KeyCode::KEY_ESC))
            {
                window->Close();
                return;
            }

            if(input.IsKeyPressed(ezn::KEY_K))
            {
                printf("k is being pressed\n");
            }

            if(input.KeyJustPressed(ezn::KeyCode::KEY_J))
            {
                printf("j was just pressed\n");
            }

            if(input.KeyReleased(ezn::KeyCode::KEY_L))
            {
                printf("L was just released\n");
            }
        };

        while(winman.Running())
        {
            winman.Update();
        }
    }
    winman.Close();

    return EXIT_SUCCESS;
}