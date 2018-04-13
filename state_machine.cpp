#include "state_machine.h"

void state_machine::state::add_transition(int trigger_event, transition trans)
{
    transitions[trigger_event] = trans;
}
