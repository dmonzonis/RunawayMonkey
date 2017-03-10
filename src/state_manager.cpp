#include "state_manager.h"

void StateManager::update(sf::Time dt)
{
    for (auto it = stateStack.rbegin(); it != stateStack.rend(); ++it)
    {
        if (!(*it)->update(dt))
            return;
    }
    applyChanges();
}

void StateManager::draw()
{
    for (State::Ptr& state : stateStack)
        state->draw();
}

void StateManager::handleEvent(const sf::Event& event)
{
    //Iterate over the active stateStack in reverse order
    for (auto it = stateStack.rbegin(); it != stateStack.rend(); ++it)
    {
        //If the state returns false on handleEvent, it doesn't want to let lower
        //stateStack get the input, so stop running the function
        if (!(*it)->handleEvent(event))
            return;
    }
    applyChanges();
}

void StateManager::pushState(States::ID id)
{
    pendingChanges.push_back(Change(Push, id));
}

void StateManager::popState()
{
    pendingChanges.push_back(Change(Pop));
}

void StateManager::clearStates()
{
    pendingChanges.push_back(Change(Clear));
}

//Finds a registered state and returns a smart pointer to the
//newly created state
State::Ptr StateManager::createState(States::ID id)
{
    auto found = stateFactory.find(id);
    assert(found != stateFactory.end());
    return found->second();
}

//Applies all pending changes one by one, then clears the pending changes list
void StateManager::applyChanges()
{
    for (Change change : pendingChanges)
    {
        switch (change.action)
        {
        case Push:
            stateStack.push_back(createState(change.id));
            break;
        case Pop:
            stateStack.pop_back();
            break;
        case Clear:
            stateStack.clear();
            break;
        }
    }

    pendingChanges.clear();
}

StateManager::Change::Change(Action action, States::ID id)
    : action(action)
    , id(id)
{
}
