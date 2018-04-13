#include "state_machine.h"
#include <iostream>

state_machine::machine::machine(state *p_default_state)
{
    mp_current_state = p_default_state;
}

void state_machine::machine::process_event(int event)
{
    std::cout << "STATE IN:  " << mp_current_state->state_name() << " <-- event[" << event << "]" << std::endl;
    bool state_changed = false;

    auto possible_transitions = mp_current_state->transitions().equal_range(event);
    if (possible_transitions.first == possible_transitions.second)
    {
        std::cout << "Warning: No state transition found" << std::endl;
    }
    else
    {
        for(auto transition_itr = possible_transitions.first; transition_itr != possible_transitions.second; transition_itr++)
        {
            if ((transition_itr->second.guard_function == nullptr) || (transition_itr->second.guard_function()))
            {
                CHANGE_STATE(mp_current_state, transition_itr->second.get_next_state());
                state_changed = true;
                break;
            }
        }
        if (!state_changed)
        {
            std::cout << "No state transition available at this time" << std::endl;
        }
    }
    std::cout << "STATE OUT: " << mp_current_state->state_name() << "\n" << std::endl;
}
