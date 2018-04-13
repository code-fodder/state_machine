#pragma once
#include "state_machine.h"

class state_start : public state_machine::state
{
public:
    state_start(std::string state_name);

    bool true_guard();
    bool false_guard();
};
