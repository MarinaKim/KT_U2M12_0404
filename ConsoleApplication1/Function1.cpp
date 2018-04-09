
#include<stdint.h>
#include <iostream>
#include<stdlib.h>
#include <time.h>
#include<string.h>
#include"Header.h"

using namespace std;

void generateDate(date *t)
{
	t->day = 1 + rand() % 30;
	t->month = 1 + rand() % 11;
	t->year = 1960 + rand() % 50;
}