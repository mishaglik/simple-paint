#ifndef VECTOR_LINKEDLIST_HPP
#define VECTOR_LINKEDLIST_HPP

#include <cstddef>
namespace mvc {

    template<class T>
    class LinkedList
    {
    public:
        struct ListIterator
        {
            size_t idx;
        };

        LinkedList(size_t size)
        {
            data_ = reinterpret_cast<ListEntry*> (new char [(size + 1) * sizeof(ListEntry)]);
            
            for(size_t i = 1; i < size; ++i)
            {
                data_[i].next = i - 1;
                data_[i].prev = -1;
            }
        }

        LinkedList(const LinkedList& oth);
        LinkedList& operator=(const LinkedList& oth);
        

        ~LinkedList()
        {
            //TODO: Implement
        }

        ListIterator insert(ListIterator it, const T& t) 
        {
            if(!free) expand();
            size_t newIdx = free;
            free = data_[free].next;

            new (&data_[newIdx]->t) T(t);

            data_[newIdx].prev = it.idx;
            data_[newIdx].next = data_[it.idx].next;
            data_[data_[newIdx].next].prev = it.idx;
            data_[it.idx].next = newIdx;
        }

    private:
        struct ListEntry
        {
            std::size_t next;
            std::size_t prev;
            T t;
        };

        ListEntry* data_ = nullptr;
        size_t free;
        size_t size_ = 0;
        size_t capacity_ = 0;

        ListEntry* getFreeEntry()
        {

        }

        void expand();
    };
}

#endif /* VECTOR_LINKEDLIST_HPP */
