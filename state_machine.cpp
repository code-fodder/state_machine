#include "state_machine.h"
#include <iostream>

// Nothing in the destructor at the moment
state_machine::state::~state()
{
    if (mp_child_machine != nullptr)
    {
        printf("Deleting child SM\r\n");
        delete mp_child_machine;
    }
}

state_machine::machine::machine(std::string name) :
    m_name(name),
    mp_current_state(nullptr),
    m_machine_running(true)
{
}

void state_machine::machine::start(state *p_default_state)
{
    mp_current_state = p_default_state;
    mp_current_state->set_parent(this);
    std::cout << "new state machine: " << m_name << ", start state: " << mp_current_state->state_name() << std::endl;
    mp_current_state->entry();

    std::cout << std::endl;
}

bool state_machine::machine::process_event(int event)
{
    std::cout << "SM: " << m_name << ", STATE IN:  " << mp_current_state->state_name() << " <-- event[" << event << "]" << std::endl;

    if ((mp_current_state->mp_child_machine != nullptr) &&
        (mp_current_state->mp_child_machine->m_machine_running))
    {
        // pass the even to the sub state machine
        printf("Processing child state machine\r\n");
        mp_current_state->mp_child_machine->process_event(event);
    }
    else
    {
        bool state_changed = false;

        // Call the state event handler
        mp_current_state->event_handler(event);

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
    }
    //std::cout << "STATE OUT: " << mp_current_state->state_name() << "\n" << std::endl;
    std::cout << std::endl;

    return true;
}
