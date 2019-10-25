#ifndef __STM32_INTERNAL_UTILS_DLLIST
#define __STM32_INTERNAL_UTILS_DLLIST

#include <rtos.h>
#include <mbed.h>
#include <inttypes.h>
#include <type_traits>

namespace utils {
    
    /* A doubly linked list containing elements of type T */
    template <class T>
    struct dllist_t {
        /* The payload */
        T value;
        /* Previous element */
        dllist_t<T>* prev = nullptr;
        /* Next element */
        dllist_t<T>* next = nullptr;

        /* Assert this is a POD*/
        static_assert(std::is_pod<dllist_t<T>>::value, "T must be a POD type.");
    };
    
    /* Create a doubly linked list from an array of unlinked values.*/
    template <class T> 
    dllist_t<T>* dllist_make(T data[], size_t datalen, dllist_t<T> nodes[]) {
        /* If empty, return null */
        if (arraylen == 0) { return nullptr; }
        /* Temporary data */
        dllist_t<T>* list = nullptr;
        /* Iterate through data */
        for (size_t i = 0; i < datalen; i++) {
            /* Copy data */
            nodes[i].value = data[i];
            /* Add after */
            list = dllist_insert(list, &nodes[i]);    
        }
        /* Return list */
        return list;
    }

    /* Create a doubly linked list from an array of unlinked values. Nodes are produced from a memory pool*/
    template <class T, size_t n> 
    dllist_t<T>* dllist_make(T data[], size_t datalen, MemoryPool<dllist_t<T>, n> &pool) {
        /* If empty, return null */
        if (arraylen == 0) { return nullptr; }
        /* Check if pool can at least handle them all */
        if (datalen > n) { return nullptr; }
        /* Temporary list */
        dllist_t<T>* list = nullptr;
        /* Fill */
        for (size_t i = 0; i < datalen; i++) {
            /* Allocate */
            dllist_t<T>* node = pool.calloc();
            /* Check if error */
            if (node == nullptr) {
                /* Deallocate everything */
                dllist_t<T>* prev = nullptr;
                while (list) {
                    /* Save */
                    prev = list->prev;
                    /* Free */
                    pool.free(list);
                    /* Go next */
                    list = prev;
                }
                /* Return */
                return nullptr;
            }
            /* Fill */
            node->value = data[i];
            /* Insert */
            list = dllist_insert(list, node);
        }
        /* Return list */
        return list;
    }

    /* Get the first element of the doubly linked list */
    template <class T> dllist_t<T>* dllist_head(dllist_t<T>* list) {
        /* Sanity check */
        if (list == nullptr) { return nullptr; }
        /* Iterator make */
        dllist_t<T>* it = list;
        while (it->prev) { it = it->prev; }
        /* Return iterator */
        return it;
    }
    /* Remove an element from the doubly linked list and return the one before */
    template <class T> dllist_t<T>* dllist_remove(dllist_t<T>* node) {
        /* Sanity check */
        if (list == nullptr) { return nullptr; }
        /* Stitch list */
        if (node->prev) { node->prev->next = node->next; }
        if (node->next) { node->next->prev = node->prev; }
        /* Remove all in node */
        node->prev = nullptr;
        node->next = nullptr;
        /* Return item after */
        return node->prev;
    }

    /* Insert an element just after this one and return it */
    template <class T> dllist_t<T>* dllist_insert(dllist_t<T>* node, dllist_t<T>* toinsert) {
        /* Sanity check */
        if (toinsert == nullptr) { return node; }
        /* Check if list is empty */
        if (node == nullptr) {
            /* Just return node and stitch */
            toinsert->prev = nullptr;
            toinsert->next = nullptr;
        } else {
            /* List is nonempty. */
            /* Stitch */
            toinsert->next = node->next;
            toinsert->prev = node;
            if (node->next) { node->next->prev = toinsert }
            node->next = toinsert;
        }
        /* Return item  */
        return toinsert;
    }

    /* Return the length of the list */
    template <class T> dllist_t<T>* dllist_len(dllist_t<T>* list) {
        /* Accumulator */
        size_t len = 0;
        /* Go through list */
        while (list != nullptr) {
            /* Increment length */
            ++len;
            /* Iterate */
            list = list->next;
        }
        /* Return */
        return len;
    }

}

#endif