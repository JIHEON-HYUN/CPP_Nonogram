#include "Drawing.h"

Drawing::Drawing(vector<vector<int>> inputDrawing)
{
	curX = 0;
	curY = 0;
	this->drawing = inputDrawing;

	rowList.resize(drawing.size());
	colList.resize(drawing[0].size());
	int count; // 연속해서 색칠해지는 숫자 값 저장하는 변수
	
	// drawing의 각 row별 연속해서 색칠해지는 숫자 값들 저장
	for (int i = 0; i < rowList.size(); i++)
	{
		count = 0;

		for (int j = 0; j < drawing[0].size(); j++)
		{
			if (drawing[i][j] == 1)
				count++;
			else
			{
				if (count != 0)
				{
					rowList[i].push_back(count);
					count = 0;
				}
			}
		}

		if (count != 0)
			rowList[i].push_back(count);

		if (rowList[i].empty())
			rowList[i].push_back(0);
	}

	// drawing의 각 col별 연속해서 색칠해지는 숫자 값들 저장
	for (int i = 0; i < colList.size(); i++)
	{
		count = 0;

		for (int j = 0; j < drawing.size(); j++)
		{
			if (drawing[j][i] == 1)
				count++;
			else
			{
				if (count != 0)
				{
					colList[i].push_back(count);
					count = 0;
				}
			}
		}

		if (count != 0)
			colList[i].push_back(count);

		if (colList[i].empty())
			colList[i].push_back(0);
	}
}

Drawing::Drawing(int width, int height)
{
	curX = 0;
	curY = 0;

	drawing.resize(width, vector<int>(height));

	// drawing의 모든 요소에 0(빈 칸) or 1(초록색) 값 랜덤 삽입
	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			drawing[i][j] = rand() % 2;
		}
	}

	rowList.resize(drawing.size());
	colList.resize(drawing[0].size());
	int count; // 연속해서 색칠해지는 숫자 값 저장하는 변수

	// drawing의 각 row별 연속해서 색칠해지는 숫자 값들 저장
	for (int i = 0; i < rowList.size(); i++)
	{
		count = 0;

		for (int j = 0; j < drawing[0].size(); j++)
		{
			if (drawing[i][j] == 1)
				count++;
			else
			{
				if (count != 0)
				{
					rowList[i].push_back(count);
					count = 0;
				}
			}
		}

		if (count != 0)
			rowList[i].push_back(count);

		if (rowList[i].empty())
			rowList[i].push_back(0);
	}

	// drawing의 각 col별 연속해서 색칠해지는 숫자 값들 저장
	for (int i = 0; i < colList.size(); i++)
	{
		count = 0;

		for (int j = 0; j < drawing.size(); j++)
		{
			if (drawing[j][i] == 1)
				count++;
			else
			{
				if (count != 0)
				{
					colList[i].push_back(count);
					count = 0;
				}
			}
		}

		if (count != 0)
			colList[i].push_back(count);

		if (colList[i].empty())
			colList[i].push_back(0);
	}
}

Drawing::Drawing(const Drawing& drawing)
{
	this->drawing = drawing.drawing;
	this->rowList = drawing.rowList;
	this->colList = drawing.colList;
	this->curX = drawing.curX;
	this->curY = drawing.curY;
}

Drawing::~Drawing()
{
}

vector<vector<int>> Drawing::GetRowList()
{
	return rowList;
}

vector<vector<int>> Drawing::GetColList()
{
	return colList;
}

int Drawing::GetRowCount()
{
	return rowList.size();
}

int Drawing::GetColCount()
{
	return colList.size();
}

int Drawing::GetCurX()
{
	return curX;
}

int Drawing::GetCurY()
{
	return curY;
}

void Drawing::SetCurX(int newCurX)
{
	curX = newCurX;
}

void Drawing::SetCurY(int newCurY)
{
	curY = newCurY;
}

int Drawing::GetValue(int index1, int index2)
{
	return drawing[index1][index2];
}

int Drawing::GetValueSum()
{
	int sum = 0;

	for (int i = 0; i < rowList.size(); i++)
	{
		for (int j = 0; j < rowList[i].size(); j++)
		{
			sum += rowList[i][j];
		}
	}

	return sum;
}

void Drawing::SetValue(int index1, int index2, int value)
{
	drawing[index1][index2] = value;
}
