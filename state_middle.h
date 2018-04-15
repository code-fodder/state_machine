#pragma once
#include "state_machine.h"
#include <iostream>

class state_middle : public state_machine::state
{
public:
    state_middle(std::string state_name);
    ~state_middle();

protected:
    //void entry();
    //void exit();


private:
    // Exit the state machine when we recieve ev_test in this state
    void event_handler(int event)
    {
        if (event == ev_test1)
        {
            if (mp_parent_machine != nullptr)
            {
                std::cout << "STATE MIDDLE parent: " << mp_parent_machine->name() << " - EXIT SM" << std::endl;
                mp_parent_machine->exit_machine();
            }
            else
            {
                std::cout << "STATE MIDDLE has no paranet SM!" << std::endl;
            }
        }
    }

};

