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
        InvalidStack,
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

        Vector(const Vector& oth)
        {
            operator=(oth);
        }

        ~Vector()
        {
            lowDestroy(data_, size_);

            delete [] reinterpret_cast<char*>(data_);    // We alloced as char* so will free as char*
            data_ = nullptr;
            size_ = 0;
            capacity_ = 0;
        }

        Vector& operator=(const Vector& other)
        {
            T* newData = nullptr;

            newData = reinterpret_cast<T*>(new char[other.capacity_ * sizeof(T)]);

            lowInitCopy(newData, other.data_, other.size_);

            if(data_)
            {
                lowDestroy(data_, size_);
            }
            size_ = other.size_;
            capacity_ = other.capacity_;
            data_ = newData;

            return *this;
        } 

        void dump(mlg::Logger& log) const
        {
            log << "Vector[" << this << "]" << mlg::endl << 
                    "{" << mlg::endl <<
                    ".size = " << size_ << mlg::endl <<
                    ".capacity = " << mlg::endl <<
                    ".data[" << data_ << "] {" << mlg::endl;
            if(data_ != nullptr){
                for(size_t i = 0; i < size_; ++i)
                {
                    log << "\t.[" << i << "] = "  << data_[i] << mlg::endl;
                }
            }
            log << '}' << mlg::endl << "}" << mlg::endl;

        }

        void validate() const
        {
            if(data_ == nullptr)  throw Exception::InvalidStack;
            if(size_ > capacity_) throw Exception::InvalidStack;
        }

        void reserve(size_t newCap)
        {
            if(newCap <= capacity_) return;

            T* newArr = nullptr;

            newArr = reinterpret_cast<T*>(new char[newCap * sizeof(T)]);
            
            if (data_ == nullptr)
            {
                data_ = newArr;
                capacity_ = newCap;
                return;
            }
            // Copying array to new place
            lowInitCopy(newArr, data_, size_);
            lowDestroy(data_, size_);

            capacity_ = newCap;

            delete [] reinterpret_cast<char*>(data_);    // We alloced as char* so will free as char*
            
            data_ = newArr;
        }

        void resize(size_t newSize)
        {
            validate();
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
                        lowDestroy(data_ + i, i - size_);
                        throw;
                    }
                }
            } else {
                lowDestroy(data_ + newSize, size_ - newSize);
            }

            size_ = newSize;
        }

        void push_back(const T& value)
        {
            validate();
            if(size_ == capacity_)
            {
                reserve(2 * capacity_);
            }

            new (data_ + size_) T(value);
            size_++;
        }

        ConstIterator<T> begin() const {return ConstIterator<T>(data_);}
        ConstIterator<T> end  () const {return ConstIterator<T>(data_ + size_);}

        const T& operator[] (size_t i) const 
        { 
            validate();
            if(i < size_) 
                return data_[i];
            else throw Exception::OutOfRangeError;
        }
        
        T& operator[] (size_t i)
        { 
            validate();
            if(i < size_) 
                return data_[i];
            else throw Exception::OutOfRangeError;
        }
        
        size_t size() const { validate(); return size_; }

        private:

            void lowInitCopy(T* dst, const T* src, size_t n)
            {
                size_t copied = 0;
                try{
                    for(size_t i = 0; i < n; ++i)
                    {
                        new (dst + i) T(src[i]);
                        copied++;
                    }
                }
                catch(...)
                {
                    lowDestroy(dst, copied);
                    throw;
                }
            }

            void lowDestroy(T* toDestroy, size_t n)
            {
                for(size_t i = 0; i < n; ++i)
                    toDestroy[i].~T();
            }
            
    };
    
    template<class T>
    bool operator==(const ConstIterator<T>& lhs, const ConstIterator<T>& rhs) { return lhs.ptr_ == rhs.ptr_;}

    template<class T>
    bool operator!=(const ConstIterator<T>& lhs, const ConstIterator<T>& rhs) { return !(lhs == rhs);}
}
#endif /* VECTOR_ARRAY_HPP */
