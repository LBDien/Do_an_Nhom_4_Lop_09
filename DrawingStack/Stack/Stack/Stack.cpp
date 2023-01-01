#include <iostream>
#include "graphics.h"
#include <dos.h>
#include <conio.h>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>

using namespace std;

struct Node {
    int data;
    Node* link;

    Node(int n)
    {
        this->data = n;
        this->link = NULL;
    }
};

struct Stack {
    Node* top;
    Stack() { top = NULL; }

    void push(int data)
    {

        Node* temp = new Node(data);
        if (!temp) {
            return;
        }
        temp->data = data;

        temp->link = top;

        top = temp;
    }
    bool isEmpty()
    {
        return top == NULL;
    }
    int getTop()
    {
        if (!isEmpty())
            return top->data;
        else
            exit(1);
    }
    void pop()
    {
        Node* temp;

        if (top == NULL) {
            cout << "\nStack Underflow" << endl;
            exit(1);
        }
        else {
            temp = top;
            top = top->link;
        }
    }
    int size()
    {
        Node* temp;
        temp = top;
        int s = 0;
        while (temp != NULL) {
            s++;
            temp = temp->link;
        }
        return s;
    }
};

struct Atribute {

    int getBlockX(int i) {
        return 100 + 150 * (i % 5);
    }

    int getBlockY(int i) {
        return 500 + 150 * (i / 5);
    }

    int sizeStack(int N) {
        int size = 800;
        if (N > 5)
            size += 75 * (N - 5);
        return size;
    }

    int getStackY(int i, int N) {
        return sizeStack(N) - 104 - i * 60;
    }

};


struct Simulation {
    Atribute A;
    Stack S1;
    Stack S2;
    int N;
    void Input() {
        cout << "Nhap so luong phan tu\n";
        cin >> N;
        int t;
        int A[100];
        for (int i = 0; i < N; i++) {
            cout << "Nhap gia tri phan thu thu " << i + 1 << "\n";
            cin >> t;
            S1.push(t);
        }
        
    }
    
    void DrawBlock() {
        Stack temp = S1;
        setcolor(0);

        for (int i = S1.size() - 1; i >= 0; i--) {
            int number = temp.getTop();

            int BlockX = A.getBlockX(i);
            int BlockY = A.getBlockY(i);

            stringstream strs;
            strs << number;
            string temp_str = strs.str();
            char* char_type = (char*)temp_str.c_str();

            rectangle(BlockX, BlockY, BlockX + 100, BlockY + 50);
            drawText(BlockX + 35, BlockY, char_type);

            temp.pop();
        }
    }

    void DrawStack() {     
        int size = A.sizeStack(N);
        Stack temp = S2;
        setcolor(15);
        line(1500, 400, 1500, size);
        line(1500, size - 50, 1700, size - 50);
        line(1700, 400, 1700, size);
        line(1500, size, 1700, size);
         
        drawText(1570, size - 50, "STACK");

        for (int i = S2.size() - 1; i >= 0; i--) {
            int number = temp.getTop();
            int StackY = A.getStackY(i,N);
            int TopY = A.getStackY(S2.size() - 1, N);
            stringstream strs;
            strs << number;
            string temp_str = strs.str();
            char* char_type = (char*)temp_str.c_str();
            setcolor(0);
            line(1650, TopY + 25, 1720, TopY + 25);
            drawText(1720,TopY, "TOP");
            rectangle(1550, StackY, 1550 + 100, StackY + 50);
            
            drawText(1550 + 35, StackY, char_type);
            
       
            
          
            temp.pop();
  
        }
        
    }

    void Insert() {
        int size1 = S1.size();
        int size2 = S2.size();     
        int BlockX = A.getBlockX(size1 - 1);
        int BlockY = A.getBlockY(size1 - 1);
        int StackY = A.getStackY(size2, N);
        int temp = S1.getTop();
        S1.pop();

        while (BlockX < 1300) {
            BlockX += 10;
            if (BlockX > 1300)
                BlockX = 1300;
            stringstream strs;
            strs << temp;
            string temp_str = strs.str();
            char* char_type = (char*)temp_str.c_str();

            setcolor(rand() % 15);
            rectangle(BlockX, BlockY, BlockX + 100, BlockY + 50);
            DrawStack();
            DrawBlock();
            drawText(BlockX + 35, BlockY, char_type);
            Sleep(10);
            system("cls");

        }

        while (BlockY != 250) {
            BlockY -= 10;
            stringstream strs;
            strs << temp;
            string temp_str = strs.str();
            char* char_type = (char*)temp_str.c_str();

            setcolor(rand() % 15);

            rectangle(BlockX, BlockY, BlockX + 100, BlockY + 50);
            DrawStack();
            DrawBlock();
            drawText(BlockX + 35, BlockY, char_type);
            Sleep(10);
            system("cls");

        }

        while (BlockX != 1550) {
            BlockX += 10;
            stringstream strs;
            strs << temp;
            string temp_str = strs.str();
            char* char_type = (char*)temp_str.c_str();

            setcolor(rand() % 15);
            rectangle(BlockX, BlockY, BlockX + 100, BlockY + 50);
            DrawStack();
            DrawBlock();
           drawText(BlockX + 35, BlockY, char_type);
           Sleep(10);
            system("cls");

        }

        while (BlockY < StackY) {
            BlockY += 10;
            if (BlockY > StackY)
                BlockY = StackY;
            stringstream strs;
            strs << temp;
            string temp_str = strs.str();
            char* char_type = (char*)temp_str.c_str();

            setcolor(rand() % 15);

            rectangle(BlockX, BlockY, BlockX + 100, BlockY + 50);
            DrawStack();
            DrawBlock();
            drawText(BlockX + 35, BlockY, char_type);
            Sleep(10);
            system("cls");

        }

        S2.push(temp);
    }

    void Delete() {
        int size = S2.size();
        int StackX = 1555, StackY = A.getStackY(size,N);

        int temp = S2.getTop();
        S2.pop();

        while (StackY != 250) {
            StackY -= 10;
            if (StackY < 250) {
                StackY = 250;
            }

            stringstream strs;
            strs << temp;
            string temp_str = strs.str();
            char* char_type = (char*)temp_str.c_str();

            setcolor(rand() % 15);

            rectangle(StackX, StackY, StackX + 100, StackY + 50);
            DrawStack();
            DrawBlock();
            drawText(StackX + 35, StackY, char_type);
            Sleep(10);
            system("cls");
        }
        system("cls");
    }

    void End() {
        system("cls");
        drawText(1000,500 ,"Ket Thuc Chuong Trinh Mo Phong");

    }
};

void RunProgram(Simulation StackSimulation) {
    StackSimulation.DrawBlock();
    StackSimulation.DrawStack();
    cout << "Nhan 1 De Insert\n";
    cout << "Nhan 2 De Delete\n";
    cout << "Nhan 3 De Exit\n";
    int choose;
    cin >> choose;
    switch (choose)
    {
        case 1:
            StackSimulation.Insert();
            break;
        case 2:
            StackSimulation.Delete();
            break;
        case 3:
            StackSimulation.End();
            exit(0);
            break;
        default:
            break;
    }
    RunProgram(StackSimulation);  
}

int main() {
    Simulation StackSimulation;
    StackSimulation.Input();
    initgraph();
    system("cls");
    cout << "Nhan phim bat ky de tiep tuc";
    
    _getch();
    system("cls");
    RunProgram(StackSimulation);
}







