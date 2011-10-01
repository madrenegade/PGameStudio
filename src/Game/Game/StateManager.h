#ifndef GAME_STATEMANAGER_H
#define GAME_STATEMANAGER_H

#include "Utilities/string.h"
#include "Utilities/Memory/STLAllocator.h"

namespace Game
{

    class StateManager
    {
    public:
        StateManager();
        ~StateManager();

        unsigned int registerState(const char* const name);
        void switchState(const unsigned int newState);

        unsigned int getCurrentState() const;

        bool hasStateChanged();

    private:
        std::vector<String, Utilities::Memory::STLAllocator<String>> registeredStates;

        unsigned int currentState;
        bool stateChanged;
    };

} // namespace Game

#endif // GAME_STATEMANAGER_H
