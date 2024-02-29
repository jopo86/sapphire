#pragma once

#include <iostream>

#include "Core.h"

typedef unsigned int uint;

/*
    @brief Sapphire is a C++ library that provides a large set of tools for developers.
    Every Sapphire function is under this namespace.
 */
namespace Sapphire
{

    /*
        @brief A namespace containing a template library data structures and algorithms.
     */
    namespace DSA
    {
        template<typename T>
        T Min(T a, T b)
        {
            return a < b ? a : b;
        }

        template<typename T>
        int MinIndex(T* arr, uint size)
        {
            if (size = 0)
            {
                Sapphire::Warn("DSA::Min(T* arr, uint size) --> size is 0, cannot find minimum value. Returning -1");
                return -1;
            }
            
            int minI = 0;
            for (int i = 1; i < size; i++)
            {
                if (arr[i] < arr[minI]) minI = i;
            }
            return minI;
        }
        
        template<typename T>
        int MinIndex(T* arr, uint start, uint end)
        {
            if (end - start == 0)
            {
                Sapphire::Warn("DSA::Min(T* arr, uint start, uint end) --> range is 0, cannot find minimum value. Returning -1");
                return -1;
            }

            int minI = start;
            for (int i = start + 1; i < end; i++)
            {
                if (arr[i] < arr[minI]) minI = i;
            }
            return minI;
        }

        template<typename T>
        T Max(T a, T b)
        {
            return a > b ? a : b;
        }

        template<typename T>
        int MaxIndex(T* arr, uint size)
        {
            if (size = 0)
            {
                Sapphire::Warn("DSA::Min(T* arr, uint size) --> size is 0, cannot find minimum value. Returning -1");
                return -1;
            }
            
            int maxI = 0;
            for (int i = 1; i < size; i++)
            {
                if (arr[i] > arr[maxI]) maxI = i;
            }
            return maxI;
        }
        
        template<typename T>
        int MaxIndex(T* arr, uint start, uint end)
        {
            if (end - start == 0)
            {
                Sapphire::Warn("DSA::Min(T* arr, uint start, uint end) --> range is 0, cannot find minimum value. Returning -1");
                return -1;
            }

            int maxI = start;
            for (int i = start + 1; i < end; i++)
            {
                if (arr[i] > arr[maxI]) maxI = i;
            }
            return maxI;
        }

        template<typename T>
        int LinearSearch(T* arr, uint size, T elem)
        {
            for (int i = 0; i < size; i++)
            {
                if (arr[i] == elem) return i;
            }
            return -1;
        }

        template<typename T>
        int BinarySearch(T* arr, uint size, T elem)
        {
            int left = 0;
            int right = size - 1;
            
            for (int i = (left + right) / 2; left - right != 1; i = (left + right) / 2)
            {
                if (elem == arr[i]) return i;
                else if (elem > arr[i]) left = i + 1;
                else right = i - 1;
            }

            return -1;
        }

        template<typename T>
        int Contains(T* arr, uint size, T elem)
        {
            return LinearSearch(arr, size, elem) != -1;
        }

        template<typename T>
        void BubbleSort(T* arr, uint size)
        {
            for (int i = 0; i < size - 1; i++)
            {
                for (int j = 0; j < size - 1; j++)
                {
                    if (arr[j] > arr[j + 1])
                    {
                        T tmp = arr[j];
                        arr[j] = arr[j + 1];
                        arr[j + 1] = tmp;
                    }
                }
            }
        }

        template<typename T>
        void SelectionSort(T* arr, uint size)
        {
            for (int i = 0; i < size - 1; i++)
            {
                int minI = MinIndex(arr, i, size);
                T tmp = arr[i];
                arr[i] = arr[minI];
                arr[minI] = tmp;
            }
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

            Array(uint size)
            {
                m_arr = new T[size];
                m_size = size;
            }

            Array(uint size, T* arr)
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
            
            Array(std::initializer_list<T> list)
            {
                m_size = list.size();
                m_arr = new T[m_size];
                int i = 0;
                for (T elem : list)
                {
                    m_arr[i] = elem;
                    i++;
                }
            }

            ~Array()
            {
                if (m_arr != nullptr) delete[] m_arr;
            }

            int linearSearch(T elem)
            {
                return LinearSearch(m_arr, m_size, elem);
            }

            int binarySearch(T elem)
            {
                return BinarySearch(m_arr, m_size, elem);
            }

            bool contains(T elem)
            {
                return linearSearch(elem) != -1;
            }

            void bubbleSort()
            {
                BubbleSort(m_arr);
            }

            void selectionSort()
            {
                SelectionSort(m_arr);
            }

            uint size()
            {
                return m_size;
            }

            T* data()
            {
                return m_arr;
            }

            T& operator[](int index)
            {
                if (index < 0 || index >= m_size)
                {
                    Sapphire::Err("DSA::Array --> array index " + std::to_string(index) + " is out of bounds (size: " + std::to_string(m_size) + ")");
                    throw std::runtime_error("Sapphire: DSA::Array --> array index " + std::to_string(index) + " is out of bounds (size: " + std::to_string(m_size) + ")");
                }
                return m_arr[index];
            }

            Array<T>& operator=(const Array<T>& other)
            {
                if (m_arr != nullptr) delete[] m_arr;
                m_arr = new T[other.m_size];
                m_size = other.m_size;
                for (int i = 0; i < m_size; i++)
                {
                    m_arr[i] = other.m_arr[i];
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
            
            class Iterator
            {
            public:
                using iterator_category = std::forward_iterator_tag;
                using difference_type = std::ptrdiff_t;
                using value_type = T;
                using pointer = T*;
                using reference = T&;

                Iterator(pointer ptr) : m_ptr(ptr) {}
                
                reference operator*() const 
                { 
                    return *m_ptr; 
                }
                
                pointer operator->() 
                {
                    return m_ptr; 
                }

                Iterator& operator++() 
                {
                    m_ptr++; return *this;
                }

                Iterator operator++(int) 
                {
                    Iterator tmp = *this; ++(*this); return tmp; 
                }

                friend bool operator==(const Iterator& it1, const Iterator& it2) 
                { 
                    return it1.m_ptr == it2.m_ptr; 
                };

                friend bool operator!=(const Iterator& it1, const Iterator& it2) 
                {
                    return it1.m_ptr != it2.m_ptr; 
                };

            private:
                pointer m_ptr;
            };

            Iterator begin() 
            {
                return Iterator(m_arr); 
            }

            Iterator end() 
            {
                return Iterator(m_arr + m_size); 
            }

        private:
            T* m_arr;
            uint m_size;
        };

        template<typename T>
        class ArrayList
        {
        public:
            ArrayList()
            {
                m_cap = 10;
                m_arr = new T[m_cap];
                m_size = 0;
            }

            ArrayList(uint size)
            {
                m_cap = Max((uint)(size * 1.5), (uint)10);
                m_arr = new T[m_cap];
                m_size = size;
            }

            ArrayList(uint size, T* arr)
            {
                m_cap = Max((uint)(size * 1.5), (uint)10);
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

            ArrayList(std::initializer_list<T> list)
            {
                m_cap = Max((uint)(list.size() * 1.5), (uint)10);
                m_arr = new T[m_cap];
                m_size = list.size();
                int i = 0;
                for (T elem : list)
                {
                    m_arr[i] = elem;
                    i++;
                }
            }

            ~ArrayList()
            {
                if (m_arr != nullptr) delete[] m_arr;
            }

            int linearSearch(T elem)
            {
                return LinearSearch(m_arr, m_size, elem);
            }

            int binarySearch(T elem)
            {
                return BinarySearch(m_arr, m_size, elem);
            }

            int contains(T elem)
            {
                return linearSearch(elem) != -1;
            }

            void bubbleSort()
            {
                BubbleSort(m_arr);
            }

            void selectionSort()
            {
                SelectionSort(m_arr);
            }

            uint size()
            {
                return m_size;
            }

            void add(T elem)
            {
                if (m_size + 1 > m_cap)
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

                m_size++;
                m_arr[m_size - 1] = elem;
            }

            void insert(T elem, int index)
            {
                T* tmp = new T[m_size];
                for (int i = 0; i < m_size; i++)
                {
                    tmp[i] = m_arr[i];
                }

                m_size++;
                if (m_size > m_cap) m_cap *= 1.5;

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

            void remove(int index)
            {
                T* tmp = new T[m_size];
                for (int i = 0; i < m_size; i++)
                {
                    tmp[i] = m_arr[i];
                }

                m_size--;

                delete[] m_arr;
                m_arr = new T[m_cap];

                for (int i = 0; i < m_size; i++)
                {
                    if (i < index) m_arr[i] = tmp[i];
                    else m_arr[i] = tmp[i + 1];
                }

                delete[] tmp;
            }

            void pop()
            {
                remove(m_size - 1);
            }

            void removeAll(T elem)
            {
                T* tmp = new T[m_size];
                for (int i = 0; i < m_size; i++)
                {
                    tmp[i] = m_arr[i];
                }

                delete[] m_arr;
                m_arr = new T[m_cap];

                int ogSize = m_size;

                for (int i = 0; i < ogSize; i++)
                {
                    if (tmp[i] == elem)
                    {
                        m_size--;
                        continue;
                    }
                    
                    m_arr[i - (ogSize - m_size)] = tmp[i];
                }

                delete[] tmp;
            }

            T* data()
            {
                return m_arr;
            }

            T& operator[](int index)
            {
                if (index < 0 || index >= m_size) 
                {
                    Sapphire::Err("DSA::ArrayList --> array index " + std::to_string(index) + " is out of bounds (size: " + std::to_string(m_size) + ")");
                    throw std::runtime_error("Sapphire: DSA::ArrayList --> array index " + std::to_string(index) + " is out of bounds (size: " + std::to_string(m_size) + ")");
                }
                return m_arr[index];
            }

            ArrayList<T>& operator=(const ArrayList<T>& other)
            {
                if (m_arr != nullptr) delete[] m_arr;
                m_arr = new T[other.m_cap];
                m_size = other.m_size;
                m_cap = other.m_cap;
                for (int i = 0; i < m_size; i++)
                {
                    m_arr[i] = other.m_arr[i];
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

            class Iterator
            {
            public:
                using iterator_category = std::forward_iterator_tag;
                using difference_type = std::ptrdiff_t;
                using value_type = T;
                using pointer = T*;
                using reference = T&;

                Iterator(pointer ptr) : m_ptr(ptr) {}
                
                reference operator*() const 
                { 
                    return *m_ptr; 
                }
                
                pointer operator->() 
                {
                    return m_ptr; 
                }

                Iterator& operator++() 
                {
                    m_ptr++; return *this;
                }

                Iterator operator++(int) 
                {
                    Iterator tmp = *this; ++(*this); return tmp; 
                }

                friend bool operator==(const Iterator& it1, const Iterator& it2) 
                { 
                    return it1.m_ptr == it2.m_ptr; 
                };

                friend bool operator!=(const Iterator& it1, const Iterator& it2) 
                {
                    return it1.m_ptr != it2.m_ptr; 
                };

            private:
                pointer m_ptr;
            };

            Iterator begin() 
            {
                return Iterator(m_arr); 
            }

            Iterator end() 
            {
                return Iterator(m_arr + m_size); 
            }

        private:
            uint m_cap;
            T* m_arr;
            uint m_size;
        };

        template<typename T1, typename T2>
        struct Pair
        {
            T1 first;
            T2 second;

            Pair() {}
            Pair(T1 first, T2 second)
            {
                this->first = first;
                this->second = second;
            }

            Pair<T1, T2>& operator=(const Pair<T1, T2>& other)
            {
                first = other.first;
                second = other.second;
                return *this;
            }

            friend bool operator==(const Pair<T1, T2>& pair1, const Pair<T1, T2>& pair2)
            {
                return pair1.first == pair2.first && pair1.second == pair2.second;
            }

            friend bool operator!=(const Pair<T1, T2>& pair1, const Pair<T1, T2>& pair2)
            {
                return !(pair1 == pair2);
            }
        };

        template<typename K, typename V>
        class HashMap
        {
        public:
            HashMap() {};

            HashMap(ArrayList<Pair<K, V>> list) 
            {
                this->list = list;
            }

            HashMap(std::initializer_list<Pair<K, V>> list)
            {
                this->list = ArrayList(list);
            }

            V& operator[](K key)
            {
                for (int i = 0; i < list.size(); i++)
                {
                    if (list[i].first == key) return list[i].second;
                }
                Sapphire::Err("DSA::HashMap --> key " + std::to_string(key) + " not found");
                throw std::runtime_error("Sapphire: DSA::HashMap --> key " + std::to_string(key) + " not found");
            }

            HashMap<K, V>& operator=(const HashMap<K, V>& other)
            {
                list = other.list;
                return *this;
            }

            friend bool operator==(const HashMap<K, V>& map1, const HashMap<K, V>& map2)
            {
                return map1.list == map2.list;
            }

            friend bool operator!=(const HashMap<K, V>& map1, const HashMap<K, V>& map2)
            {
                return !(map1 == map2);
            }

            void set(K key, V value)
            {
                for (int i = 0; i < list.size(); i++)
                {
                    if (list[i].first == key)
                    {
                        list[i].second = value;
                        return;
                    }
                }

                list.add(Pair<K, V>(key, value));
            }

            class Iterator
            {
            public:
                using iterator_category = std::forward_iterator_tag;
                using difference_type = std::ptrdiff_t;
                using value_type = Pair<K, V>;
                using pointer = Pair<K, V>*;
                using reference = Pair<K, V>&;

                Iterator(pointer ptr) : m_ptr(ptr) {}
                
                reference operator*() const 
                { 
                    return *m_ptr; 
                }
                
                pointer operator->() 
                {
                    return m_ptr; 
                }

                Iterator& operator++() 
                {
                    m_ptr++; return *this;
                }

                Iterator operator++(int) 
                {
                    Iterator tmp = *this; ++(*this); return tmp; 
                }

                friend bool operator==(const Iterator& it1, const Iterator& it2) 
                { 
                    return it1.m_ptr == it2.m_ptr; 
                };

                friend bool operator!=(const Iterator& it1, const Iterator& it2) 
                {
                    return it1.m_ptr != it2.m_ptr; 
                };

            private:
                pointer m_ptr;
            };

            Iterator begin() 
            {
                return Iterator(list.data()); 
            }

            Iterator end() 
            {
                return Iterator(list.data() + list.size()); 
            }
            
        private:
            ArrayList<Pair<K, V>> list;
        };
        
    }
}
