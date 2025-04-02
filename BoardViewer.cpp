#include "BoardViewer.h"
#include <iostream>
#include <windows.h>

BoardViewer::BoardViewer()
{
}

BoardViewer::~BoardViewer()
{
}


void BoardViewer::Render(Drawing* drawing)
{
	COORD pos = { (SHORT)0, (SHORT)0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

	auto rowList = drawing->GetRowList();
	auto colList = drawing->GetColList();
	int maxRowCount = 0;
	int maxColCount = 0;

	// rowList ��� �߿� ���� ���� �� ���ϱ�
	for (auto row : rowList)
	{
		if (row.size() > maxRowCount)
			maxRowCount = row.size();
	}

	// colList ��� �߿� ���� ���� �� ���ϱ�
	for (auto col : colList)
	{
		if (col.size() > maxColCount)
			maxColCount = col.size();
	}

	// colList ���
	for (int i = 0; i < maxColCount; i++)
	{
		for (int j = 0; j < maxRowCount; j++)
		{
			// ������ ���������� �ؼ� �ܼ�â�� ��������
			// "��"�� ũ��� "  "(���� 2ĭ)�� �����Ƿ�, 2�ڸ��������� ���� ���� ����
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
			cout << "��";
		}

		for (int j = 0; j < drawing->GetColCount(); j++)
		{
			// �ش� ���ڿ� ���ڰ� ���� ��� ����(������) ���
			if (colList[j].size() < maxColCount - i)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
				cout << "��";
			}
			// �ش� ���ڿ� ���ڰ� ���� ��� ����(ȸ��) ���
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
				if(colList[j][colList[j].size() - maxColCount + i] >= 10)
					cout << colList[j][colList[j].size() - maxColCount + i];
				else
					cout << colList[j][colList[j].size() - maxColCount + i] << " ";
			}
		}

		cout << "\n";
	}

	for (int i = 0; i < drawing->GetRowCount(); i++)
	{
		// rowList ���
		for (int j = 0; j < maxRowCount; j++)
		{
			// �ش� ���ڿ� ���ڰ� ���� ��� ����(������) ���
			if (rowList[i].size() < maxRowCount - j)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
				cout << "��";
			}
			// �ش� ���ڿ� ���ڰ� ���� ��� ����(ȸ��) ���
			else
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
				if(rowList[i][rowList[i].size() - maxRowCount + j] >= 10)
					cout << rowList[i][rowList[i].size() - maxRowCount + j];
				else
					cout << " " << rowList[i][rowList[i].size() - maxRowCount + j];
			}
		}

		// �׸� ������ ���
		for (int j = 0; j < drawing->GetColCount(); j++)
		{
			switch (drawing->GetValue(i, j))
			{
			case 0:
				if(drawing->GetCurX() == j  && drawing->GetCurY() == i)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); // ���� Ŀ���� ��� �����
				else
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // �� ĭ : �Ͼ��
				cout << "��";
				break;
			case 1:
				if (drawing->GetCurX() == j && drawing->GetCurY() == i)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); // ���� Ŀ���� ��� �����
				else
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // ��ĥ : �ʷϻ�
				cout << "��";
				break;
			case 2:
				
				if (drawing->GetCurX() == j && drawing->GetCurY() == i)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6); // ���� Ŀ���� ��� �����
				else
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // X : ������
				cout << "��";
				break;
			default:
				break;
			}
		}

		cout << "\n";
	}

	cout << "\n";

	// ��� ��� ��� ��, �ٽ� ������� �� ����
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}
