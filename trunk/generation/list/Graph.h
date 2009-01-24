#ifndef __GRAPH_H__
#define __GRAPH_H__

#include "LinkedList.h"
#include "MapNode.h"

/*
class DirectedGraph {
	public:
		void addNode(int id);
		void addEdge(int fromid, int toid);
		void deleteNode(int id);
		void deleteNthNode(int n);
		void deleteEdge(int fromid, int toid);
		void deleteRandomEdge();

	private:
		SortedLinkedList<MapNode> nodeList;
};
*/
class UndirectedGraph {
	public:

		MapNode* findNode(int id)
		{
			return nodeList.find(id);
		}

		MapNode* addNode(int id) {
			return nodeList.insert(id);
		}

		bool addEdge(int fromid, int toid) {
			
			MapNode* from = findNode(fromid);
			MapNode* to = findNode(toid);

			if(from == NULL || to == NULL)
			{
				return false;
			}
			
			from->addEdge(toid);
			to->addEdge(fromid);
			return true;
		}

		void deleteNode(int id)
		{
			MapNode removee(id); 
			nodeList.remove(removee);
			purgeEdges(id);
		}

		void deleteNthNode(int n) {
			MapNode *target = nodeList.warp(n);
			deleteNode(target->getId()); // this part is duplicating search to the target, might be inefficient..
		}

		bool deleteEdge(int fromid, int toid)
		{
			MapNode *from = findNode(fromid);
			MapNode *to = findNode(toid);

			if(from == NULL || to == NULL)
				return false;

			from->deleteEdge(toid);
			to->deleteEdge(fromid);
		}

	protected:
		SortedLinkedList<MapNode> nodeList;
	private:

		// delete all edges involving node with nodeid ( complexity: n * e)
		void purgeEdges(int nodeid) {
			ListIterator< MapNode> iter(nodeList);
			for( MapNode *i = iter.start(); iter.hasNext(i); i = iter.next())
			{
				i->deleteEdge(nodeid);
			}
			deleteUnconnectedNodes();
		}


	public:
		void deleteUnconnectedNodes() {
			bool found = true;
			while(found)
			{
				found = false;
				ListIterator< MapNode> iter(nodeList);
				for( MapNode *i = iter.start(); iter.hasNext(i); i = iter.next())
				{
					if(i->size() == 0)
					{
						nodeList.warp(iter);
						nodeList.destroy();
						found = true;
						break;
					}
				}
			}
		}

		void renameEdges(int oldid, int newid) {
			ListIterator< MapNode> iter(nodeList);
			for( MapNode *i = iter.start(); iter.hasNext(i); i = iter.next())
			{
				printf("ren(%d)",i->getId());
				i->renameEdges(oldid, newid);
			}
			printf("\n");
					
		}


};



#endif
