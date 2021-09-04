#ifndef _EZN_WINMAN_H__
#define _EZN_WINMAN_H__

#include <memory>
#include <unordered_set>
#include <queue>

namespace ezn
{

class Window;

class Winman
{
public:
    Winman();
    ~Winman();

    void Close();

    void AddWindow(Window *window){ this->windows.emplace(window); }
    void RemoveWindow(Window *window){ this->windowCloseQueue.push(window); }
    void Update();

    int GetMonitorsCount();

    bool Running(){ return !this->windows.empty(); }
    void ToggleVSync(bool on);

private:
    static void ErrorCallback(int error, const char *description);

private:
    std::unordered_set<Window*> windows;
    std::queue<Window*> windowCloseQueue;
};

} // namespace ezn

#endif