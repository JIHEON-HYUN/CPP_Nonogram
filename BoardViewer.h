#pragma once
#include "Drawing.h"

using namespace std;

class BoardViewer
{
public:
	BoardViewer();
	~BoardViewer();

	void Render(Drawing* drawing); // 그림 출력
};

