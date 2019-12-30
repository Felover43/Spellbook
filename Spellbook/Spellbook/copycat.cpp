
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
using namespace std;


//Save the cat : takes copy vector and turns into text file
//
//
//
void SaveTheCat(record& rec,string save)
{
	std::ofstream file;
	file.open(ExePath() + "\\savefiles\\" + save.c_str() + ".txt", std::ofstream::out | std::ofstream::trunc);
	if (file.is_open())
	{
			for (unsigned int i = 0; i < rec.getvector().size(); i++) {
				file << rec.getvector()[i].key<<"\n";
				file << rec.getvector()[i].pos.x<<"\n";
				file << rec.getvector()[i].pos.y << "\n";
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
	int i=0;
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
						rec.setvecrep(stold(line));
						i++;
						break;
					}
					case 4:
					{
						rec.setvectime(stold(line));
						i++;
						break;
					}
					case 5:
					{
						if(line == "" )
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

void copycatrecord(record& rec)
{
	std::chrono::time_point<std::chrono::system_clock> otime ,ntime ,etime ;
	vector<int> nums;
	int emp = 0;
	vector<std::chrono::time_point<std::chrono::system_clock>*> times; //otime, ntime , rep, repe 
	POINT mouse1, mouse2;														
	int* keys;															//changed to pointer to use as array
	int check = 1;
	int i=0;
	int j=0;
	std::chrono::duration<long double> rep;
	std::chrono::duration<long double> num;
	
	
	while (GetAsyncKeyState(VK_F1))				//make sure f1 doesnt go into the vector, so we delay the repeat
	{
		
	}
	while (check)													//loops till f2
	{
		
		otime = std::chrono::system_clock::now();					//start
		
		keys = whichkey();															//the main function!!!!
		emp = 0;
		j = 0;
			

		for (i = 0; i < sizeof(keys); i++)
		{
			if (nums.empty())											
			{
				if (keys[0] != VK_F2)
				{
					check = 0;
					break;
				}

				nums.push_back(keys[0]);
				times.push_back(&otime);
				ntime = std::chrono::system_clock::now();
				times[0][1] = ntime;									//end = s-rep they are the same in the end...(this is both end and rep)
				emp++;
				j++;
				i++;
				if (sizeof(keys) == i)
					break;
			}
			if (keys[i] == VK_F2)
			{
				check = 0;
				j = 0;
				break;
			}
				if (keys[i] <= nums[j])
				{
					if (!(keys[i] == nums[j]))
					{
						nums.insert(nums.begin() + j, keys[i]);
						if (check)				//add else 
						{
							times.insert(times.begin() + j, &ntime);		//0 time
							times[j+1][1] = ntime;
						}

						else								//if nums is empty
						{
							times.insert(times.begin() + j, &otime);
							times[0][1] = ntime;
						}
						j++;
					}
					else								//the nums[j] == key[i] we push them both forward(no need to pop)
						j++;
				}
				else                               //if key[i] > nums[j] it goes in to the end 
				{
					if (nums.size()==j)
					{
						for (i = i; i < sizeof(keys); i++)
						{
							if (keys[i] == VK_F2)
							{
								check = 0;
								j = 0;
								break;
							}
							nums.push_back(keys[i]);
							j++;
							if (emp)
							{
								times.push_back(&ntime);		// 0 time
								times[j + 1][1] = ntime;		//ntime - ntime
							}

							else								//if nums is empty
							{
								times.push_back(&otime);
								times[0][1] = ntime;
								emp++;
							}
						}
						break;
					}
					else
					{
						GetCursorPos(&mouse2);
						num = times[j][1] - times[j][0];
						rep = std::chrono::system_clock::now() - times[j][1];
						rec.setvector(num.count(), mouse1, nums[j], rep.count());
						nums.erase(nums.begin() + j);
						times.erase(times.begin() + j);
						nums.insert(nums.begin() + j, keys[i]);
						if (emp)
						{
							times.push_back(&ntime);		//0 time 
							times[j+1][1] = ntime;
						}

						else								//if nums is empty
						{
							emp++;
							times.push_back(&otime);
							times[0][1] = ntime;
						}
						j++;
						break;



					}
				}
				
			
			
		}
		while (j < nums.size())							//assume you start on num[j]that needs erase
		{
			GetCursorPos(&mouse2);
			num = times[j][1] - times[j][0];
			rep = std::chrono::system_clock::now() - times[j][1];
			rec.setvector(num.count(), mouse1, nums[j], rep.count());
			nums.erase(nums.begin() + j);
			times.erase(times.begin() + j);
		}


	}
	
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

void copycatexecute(record& rec)
{
	vector<record::node*> pressed;
	std::vector<std::chrono::time_point<std::chrono::system_clock>> times;						//here we put now + rep for each value and wait till now reaches  that time.
	record::node* poi;
	std::chrono::time_point<std::chrono::system_clock> now;
	int check = 1;
	int i=0;
	while (check != -1)
	{
		now = std::chrono::system_clock::now();
		/*wait = now +vec
		while(now+time)		*/								//here goes now+start time.
			poi = &(rec.getvector()[i]);
			PressDown(poi);
			pressed.push_back(poi);

			
		

			if (rec.getvector().size() <= i)
				if (check == 2)
					break;
				else
					i = 0;
		
	}
}