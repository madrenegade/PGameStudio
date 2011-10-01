#include "Game/StateManager.h"

namespace Game
{

    StateManager::StateManager()
        : currentState(0), stateChanged(false)
    {
        //ctor
    }

    StateManager::~StateManager()
    {
        //dtor
    }

    unsigned int StateManager::registerState(const char* const name)
    {
        const unsigned int id = registeredStates.size();

        registeredStates.push_back(name);

        return id;
    }

    void StateManager::switchState(const unsigned int newState)
    {
        stateChanged = true;
        currentState = newState;
    }

    unsigned int StateManager::getCurrentState() const
    {
        return currentState;
    }

    bool StateManager::hasStateChanged()
    {
        const bool changed = stateChanged;
        stateChanged = false;

        return changed;
    }

} // namespace Game
