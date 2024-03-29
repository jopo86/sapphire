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
        /*
            @brief Returns the minimum of two values.
         !  Will throw an error if the value type is not comparable.
            @param a The first value.
            @param b The second value.
            @return The minimum of the two values.
         */
        template<typename T>
        T Min(T a, T b)
        {
            return a < b ? a : b;
        }
        
        /*
            @brief Returns the index of the minimum value in an array in the given range.
         !  Will throw an error if the value type in the array is not comparable.
            @param arr The array to search.
            @param start The start index of the range, inclusive.
            @param end The end index of the range, exclusive.
            @return The index of the minimum value in the given range.
         */
        template<typename T>
        int MinIndex(T* arr, uint start, uint end)
        {
            if (end - start == 0)
            {
                Sapphire::Warn("DSA::MinIndex() --> range is 0, cannot find minimum value. Returning -1");
                return -1;
            }

            int minI = start;
            for (int i = start + 1; i < end; i++)
            {
                if (arr[i] < arr[minI]) minI = i;
            }
            return minI;
        }

        /*
            @brief Returns the index of the minimum value in an array.
         !  Will throw an error if the value type in the array is not comparable.
            @param arr The array to search.
            @param size The size of the array.
            @return The index of the minimum value in the array.
         */
        template<typename T>
        int MinIndex(T* arr, uint size)
        {
            return MinIndex(arr, 0, size);
        }

        /*
            @brief Returns the maximum of two values.
         !  Will throw an error if the value type is not comparable.
            @param a The first value.
            @param b The second value.
            @return The maximum of the two values.
         */
        template<typename T>
        T Max(T a, T b)
        {
            return a > b ? a : b;
        }
        
        /*
            @brief Returns the index of the maximum value in an array in the given range.
         !  Will throw an error if the value type in the array is not comparable.
            @param arr The array to search.
            @param start The start index of the range, inclusive.
            @param end The end index of the range, exclusive.
            @return The index of the maximum value in the given range.
         */
        template<typename T>
        int MaxIndex(T* arr, uint start, uint end)
        {
            if (end - start == 0)
            {
                Sapphire::Warn("DSA::MaxIndex() --> range is 0, cannot find maximum value. Returning -1");
                return -1;
            }

            int maxI = start;
            for (int i = start + 1; i < end; i++)
            {
                if (arr[i] > arr[maxI]) maxI = i;
            }
            return maxI;
        }

        /*
            @brief Returns the index of the maximum value in an array.
         !  Will throw an error if the value type in the array is not comparable.
            @param arr The array to search.
            @param size The size of the array.
            @return The index of the maximum value in the array.
         */
        template<typename T>
        int MaxIndex(T* arr, uint size)
        {
            return MaxIndex(arr, 0, size);
        }

        /*
            @brief Swaps the values of two pointers.
            @param p_a The first pointer.
            @param p_b The second pointer.
         */
        template<typename T>
        void Swap(T* p_a, T* p_b)
        {
            T tmp = *p_a;
            *p_a = *p_b;
            *p_b = tmp;
        }

        /*
            @brief Searches an array for a given element using linear search.
            Works for all arrays, ideal for unsorted arrays.
            Runtime complexity: O(n)
            @param arr The array to search.
            @param size The size of the array.
            @param elem The element to search for.
            @return The index of the element in the array, or -1 if the element is not found.
         */
        template<typename T>
        int LinearSearch(T* arr, uint size, T elem)
        {
            for (int i = 0; i < size; i++)
            {
                if (arr[i] == elem) return i;
            }
            return -1;
        }

        /*
            @brief Searches an array for a given element using binary search.
            Only works for sorted arrays.
         !  Will throw an error if the value type in the array is not comparable.
            Runtime complexity: O(log n)
            @param arr The array to search.
            @param size The size of the array.
            @param elem The element to search for.
            @return The index of the element in the array, or -1 if the element is not found.
         */
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

        /*
            @brief Searches an array for a given element using interpolation search.
            Only works for sorted arrays, ideal for uniformly distributed arrays.
         !  Will throw an error if the value type in the array is not comparable.
         !  Will throw an error if the value type in the array is not comparable.
            Runtime complexity: O(log log n), worst case O(n)
            @param arr The array to search.
            @param size The size of the array.
            @param elem The element to search for.
            @return The index of the element in the array, or -1 if the element is not found.
         */
        template<typename T>
        int InterpolationSearch(T* arr, uint size, T elem)
        {
            int high = size - 1;
            int low = 0;

            while(elem >= arr[low] && elem <= arr[high] && low <= high)
            {
                int probe = low + (high - low) * (elem - arr[low]) / (arr[high] - arr[low]);

                if (elem == arr[probe]) return probe;
                else if (elem > arr[probe]) low = probe + 1;
                else high = probe - 1;
            }

            return -1;
        }

        /*
            @brief Checks if an array contains a given element.
            Uses linear search.
            @param arr The array to search.
            @param size The size of the array.
            @param elem The element to search for.
            @return True if the element is found, false otherwise.
         */
        template<typename T>
        int Contains(T* arr, uint size, T elem)
        {
            return LinearSearch(arr, size, elem) != -1;
        }

        /*
            @brief Sorts an array using the bubble sort algorithm.
         !  Will throw an error if the value type in the array is not comparable.
            Runtime complexity: O(n^2)
            @param arr The array to sort.
            @param size The size of the array.
         */
        template<typename T>
        void BubbleSort(T* arr, uint size)
        {
            for (int i = 0; i < size - 1; i++)
            {
                for (int j = 0; j < size - 1; j++)
                {
                    if (arr[j] > arr[j + 1])
                    {
                        Swap(&arr[j], &arr[j + 1]);
                    }
                }
            }
        }

        /*
            @brief Sorts an array using the selection sort algorithm.
         !  Will throw an error if the value type in the array is not comparable.
            Runtime complexity: O(n^2)
            @param arr The array to sort.
            @param size The size of the array.
         */
        template<typename T>
        void SelectionSort(T* arr, uint size)
        {
            for (int i = 0; i < size - 1; i++)
            {
                int minI = MinIndex(arr, i, size);
                Swap(&arr[i], &arr[minI]);
            }
        }

        /*
            @brief Merges two sorted arrays into one sorted array.
         !  Will throw an error if the value type in the array is not comparable.
            Used as a helper function for MergeSort.
            @param leftArr The left array to merge.
            @param rightArr The right array to merge.
            @param arr The array to merge into.
            @param size The size of the arrays.
         */
        template<typename T>
        void Merge(T* leftArr, T* rightArr, T* arr, uint size)
        {
            int leftSize = size / 2;
            int rightSize = size - leftSize;
            int i = 0, l = 0, r = 0;

            while (l < leftSize && r < rightSize)
            {
                if (leftArr[l] < rightArr[r])
                {
                    arr[i] = leftArr[l];
                    i++;
                    l++;
                }
                else
                {
                    arr[i] = rightArr[r];
                    i++;
                    r++;
                }
            }

            while (l < leftSize)
            {
                arr[i] = leftArr[l];
                i++;
                l++;
            }

            while (r < rightSize)
            {
                arr[i] = rightArr[r];
                i++;
                r++;
            }
        }

        /*
            @brief Sorts an array using the merge sort algorithm.
            Ideal for larger arrays.
         !  Will throw an error if the value type in the array is not comparable.
            Runtime complexity: O(n log n)
            Space complexity: O(n)
            @param arr The array to sort.
            @param size The size of the array.
         */
        template<typename T>
        void MergeSort(T* arr, uint size)
        {
            if (size <= 1) return;

            int mid = size / 2;
            int* leftArr = new int[mid];
            int* rightArr = new int[size - mid];

            int i = 0, j = 0;

            for (; i < size; i++)
            {
                if (i < mid) leftArr[i] = arr[i];
                else 
                {
                    rightArr[j] = arr[i];
                    j++;
                }
            }

            MergeSort(leftArr, mid);
            MergeSort(rightArr, size - mid);
            Merge(leftArr, rightArr, arr, size);

            delete[] leftArr;
            delete[] rightArr;
        }

        /*
            @brief Partitions an array and generates a pivot.
            Used as a helper function for QuickSort.
         !  Will throw an error if the value type in the array is not comparable.
            @param arr The array to partition.
            @param start The start index of the partition.
            @param end The end index of the partition.
            @return The index of the pivot.
         */
        template<typename T>
        int Partition(T* arr, int start, int end) 
        {
            T pivot = arr[end];

            int i = start - 1;
            for (int j = start; j < end; j++) 
            {
                if (arr[j] <= pivot) 
                {
                    i++;
                    Swap(&arr[i], &arr[j]);
                }
            }
            
            Swap(&arr[i + 1], &arr[end]);
            return i + 1;
        }

        /*
            @brief Sorts an array using the quick sort algorithm.
            Ideal for smaller arrays.
         !  Will throw an error if the value type in the array is not comparable.
            Runtime complexity: O(n log n)
            Space complexity: O(log n)
            @param arr The array to sort.
            @param start The start index of the array.
            @param end The end index of the array.
         */
        template<typename T>
        void QuickSort(T* arr, int start, int end) 
        {
            if (start < end) 
            {
                int pivot = Partition(arr, start, end);
                QuickSort(arr, start, pivot - 1);
                QuickSort(arr, pivot + 1, end);
            }
        }

        /*
            @brief Sorts an array using the quick sort algorithm.
            Ideal for smaller arrays.
         !  Will throw an error if the value type in the array is not comparable.
            Runtime complexity: O(n log n)
            Space complexity: O(log n)
            @param arr The array to sort.
            @param size The size of the array.
         */
        template<typename T>
        void QuickSort(T* arr, uint size)
        {
             QuickSort(arr, 0, size - 1);
        }

        /*
            @brief A class to represent a fixed-size array.
         */
        template<typename T>
        class Array
        {
        public:
            /*
                @brief Creates an empty array.
             */
            Array()
            {
                m_arr = new T[0];
                m_size = 0;
            }

            /*
                @brief Creates an array of a given size.
                @param size The size of the array.
             */
            Array(uint size)
            {
                m_arr = new T[size];
                m_size = size;
            }

            
            /*
                @brief Creates an array from a given array.
                @param arr The array to copy.
                @param size The size of the array.
             */
            Array(T* arr, uint size)
            {
                m_arr = new T[size];
                m_size = size;
                for (int i = 0; i < size; i++)
                {
                    m_arr[i] = arr[i];
                }
            }

            /*
                @brief Creates an array from a given array object.
                @param arr The array to copy.
             */
            Array(const Array<T>& arr)
            {
                m_arr = new T[arr.m_size];
                m_size = arr.m_size;
                for (int i = 0; i < m_size; i++)
                {
                    m_arr[i] = arr.m_arr[i];
                }
            }
            
            /*
                @brief Creates an array from a given initializer list.
                @param list The initializer list to copy.
             */
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

            /*
                @brief Destroys the array object and frees the memory.
             */
            ~Array()
            {
                if (m_arr != nullptr) delete[] m_arr;
            }

            /*
                @brief Searches an array for a given element using linear search.
                Works for all arrays, ideal for unsorted arrays.
                Runtime complexity: O(n)
                @param elem The element to search for.
                @return The index of the element in the array, or -1 if the element is not found.
             */
            int linearSearch(T elem)
            {
                return LinearSearch(m_arr, m_size, elem);
            }

            /*
                @brief Searches an array for a given element using binary search.
                Only works for sorted arrays.
             !  Will throw an error if the value type in the array is not comparable.
                Runtime complexity: O(log n)
                @param elem The element to search for.
                @return The index of the element in the array, or -1 if the element is not found.
             */
            int binarySearch(T elem)
            {
                return BinarySearch(m_arr, m_size, elem);
            }

            /*
                @brief Searches an array for a given element using interpolation search.
                Only works for sorted arrays, ideal for uniformly distributed arrays.
             !  Will throw an error if the value type in the array is not comparable.
                Runtime complexity: O(log log n), worst case O(n)
                @param elem The element to search for.
                @return The index of the element in the array, or -1 if the element is not found.
             */
            int interpolationSearch(T elem)
            {
                return InterpolationSearch(m_arr, m_size, elem);
            }

            /*
                @brief Checks if an array contains a given element.
                Uses linear search.
                @param elem The element to search for.
                @return True if the element is found, false otherwise.
             */
            bool contains(T elem)
            {
                return linearSearch(elem) != -1;
            }

            /*
                @brief Sorts an array using the bubble sort algorithm.
             
             !  Will throw an error if the value type in the array is not comparable.!  Will throw an error if the value type in the array is not comparable.
                Runtime complexity: O(n^2)
             */
            void bubbleSort()
            {
                BubbleSort(m_arr, m_size);
            }

            /*
                @brief Sorts an array using the selection sort algorithm.
             !  Will throw an error if the value type in the array is not comparable.
                Runtime complexity: O(n^2)
             */
            void selectionSort()
            {
                SelectionSort(m_arr, m_size);
            }

            /*
                @brief Sorts an array using the merge sort algorithm.
                Ideal for larger arrays.
             !  Will throw an error if the value type in the array is not comparable.
                Runtime complexity: O(n log n)
                Space complexity: O(n)
             */
            void mergeSort()
            {
                MergeSort(m_arr, m_size);
            }

            /*
                @brief Sorts an array using the quick sort algorithm.
                Ideal for smaller arrays.
             !  Will throw an error if the value type in the array is not comparable.
                Runtime complexity: O(n log n)
                Space complexity: O(log n)
             */
            void quickSort()
            {
                QuickSort(m_arr, m_size);
            }

            /*
                @brief Returns the size of the array.
                @return The number of elements in the array.
             */
            uint size()
            {
                return m_size;
            }

            /*
                @brief Returns the underlying array/pointer.
                @return The array data.
             */
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

        /*
            @brief A class to represent a dynamic array, known as std::vector in C++ and ArrayList in Java and some other languages.
         */
        template<typename T>
        class ArrayList
        {
        public:
            /*
                @brief Creates an empty array list.
             */
            ArrayList()
            {
                m_cap = 10;
                m_arr = new T[m_cap];
                m_size = 0;
            }

            /*
                @brief Creates an array list of a given size.
                @param size The size of the array list.
             */
            ArrayList(uint size)
            {
                m_cap = Max((uint)(size * 1.5), (uint)10);
                m_arr = new T[m_cap];
                m_size = size;
            }

            /*
                @brief Creates an array list from a given array.
                @param size The size of the array list.
                @param arr The array to copy.
             */
            ArrayList(T* arr, uint size)
            {
                m_cap = Max((uint)(size * 1.5), (uint)10);
                m_arr = new T[m_cap];
                m_size = size;
                for (int i = 0; i < size; i++)
                {
                    m_arr[i] = arr[i];
                }
            }

            /*
                @brief Creates an array list from a given array list object.
                @param arr The array list to copy.
             */
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

            /*
                @brief Creates an array list from a given initializer list.
                @param list The initializer list to copy.
             */
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

            /*
                @brief Destroys the array list object and frees the memory.
             */
            ~ArrayList()
            {
                if (m_arr != nullptr) delete[] m_arr;
            }

            /*
                @brief Searches an array list for a given element using linear search.
                Works for all arrays, ideal for unsorted arrays.
                Runtime complexity: O(n)
                @param elem The element to search for.
                @return The index of the element in the array list, or -1 if the element is not found.
             */
            int linearSearch(T elem)
            {
                return LinearSearch(m_arr, m_size, elem);
            }

            /*
                @brief Searches an array list for a given element using binary search.
                Only works for sorted arrays.
             !  Will throw an error if the value type in the array is not comparable.
                Runtime complexity: O(log n)
                @param elem The element to search for.
                @return The index of the element in the array list, or -1 if the element is not found.
             */
            int binarySearch(T elem)
            {
                return BinarySearch(m_arr, m_size, elem);
            }


            /*
                @brief Searches an array list for a given element using interpolation search.
                Only works for sorted arrays, ideal for uniformly distributed arrays.
             !  Will throw an error if the value type in the array is not comparable.
                Runtime complexity: O(log log n), worst case O(n)
                @param elem The element to search for.
                @return The index of the element in the array list, or -1 if the element is not found.
             */
            int interpolationSearch(T elem)
            {
                return InterpolationSearch(m_arr, m_size, elem);
            }


            /*
                @brief Checks if an array list contains a given element.
                Uses linear search.
             !  Will throw an error if the value type in the array is not comparable.
                @param elem The element to search for.
                @return True if the element is found, false otherwise.
             */
            int contains(T elem)
            {
                return linearSearch(elem) != -1;
            }

            /*
                @brief Sorts an array list using the bubble sort algorithm.
             !  Will throw an error if the value type in the array is not comparable.
                Runtime complexity: O(n^2)
             */
            void bubbleSort()
            {
                BubbleSort(m_arr, m_size);
            }

            /*
                @brief Sorts an array list using the selection sort algorithm.
             !  Will throw an error if the value type in the array is not comparable.
                Runtime complexity: O(n^2)
             */
            void selectionSort()
            {
                SelectionSort(m_arr, m_size);
            }

            /*
                @brief Sorts an array list using the merge sort algorithm.
                Ideal for larger arrays.
             !  Will throw an error if the value type in the array is not comparable.
                Runtime complexity: O(n log n)
                Space complexity: O(n)
             */
            void mergeSort()
            {
                MergeSort(m_arr, m_size);
            }

            /*
                @brief Sorts an array list using the quick sort algorithm.
                Ideal for smaller arrays.
             !  Will throw an error if the value type in the array is not comparable.
                Runtime complexity: O(n log n)
                Space complexity: O(log n)
             */
            void quickSort()
            {
                QuickSort(m_arr, m_size);
            }

            /*
                @brief Returns the size of the array list.
                @return The number of elements in the array list.
             */
            uint size()
            {
                return m_size;
            }

            /*
                @brief Adds an element to the end of the array list.
                @param elem The element to add.
             */
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

            /*
                @brief Inserts an element at a given index in the array list.
                @param elem The element to insert.
                @param index The index to insert the element at.
             */
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

            /*
                @brief Removes an element at a given index in the array list.
                @param index The index to remove the element at.
             */
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

            /*
                @brief Removes the last element in the array list.
                @return The removed element.
             */
            T pop()
            {
                T elem = m_arr[m_size - 1];
                remove(m_size - 1);
                return elem;
            }

            /*
                @brief Removes all occurrences of a given element in the array list.
                @param elem The element to remove.
             */
            
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

            /*
                @brief Returns the underlying array/pointer.
                @return The array list data.
             */
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

        /*
            @brief A class to represent a pair of values.
         */
        template<typename T1, typename T2>
        struct Pair
        {
            T1 first;
            T2 second;

            /*
                @brief Creates an empty pair (with garbage values).
             */
            Pair() {}

            /*
                @brief Creates a pair from two given values.
                @param first The first value.
                @param second The second value.
             */
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

        /*
            @brief A class to represent a hash map, known as std::map in C++ and a HashMap in Java and some other languages.
         */
        template<typename K, typename V>
        class HashMap
        {
        public:
            /*
                @brief Creates an empty hash map.
             */
            HashMap() {};

            /*
                @brief Creates a hash map from a given array list of pairs.
                @param list The array list to copy.
             */
            HashMap(ArrayList<Pair<K, V>> list) 
            {
                this->list = list;
            }

            /*
                @brief Creates a hash map from a given initializer list of pairs.
                @param list The initializer list to copy.
             */
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
