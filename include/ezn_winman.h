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
    std::unordered_set<std::shared_ptr<Window>> windows;
};

} // namespace ezn

#endif