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

	drawing.resize(height, vector<int>(width));

	// drawing의 모든 요소에 0(빈 칸) or 1(초록색) 값 랜덤 삽입
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
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

Drawing::Drawing(const Drawing& otherDrawing)
{
	this->drawing = otherDrawing.drawing;
	this->rowList = otherDrawing.rowList;
	this->colList = otherDrawing.colList;
	this->curX = otherDrawing.curX;
	this->curY = otherDrawing.curY;
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

void Drawing::SetRowList(vector<vector<int>> newRowList)
{
	rowList = newRowList;
}

void Drawing::SetColList(vector<vector<int>> newColList)
{
	colList = newColList;
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

void Drawing::SetValue(int index1, int index2, int value)
{
	drawing[index1][index2] = value;
}

int Drawing::GetValue(int index1, int index2)
{
	return drawing[index1][index2];
}

int Drawing::GetRowSum(int index)
{
	int sum = 0;
	for (int j = 0; j < GetColCount(); j++)
	{
		if(drawing[index][j] == 1)
			sum += drawing[index][j];
	}

	return sum;
}

int Drawing::GetColSum(int index)
{
	int sum = 0;
	for (int j = 0; j < GetRowCount(); j++)
	{
		if(drawing[j][index] == 1)
			sum += drawing[j][index];
	}

	return sum;
}

int Drawing::GetAllSum()
{
	int sum = 0;
	for (int i = 0; i < GetRowCount(); i++)
	{
		sum += GetRowSum(i);
	}

	return sum;
}


