#pragma once

#include <string>

// Action states for preventing memory bugs
enum Action
{
    NONE,
    MOVE_NODE,
    CREATE_SHAPE,
};

// Get string name of Action
std::string ActionToString(Action action);
