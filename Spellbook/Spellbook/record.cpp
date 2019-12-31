#include "record.h"
#include <windows.h>


void record::node::setnode(long double t, POINT p,POINT p2, int k ,long double r)
	{
		time = t;
		pos = p;
		key = k;
		rep = r;
		pos2 = p2;

	}
