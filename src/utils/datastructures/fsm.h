#ifndef __STM32_INTERNAL_UTILS_FSM
#define __STM32_INTERNAL_UTILS_FSM

#include <rtos.h>
#include <mbed.h>
#include <inttypes.h>
#include <type_traits>

namespace utils {
    
    /* A range */
    template <typename T>
    struct fsm_t {
        /* Current state */
        T state;
        /* State table */
        T** table;
        /* Number of states */
        size_t nStates;
        /* Number of events */
        size_t nEvents;

        /* Verify this is an integral type */
        static_assert(std::is_integral<T>::value, "Integral type required in fsm_t.");
    };

    /* Make a fsm */
    template <typename T, size_t nStates, size_t nEvents>
    __always_inline fsm_t<T> fsm_make(T table[nStates][nEvents], T initialState) {
        /* Assert that initial state is in range */
        MBED_ASSERT(initialState < nStates);
        /* Make */
        return { initialState, table, nStates, nEvents };
    }

    /* Apply a transition */
    template <typename T>
    __always_inline T fsm_go(fsm_t<T>& fsm, size_t event, const T& invalidState) {
        /* Assert that event is in range */
        MBED_ASSERT(event < fsm.nEvents);
        /* Compute the next state */
        T next = fsm.table[fsm.state][event];
        /* Assert that next state is in range */
        MBED_ASSERT(next < fsm.nStates);
        /* Check if invalid */
        if (next == invalidState) {
            /* Do nothing */
            return fsm.state;
        }
        /* Move */
        return fsm.state = next;
    }

}

#endif