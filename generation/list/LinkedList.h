#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include <ga/ga.h>

template<typename T>
class ListIterator : public GAListIter<T> {
	public:

	ListIterator(const GAList<T> &list)
	: GAListIter<T>(list)
	{
		starting = true;
		theHead = GAListIter<T>::head();
	}

	T *start()
	{
		return theHead;
	}

	bool isStart(T *i) {
		return (theHead == i);
	}

	bool hasNext(T *i) {
		bool rval = i && (starting || i!=theHead);
		starting = false;
		return rval;
	}

	T *next()
	{
		return GAListIter<T>::next();
	}


	private:
		T *theHead;
		bool starting;

};




template <typename T>
class LinkedList : public GAList<T>
{
public:

 	T* find(const T& target)
	{
		ListIterator<T> iter(*this);
		for(T *i = iter.start(); iter.hasNext(); i = iter.next())
		{
			if(target == *i)
				return i;
		}
		return NULL;
	}

	T* getNth(int n)
	{
		ListIterator<T> iter(*this);
		int j = 0;
		for(T *i = 	iter.start(); iter.hasNext(); i = iter.next())
		{
			if(j == n)
				return i;
		}
		return NULL;
	}

	bool remove(T& removee)
	{
		ListIterator<T> iter(*this);
		for(T *i = 	iter.start(); iter.hasNext(); i = iter.next())
		{
			if(removee == *i) {
				warp(iter);
				GAList<T>::destroy();
				return true;
			}
		}
		return false;
	}

	bool removeNth(int n)
	{
		ListIterator<T> iter(*this);
		int j = 0;
		for(T *i = iter.start(); iter.hasNext(); i = iter.next())
		{
			if(j == n)
			{
				warp(iter);
				GAList<T>::destroy();
				return true;
			}
			if(j > n)
				return false;
			j++;
		}
		return false;
		
	}


	friend ostream& operator<<(ostream &os, const LinkedList<T>& p) {
		LinkedList<T> t(p);
		for(T *i = t.iterator();t.hasNext(i);i = t.next())
		{
			os << *i << " ";
		}
		return os;
	}
};

/* sorted list that keeps unique elements only */
template<typename T>
class SortedLinkedList : public LinkedList<T>
{
	public: 

 	T* find(const T& target)
	{
		ListIterator<T> iter(*this);
		for(T *i = iter.start(); iter.hasNext(); i = iter.next())
		{
			if(target == *i)
				return i;
			if(*i < target) // assuming sorted list, no need to go further
				return NULL;
		}
		return NULL;
	}

	// insert T t with order
	bool insert(const T& insertee)
	{
		ListIterator<T> iter(*this);
		for(T *i = 	iter.start(); iter.hasNext(); i = iter.next())
		{
			if(insertee == *i)		
				return false;
			if(insertee < *i)
			{
				warp(iter);
				if(iter.isStart(i))
					LinkedList<T>::insert(insertee, GAListBASE::HEAD);
				else
					LinkedList<T>::insert(insertee, GAListBASE::BEFORE);
				return true;
			}
		}
		
		LinkedList<T>::tail();
		LinkedList<T>::insert(insertee, GAListBASE::TAIL);
	}

	bool remove(const T& removee)
	{
		ListIterator<T> iter(*this);
		for(T *i = 	iter.start(); iter.hasNext(); i = iter.next())
		{
			if(removee == *i) {
				LinkedList<T>::warp(iter);
				LinkedList<T>::destroy();
				return true;
			}
			if(*i < removee) // assuming sorted list, no need to go further
				return false;
		}
		return false;	
	}


	private:

	void insert(GAList<T> * t, GAListBASE::Location where=GAListBASE::AFTER)
	{
		LinkedList<T>::insert(t, where);
	}
/*
	void insert(const T& t, GAListBASE::Location where=GAListBASE::AFTER)
	{
		LinkedList<T>::insert(t, where);
	}
*/
};

#endif
