#pragma once
#include <vector>
#include "PlayScene.h"

using namespace std;

class Drawing
{
private:
	// �� �׸� ��ü�� ��ĥ �迭�� ����� 2��������
	// drawing[��][��], �� ĭ�̸� ���� 0, ��ĥ(�ʷ�)������ ���� 1, X(����)ǥ�ô� 2
	vector<vector<int>> drawing; 

	// �� �ึ�� ���ӵ� ��ĥ(�ʷ�)ĭ�� ����� ����� 2���� ����
	vector<vector<int>> rowList; 

	// �� ������ ���ӵ� ��ĥ(�ʷ�)ĭ�� ����� ����� 2���� ����
	vector<vector<int>> colList; 

	int curX; // ���� Ŀ�� ��ġ ����� ���� X��ǥ ����
	int curY; // ���� Ŀ�� ��ġ ����� ���� Y��ǥ ����

public:
	// �Է¹��� �׸����� Drawing ��ü ����
	Drawing(vector<vector<int>> inputDrawing); 

	// �Է¹��� ����, ���� ���̷� ������ ��ġ�� Drawing ��ü ����
	Drawing(int width, int height); 

	// ��������� => PlayScene�� playerDrawing�� �����ϴ� �� ���
	// PlayScene���� ���� ������ ��, ���� Drawing�� ���������ʹ� �����ϸ� �ȵǹǷ�, ���� ����� ����
	Drawing(const Drawing& drawing); 

	~Drawing();

	vector<vector<int>> GetRowList();
	vector<vector<int>> GetColList();
	void SetRowList(vector<vector<int>> newRowList);
	void SetColList(vector<vector<int>> newColList);

	int GetRowCount();
	int GetColCount();

	int GetCurX();
	int GetCurY();
	void SetCurX(int newCurX);
	void SetCurY(int newCurY);

	int GetValue(int index1, int index2); // drawing[index1][index2]�� ����� value return
	int GetValueSum();
	void SetValue(int index1, int index2, int value); // drawing[index1][index2]�� ���� value������ ����
};

