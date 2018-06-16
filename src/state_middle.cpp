#include "state_middle.h"
#include "state_start.h"

state_middle::state_middle(std::string state_name) :
    state(state_name)
{
    // transitions            event       next state      guard function
    ADD_UNGUARDED_TRANSITION (ev_start,  state_start                      );
    ADD_UNGUARDED_TRANSITION (ev_middle, state_middle                     );

    PRINT_PLANT_UML
}

state_middle::~state_middle()
{
}

