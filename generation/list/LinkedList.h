#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

#include <ga/ga.h>

template <typename T>
class LinkedList : public GAList<T>
{
public:

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
class SortedLinkedList : public LinkedList
{
	public: 

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
					LinkedList::insert(insertee, GAListBASE::HEAD);
				else
					LinkedList::insert(insertee, GAListBASE::BEFORE);
				return true;
			}
		}
		
		tail();
		LinkedList::insert(insertee, GAListBASE::TAIL);
	}

	private:

	void insert(GAList<T> * t, GAListBASE::Location where=AFTER)
	{
		LinkedList::insert(t, where);
	}

	void insert(const T& t, GAListBASE::Location where=AFTER)
	{
		LinkedList::insert(t, where);
	}

}



template<typename T>
class ListIterator : public GAListIter<T> {
	public:

	ListIterator<T>(const GAList<T> &list)
	: GAListIter<T>(list)
	{
		start = true;
		theHead = head();
	}

	T *start()
	{
		return theHead;
	}

	bool isStart(T *i) {
		return (theHead == i);
	}

	bool hasNext(T *i) {
		bool rval = i && (start || i!=theHead);
		start = false;
		return rval;
	}

	T *next()
	{
		return next();
	}


	private:
		T *theHead;
		bool start;

};


#endif
