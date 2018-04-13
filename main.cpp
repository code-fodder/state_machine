#include <iostream>
#include "state_machine.h"
#include "state_start.h"
#include "state_middle.h"

// This should mostly all be put into a state machine...
int main()
{
    std::cout << "Hello World!" << std::endl;

    // The states
    DECL_STATE(state_start,  "start");
    DECL_STATE(state_middle, "middle");

    //                     Event          Current State        Next State      guard
    ADD_TRANSITION_GUARDED(ev_start,      state_start,         state_start,    state_start::false_guard    );
    ADD_TRANSITION_GUARDED(ev_middle,     state_start,         state_middle,   state_start::true_guard     );
    ADD_TRANSITION        (ev_start,      state_middle,        state_start                                 );
    ADD_TRANSITION        (ev_middle,     state_middle,        state_middle                                );


    // Start running...
    state_machine::state *p_current_state = &STATE(state_start);

    printf("current in state: %s\r\n", p_current_state->m_state_name.c_str());

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

    printf("current in state: %s\r\n", p_current_state->m_state_name.c_str());

    return 0;
}

