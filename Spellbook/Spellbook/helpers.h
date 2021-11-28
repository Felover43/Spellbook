#pragma once
#ifndef _HELPERS_
#include <Windows.h>
#include <string>
#include "record.h"
#include <vector>
#include <chrono>
using namespace std;
double dran(double, double);
long double DelayMove(long double);
std::string ExePath();
bool is_digits(const char*);
void SetColorPurp(HDC);
vector<int> whichkey();
void check_key(int, record&,int&, std::chrono::time_point<std::chrono::system_clock>, std::chrono::duration<long double>,int, std::vector<POINT>,bool&);
int key_press(record::node*);
int MoveMouse(POINT,int,long double);
int DelayPress(long double);
int PressDown(record::node*);
int PressUp(record::node*);
#endif //  !HELPERS