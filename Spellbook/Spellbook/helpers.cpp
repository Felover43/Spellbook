#include <string>
#include "helpers.h"
#include <chrono>
#include <Windows.h>
#include <fstream>
#include <algorithm> 
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
	return check;
}
void SetColorPurp(HDC h)
{
	SetTextColor(h, RGB(255, 255, 255));
	SetBkColor(h, RGB(0, 0, 0));
}

vector<int> whichkey()
{
	vector<int> nums;

	for (int i = 0; i < 256; i++) {
		if (GetAsyncKeyState(i) & 0x8000) {
			nums.push_back(i);
		}
	}

	return nums;
}

double dran(double max, double min)
{
	return (max - min) * ((double)rand() / (double)RAND_MAX) + min;
}
long double DelayMove(long double time)
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	std::chrono::duration<long double> num;
	long double randtime = dran(1.5, 0.7);
	start = std::chrono::system_clock::now();
	end = std::chrono::system_clock::now();
	num = end - start;
	while (num.count() <= time - randtime)
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
		currx = mouse.x + (long)((poi.x - mouse.x) * i / step);
		curry = mouse.y + (long)((poi.y - mouse.y) * i / step);
		SetCursorPos((int)currx, (int)curry);
		start = std::chrono::system_clock::now();
		end = std::chrono::system_clock::now();
		num = end - start;
		while (num.count() <= time / step)			//delays the movement speed so it looks natural
		{
			if (GetAsyncKeyState(VK_F2))
				return -1;
			end = std::chrono::system_clock::now();
			num = end - start;
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


//Presses the key down with input function and Simulates mouse movement
int PressDown(record::node* node)
{

	INPUT in;

	POINT mouse;
	int check = 1;


	if (node->key < 10)
	{
		//to simulate mouse movement
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


		SendInput(1, &in, sizeof(in));
	}
	else
	{
		in.type = INPUT_KEYBOARD;
		in.ki.wScan = node->key;
		in.ki.time = 0;
		in.ki.dwFlags = KEYEVENTF_SCANCODE;
		SendInput(1, &in, sizeof(INPUT));

	}

	return 1;

}
//Presses the key up with input function and Simulates mouse movement
int PressUp(record::node* node)
{

	INPUT in;

	POINT mouse;
	int check = 1;


	if (node->key < 10)
	{
		//simulates mouse movement
		check = MoveMouse(node->pos2, 100, node->time);
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
			in.mi.dwFlags = MOUSEEVENTF_LEFTUP;
		}

		else
			if (node->key == 2)
				in.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
			else
				if (node->key == 3)
					in.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;


		SendInput(1, &in, sizeof(in));
		/*start = std::chrono::system_clock::now();
		end = std::chrono::system_clock::now();
		num = end - start;*/
	}
	else
	{

		/*if (!DelayPress(node->time))
			return -1;*/
		in.type = INPUT_KEYBOARD;
		in.ki.wScan = node->key;
		in.ki.time = 0;
		in.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &in, sizeof(in));

	}

	return 1;

}
//checks which key was pressed and records data based on it like mouse pos
void check_key(int key, record& rec, int& check, std::chrono::time_point<std::chrono::system_clock> ntime, std::chrono::duration<long double> start, int i, std::vector<POINT> mice, bool& first)
{

	std::chrono::duration<long double> rep;
	if (key == VK_F2)
		check = 0;
	while (GetAsyncKeyState(key) && check == 1)
	{
	}
	std::chrono::time_point<std::chrono::system_clock> etime = std::chrono::system_clock::now();
	if (check) {
		rep = etime - ntime;
		if (i == 0)
		{
			rec.setvector((long double)start.count(), mice[0], mice[1], key, (long double)rep.count());
			first = false;
		}
		else
		{
			while (first)
			{
			}
			rec.setvector((long double)0, mice[0], mice[1], key, (long double)((rep).count()));
		}
	}

}

//int key_press(record::node* node) {
//
//	std::chrono::time_point<std::chrono::system_clock> now, ends, endr;
//	std::chrono::duration<long double> num;
//	Sleep(1);
//	PressDown(node);
//	now = std::chrono::system_clock::now();
//	ends = std::chrono::system_clock::now();
//	num = (ends - now);
//	while (num.count() < node->rep)								//wait till entry
//	{	
//		if (GetAsyncKeyState(VK_F2))
//			break;
//		ends = std::chrono::system_clock::now();
//		num = (ends - now);
//	}
//	Sleep(1);
//	PressUp(node);
//	return 1;
//}

int key_press(record::node* node) {

	std::chrono::time_point<std::chrono::system_clock> now, ends, endr;
	std::chrono::duration<long double> num;
	int check = 1;
	Sleep(1);
	check = PressDown(node);
	if (check != 1)
		return check;
	Sleep(1);
	check = PressUp(node);
	if (check != 1)
		return check;
	return 1;
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