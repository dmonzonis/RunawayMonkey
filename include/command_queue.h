/**
 * @file command_queue.h
 * @author Daniel Monzonís
 */

#pragma once

#include "command.h"

#include <queue>
#include <cassert>

/**
 * @brief Queue of Command objects with custom methods.
 *
 * CommandQueue holds a queue of Command objects, with methods
 * to push a command in and get a command out of the queue, using
 * the FIFO method.
 */
class CommandQueue
{
public:
    /**
     * Push command at the end of the queue.
     *
     * @param command Reference to the command to be inserted into the queue.
     */
    void push(const Command& command);

    /**
     * Get the command at the beginning of the queue and remove it from
     * the queue.
     *
     * @return The first Command object inserted to the queue that
     * has not been removed yet.
     */
    Command pop();

    /**
     * Checks if the queue is empty.
     *
     * @return true if the queue has no commands, false otherwise.
     */
    bool isEmpty() const;

private:
    std::queue<Command> commandQueue;
};
