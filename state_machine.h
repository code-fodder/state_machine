#pragma once
#include <functional>
#include <map>
#include <iostream>

// Events - this should be expandable list out side of here... maybe a class?
enum state_events
{
    ev_start = 0,
    ev_middle,
    ev_end,
    ev_test1,
    ev_test2,
    ev_test3
};

#define NEW_STATE(state_name) new state_name(#state_name)
#define CHANGE_STATE(p_state, new_state_name) delete p_state; p_state NEW_STATE(new_state_name)
#define ADD_GUARDED_TRANSITION(tr_event_id, tr_next_state, tr_guard_fn) \
        transitions.insert( \
            std::make_pair( \
                tr_event_id, \
                state_machine::transition{\
                    [](){ return new tr_next_state(#tr_next_state); }, \
                    [this](){ return this->tr_guard_fn(); }\
                } \
            ) \
        );
#define ADD_UNGUARDED_TRANSITION(tr_event_id, tr_next_state) \
        transitions.insert( \
            std::make_pair( \
                tr_event_id, \
                state_machine::transition{\
                    [](){ return new tr_next_state(#tr_next_state); }, \
                    nullptr \
                } \
            ) \
        );



namespace state_machine
{
    // forward decl
    class state;

    // Transition consists of a guard function and a state pointer
    struct transition
    {
        std::function<state *()> get_next_state;
        std::function<bool()> guard_function;
    };

    class state
    {
    public: // todo make some of this protected / maybe make state_machine::machine a friend class to access it
        state(std::string state_name) : m_state_name(state_name) {}
        std::multimap<int, transition> transitions;
        std::string m_state_name;
    };

}




