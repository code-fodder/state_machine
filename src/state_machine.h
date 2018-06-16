#pragma once
#include <functional>
#include <map>
#include <iostream>

// Plantuml printing
#define PRINT_PLANT_UML \
    static bool plantuml_print_once = true; \
    if (plantuml_print_once) \
    { \
        print_plantuml(); \
    } \
    plantuml_print_once = false;

// These defines are used to create/change the states and add transitions
#define CREATE_STATE(state_name) new state_name(#state_name)
#define ADD_GUARDED_TRANSITION(tr_event_id, tr_next_state, tr_guard_fn) \
        m_transitions.insert( \
            std::make_pair( \
                tr_event_id, \
                state_machine::transition{\
                    [this](){ return new tr_next_state(#tr_next_state); }, \
                    [this](){ return this->tr_guard_fn(); },\
                    #tr_next_state, \
                    #tr_event_id, \
                    #tr_guard_fn \
                } \
            ) \
        );
#define ADD_UNGUARDED_TRANSITION(tr_event_id, tr_next_state) \
        m_transitions.insert( \
            std::make_pair( \
                tr_event_id, \
                state_machine::transition{\
                    [this](){ return new tr_next_state(#tr_next_state); }, \
                    nullptr, \
                    #tr_next_state, \
                    #tr_event_id, \
                    "" \
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
    class machine;

    // Transition consists of a guard function and a state pointer
    struct transition
    {
        std::function<state *()> get_next_state;
        std::function<bool()> guard_function;
        std::string next_state_str;
        std::string event_str;
        std::string guard_fn_str;
    };

    class state
    {
        // Machine will need to access some protected functions like entry()/exit().
        friend class machine;
    public:
        state(std::string state_name) :
            m_state_name(state_name),
            mp_parent_machine(nullptr),
            mp_child_machine(nullptr)
        {
        }
        virtual ~state() = 0;

        inline const std::multimap<int, transition> &transitions() {return m_transitions;}
        inline const std::string &state_name() {return m_state_name;}

    protected:
        virtual void event_handler(int event) {std::cout << m_state_name << " - event_handler(" << event << ")" << std::endl;}
        virtual void entry() {std::cout << m_state_name << " - entry" << std::endl;}
        virtual void exit() {std::cout << m_state_name << " - exit" << std::endl;}
        void set_parent(machine *p_parent) { mp_parent_machine = p_parent;}

        void print_plantuml();

        std::string m_state_name;
        std::multimap<int, transition> m_transitions;
        machine *mp_parent_machine;
        machine *mp_child_machine;
    };

    class machine
    {
    public:
        machine(std::string name);
        ~machine();
        void start(state *p_default_state);
        bool process_event(int event);
        void exit_machine() { m_machine_running = false; }
        std::string name() { return m_name; }        

    private:
        std::string m_name;
        state *mp_current_state;
        bool m_machine_running;
    };

}




