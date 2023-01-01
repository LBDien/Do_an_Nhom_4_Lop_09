#include<iostream>
#include<windows.h>
#include<math.h>
#include<cmath>
#include "graphics.h"
#include <dos.h>
#include <conio.h>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>

using namespace std;
int n;

struct NODE
{
	int SUC;
	NODE* NEXT;
	NODE()
	{
		SUC = 0;
		NEXT = NULL;
	}
};
struct Obj
{
	int Count;
	NODE* TOP;
};
struct ToaDo
{
	int x;
	int y;
};
ToaDo td[100];
Obj* Base = (struct Obj*)malloc(n * sizeof(struct Obj));
void Ve(int n)
{
	setcolor(3);
	double pi = atan(1) * 4;
	double alpha = 2 * pi / n;
	int x = 500;
	int y = 500;
	
	for (int i = 0; i < n; i++)
	{
		
		x = 500 + 300 * sin(i*alpha);
		y = 500 - 300 * cos(i*alpha);
		td[i+1].x = x;
		td[i+1].y = y;
		circle(x, y, 50);

		stringstream strs;
		strs << i+1;
		string temp_str = strs.str();
		char* char_type = (char*)temp_str.c_str();
		
		drawText(x-20, y-20, char_type);
		
	}
}
void VeNode(int i, int F)
{
	stringstream strs;
	strs << F;
	string temp_str = strs.str();
	char* char_type = (char*)temp_str.c_str();

	
	int x = 200 + i * 100;
	int y = 900;
	circle(x, y, 50);
	if (i != n-1)
	{
		line(x, y, x + 70, y);
	}
	drawText(x - 20, y - 20, char_type);
}
int m = 0;
int main()
{	
	initgraph();
	cout << "Nhap gia tri cua n: ";//So dinh cua do thi
	cin >> n;
	int N;
	int QLINK[100];
	int k;
	int j;
	
	N = n;
	for (int i = 1; i <= N; ++i)
	{
		Base[i].Count = 0;
		Base[i].TOP = NULL;
	}
	cout << "Nhap so luong cac moi quan he: ";//So canh cua do thi
	int z;
	cin >> z;
	
	
	NODE* P;
	Ve(n);
	for (int i = 1; i <= z; i++)
	{
		cin >> j >> k;             
		Base[k].Count++;
		P = (NODE*)malloc(sizeof(NODE));
		P = new NODE();
		P->SUC = k;
		P->NEXT = Base[j].TOP;
		Base[j].TOP = P;
		setcolor(3);
		line(td[j].x, td[j].y, td[k].x, td[k].y);
		
	}
	int R = 0;
	QLINK[0] = 0;
	for (int i = 1; i <= N; i++)
	{
		if (Base[i].Count == 0)
		{
			
			QLINK[R] = i;
			R = i;
		}
	}
	int F = QLINK[0];
	
	while(N != 0)
	{
		Sleep(1000);
		VeNode(m, F);
		m++;
		
		if (F != 0)
		{
			N = N - 1;
			P = Base[F].TOP;


			while (P != NULL)
			{
				Base[P->SUC].Count -= 1;
				if (Base[P->SUC].Count == 0)
				{
					QLINK[R] = P->SUC;
					R = P->SUC;
				}
				P = P->NEXT;
			}
			F = QLINK[F];
		}
	}
	
	return 0;
}