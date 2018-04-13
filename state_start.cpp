#include "state_start.h"
#include "state_middle.h"

state_start::state_start(std::string state_name) :
    state(state_name)
{
}

bool state_start::true_guard()
{
    printf("state_start::some_guard() - ok\r\n");
    return true;
}

bool state_start::false_guard()
{
    printf("state_start::some_guard() - failed\r\n");
    return false;
}
