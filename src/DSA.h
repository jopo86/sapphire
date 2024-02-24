#pragma once

#include <iostream>

/*
    @brief Sapphire is a C++ library that provides a large set of tools for developers.
    Every Sapphire function is under this namespace.
 */
namespace Sapphire
{

    /*
        @brief A namespace containing data structures and algorithms.
     */
    namespace DSA
    {
        template<typename T>
        T Max(T a, T b)
        {
            return a > b ? a : b;
        }

        template<typename T>
        class Array
        {
        public:
            Array()
            {
                m_arr = new T[0];
                m_size = 0;
            }

            Array(int size)
            {
                m_arr = new T[size];
                m_size = size;
            }

            Array(int size, T* arr)
            {
                m_arr = new T[size];
                m_size = size;
                for (int i = 0; i < size; i++)
                {
                    m_arr[i] = arr[i];
                }
            }

            Array(const Array<T>& arr)
            {
                m_arr = new T[arr.m_size];
                m_size = arr.m_size;
                for (int i = 0; i < m_size; i++)
                {
                    m_arr[i] = arr.m_arr[i];
                }
            }

            ~Array()
            {
                if (m_arr != nullptr) delete[] m_arr;
            }

            T& operator[](int index)
            {
                return m_arr[index];
            }

            Array<T>& operator=(const Array<T>& arr)
            {
                if (m_arr != nullptr) delete[] m_arr;
                m_arr = new T[arr.m_size];
                m_size = arr.m_size;
                for (int i = 0; i < m_size; i++)
                {
                    m_arr[i] = arr.m_arr[i];
                }
                return *this;
            }

            friend bool operator==(const Array<T>& arr1, const Array<T>& arr2)
            {
                if (arr1.m_size != arr2.m_size) return false;
                for (int i = 0; i < arr1.m_size; i++)
                {
                    if (arr1.m_arr[i] != arr2.m_arr[i]) return false;
                }
                return true;
            }

            friend bool operator!=(const Array<T>& arr1, const Array<T>& arr2)
            {
                return !(arr1 == arr2);
            }

            int size()
            {
                return m_size;
            }
            
            class Iterator
            {
            public:
                using iterator_category = std::forward_iterator_tag;
                using difference_type = std::ptrdiff_t;
                using value_type = T;
                using pointer = T*;
                using reference = T&;

                Iterator(pointer ptr) : m_ptr(ptr) {}
                
                reference operator*() const { return *m_ptr; }
                pointer operator->() { return m_ptr; }

                Iterator& operator++() { m_ptr++; return *this; }
                Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

                friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
                friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

            private:
                pointer m_ptr;
            };

            Iterator begin() { return Iterator(m_arr); }
            Iterator end() { return Iterator(m_arr + m_size); }

        private:
            T* m_arr;
            int m_size;
        };

        template<typename T>
        class ArrayList
        {
        public:
            ArrayList()
            {
                m_cap = 10;
                m_arr = new T[m_cap];
                for (int i = 0; i < m_cap; i++)
                {
                    m_arr[i] = 0;
                }
                m_size = 0;
            }

            ArrayList(int size)
            {
                m_cap = Max((int)(size * 1.5), 10);
                m_arr = new T[m_cap];
                for (int i = 0; i < m_cap; i++)
                {
                    m_arr[i] = 0;
                }
                m_size = size;
            }

            ArrayList(int size, T* arr)
            {
                m_cap = Max((int)(size * 1.5), 10);
                m_arr = new T[m_cap];
                m_size = size;
                for (int i = 0; i < size; i++)
                {
                    m_arr[i] = arr[i];
                }
            }

            ArrayList(const ArrayList<T>& arr)
            {
                m_cap = arr.m_cap;
                m_arr = new T[arr.m_cap];
                m_size = arr.m_size;
                for (int i = 0; i < m_size; i++)
                {
                    m_arr[i] = arr.m_arr[i];
                }
            }

            ArrayList(const Array<T>& arr)
            {
                m_cap = arr.size() * 1.5;
                m_arr = new T[m_cap];
                m_size = arr.size();
                for (int i = 0; i < m_size; i++)
                {
                    m_arr[i] = arr[i];
                }
            }

            ~ArrayList()
            {
                if (m_arr != nullptr) delete[] m_arr;
            }

            T& operator[](int index)
            {
                return m_arr[index];
            }

            ArrayList<T>& operator=(const ArrayList<T>& arr)
            {
                if (m_arr != nullptr) delete[] m_arr;
                m_arr = new T[arr.m_cap];
                m_size = arr.m_size;
                m_cap = arr.m_cap;
                for (int i = 0; i < m_size; i++)
                {
                    m_arr[i] = arr.m_arr[i];
                }
                return *this;
            }

            friend bool operator==(const ArrayList<T>& arr1, const ArrayList<T>& arr2)
            {
                if (arr1.m_size != arr2.m_size) return false;
                for (int i = 0; i < arr1.m_size; i++)
                {
                    if (arr1.m_arr[i] != arr2.m_arr[i]) return false;
                }
                return true;
            }

            friend bool operator!=(const ArrayList<T>& arr1, const ArrayList<T>& arr2)
            {
                return !(arr1 == arr2);
            }

            int size()
            {
                return m_size;
            }

            void add(T elem)
            {
                m_size++;
                if (m_size > m_cap)
                {
                    m_cap *= 1.5;
                    T* tmp = new T[m_size];
                    for (int i = 0; i < m_size; i++)
                    {
                        tmp[i] = m_arr[i];
                    }
                    delete[] m_arr;
                    m_arr = new T[m_cap];
                    for (int i = 0; i < m_size; i++)
                    {
                        m_arr[i] = tmp[i];
                    }
                    delete[] tmp;
                }

                m_arr[m_size - 1] = elem;
            }

            void add(T elem, int index)
            {
                m_size++;
                if (m_size > m_cap) m_cap *= 1.5;

                T* tmp = new T[m_size];
                for (int i = 0; i < m_size; i++)
                {
                    tmp[i] = m_arr[i];
                }
                delete[] m_arr;
                m_arr = new T[m_cap];
                for (int i = 0; i < m_size; i++)
                {
                    if (i < index) m_arr[i] = tmp[i];
                    else if (i == index) m_arr[i] = elem;
                    else m_arr[i] = tmp[i - 1];
                }
                delete[] tmp;
            }

        private:
            int m_cap;
            T* m_arr;
            int m_size;
        };

        template<typename T>
        class LinkedList
        {

        };

        template<typename T>
        class Stack
        {

        };

        template<typename T>
        class Queue
        {

        };

        template<typename K, typename V>
        class HashMap
        {

        };

        template<typename T1, typename T2>
        class Pair
        {

        };

        
    }
}