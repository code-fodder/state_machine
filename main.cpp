#include <iostream>
#include "state_machine.h"
#include "state_start.h"
#include "state_middle.h"

// This should mostly all be put into a state machine...
int main()
{
    std::cout << "Hello World!" << std::endl;

    // Start running...
    state_machine::state *p_current_state = NEW_STATE(state_start);
    printf("current in state: %s\r\n", p_current_state->m_state_name.c_str());

    int i = ev_middle;
    auto possible_transitions = p_current_state->transitions.equal_range(i);
    for(auto transition_itr = possible_transitions.first; transition_itr != possible_transitions.second; transition_itr++)
    {
        printf("\nChecking transition for event %d...\r\n", i);
        if (transition_itr->second.guard_function == nullptr)
        {
            printf("No guard - transition is valid\r\n");
        }
        else
        {
            if (transition_itr->second.guard_function())
            {
                printf("Guard passed - transition is valid\r\n");
            }
            else
            {
                printf("Guard failed - transition is not valid\r\n");
            }
        }
    }

    printf("\r\n");

    auto trans1 = p_current_state->transitions.find(i);
    if (trans1 != p_current_state->transitions.end())
    {
        printf("Found transition for event %d\r\n", i);
        state_machine::state *p_next = trans1->second.get_next_state();
        std::cout << "next = " << p_next->m_state_name << std::endl;
        delete p_current_state;
        p_current_state = trans1->second.get_next_state();
    }

 /*
    // receive an event
    int event = ev_middle;
    auto trans = p_current_state->transitions.find(event);
    if (trans != p_current_state->transitions.end())
    {
        if (trans->second.guard_function)
        {
            if (trans->second.guard_function())
            {
                printf("Guard check ok - transition state\r\n");
                p_current_state = trans->second.p_next_state;
            }
            else
            {
                printf("Guard check failed - transition state\r\n");
            }
        }
        else
        {
            printf("transition state\r\n");
            p_current_state = trans->second.p_next_state;
        }
    }
*/
    printf("current in state: %s\r\n", p_current_state->m_state_name.c_str());

    return 0;
}

