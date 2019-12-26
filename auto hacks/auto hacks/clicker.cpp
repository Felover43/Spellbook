#include <windows.h>
#include <iostream>
#include <WinUser.h>
#include "clicker.h"
#include <chrono>
#include <stdlib.h>
#include "helpers.h"
#include <time.h>

using namespace std;

void startclicker(double sleep, bool isran)
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	POINT mouse;
	double mx, my;
	double ran=0;
	int check = 0;
	std::chrono::duration<long double> num;
	while (true)
	{

		if (isran)
		{
			ran = dran(1.6,0);
		}
		start = std::chrono::system_clock::now();

			while (1)
			{
				
				if (GetAsyncKeyState(VK_F2))
				{
					check = 1;
					break;
				}
				end = std::chrono::system_clock::now();
				num = end - start;
				if ((num.count()) >= sleep+ran)
				{
					break;
				}
			}
			if (check == 1)
				break;
		
		if (!isran) {
			GetCursorPos(&mouse);
			mouse_event(MOUSEEVENTF_LEFTDOWN, mouse.x, mouse.y, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, mouse.x, mouse.y, 0, 0);
		}
		if (isran)
		{	
				mx = dran(3, -3);
				my = dran(3, -3);
			mouse_event(MOUSEEVENTF_MOVE, (int)mx, (int)my, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0,0, 0, 0);
			mouse_event(MOUSEEVENTF_MOVE, (int)-mx, (int)-my ,0, 0);

		}
	}
}
