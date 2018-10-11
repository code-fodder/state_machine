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

// This is to force profiling / memcheck issues... probably remove this now...
#if 0
    // For profiling test
    std::cout << "Starting profile test...\r\n";
    for (int i = 0; i < 1000000000; i++) {;}
    std::cout << "done\r\n";

    // For valgrind test
    std::cout << "Starting memcheck test...\r\n";
    int *p = new int();
    std::cout << "\tp address: " << p << ", value: " << *p << "\r\n";
    *p += 1;
    std::cout << "\tp address: " << p << ", value: " << *p << "\r\n";
    //delete p;
    std::cout << "done\r\n";
#endif
    return 0;
}

