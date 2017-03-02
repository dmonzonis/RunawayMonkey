#include "command.h"

Command::Command()
    : action()
    , category(Category::None)
{
}

Command::Command(Action action, Category::Type type)
    : action(action)
    , category(type)
{
}
