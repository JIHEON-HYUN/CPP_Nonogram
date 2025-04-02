#include <iostream>
#include <cstdlib>
#include <ctime>
#include "GameManager.h"

using namespace std;

int main()
{
	srand(time(NULL));
	GameManager gm;
	gm.ShowMenu();

	return 0;
}