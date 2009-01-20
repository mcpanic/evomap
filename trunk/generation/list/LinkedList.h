#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__


#include <ga/ga.h>

template <typename T>
class LinkedList : public GAList<T>
{
public:
	
	LinkedList()
	: GAList<T>()
	{
		iter = NULL;
	}

	LinkedList(const T& t)
	: GAList<T>(t)
	{
		iter = NULL;
	}

	LinkedList(const GAList<T>& orig)
	:	GAList<T>(orig)
	{
		iter = NULL;
	}	

	~LinkedList()
	{
		if(iter != NULL)
			delete iter;
	}

	T* iterator() {
		if(iter != NULL)
		{				
			delete iter;
		}
		iter = new GAListIter<T>(*this);
		start = true;
		theHead = iter->head();
		return theHead;
	}
	bool hasNext(T *i) {
		bool rval = i && (start || i!=theHead);
		start = false;
		return rval;
	}

	T *next()
	{
		return iter->next();
	}
	
	GAListIter<T>& getIterator()
	{
		if(iter==NULL)
			return *(iter = new GAListIter<T>(*this));
		return *iter;
	}


	friend ostream& operator<<(ostream &os, const LinkedList<T>& p) {
		LinkedList<T> t(p);
		for(T *i = t.iterator();t.hasNext(i);i = t.next())
		{
			os << *i << " ";
		}
		return os;
	}



	private:
		GAListIter<T> *iter;
		T *theHead;
		bool start;
};


#endif
