#include "record.h"
#include <windows.h>


void record::node::setnode(long double t, POINT p, int k ,long double r)
	{
		time = t;
		pos = p;
		key = k;
		rep = r;
	}
