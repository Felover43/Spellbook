#pragma once
#ifndef _HELPERS_
#include <Windows.h>
#include <string>
#include "record.h"
#include <vector>

using namespace std;
double dran(double, double);
long double DelayMove(long double);
std::string ExePath();
bool is_digits(const char*);
void SetColorPurp(HDC);
int* whichkey();
int MoveMouse(POINT,int,long double);
int DelayPress(long double);
int PressDown(record::node*);
int PressUp(record::node*);
#endif //  !HELPERS