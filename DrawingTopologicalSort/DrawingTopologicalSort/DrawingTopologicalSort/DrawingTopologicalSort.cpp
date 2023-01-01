#include <iostream>
#include "graphics.h"
#include <dos.h>
#include <conio.h>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>

using namespace std;

struct Successor {
	int SUC;
	Successor* NEXT;
};

struct Object {
	int COUNT;
	Successor* TOP;
};

struct NextRelation {
	int LEFT;
	int RIGHT;
};

int n, N, m;
NextRelation Pair[100];
Object* Base = (struct Object*)malloc(n * sizeof(struct Object));
Successor* P;
int J, K;
int R ;
int QLINK[100] = {0};
int F;





struct Simulation {	
	int result[100];
	int maxSucCount = 0;

	Simulation() {

	}
	void drawArrow(Successor * next, int x, int y) {

		if (next != NULL) {
			circle(x, y, 8);
			line(x, y, x, y + 110);
			line(x - 10, y + 100, x, y + 110);
			line(x , y + 110, x + 10, y + 100);

		}
		else {
			circle(x , y,8 );
			line(x, y, x, y + 100);
			line(x - 10, y + 100, x + 10, y + 100);
			line(x - 5, y + 105, x + 5, y + 105);
			line(x - 2.5, y + 110, x + 2.5, y + 110);
		}
	}



	void drawSuccessor(Successor* Temp, int i, int count) {
		int x = 300 + 100 * i;
		int y = 515 + 215*count;

		stringstream strs;
		strs << Temp->SUC;
		string temp_str = strs.str();
		char* char_type = (char*)temp_str.c_str();

		drawText(x+20, y + 10, char_type,0);

		square(x , y, 70);
		square(x,	y +70, 70);	
		drawArrow(Temp->NEXT, x + 35, y + 105 );
	}

	void drawSuccessors() {
		for (int i = 1; i <= m; i++) {
			int t1 = Pair[i].LEFT;
			int t2 = Pair[i].RIGHT;


			Successor* Temp = (Successor*)malloc(sizeof(Successor));
			Temp = Base[t1].TOP;
			int l = 0;
			while (Temp != NULL) {

				drawSuccessor(Temp, t1, l);
				
				Temp = Temp->NEXT;
				
				l++;
				maxSucCount = max(maxSucCount, l);
			}
		}
	}
	void drawObject(int i) {
		int x = 300 + 100 * i;
		int y = 300;

		square(x, y, 70);
		square(x, y+70, 70);

		stringstream strs;
		strs << Base[i].COUNT;
		string temp_str = strs.str();
		char* char_type = (char*)temp_str.c_str();

		drawText(x + 20, y + 10, char_type, 0);
		drawArrow(Base[i].TOP, x+35, y + 70 + 35);
	}

	void drawObjects() {
		for (int i = 1; i <= n; i++) {

			drawObject(i);
		}
		
	}

	void drawPair() {
		setcolor(4);
		stringstream strs1, strs2;
		string temp_str;
		char* char_type;

		square(100, 300, 70);
		square(100, 370, 70);
		square(170, 300, 70);
		square(170, 370, 70);
		drawText(120, 310, "J",0);
		drawText(120, 380, "K",0);

		strs1 << J;
		temp_str = strs1.str();
		char_type = (char*)temp_str.c_str();

		drawText(180, 310, char_type,0);

		strs2 << K;
		temp_str = strs2.str();
		char_type = (char*)temp_str.c_str();

		drawText(180, 380, char_type,0);

		setcolor(15);
	}

	void drawDetail() {
		drawText(280, 220, "k", 0);
		drawText(280, 310, "COUNT[k]", 0);
		drawText(280, 380, "TOP[k]", 0);

		for (int i = 1; i <= n; i++) {
			int x = 280 + 100 * i;
			int y = 220;


			stringstream strs;
			strs << i;
			string temp_str = strs.str();
			char* char_type = (char*)temp_str.c_str();

			drawText(x + 40, y, char_type, 0);
		}

		for (int i = 0; i < maxSucCount; i++) {
			drawText(280, 550 + 215 * i, "SUC", 0);
			drawText(280, 550 + 70 + 215 * i, "NEXT", 0);
		}
	}
	

	void drawActiveCount(int i) {
		setcolor(4);
		int x = 300 + 100 * i;
		int y = 300;		
		square(x , y, 70);
		setcolor(15);
	
	}

	void drawActiveQLINK(int i) {
		setcolor(4);
		int x = 300 + 100 * (n + 4);
		int y = 300 + 70 * (i);

		square(x, y, 70);
		square(x + 70, y, 70);
		setcolor(15);

	}

	void drawR() {
		setcolor(15);
		int x = 300 + 100 * (n+2);

		stringstream strs;
		strs << R;
		string temp_str = strs.str();
		char* char_type = (char*)temp_str.c_str();

		drawText(x+20, 310, "R", 0);
		square(x, 300, 70);
		square(x+70, 300, 70);
		drawText(x + +70 + 20, 310, char_type, 0);
	}

	void drawQLINK() {
		setcolor(15);
		int x = 300 + 100 * (n + 4);

		for (int i = 0; i <= n; i++) {
			int y = 300 + 70 * i;

			stringstream strs1;
			strs1 << i;
			string temp_str1 = strs1.str();
			char* char_type1 = (char*)temp_str1.c_str();

			drawText(x + 20, y + 10,char_type1,0 );

			stringstream strs2;
			strs2 << QLINK[i];
			string temp_str2 = strs2.str();
			char* char_type2 = (char*)temp_str2.c_str();

			drawText(x + 20 + 70, y + 10, char_type2, 0);

			square(x  , y, 70);
			square(x + 70, y, 70);
			


		}
	}

	void drawF() {
		setcolor(15);
		int x = 300 + 100 * (n + 6);

		stringstream strs;
		strs << F;
		string temp_str = strs.str();
		char* char_type = (char*)temp_str.c_str();

		drawText(x + 20, 310, "F", 0);
		square(x, 300, 70);
		square(x + 70, 300, 70);
		drawText(x + 70 + 20, 310, char_type, 0);
	}


	void drawN() {
		setcolor(15);
		int x = 300 + 100 * (n + 6);

		stringstream strs;
		strs << N;
		string temp_str = strs.str();
		char* char_type = (char*)temp_str.c_str();

		drawText(x + 20, 410, "N", 0);
		square(x, 400, 70);
		square(x + 70, 400, 70);
		drawText(x + 70 + 20, 410, char_type, 0);
	}

	void drawResult() {
		for (int i = 1; i <= n - N; i++) {
			stringstream strs;
			strs << result[i];
			string temp_str = strs.str();
			char* char_type = (char*)temp_str.c_str();

			drawText(280, 550 + 215 * (maxSucCount + 1) + 10, "OUTPUT", 0);
			drawText(370 + 70*i + 20, 550 + 215 *( maxSucCount + 1) + 10, char_type, 0);
			square(370 + 70 * i, 550 + 215 * (maxSucCount + 1), 70);
		}
	}

	
	void drawAll(bool t1,bool t2, bool t3, bool t4,bool t5) {
		
		if (t1) {
			drawDetail();
			drawObjects();
		}

		if (t2) {
			drawPair();
		}

		if (t3) {
			drawSuccessors();
		}
		
		if (t4) {
			drawR();
			drawQLINK();
		}
		if (t5) {
			drawF();
			drawN();
			drawResult();
		}
		
		
				
	}


};

struct SimulationStep
{
	Simulation simulation;

	SimulationStep() {
		simulation = Simulation();
	}

	void Input() {
		cout << "Nhap n\n";
		cin >> n;
		cout << "Nhap so luong cac moi quan he\n";
		cin >> m;
		for (int i = 1; i <= m; i++) {
			int j, k;
			cin >> j >> k;
			Pair[i].LEFT = j;
			Pair[i].RIGHT = k;
		}
		system("cls");
	}


	void Step1() {
		drawText(280, 100, "STEP 1: SET COUNT[k] <- 0 and TOP[k] <- NULL for 1 <= k <= n. SET N <- n ", 0);
		Sleep(5000);

		system("cls");
		for (int k = 1; k <= n; k++) {
			Base[k].COUNT = 0;
			Base[k].TOP = NULL;		
		}
		drawText(280, 100, "STEP 1: SET COUNT[k] <- 0 and TOP[k] <- NULL for 1 <= k <= n. SET N <- n ", 1);
		simulation.drawAll(TRUE, FALSE, FALSE,FALSE,FALSE);
		Sleep(10000);

		N = n;

		
	}



	void Step23() {
		system("cls");
		drawText(280, 100, "STEP 2: GET THE NEXT RELATION (j;k) FROM INPUT. IF THE INPUT HAS EXHAUSTED, GO TO STEP 4 ", 0);
		drawText(280, 140, "STEP 3: COUNT[k]++ . SET P <= AVAIL, SUC(P) <- k, NEXT(P) <- TOP[j], TOP[j] <- P", 0);
		simulation.drawAll(TRUE, FALSE, FALSE, FALSE, FALSE);
		Sleep(5000);
		system("cls");
		for (int i = 1; i <= m; i++) {
			
			J = Pair[i].LEFT;
			K = Pair[i].RIGHT;

			drawText(280, 100, "STEP 2: GET THE NEXT RELATION (j;k) FROM INPUT. IF THE INPUT HAS EXHAUSTED, GO TO STEP 4 ", 1);
			drawText(280, 140, "STEP 3: COUNT[k]++ . SET P <= AVAIL, SUC(P) <- k, NEXT(P) <- TOP[j], TOP[j] <- P", 0);
			simulation.drawAll(TRUE, TRUE, TRUE, FALSE, FALSE);
			Sleep(5000);
	
			system("cls");


			Base[K].COUNT++;
			P = (Successor*)malloc(sizeof(Successor));
			
			P->SUC = K;
			P->NEXT = Base[J].TOP;
			Base[J].TOP = P;

			drawText(280, 100, "STEP 2: GET THE NEXT RELATION (j;k) FROM INPUT. IF THE INPUT HAS EXHAUSTED, GO TO STEP 4 ", 0);
			drawText(280, 140, "STEP 3: COUNT[k]++ . SET P <= AVAIL, SUC(P) <- k, NEXT(P) <- TOP[j], TOP[j] <- P", 1);
			simulation.drawAll(TRUE, TRUE, TRUE, FALSE, FALSE);
			simulation.drawActiveCount(K);

			Sleep(5000);
			system("cls");


		}
		simulation.drawAll(TRUE, TRUE, TRUE, FALSE, FALSE);
		Sleep(10000);
		system("cls");
	}

	void Step4() {
		drawText(280, 100, "STEP 4: SET R <- 0, SET QLINK[0] <- 0. FOR 1 <= k <= n : IF COUNT[k] = 0, SET QLINK[R] <- k AND R <- k", 0);
		simulation.drawAll(TRUE, TRUE, TRUE, TRUE, FALSE);
		R = 0;
		QLINK[0] = 0;
		Sleep(5000);
		system("cls");
		for (int k = 1; k <= n; k++) {
			if (Base[k].COUNT == 0) {
				QLINK[R] = k;
				drawText(280, 100, "STEP 4: SET R <- 0, SET QLINK[0] <- 0. FOR 1 <= k <= n : IF COUNT[k] = 0, SET QLINK[R] <- k AND R <- k", 1);
				simulation.drawAll(TRUE, FALSE, TRUE, TRUE, FALSE);
				simulation.drawActiveQLINK(R);
				simulation.drawActiveCount(k);
				Sleep(5000);
				system("cls");

				R = k;

			}
			simulation.drawAll(TRUE, FALSE, TRUE, TRUE, FALSE);
			
			system("cls");
		}
		simulation.drawAll(TRUE, FALSE, TRUE, TRUE, FALSE);
		Sleep(5000);
		system("cls");
	}

	void Step5678() {
		drawText(280, 20, "STEP 5: OUPUT F. IF F = 0, GO TO STEP 8, OTHERWISE SET N <- N - 1, P<-TOP[F]  ", 0);
		drawText(280, 60, "STEP 6: IF P = NULL, GO TO STEP 7. OTHERWISE COUNT[SUC(P)]-- ", 0);
		drawText(280, 100, "        IF COUNT[SUC(P)] = 0, SET QLINK[R] <- SUC(P) AND R <- SUC(P). SET P <- NEXT(P) AND REPEAT THIS STEP", 0);
		drawText(280, 140, "STEP 7: SET F = QLINK[F] AND GO BACK STEP 5", 0);
		drawText(280, 180, "STEP 8: IF N = 0, END OF PROCESS", 0);
		simulation.drawAll(TRUE, FALSE, TRUE, TRUE, FALSE);
		F = QLINK[0];
		Sleep(2000);
		system("cls");
		while (N != 0) {
			while (F != 0) {
				N = N - 1;
				P = Base[F].TOP;

				drawText(280, 20, "STEP 5: OUPUT F. IF F = 0, GO TO STEP 8, OTHERWISE SET N <- N - 1, P<-TOP[F]  ", 1);
				drawText(280, 60, "STEP 6: IF P = NULL, GO TO STEP 7. OTHERWISE COUNT[SUC(P)]-- ", 0);
				drawText(280, 100, "        IF COUNT[SUC(P)] = 0, SET QLINK[R] <- SUC(P) AND R <- SUC(P). SET P <- NEXT(P) AND REPEAT THIS STEP", 0);
				drawText(280, 140, "STEP 7: SET F = QLINK[F] AND GO BACK STEP 5", 0);
				drawText(280, 180, "STEP 8: IF N = 0, END OF PROCESS", 0);
				simulation.result[n-N] = F;
				simulation.drawAll(TRUE, FALSE, TRUE, TRUE, TRUE);
				Sleep(5000);
				system("cls");



				while (P != NULL) {
					Base[P->SUC].COUNT--;

					drawText(280, 20, "STEP 5: OUPUT F. IF F = 0, GO TO STEP 8, OTHERWISE SET N <- N - 1, P<-TOP[F]  ", 0);
					drawText(280, 60, "STEP 6: IF P = NULL, GO TO STEP 7. OTHERWISE COUNT[SUC(P)]-- ", 1);
					drawText(280, 100, "        IF COUNT[SUC(P)] = 0, SET QLINK[R] <- SUC(P) AND R <- SUC(P). SET P <- NEXT(P) AND REPEAT THIS STEP", 1);
					drawText(280, 140, "STEP 7: SET F = QLINK[F] AND GO BACK STEP 5", 0);
					drawText(280, 180, "STEP 8: IF N = 0, END OF PROCESS", 0);

					simulation.drawAll(TRUE, FALSE, TRUE, TRUE, TRUE);
					simulation.drawActiveCount(P->SUC);

					if (Base[P->SUC].COUNT == 0)
					{
						QLINK[R] = P->SUC;
						simulation.drawActiveQLINK(R);
						R = P->SUC;


					}
					P = P->NEXT;
					Sleep(5000);
					system("cls");
				}
				drawText(280, 20, "STEP 5: OUPUT F. IF F = 0, GO TO STEP 8, OTHERWISE SET N <- N - 1, P<-TOP[F]  ", 0);
				drawText(280, 60, "STEP 6: IF P = NULL, GO TO STEP 7. OTHERWISE COUNT[SUC(P)]-- ", 1);
				drawText(280, 100, "        IF COUNT[SUC(P)] = 0, SET QLINK[R] <- SUC(P) AND R <- SUC(P). SET P <- NEXT(P) AND REPEAT THIS STEP", 1);
				drawText(280, 140, "STEP 7: SET F = QLINK[F] AND GO BACK STEP 5", 0);
				drawText(280, 180, "STEP 8: IF N = 0, END OF PROCESS", 0);
				simulation.drawAll(TRUE, FALSE, TRUE, TRUE, TRUE);
				Sleep(5000);
				system("cls");

				F = QLINK[F];

				drawText(280, 20, "STEP 5: OUPUT F. IF F = 0, GO TO STEP 8, OTHERWISE SET N <- N - 1, P<-TOP[F]  ", 0);
				drawText(280, 60, "STEP 6: IF P = NULL, GO TO STEP 7. OTHERWISE COUNT[SUC(P)]-- ", 0);
				drawText(280, 100, "        IF COUNT[SUC(P)] = 0, SET QLINK[R] <- SUC(P) AND R <- SUC(P). SET P <- NEXT(P) AND REPEAT THIS STEP", 0);
				drawText(280, 140, "STEP 7: SET F = QLINK[F] AND GO BACK STEP 5", 1);
				drawText(280, 180, "STEP 8: IF N = 0, END OF PROCESS", 0);
				simulation.drawAll(TRUE, FALSE, TRUE, TRUE, TRUE);


				Sleep(5000);
				system("cls");

			}		
		}
		drawText(280, 20, "STEP 5: OUPUT F. IF F = 0, GO TO STEP 8, OTHERWISE SET N <- N - 1, P<-TOP[F]  ", 0);
		drawText(280, 60, "STEP 6: IF P = NULL, GO TO STEP 7. OTHERWISE COUNT[SUC(P)]-- ", 0);
		drawText(280, 100, "        IF COUNT[SUC(P)] = 0, SET QLINK[R] <- SUC(P) AND R <- SUC(P). SET P <- NEXT(P) AND REPEAT THIS STEP", 0);
		drawText(280, 140, "STEP 7: SET F = QLINK[F] AND GO BACK STEP 5", 0);
		drawText(280, 180, "STEP 8: IF N = 0, END OF PROCESS", 1);



		simulation.drawAll(TRUE, FALSE, TRUE, TRUE, TRUE);
		}
		
};

int main() {
	initgraph();

	SimulationStep Topo;

	Topo.Input();
	Topo.Step1();
	
	Topo.Step23();
	Topo.Step4();
	Topo.Step5678();

	_getch();
}