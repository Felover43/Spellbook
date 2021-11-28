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

void  record::sortcat() {
	int i = 0;
	while (1+i < vec.size())
	{
		if (vec[i].time > vec[1+i].time)
		{
			std::swap(vec[i], vec[1+i]);
			i = 0;
		}
		else {
			i++;
		}

	}
}