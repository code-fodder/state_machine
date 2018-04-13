#include "state_start.h"
#include "state_middle.h"


state_start::state_start(std::string state_name) :
    state(state_name)
{
    // transitions            event       next state      guard function
    ADD_GUARDED_TRANSITION   (ev_middle,  state_middle,   false_guard     );
    ADD_GUARDED_TRANSITION   (ev_middle,  state_middle,   true_guard      );
    ADD_UNGUARDED_TRANSITION (ev_start,   state_start                     );
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
