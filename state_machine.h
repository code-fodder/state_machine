#pragma once
#include <functional>
#include <map>

// These defines are used to create/change the states and add transitions
#define CREATE_STATE(state_name) new state_name(#state_name)
#define CHANGE_STATE(p_state, p_new_state) \
    std::cout << "STATE: " << p_state->state_name(); \
    delete p_state; \
    p_state = p_new_state; \
    std::cout << " --> " << p_state->state_name() << std::endl;
#define ADD_GUARDED_TRANSITION(tr_event_id, tr_next_state, tr_guard_fn) \
        m_transitions.insert( \
            std::make_pair( \
                tr_event_id, \
                state_machine::transition{\
                    [](){ return new tr_next_state(#tr_next_state); }, \
                    [this](){ return this->tr_guard_fn(); }\
                } \
            ) \
        );
#define ADD_UNGUARDED_TRANSITION(tr_event_id, tr_next_state) \
        m_transitions.insert( \
            std::make_pair( \
                tr_event_id, \
                state_machine::transition{\
                    [](){ return new tr_next_state(#tr_next_state); }, \
                    nullptr \
                } \
            ) \
        );



// Some events... should not be here - should be specific for each state header (I think, or maybe globally for a specific state machine)
enum state_events
{
    ev_start = 0,
    ev_middle,
    ev_end,
    ev_test1,
    ev_test2,
    ev_test3
};

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
        inline const std::multimap<int, transition> &transitions() {return m_transitions;}
        inline const std::string &state_name() {return m_state_name;}

    protected:
        std::string m_state_name;
        std::multimap<int, transition> m_transitions;
    };

    class machine
    {
    public:
        machine(state *p_default_state);
        void process_event(int event);

    private:
        state *mp_current_state;
    };

}




