#ifndef _EZN_WINMAN_H__
#define _EZN_WINMAN_H__

#include <memory>
#include <unordered_set>

namespace ezn
{

class Window;

class Winman
{
public:
    Winman();
    ~Winman();

    Window *CreateWindow();

private:
    static void ErrorCallback(int error, const char *description);

private:
    std::unordered_set<Window*> windows;
};

} // namespace ezn

#endif