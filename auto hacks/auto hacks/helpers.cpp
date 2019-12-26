#include <string>
#include "helpers.h"
#include <chrono>
#include <Windows.h>
#include <fstream>
using namespace std;

string ExePath()
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	return string(buffer).substr(0, pos);
}
bool is_digits(const char* str)
{
	size_t n;
	int i = 0;
	bool check = true;
	string str1 = str;
	n = str1.length();
	while (i < n)
	{
		if (!isdigit(str[i]))
		{
			check = false;
			break;
		}
		i++;

	}
	return check ;
}
void SetColorPurp(HDC h)
{
	SetTextColor(h, RGB(255, 255, 255));
	SetBkColor(h, RGB(0, 0, 0));
}

int* whichkey()
{
	int pos = 0;
	int* b;
	while (true)
	{
		for (int i = 0; i < 256; i++) {
			if (GetAsyncKeyState(i) & 0x8000) {
				b[pos] = i;
				pos++;
			}
		}

	}
}

double dran(double max, double min)
{
	return (max - min) * ((double)rand() / (double)RAND_MAX) + min;
}
long double DelayMove(long double time)
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<long double> num;
	long double randtime = dran(1.5,0.7);
	start = std::chrono::system_clock::now();
	end = std::chrono::system_clock::now();
	num = end - start;
	while (num.count() <= time-randtime)
	{
		if (GetAsyncKeyState(VK_F2))
			return 0;
		end = std::chrono::system_clock::now();
		num = end - start;
	}
	return randtime;
}
//moves the mouse 
int MoveMouse(POINT poi, int step, long double time)
{
	POINT mouse;
	long currx, curry;
	
	if (time > 3)
	{
		time = DelayMove(time);
		if (time == 0)
			return -1;
	}
	GetCursorPos(&mouse);
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<long double> num;
	for (int i = 0; i < step; i++)						//divides the mouses movements into steps
	{
		if (GetAsyncKeyState(VK_F2))
			return -1;
		currx = mouse.x + (long)((poi.x - mouse.x)*i / step);
		curry = mouse.y + (long)((poi.y - mouse.y)*i / step);
		SetCursorPos((int)currx,(int)curry);
		start = std::chrono::system_clock::now();
		end = std::chrono::system_clock::now();
		num = end -start;
		while (num.count() <= time / step)			//delays the movement speed so it looks natural
		{
			if (GetAsyncKeyState(VK_F2))
				return -1;
			end = std::chrono::system_clock::now();
			num = end -start;
		}


	}
	SetCursorPos(poi.x, poi.y);
	return 1;
}

int DelayPress(long double time)
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<long double> num;
	start = std::chrono::system_clock::now();
	end = std::chrono::system_clock::now();
	num = end - start;
	while (num.count() <= time)
	{
		if (GetAsyncKeyState(VK_F2))
			return 0;
		end = std::chrono::system_clock::now();
		num = end - start;
	}
	return 1;
}

int PressDown(record::node* node)
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<long double> num;
	INPUT in;
	
	POINT mouse;
	int check = 1;
	
	 
		if (node->key < 10)
		{
			check = MoveMouse(node->pos, 100, node->time);
			if (check == -1)
				return -1;
			in.type = INPUT_MOUSE;
			GetCursorPos(&mouse);
			in.mi.dx = mouse.x;
			in.mi.dy = mouse.y;
			in.mi.mouseData = 0;
			in.mi.time = 0;
			in.mi.dwExtraInfo = 0;
			in.mi.dwExtraInfo = 0;
			if (node->key == 1)
			{
				in.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
			}

			else
				if (node->key == 2)
					in.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
				else
					if (node->key == 3)
						in.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;

			//do something with this delta time , needs to be returned !!!!!!!!!!!!!!!!
			
			SendInput(1, &in, sizeof(in));
			start = std::chrono::system_clock::now();
			end = std::chrono::system_clock::now();
			num = end - start;
		}
		else
		{

			if (!DelayPress(node->time))
				return -1;
			in.type = INPUT_KEYBOARD;
			in.ki.wScan = node->key;
			in.ki.time = 0;
			in.ki.dwFlags = KEYEVENTF_SCANCODE;
			//save this delta boi!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			start = std::chrono::system_clock::now();
			end = std::chrono::system_clock::now();
			num = end - start;
			SendInput(1, &in, sizeof(in));
		
		}
		
			
		
	

	
}
//int PressUp(record::node* node)
//{
//	while (num.count() < rec.getvector()[i].rep)
//	{
//
//		end = std::chrono::system_clock::now();
//		num = end - start;
//		if (GetAsyncKeyState(VK_F2))
//		{
//			check = -1;
//			break;
//		}
//		if (GetAsyncKeyState(VK_F3))
//			while (1)			// this whiles is meant to function as a pause when f3 is pressed
//			{
//				if (GetAsyncKeyState(VK_F1))		//resumes on f1
//					break;
//				if (GetAsyncKeyState(VK_F2))
//				{
//					check = -1;
//					break;
//				}
//			}
//		if (check == -1)
//			break;
//
//	}
//	SendInput(1, &in[1], sizeof(in[1]));
//	if (check == -1)
//		break;
//}