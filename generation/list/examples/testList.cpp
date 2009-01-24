#include <ga/ga.h>
#include <ga/std_stream.h>



void printList(GAList< GAList<int> > &list)
{
	GAListIter< GAList<int> > iter(list);
	GAList<int>*head = iter.head();
	bool start = true;
	for(GAList<int>* i = head; i && (start || i!=head); i = iter.next())
	{
		GAListIter<int> iter2(*i);
		int *head = iter2.head();
		start = false;	
		bool start = true;
		for(int *j = head; j && (start || j!=head); j = iter2.next())
		{
			printf("%d\n", *j);
			start = false;
		}
	}
}



int main(int argc, char* argv[])
{
	GAList<int> ilist;
	GAList<  GAList<int> > list;

	ilist.insert(5);
	ilist.insert(6);
	ilist.insert(7);

	list.insert(ilist);
	ilist.insert(8);
	list.insert(ilist);

	GAListIter< int >iter(ilist);
	iter.head();
	iter.next();
	ilist.warp(iter);
	ilist.insert(9,GAListBASE::BEFORE);
	int *t = ilist.current();
	printf("%d\n", *t);

	list.insert(ilist);

	//printList(list);

}


