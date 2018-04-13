#pragma once
#include <functional>
#include <map>

// Events - this should be expandable list out side of here... maybe a class?
enum state_events
{
    ev_start = 0,
    ev_middle,
    ev_end
};

#define DECL_STATE(state_type_name, str_name) state_type_name state_type_name##_inst(str_name)
#define STATE(state_type_name) state_type_name##_inst

#define ADD_TRANSITION_GUARDED(event_id, start_state_name, next_state_name, guard_fn) \
    start_state_name##_inst.add_transition(event_id, \
    state_machine::transition{ std::bind(&guard_fn, &start_state_name##_inst), &next_state_name##_inst })

#define ADD_TRANSITION(event_id, start_state_name, next_state_name) \
    start_state_name##_inst.add_transition(event_id, \
    state_machine::transition{ nullptr, &next_state_name##_inst })

namespace state_machine
{
    // forward decl
    class state;

    // Transition consists of a guard function and a state pointer
    struct transition
    {
        std::function<bool()> guard_function;
        state *p_next_state;
    };

    class state
    {
    public: // todo make some of this protected / maybe make state_machine::machine a friend class to access it
        state(std::string state_name) : m_state_name(state_name) {}
        void add_transition (int trigger_event, transition trans);
        std::map<int, transition> transitions;
        std::string m_state_name;
    };

}




