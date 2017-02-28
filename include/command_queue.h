#pragma once

#include "command.h"

#include <queue>
#include <cassert>

class CommandQueue
{
public:
    void push(const Command& command);
    Command pop();
    bool isEmpty() const;

private:
    std::queue<Command> commandQueue;
};
