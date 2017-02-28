#include "command_queue.h"

void CommandQueue::push(const Command& command)
{
    commandQueue.push(command);
}

Command CommandQueue::pop()
{
    assert(!isEmpty());
    //Return first element and remove it from the queue
    Command command = commandQueue.front();
    commandQueue.pop();
    return command;
}

bool CommandQueue::isEmpty() const
{
    return commandQueue.empty();
}
