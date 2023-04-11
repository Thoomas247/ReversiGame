/*
* Thomas Amiouny (107527)
* Gonçalo Paiva	(106888)
*/

#include "ValidMove.h"

#include <stdlib.h>
#include <stdio.h>

/*
* Helper function to return the last node of the list.
*/
static ValidMoveNode* getLastNode(ValidMoveList* pList)
{
	ValidMoveNode* pNode = pList->pFirst;

	/* return NULL if list is empty */
	if (!pNode) return NULL;

	/* find the last node */
	while (pNode->pNext != NULL)
	{
		pNode = pNode->pNext;
	}

	return pNode;
}

/*
* Helper function to allocate a single node.
* Used to keep track of allocations.
*/
static ValidMoveNode* allocateNode()
{
	ValidMoveNode* pNode = (ValidMoveNode*)calloc(1, sizeof(ValidMoveNode));

#ifdef DEBUG
	printf("Allocated node.\n");
#endif

	return pNode;
}

/*
* Helper function to free a single node.
* Used to keep track of free operations.
*/
static void freeNode(ValidMoveNode* pNode)
{
	free(pNode);
#ifdef DEBUG
	printf("Freed node.\n");
#endif
}

ValidMoveList ValidMoveList_create()
{
	ValidMoveList list;
	list.count = 0;
	list.pFirst = NULL;
	return list;
}

void ValidMoveList_add(ValidMoveList* pList, ValidMove data)
{
	ValidMoveNode* pNode = allocateNode();

	/* return if allocation failed */
	if (!pNode) return;

	ValidMoveNode* pLast = getLastNode(pList);

	if (!pLast)
	{
		pList->pFirst = pNode;
	}
	else
	{
		pLast->pNext = pNode;
	}

	pNode->data = data;
	++(pList->count);
}

void ValidMoveList_clear(ValidMoveList* pList)
{
	ValidMoveNode* pNode = pList->pFirst;
	ValidMoveNode* pNext;

	while (pNode)
	{
		pNext = pNode->pNext;
		freeNode(pNode);
		pNode = pNext;
	}

	pList->count = 0;
	pList->pFirst = NULL;
}
