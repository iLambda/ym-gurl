#ifndef __YM_GURL_UTILS_EVENT
#define __YM_GURL_UTILS_EVENT

#include <mbed.h>
#include <rtos.h>

namespace utils {

    /* The event class */
    template <typename T, size_t poolsize = 16>
    class Event {

        private:
            struct eventlist_t {
              /* The next event */
              eventlist_t* next = nullptr;
              /* The payload */
              Callback<void(T)> listener = 0;
            };

        private:   
            /* The callbacks */
            mutable eventlist_t* m_callbacks;
            /* The once callbacks */
            mutable eventlist_t* m_callonces;
            /* The memory pool */
            mutable MemoryPool<eventlist_t, poolsize> m_mempool;

        public:
            /* An event */
            Event() {
                /* Initialize */
                this->m_callbacks = nullptr;
                this->m_callonces = nullptr;
            }

        public:
            /* Fire */
            void fire(T parameter) {
                /* Iterator */
                eventlist_t* it;
                eventlist_t* pastit;

                /* Go though callbacks, fire them */
                it = this->m_callbacks;
                while (it != nullptr) {
                    /* Fire */
                    it->listener(parameter);
                    /* Next */
                    it = it->next;
                }

                /* Go though callonces, fire them */
                it = this->m_callonces;
                while (it != nullptr) {
                    /* Fire */
                    it->listener(parameter);
                    /* Next */
                    pastit = it;
                    it = it->next;
                    /* Free old iterator */
                    this->m_mempool.free(pastit);
                }
                /* They've all been released ; pointer is no more */
                this->m_callonces = nullptr;
            }

            /* Register once */
            bool once(Callback<void(T)> callback) const {
                return this->append(&this->m_callonces, callback);
            }
            
            /* Register every time */
            bool on(Callback<void(T)> callback) const {
                return this->append(&this->m_callbacks, callback);
            }

            /* Unregister */
            bool remove(Callback<void(T)> callback) const {
                return this->remove(&this->m_callbacks, callback);
            }

            /* Unregister */
            bool removeOnce(Callback<void(T)> callback) const {
                return this->remove(&this->m_callonces, callback);
            }


        private:
            inline bool remove(eventlist_t** list, Callback<void(T)> callback) const {
                /* Check if callback is null and list is empty => trivial */
                if (!callback) { return false; }
                if (*list == nullptr) { return false; }
                /* Assertion : list is nonempty, and callback not null. */
                /* Make iterators */
                eventlist_t* it = *list;
                eventlist_t* previous = nullptr;
                /* Go through */
                while (it != nullptr) {
                    /* Check if callback is the same as element */
                    if (it->listener == callback) {          
                        /* Check if there was a previous element */
                        if (previous == nullptr) {
                            /* No previous element. Meaning, this is first element of list */
                            /* In this case, new list head is next element */
                            *list = it->next;
                            /* No need to stitch list up. Free `it` */
                        } else {
                            /* There was a previous element. Reconnect list. */
                            previous->next = it->next;
                            /* Current element `it` is now completely separated. Free `it` */
                        }
                        /* Free the memory for the current element */
                        this->m_mempool.free(it);
                        /* Found */
                        return true;
                    }
                    /* Next element (iterate previous) */
                    previous = it;
                    it = it->next; 
                }
                /* Not found. False */
                return false;
            }

            inline bool append(eventlist_t** list, Callback<void(T)> callback) const {
                /* Check if callback is null */
                if (!callback) { return false; }
                /* Allocate node */
                eventlist_t* newnode = this->m_mempool.alloc();
                /* Check if allocation worked */
                if (newnode == nullptr) { return false; }
                
                /* Fill new node */
                newnode->next = nullptr;
                newnode->listener = callback;

                /* Actually append */
                if (*list == nullptr) {
                    /* No first node. Just set it */
                    *list = newnode;
                } else {
                    /* There is a first node. Append to end */
                    eventlist_t* it = *list;
                    while (it->next != nullptr) { it = it->next; }
                    it->next = newnode;
                }

                /* OK */
                return true;
            }

    };

}

#endif