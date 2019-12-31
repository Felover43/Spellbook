#pragma once
#ifndef _RECORD_

#include <windows.h>
#include <vector>


class record
{
public:
		class node
		{
		public:
			long double time;  // time is in between each node and not from start to new node
			POINT pos;		//cursor pos
			POINT pos2;		//when dragging
			int key;
			long double rep;
			//ctor&dtor
			node() { time = -1; key = 0; pos.x = 0; pos.y = 0; rep = 0; pos2.x = 0; pos2.y = 0; };
			~node() {};

			//sets the data for each moment in recording
			void setnode(long double t, POINT p,POINT p2, int k,long double r);
			void setkey(int k) { key = k; };
			void setposx(int x) { pos.x = x; };
			void setposy(int y) { pos.y = y; };
			void setpos2x(int x) { pos2.x = x; };
			void setpos2y(int y) { pos2.y = y; };
			void setrep(long double r) { rep = r; };
			void settime(long double t) { time = t; };
		};
		  //make sure this prototype works!!!!!!!!!!!!!!!!!!!!!!!!!!
private:
	std::vector<node> vec;
public:
	//ctor dtor
	record() {};
	~record() { vec.clear(); };
	//sets the vector
	void setvector(long double t, POINT p,POINT p2, int k, long double r)
	{
		node n;
		n.setnode(t, p,p2,k,r);
		vec.push_back(n);
	}
	void setEvec()
	{
		node n;
		POINT p ,p2;
		p.x = 0;
		p.y = 0;
		p2.x = 0;
		p2.y = 0;
		n.setnode(0, p, p2, 0, 0);
		vec.push_back(n);
	}
	std::vector<node> getvector(){return vec;}
	void setveckey(int k) { vec.back().setkey(k); }
	void setvecposx(int x) { vec.back().setposx(x); }
	void setvecposy(int y) { vec.back().setposy(y); }
	void setvecpos2x(int x) { vec.back().setpos2x(x); }
	void setvecpos2y(int y) { vec.back().setpos2y(y); }
	void setvecrep(long double r) { vec.back().setrep(r); }
	void setvectime(long double t) { vec.back().settime(t); }
	void cleancat() { vec.clear(); };
	
};


#endif //  !RECORD