
#include "copycat.h"
#include "record.h"
#include <chrono>
#include <Windows.h>
#include "helpers.h"
#include <iostream>
#include <winuser.h>
#include <fstream>
#include <sstream>
#include <string>
#include <thread> 
#include <algorithm>
using namespace std;


//Save the cat : takes copy vector and turns into text file
//
//
//
void SaveTheCat(record& rec, string save)
{
	std::ofstream file;
	file.open(ExePath() + "\\savefiles\\" + save.c_str() + ".txt", std::ofstream::out | std::ofstream::trunc);
	if (file.is_open())
	{
		for (unsigned int i = 0; i < rec.getvector().size(); i++) {
			file << rec.getvector()[i].key << "\n";
			file << rec.getvector()[i].pos.x << "\n";
			file << rec.getvector()[i].pos.y << "\n";
			file << rec.getvector()[i].pos2.x << "\n";
			file << rec.getvector()[i].pos2.y << "\n";
			file << rec.getvector()[i].rep << "\n";
			file << rec.getvector()[i].time << "\n";
			file << "\n";
		}
		file.close();
	}
	else
		Beep(440, 500);
}
// upload the cat : turns text file into copy vector
//
//
//
// 
void UploadTheCat(record& rec, string save)
{

	std::ifstream file;
	file.open(ExePath() + "\\savefiles\\" + save.c_str() + ".txt");
	int i = 0;
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			if (file.eof())
				if (i == 5 || i == 0)
					break;
				else
					rec.getvector().clear();
			else
				switch (i)

				{
				case 0:
				{
					rec.setEvec();
					rec.setveckey(stoi(line));
					i++;
					break;
				}
				case 1:
				{
					rec.setvecposx(stoi(line));
					i++;
					break;
				}
				case 2:
				{
					rec.setvecposy(stoi(line));
					i++;
					break;
				}
				case 3:
				{
					rec.setvecpos2x(stoi(line));
					i++;
					break;
				}
				case 4:
				{
					rec.setvecpos2y(stoi(line));
					i++;
					break;
				}
				case 5:
				{
					rec.setvecrep(stold(line));
					i++;
					break;
				}
				case 6:
				{
					rec.setvectime(stold(line));
					i++;
					break;
				}
				case 7:
				{
					if (line == "")
						i = 0;
					else
					{
						rec.getvector().clear();
						i = -1;
					}
					break;
				}
				default:
					break;


				}

		}
		file.close();

	}
	else
		Beep(440, 500);



}

//void copycatrecord(record& rec)
//{
//	std::chrono::time_point<std::chrono::system_clock> otime ,ntime ,ctime ;
//	vector<std::chrono::time_point<std::chrono::system_clock>> time;				//!!!search for all places with otime and change.!!!!
//	vector<int> nums;
//	int emp = 0;
//	vector<vector<std::chrono::time_point<std::chrono::system_clock>>> times;				//otime, ntime , rep, repe 
//	std::vector<POINT> mice;
//	POINT mouse;														
//	vector<int> keys;																			//changed to pointer to use as array
//	int check = 1;
//	int i=0;
//	int j=0;
//	std::chrono::duration<long double> rep;
//	std::chrono::duration<long double> num;
//	
//	
//	while (GetAsyncKeyState(VK_F1))														//make sure f1 doesnt go into the vector, so we delay the repeat
//	{
//		
//	}
//	otime = std::chrono::system_clock::now();
//	time.push_back(otime);
//	time.push_back(otime);
//	while (check)																		//loops till f2
//	{
//		
//		keys = whichkey();																//the main function!!!!
//		emp = 0;
//		j = 0;
//			
//
//		for (i = 0; i < keys.size(); i++)
//		{
//			if (nums.empty())											
//			{
//				if (keys[0] == VK_F2)
//				{
//					check = 0;
//					break;
//				}
//				ntime = std::chrono::system_clock::now();
//				time[0]=otime;
//				otime = std::chrono::system_clock::now();
//				time[1]=ntime;
//				times.push_back(time);
//				nums.push_back(keys[0]);
//				GetCursorPos(&mouse);
//				mice.push_back(mouse);
//				
//															//end = s-rep they are the same in the end...(this is both end and rep)
//				emp++;
//				j++;
//				i++;
//				if (keys.size() == i)
//					break;
//			}
//			if (keys[i] == VK_F2)
//			{
//				check = 0;
//				j = 0;
//				break;
//			}
//				if (keys[i] <= nums[j])
//				{
//					if (!(keys[i] == nums[j]))
//					{
//						nums.insert(nums.begin() + j, keys[i]);
//						GetCursorPos(&mouse);
//						mice.insert(mice.begin() + j,mouse);
//						if (emp)				//add else				
//						{
//							time[0] = ntime;
//							times.insert(times.begin() + j, time);		// time[0] = ntime ,time[1]=ntime; time[0]-time[1]=0
//						}
//
//						else								//if nums is empty
//						{
//
//							emp++;
//							time[0] = otime;
//							otime = std::chrono::system_clock::now();
//							ntime = std::chrono::system_clock::now();			//possible ntime here for instance A held but then hit B aswell.
//							time[1] = ntime;
//							times.insert(times.begin() + j, time);
//							
//						}
//						j++;
//					}
//					else								//the nums[j] == key[i] we push them both forward(no need to pop)
//						j++;
//				}
//				else                               //if key[i] > nums[j] it goes in to the end 
//				{
//					if (nums.size()==j)
//					{
//						for (i = i; i < keys.size(); i++)
//						{
//							if (keys[i] == VK_F2)
//							{
//								check = 0;
//								j = 0;
//								break;
//							}
//							nums.push_back(keys[i]);
//							GetCursorPos(&mouse);
//							mice.push_back(mouse);											//check this area something wrong with the j from this point !!!!!
//							j++;
//							if (emp)
//							{
//								time[0] = ntime;
//								times.push_back(time);									// 0 time
//								times[j + 1][1] = ntime;									//ntime - ntime
//							}
//
//							else																//if nums is empty
//							{
//								time[0] = otime;
//								otime = std::chrono::system_clock::now();
//								times.push_back(time);
//								ntime = std::chrono::system_clock::now();
//								times[0][1] = ntime;
//								emp++;
//							}
//						}
//						break;
//					}
//					else
//					{
//						GetCursorPos(&mouse);
//						num = times[j][1] - times[j][0];
//						rep = std::chrono::system_clock::now() - times[j][1];
//						rec.setvector(num.count(), mice[j],mouse, nums[j], rep.count());
//						nums.erase(nums.begin() + j);
//						times.erase(times.begin() + j);
//						mice.erase(mice.begin() + j);
//
//						nums.insert(nums.begin() + j, keys[i]);
//						GetCursorPos(&mouse);
//						mice.push_back(mouse);
//						if (emp)
//						{
//							time[0] = ntime;
//							times.push_back(time);		//0 time 
//							times[j+1][1] = ntime;
//						}
//
//						else								//if nums is empty
//						{
//							time[0] = otime;
//							otime = std::chrono::system_clock::now();
//							emp++;
//							times.push_back(time);
//							ntime = std::chrono::system_clock::now();
//							times[0][1] = ntime;
//						}
//						j++;
//						break;
//
//
//
//					}
//				}
//				
//			
//			
//		}
//		while (j < nums.size())							//assume you start on num[j]that needs erase
//		{
//			GetCursorPos(&mouse);
//			num = times[j][1] - times[j][0];
//			rep = std::chrono::system_clock::now() - times[j][1];
//			rec.setvector(num.count(), mice[j],mouse, nums[j], rep.count());
//			nums.erase(nums.begin() + j);
//			times.erase(times.begin() + j);
//			mice.erase(mice.begin() + j);
//		}
//
//
//	}
//	
//}



void copycatrecord(record& rec)
{
	std::chrono::time_point<std::chrono::system_clock> otime, ntime;
	vector<int> nums;
	vector<int> diff;
	std::vector<POINT> mice;
	POINT mouse;
	vector< std::thread> threads;
	vector<int> keys;
	int check = 1;
	int i = 0;
	GetCursorPos(&mouse);
	mice.push_back(mouse);
	mice.push_back(mouse);
	bool first = false;

	while (GetAsyncKeyState(VK_F1))														//make sure f1 doesnt go into the vector, so we delay the repeat
	{
	}

	otime = std::chrono::system_clock::now();
	ntime = std::chrono::system_clock::now();

	while (check)																		//loops till f2
	{
		//checks which key is being pressed.
		diff.clear();
		keys = whichkey();
		std::set_difference(keys.begin(), keys.end(), nums.begin(), nums.end(),
			std::inserter(diff, diff.begin()));
		nums = keys;
		if (!diff.empty())
		{


			ntime = std::chrono::system_clock::now();
			mice[0] = mice[1];
			GetCursorPos(&mouse);
			mice[1] = mouse;
		}
		for (i = 0; i < diff.size(); i++)
		{	//waits till keys are not pressed , we send i to know if its the first or not for later time calc
			first = true;
			if (i < 4)
				threads.emplace_back(std::thread(check_key, diff[i], std::ref(rec), std::ref(check), ntime, (ntime - otime), i, mice, std::ref(first)));
		}
	}
	for (auto& th : threads)
		th.join();

	rec.sortcat();
}



//void copycatexecute(record& rec)
//{
//	std::chrono::time_point<std::chrono::system_clock> start, end;
//	std::chrono::duration<long double> num;
//	INPUT in[2];
//	POINT mouse;
//	int check = 1;
//	
//	//make sure to make a f2 exit all over the place.
//	while (check != -1)
//	{
//		for (unsigned int i = 0; i < rec.getvector().size(); i++) {
//			if (rec.getvector()[i].key < 10)
//			{
//				check = MoveMouse(rec.getvector()[i].pos, 100, rec.getvector()[i].time);
//				if (check == -1)
//					break;
//				in[0].type = INPUT_MOUSE;
//				in[1].type = INPUT_MOUSE;
//				GetCursorPos(&mouse);
//				in[0].mi.dx = mouse.x;
//				in[1].mi.dx = mouse.x;
//				in[0].mi.dy = mouse.y;
//				in[1].mi.dy = mouse.y;
//				in[0].mi.mouseData = 0;
//				in[1].mi.mouseData = 0;
//				in[0].mi.time = 0;
//				in[1].mi.time = 0;
//				in[0].mi.dwExtraInfo = 0;
//				in[1].mi.dwExtraInfo = 0;
//				if (rec.getvector()[i].key == 1)
//				{
//					in[0].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
//					in[1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
//				}
//					
//				else
//					if (rec.getvector()[i].key == 2)
//					{
//						in[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
//						in[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;
//					}
//					else
//						if (rec.getvector()[i].key == 3)
//						{
//							in[0].mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
//							in[1].mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
//						}
//				
//				start = std::chrono::system_clock::now();
//				end = std::chrono::system_clock::now();
//				num = end - start;
//				SendInput(1, &in[0], sizeof(in[0]));
//				while (num.count() < rec.getvector()[i].rep)
//				{
//					
//					end = std::chrono::system_clock::now();
//					num = end - start;
//					if (GetAsyncKeyState(VK_F2))
//					{
//						check = -1;
//						break;
//					}
//					if(GetAsyncKeyState(VK_F3))
//						while (1)			// this whiles is meant to function as a pause when f3 is pressed
//						{
//							if (GetAsyncKeyState(VK_F1))		//resumes on f1
//								break;
//							if (GetAsyncKeyState(VK_F2))
//							{
//								check = -1;
//								break;
//							}
//						}
//						if (check == -1)
//							break;
//					
//				}
//				SendInput(1, &in[1], sizeof(in[1]));
//				if (check == -1)
//					break;
//			}
//			else
//			{
//
//				if (!DelayPress(rec.getvector()[i].time))
//					break;
//				in[0].type = INPUT_KEYBOARD;
//				in[1].type = INPUT_KEYBOARD;
//				in[0].ki.wVk = rec.getvector()[i].key;
//				in[1].ki.wVk = rec.getvector()[i].key;								
//				in[0].ki.time = 0;
//				in[1].ki.time = 0;
//				in[0].ki.dwFlags = 0;
//				in[1].ki.dwFlags = KEYEVENTF_KEYUP;
//				start = std::chrono::system_clock::now();
//				end = std::chrono::system_clock::now();
//				num = end - start;
//				SendInput(1, &in[0], sizeof(in[0]));
//				while (num.count() < rec.getvector()[i].rep)
//				{
//					
//					SendInput(2, in, sizeof(in));
//					if (GetAsyncKeyState(VK_F2))
//					{
//						check = -1;
//						break;
//					}
//					if (GetAsyncKeyState(VK_F3))
//						while (1)			// this whiles is meant to function as a pause when f3 is pressed
//						{
//							if (GetAsyncKeyState(VK_F1))		//resumes on f1
//								break;
//							if (GetAsyncKeyState(VK_F2))
//							{
//								check = -1;
//								break;
//							}
//						}
//					if (check == -1)
//						break;
//					end = std::chrono::system_clock::now();
//					num = end - start;
//					
//				}
//				SendInput(1, &in[1], sizeof(in[1]));
//				
//				if (check == -1)
//					break;
//			}
//
//
//		}
//	}
//
//
//}

//void copycatexecute(record& rec)
//{
//	vector<record::node*> pressed;
//	record::node copy;
//	std::vector<std::chrono::time_point<std::chrono::system_clock>> times;						//here we put now + rep for each value and wait till now reaches  that time.
//	std::chrono::time_point<std::chrono::system_clock> now, ends, endr;
//	std::chrono::duration<long double> num;
//	int check = 1;
//	int i=0;
//	int j = 0;
//	while (check != -1)
//	{
//		if (rec.getvector().size() <= i)
//		{
//			if (check == 2)
//				break;
//			else
//				i = 0;
//		}
//		now = std::chrono::system_clock::now();
//		ends = std::chrono::system_clock::now();
//		num = (ends - now);
//		while (num.count() < rec.getvector()[i].time)								//wait till entry
//		{
//			if (GetAsyncKeyState(VK_F2))
//			{
//				check = -1;
//				break;
//			}
//			if (GetAsyncKeyState(VK_F3))
//				check = 2;
//
//			if (!times.empty())																		
//			{
//				endr = std::chrono::system_clock::now();
//				if (j >= times.size())
//					j = 0;
//				num = (endr - times[j]);
//				if (num.count() >= pressed[j]->rep)								//checks time for reps while we wait on next start
//				{
//					PressUp(pressed[j]);
//					pressed.erase(pressed.begin() + j);
//					times.erase(times.begin() + j);
//
//				}
//				else
//					j++;
//			}
//			ends = std::chrono::system_clock::now();
//			num = (ends - now);
//		}
//		while (check == 1)
//		{
//			if (GetAsyncKeyState(VK_F2))
//			{
//				check = -1;
//				break;
//			}
//			if (GetAsyncKeyState(VK_F3))
//				check = 2;
//
//			PressDown(&(rec.getvector()[i]));
//			copy.setnode(rec.getvector()[i].time, rec.getvector()[i].pos, rec.getvector()[i].pos2, rec.getvector()[i].key, rec.getvector()[i].rep);
//			pressed.push_back(&copy);
//			times.push_back(std::chrono::system_clock::now());
//			if ((1+i) < rec.getvector().size())
//			{
//				i++;
//				if (rec.getvector()[i].time != 0)
//					break;
//				
//			}
//			else
//			{
//				i = 0;
//				break;
//			}
//
//				
//			
//
//					
//		}
//
//	
//		
//	}
//	i = 0;
//	while (!times.empty())
//	{
//		
//		PressUp(pressed[i]);
//		pressed.erase(pressed.begin() + i);
//		times.erase(times.begin() + i);
//
//	}
//}



//this is obviously incorrect, i prob dont need multithreading for this step rather a sort function so things happen on time.
void copycatexecute(record& rec)
{
	record::node copy;
	std::vector<std::chrono::time_point<std::chrono::system_clock>> times;						//here we put now + rep for each value and wait till now reaches  that time.
	std::chrono::time_point<std::chrono::system_clock> now, ends, endr;
	std::chrono::duration<long double> num;
	int check = 1;
	int i = 0;
	int j = 0;
	now = std::chrono::system_clock::now();
	while (check != -1)
	{
		if (rec.getvector().size() <= i)
		{
			if (check == 2)
				break;
			else {
				now = std::chrono::system_clock::now();
				i = 0;
			}
		}

		ends = std::chrono::system_clock::now();
		num = (ends - now);
		while (num.count() < rec.getvector()[i].time)								//wait till entry
		{

			ends = std::chrono::system_clock::now();
			num = (ends - now);
			if (GetAsyncKeyState(VK_F2))
				check = -1;
		}
		if (check != -1)
		{
			copy = rec.getvector()[i];

			check = key_press(&copy);

		}

		i++;
		if (GetAsyncKeyState(VK_F2))
			check = -1;

	}

}