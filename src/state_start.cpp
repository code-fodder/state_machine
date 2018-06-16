#include "state_start.h"
#include "state_middle.h"
#include <chrono>
#include <thread>

state_start::state_start(std::string state_name) :
    state(state_name)
{
    // transitions            event       next state      guard function
    ADD_GUARDED_TRANSITION   (ev_middle,  state_middle,   false_guard     );
    ADD_GUARDED_TRANSITION   (ev_middle,  state_middle,   true_guard      );
    ADD_UNGUARDED_TRANSITION (ev_start,   state_start                     );

    PRINT_PLANT_UML
}

state_start::~state_start()
{
}

void state_start::entry()
{
    printf("void state_start::entry()\r\n");

    // this state has a child state machine
    if (mp_parent_machine != nullptr)
    {
        mp_child_machine = new state_machine::machine(mp_parent_machine->name() + "::sub_start");
        mp_child_machine->start(CREATE_STATE(state_middle));
    }
    else
    {
        printf("ERROR: Nullptr\r\n");
    }
}

void state_start::exit()
{
    printf("void state_start::exit()\r\n");
}

bool state_start::true_guard()
{
    printf("state_start::true_guard() - passed\r\n");
    return true;
}

bool state_start::false_guard()
{
    printf("state_start::false_guard() - failed\r\n");
    return false;
}
