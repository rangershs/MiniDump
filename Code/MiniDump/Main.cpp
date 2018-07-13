#include "MiniDump.h"
#include <stdlib.h>
#include <ctime>
#include <string>
#include <random>

void main()
{
	MiniDump::EnableAutoDump(true);
	//	理论上必须dump
	/*const int iNum = 6;
	srand((unsigned)time(nullptr));
	int iRandom = rand() % iNum;*/

	//	运气好则不会dump
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, 6);
	int iRandom = dist(mt);

	switch (iRandom)
	{
	case 0:
		{
			int* p = nullptr;
			*p = 5;
		}
		break;
	case 1:
		{
			int j = 0;
			int i = 5 / j;
		}
		break;
	case 2:
		{
			int* p = nullptr;
			*p = 5;
		}
		break;
	case 3:
		{
			int* p = nullptr;
			*p = 5;
		}
		break;
	case 4:
		{
			int* p = nullptr;
			*p = 5;
		}
		break;
	case 5:
		{
			int* p = nullptr;
			*p = 5;
		}
		break;
	default:
		break;
	}
}