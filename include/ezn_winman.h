#ifndef _EZN_WINDOW_MANAGER_H__
#define _EZN_WINDOW_MANAGER_H__

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

private:
    static void ErrorCallback(int error, const char *description);

private:
    std::unordered_set<std::shared_ptr<Window>> windows;
};

} // namespace ezn

#endif