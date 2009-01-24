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
		starting = true;
		theHead = GAListIter<T>::head();

		return theHead;
	}

	bool isStart(T *i) {
		return (theHead == i);
	}

	bool hasNext(T *i) {
		bool rval = i && (starting || i!=theHead);
		return rval;
	}

	T *next()
	{
		starting = false;
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
		return GAList<T>::warp(n);
	}

	bool remove(T& removee)
	{
		ListIterator<T> iter(*this);
		for(T *i = 	iter.start(); iter.hasNext(i); i = iter.next())
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
		GAList<T>::warp(n);
		GAList<T>::destroy();
		return true;
		
	}


	friend ostream& operator<<(ostream &os, const LinkedList<T>& p) {
		ListIterator<T> iter(p);
		for(T *i = iter.start();iter.hasNext(i);i = iter.next())
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
		for(T *i = iter.start(); iter.hasNext(i); i = iter.next())
		{
			//printf("%d %d\n", target.getId(),i->getId());
			if(target == *i)
				return i;
			
			if(target < *i) // assuming sorted list, no need to go further
				return NULL;
		}
		return NULL;
	}

	// insert T t with order
	T* insert(const T& insertee)
	{
		ListIterator<T> iter(*this);
		for(T *i = 	iter.start(); iter.hasNext(i); i = iter.next())
		{
			if(insertee == *i)
			{
				return NULL;
			}
			if(insertee < *i)
			{
				warp(iter);
				if(iter.isStart(i)) {
					LinkedList<T>::insert(insertee, GAListBASE::HEAD);
					return LinkedList<T>::head();
				}
				else {
					LinkedList<T>::insert(insertee, GAListBASE::BEFORE);
					return LinkedList<T>::current();
				}
			}
		}
		
		LinkedList<T>::tail();
		LinkedList<T>::insert(insertee, GAListBASE::TAIL);
		return LinkedList<T>::tail();
	}

	bool remove(const T& removee)
	{
		ListIterator<T> iter(*this);
		for(T *i = 	iter.start(); iter.hasNext(i); i = iter.next())
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
