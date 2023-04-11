#pragma once

#include "Vec2.h"

typedef unsigned int DirectionField;

/*
* Struct representing a single valid move and the number of points it would give.
*/
typedef struct ValidMove
{
	Vec2 coord;
	int strength;
	DirectionField directions;
} ValidMove;

/*
* A wrapper around ValidMove which holds a pointer to the next item in the list.
*/
typedef struct ValidMoveNode
{
	ValidMove data;
	struct ValidMoveNode* pNext;
} ValidMoveNode;

/*
* Holds a pointer to the first item in the list and a count for convenience.
*/
typedef struct ValidMoveList
{
	int count;
	ValidMove* pFirst;
} ValidMoveList;

/*
* Creates an empty ValidMoveList.
*/
ValidMoveList ValidMoveList_create();

/*
* Adds an item to the list.
*/
void ValidMoveList_add(ValidMoveList* pList, ValidMove move);

/*
* Clears the list completely.
*/
void ValidMoveList_clear(ValidMoveList* pList);

