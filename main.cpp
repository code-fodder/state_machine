#include <iostream>
#include "state_machine.h"
#include "state_start.h"

int main()
{
    state_machine::machine sm("top-level");
    sm.start(CREATE_STATE(state_start));

    sm.process_event(ev_start);
    sm.process_event(ev_middle);
    sm.process_event(ev_test1);
    sm.process_event(ev_test1);
    sm.process_event(ev_middle);
    sm.process_event(ev_middle);
//    sm.process_event(ev_start);
//    sm.process_event(ev_start);
//    sm.process_event(ev_middle);
//    sm.process_event(ev_test1);

    return 0;
}

