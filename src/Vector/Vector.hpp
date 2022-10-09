#ifndef VECTOR_ARRAY_HPP
#define VECTOR_ARRAY_HPP
#include <cstdlib>
#include <LogUtils/Logger.hpp>
#include <exception>
#include <new>

void* operator new (size_t, void* mem) noexcept;

namespace mvc {

    enum class Exception
    {
        OutOfMemory,
        OutOfRangeError,
    };

    template<class T>
    class ConstIterator
    {
        const T* ptr_;
    public:
        ConstIterator(const T* ptr) : ptr_(ptr) {}

        const T& operator*() const {return *ptr_;}
        ConstIterator& operator++()    {ptr_++; return *this;}
        ConstIterator  operator++(int) {ConstIterator retval = *this; ptr_++; return retval;}
        T* operator->() {return ptr_;}
        template<class U>
        friend bool operator==(const ConstIterator<U>&, const ConstIterator<U>&);
    };

    template<class T, size_t size>
    class Array
    {
        T data_[size];
    public:
        const T& operator[] (size_t i) const
        { 
            if(i < size) 
                return data_[i];
            else throw Exception::OutOfRangeError;
        }
        
        T& operator[] (size_t i)
        { 
            if(i < size) 
                return data_[i];
            else throw Exception::OutOfRangeError;
        }

    };

    template<class T>
    class Vector
    {
        T* data_ = nullptr;
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
                data_[i].~T();
            }

            delete [] reinterpret_cast<char*>(data_);    // We alloced as char* so will free as char*
        }

        Vector(const Vector& oth)
        {
            operator=(oth);
        }

        Vector& operator=(const Vector& other)
        {
            resize(other.size_);

            for(size_t i = 0; i < other.size_; ++i)
            {
                data_[i] = other[i];
            }


            return *this;
        } 


        void reserve(size_t newCap)
        {
            if(newCap <= capacity_) return;

            T* newArr = nullptr;
            try {
                newArr = reinterpret_cast<T*>(new char[newCap * sizeof(T)]);
            
            } catch (const std::bad_alloc&) {
                throw Exception::OutOfMemory;
            }
            
            if (data_ == nullptr)
            {
                data_ = newArr;
                capacity_ = newCap;
                return;
            }
            // Copying array to new place
            
            for(size_t i = 0; i < size_; ++i)
            {
                try{
                    new (newArr + i) T(data_[i]);
                }
                catch(...){
                    for(size_t j = 0; j < i; ++j)
                        newArr[i].~T();
                    delete [] reinterpret_cast<char*>(newArr);
                    std::rethrow_exception(std::current_exception());
                }
            }

            for(size_t i = 0; i < size_; ++i)
                data_[i].~T();

            capacity_ = newCap;

            delete [] reinterpret_cast<char*>(data_);    // We alloced as char* so will free as char*
            
            data_ = newArr;
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
                    try{
                        new (data_ + i) T;
                    }
                    catch(...)
                    {
                        for(size_t j = size_; j < i; ++j)
                            data_[i].~T();
                        std::rethrow_exception(std::current_exception());
                    }
                }
            } else {
                for(size_t i = newSize; i < size_; ++i)
                {
                    data_[i].~T();
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

            new (data_ + size_++) T(value);
        }

        ConstIterator<T> begin() const {return ConstIterator<T>(data_);}
        ConstIterator<T> end  () const {return ConstIterator<T>(data_ + size_);}

        const T& operator[] (size_t i) const 
        { 
            if(i < size_) 
                return data_[i];
            else throw Exception::OutOfRangeError;
        }
        
        T& operator[] (size_t i)
        { 
            if(i < size_) 
                return data_[i];
            else throw Exception::OutOfRangeError;
        }
        
        size_t size() const { return size_; }
    };
    
    template<class T>
    bool operator==(const ConstIterator<T>& lhs, const ConstIterator<T>& rhs) { return lhs.ptr_ == rhs.ptr_;}

    template<class T>
    bool operator!=(const ConstIterator<T>& lhs, const ConstIterator<T>& rhs) { return !(lhs == rhs);}
}
#endif /* VECTOR_ARRAY_HPP */
