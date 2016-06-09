/**
 * xlxChain.h - Xlight Chain Object Library - This library creates the linkedlists in working memory (Rules, Schedule, Scenerio etc)
 *
 * Created by Baoshi Sun <bs.sun@datatellit.com>
 * Copyright (C) 2015-2016 DTIT
 * Full contributor list:
 *
 * Documentation:
 * Support Forum:
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 *******************************
 *
 * REVISION HISTORY
 * Version 1.0 - Created by Baoshi Sun <bs.sun@datatellit.com>
 *
 * DESCRIPTION
 *
 * ToDo:
**/

#include "xliCommon.h"
#include "LinkedList.h"

//------------------------------------------------------------------
// Chain Class, inherited from Arduino LinkedList base class
// Keep all member functions inside of this header file
//------------------------------------------------------------------
template <typename T>
class ChainClass : public LinkedList<T>
{
private:
  int max_chain_length;

public:
	ChainClass(int max);
	virtual ListNode<T>* search(uint8_t uid);
  virtual bool update(uint8_t uid, T);

  //overload set function to accept ptr to node, and data T
  virtual bool set(ListNode<T>* ptr, T);

	//overload all "add" functions to first check if linkedlist length is greater than PRE_FLASH_MAX_TABLE_SIZE
  virtual bool add(int index, T);
  virtual bool add(T);
  virtual bool unshift(T);

};

//------------------------------------------------------------------
// Member Functions
//------------------------------------------------------------------
template<typename T>
ChainClass<T>::ChainClass(int max)
{
  max_chain_length = max;
}

template<typename T>
ListNode<T>* ChainClass<T>::search(uint8_t uid)
{
  ListNode<T> *tmp = LinkedList<T>::root;
  while(tmp!=false)
	{
		if(tmp->data.uid == uid) {
      return tmp;
    }
		tmp=tmp->next;
	}
  return NULL;
}

template<typename T>
bool ChainClass<T>::update(uint8_t uid, T _t)
{
  if (search(uid) == NULL) {
    return false;
  }

  if (uid != _t.uid) {
    return false;
  }

  set(search(uid), _t);
  return true;
}

template<typename T>
bool ChainClass<T>::set(ListNode<T>* ptr, T _t)
{
	if (ptr == NULL) {
    return false;
  }
	ptr->data = _t;
	return true;
}

template<typename T>
bool ChainClass<T>::add(int index, T _t)
{
	if (LinkedList<T>::size() < max_chain_length)
	{
		return LinkedList<T>::add(index, _t);
	}
	else
	{
		return false;
	}
}

template<typename T>
bool ChainClass<T>::add(T _t)
{
	if (LinkedList<T>::size() < max_chain_length)
	{
		return LinkedList<T>::add(_t);
	}
	else
	{
		return false;
	}
}

template<typename T>
bool ChainClass<T>::unshift(T _t)
{
  if (LinkedList<T>::size() < max_chain_length)
	{
		return LinkedList<T>::add(_t);
	}
	else
	{
		return false;
	}
}
