#ifndef VECTOR_ARRAY_HPP
#define VECTOR_ARRAY_HPP
#include <cstdlib>
#include <LogUtils/Logger.hpp>

void* operator new (size_t, void* mem) noexcept;

namespace mvc {

    template<class T>
    class ConstIterator
    {
        const T* ptr_;
    public:
        ConstIterator(const T* ptr) : ptr_(ptr) {}

        const T& operator*() const {return *ptr_;}
        ConstIterator& operator++()    {ptr_++; return *this;}
        ConstIterator  operator++(int) {ConstIterator retval = *this; ptr_++; return retval;}
        template<class U>
        friend bool operator==(const ConstIterator<U>&, const ConstIterator<U>&);
    };

    template<class T, size_t size>
    class Array
    {
        T arr_[size];
    public:
        const T& operator[] (size_t i) const { return arr_[i]; }
              T& operator[] (size_t i)       { return arr_[i]; }
    };



    template<class T>
    class Vector
    {
        T* arr_ = nullptr;
        size_t size_ = 0, capacity_ = 0;
    public:

        

        Vector()
        {
            reserve(8);
        }

        explicit Vector(size_t size)
        {
            resize(size);
        }

        ~Vector()
        {
            for(size_t i = 0; i < size_; ++i)
            {
                arr_[i].~T();
            }

            delete [] reinterpret_cast<char*>(arr_);    // We alloced as char* so will free as char*
        }

        Vector& operator=(const Vector& other)
        {
            resize(other.size_);

            for(size_t i = 0; i < other.size_; ++i)
            {
                arr_[i] = other[i];
            }


            return *this;
        } 


        void reserve(size_t newCap)
        {
            if(newCap <= capacity_) return;

            T* newArr = reinterpret_cast<T*>(new char[newCap * sizeof(T)]);
            
            if (arr_ == nullptr)
            {
                arr_ = newArr;
                capacity_ = newCap;
                return;
            }
            // Copying array to new place
            
            for(size_t i = 0; i < size_; ++i)
            {
                new (newArr + i) T(arr_[i]);
                arr_[i].~T();
            }

            capacity_ = newCap;

            delete [] reinterpret_cast<char*>(arr_);    // We alloced as char* so will free as char*
            
            arr_ = newArr;
        }

        void resize(size_t newSize)
        {
            if(newSize > capacity_)
            {
                reserve(newSize);
            }

            if(newSize > size_)
            {
                for(size_t i = size_; i < newSize; ++i)
                {
                    new (arr_ + i) T;
                }
            } else {
                for(size_t i = newSize; i < size_; ++i)
                {
                    arr_[i].~T();
                }
            }

            size_ = newSize;
        }

        void push_back(const T& value)
        {
            if(size_ == capacity_)
            {
                reserve(2 * capacity_);
            }

            new (arr_ + size_++) T(value);
        }

        ConstIterator<T> begin() const {return ConstIterator<T>(arr_);}
        ConstIterator<T> end  () const {return ConstIterator<T>(arr_ + size_);}

        const T& operator[] (size_t i) const { return arr_[i]; }

              T& operator[] (size_t i)       { return arr_[i]; }
        
        size_t size() const { return size_; }
    };
    
    template<class T>
    bool operator==(const ConstIterator<T>& lhs, const ConstIterator<T>& rhs) { return lhs.ptr_ == rhs.ptr_;}

    template<class T>
    bool operator!=(const ConstIterator<T>& lhs, const ConstIterator<T>& rhs) { return !(lhs == rhs);}
}
#endif /* VECTOR_ARRAY_HPP */
