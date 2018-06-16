#pragma once
#include "state_machine.h"
#include <iostream>

class state_start : public state_machine::state
{
public:
    state_start(std::string state_name);
    ~state_start();

protected:
    void entry();
    void exit();


private:
    bool true_guard();
    bool false_guard();

    // Exit the state machine when we recieve ev_test1 in this state
    void event_handler(int event)
    {
        if (event == ev_test1)
        {
            if (mp_parent_machine != nullptr)
            {
                std::cout << "STATE START parent: " << mp_parent_machine->name() << " - EXIT SM" << std::endl;
                mp_parent_machine->exit_machine();
            }
            else
            {
                std::cout << "STATE START has no paranet SM!" << std::endl;
            }
        }
    }

};
