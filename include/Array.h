/*
 * Array.h
 *
 *  Created on: Feb 4, 2024
 *      Author: olavt
 */

#pragma once

template <typename T> class Array
{

public:

  Array();

  // 1. Copy constructor
  Array(const Array& copyFrom);

  Array(int size);

  // 2. Copy assignment operator
  Array& operator=(const Array& copyFrom);

  // 3. Destructor
  ~Array();

  T& operator[](int index);

  int size();

private:

  int _size;
  T* _array;

};

template <typename T> Array<T>::Array()
{
  _size = 0;
  _array = 0;
}

// Copy constructor
template <typename T> Array<T>::Array(const Array& copyFrom)
{
    _size = copyFrom._size;
    _array = new T[_size];
    for (int i = 0; i < _size; i++)
        _array[i] = copyFrom._array[i];
}

template <typename T> Array<T>::Array(int size)
{
  _size = size;
  _array = new T[size];
}

// https://stackoverflow.com/questions/4172722/what-is-the-rule-of-three
// The default copy constructor does only perform a bitwise copy. To properly
// handle dynamically allocated resources by this class we need to override
// the copy assignment constructor.
template <typename T> Array<T>& Array<T>::operator=(const Array<T>& copyFrom)
{
    T* localArray = new T[copyFrom._size];
    // If the above statement throws,
    // the object is still in the same state as before.
    // None of the following statements will throw an exception :)
    for (int i = 0; i < copyFrom._size; i++)
        localArray[i] = copyFrom._array[i];
    delete[] _array;
    _array = localArray;
    _size = copyFrom._size;
    return *this;
}

template <typename T> Array<T>::~Array()
{
  delete _array;
}

template <typename T> T& Array<T>::operator[](int index)
{
  return _array[index];
}

template <typename T> int Array<T>::size()
{
  return _size;
}
