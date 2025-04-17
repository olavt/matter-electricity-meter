/*
 * ArraySlice.h
 *
 *  Created on: Feb 4, 2024
 *      Author: olavt
 */

#pragma once

template <typename T> class ArraySlice
{

public:

  ArraySlice(T fromArray[], int start, int length);

  ArraySlice(ArraySlice& fromSlice, int start, int length);

  const T& operator[](int index);

  int size();

private:

  T* _array;
  int _start;
  int _length;

};

template <typename T> ArraySlice<T>::ArraySlice(T fromArray[], int start, int length)
{
  _array = fromArray;
  _start = start;
  _length = length;
}

template <typename T> ArraySlice<T>::ArraySlice(ArraySlice& fromSlice, int start, int length)
{
  _array = fromSlice._array;
  _start = fromSlice._start + start;
  _length = length;
}

template <typename T> int ArraySlice<T>::size()
{
  return _length;
}

template <typename T> const T& ArraySlice<T>::operator[](int index)
{
  return _array[_start + index];
}
