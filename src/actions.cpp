#include "actions.hpp"

#include <string>

std::string ActionToString(Action action)
{
    switch (action)
    {
        case Action::CREATE_SHAPE:
            return "Create Shape";
        case Action::MOVE_NODE:
            return "Move Node";
        default:
            return "None";
    }
}
