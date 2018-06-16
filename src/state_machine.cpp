#include "state_machine.h"
#include <iostream>

/*********** STATE *************/

// Nothing in the destructor at the moment
state_machine::state::~state()
{
    if (mp_child_machine != nullptr)
    {
        printf("Deleting child SM\r\n");
        delete mp_child_machine;
    }
}

void state_machine::state::print_plantuml()
{
    for (auto &trans : m_transitions)
    {
        if (trans.second.guard_fn_str.size() > 0)
        {
            printf("@ %s --> %s : %s / %s()\r\n", m_state_name.c_str(),
                                                  trans.second.next_state_str.c_str(),
                                                  trans.second.event_str.c_str(),
                                                  trans.second.guard_fn_str.c_str());
        }
        else
        {
            printf("@ %s --> %s : %s\r\n", m_state_name.c_str(),
                                                  trans.second.next_state_str.c_str(),
                                                  trans.second.event_str.c_str());
        }
    }
}

/*********** MACHINE *************/

state_machine::machine::machine(std::string name) :
    m_name(name),
    mp_current_state(nullptr),
    m_machine_running(true)
{
}

state_machine::machine::~machine()
{
    // Clear any states that are left
    std::cout << "SM: ~" << m_name << "(), deleting current state" << std::endl;
    if (mp_current_state)
    {
        delete mp_current_state;
    }
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
                    /**** CHANGE STATE ****/

                    // Run the current state exit function
                    mp_current_state->exit();

                    // Get pointer to instance of the new state
                    state *p_new_state = transition_itr->second.get_next_state();

                    // Print the state transition
                    std::cout << "STATE MACHINE " << m_name << ": " << mp_current_state->state_name() << " --> " << p_new_state->state_name() << std::endl;

                    // Delete the old state
                    delete mp_current_state;

                    // Set the new state to the current state pointer
                    mp_current_state = p_new_state;

                    // Set the parent state machine to 'this' one
                    mp_current_state->set_parent(this);

                    // run the state entry function
                    mp_current_state->entry();

                    // Finally mart the state_changed flag to true for successful state change
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
