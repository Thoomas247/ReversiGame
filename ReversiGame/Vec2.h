/*
* Thomas Amiouny (107527)
* Gonçalo Paiva	(106888)
*/

#include "GameOptions.h"

typedef struct Vec2
{
	int x;
	int y;
} Vec2;

/*
* Returns the sum of a and b.
* Adds the two Vec2s component-wise.
*/
Vec2 Vec2_add(Vec2 a, Vec2 b);

/*
* Returns true if a and b are equal, false otherwise.
*/
BOOL Vec2_equal(Vec2 a, Vec2 b);

/*
* Returns the sum of the components of a.
*/
int Vec2_componentSum(Vec2 a);