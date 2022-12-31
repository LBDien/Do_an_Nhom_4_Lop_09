#include <iostream>
#include "graphics.h"
#include <dos.h>
#include <conio.h>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
using namespace std;
void Control();
struct Node {
    int data;
    Node* next;

    Node(int n)
    {
        this->data = n;
        this->next = NULL;
    }
};
struct Queue {
    Node* front;
    Node* rear;
    Queue() {
        front = NULL;
        rear = NULL;
    }

    void push(int data)
    {

        Node* temp = new Node(data);
        if (!temp) {
            return;
        }
        if (rear == NULL)
        {
            front = rear = temp;
            return;
        }

        rear->next = temp;

        rear = temp;
    }
    bool isEmpty()
    {
        return front == NULL;
    }
    int getFront()
    {
        if (!isEmpty())
            return front->data;
        else
            exit(1);
    }

    void pop()
    {
        if (front == NULL) {
            cout << "\nQueue Underflow" << endl;
            exit(1);
        }
        front = front->next;
        if (front == NULL)
            rear = NULL;
    }
    int size()
    {
        Node* temp;
        temp = front;
        int s = 0;
        while (temp != NULL) {
            s++;
            temp = temp->next;
        }
        return s;

    }
};

int N;
Queue S1;
Queue S2;
int posBX(int i) {
    return 100 + 100 * (i / 5);
}

int posBY(int i) {
    return 400 + 100 * (i % 5);
}

int sizeContainer() {
    int size = 1600;
    if (N > 5)
        size += 75 * (N - 5);
    return size;
}

int posCX(int i) {
    return sizeContainer()  - i * 104;
}

void drawBlock() {
    int i = S1.size();
    Queue temp = S1;
    setcolor(0);
    for (int i = 0; i <= S1.size() - 1; i++) {
        int number = temp.getFront();
        stringstream strs;
        strs << number;
        string temp_str = strs.str();
        char* char_type = (char*)temp_str.c_str();
        int x = posBX(i);
        int y = posBY(i);
        rectangle(x, y, x + 100, y + 50);
        drawText(x + 35, y, char_type);
        temp.pop();
    }
}

void drawContainer() {
    setcolor(15);
    int x = sizeContainer();

    line(1050,200, x, 200);
    line(1050,300, x, 300);
    if (S2.isEmpty() == false)
    {   
        line(posCX(0) - 100 + 45, 222, posCX(0) - 100 + 45, 150);
        line(posCX(0), 100, posCX(0),150 );
        line(posCX(0), 100, posCX(0) - 100, 100);
        line(posCX(0) - 100, 100, posCX(0) - 100, 150);
        line(posCX(0), 150, posCX(0) - 100, 150);
        drawText(posCX(0) - 100 + 25, 105, "Front");

        line(posCX(S2.size() - 1) - 100 + 45, 282, posCX(S2.size() - 1) - 100 + 45, 350);
        line(posCX(S2.size() - 1), 400, posCX(S2.size() - 1), 350);
        line(posCX(S2.size() - 1), 400, posCX(S2.size() - 1) - 100, 400);
        line(posCX(S2.size() - 1) - 100, 400, posCX(S2.size() - 1) - 100, 350);
        line(posCX(S2.size() - 1), 350, posCX(S2.size() - 1) - 100, 350);
        drawText(posCX(S2.size() - 1) - 100 + 28, 355, "Rear");
    };

    Queue temp = S2;
    for (int i = 0; i <= S2.size() - 1; i++) {
        int number = temp.getFront();
        stringstream strs;
        strs << number;
        string temp_str = strs.str();
        char* char_type = (char*)temp_str.c_str();
        setcolor(0);
        rectangle(posCX(i), 225 , posCX(i)-100, 225 + 50);
        drawText(posCX(i)-100 + 35, 225, char_type);
        temp.pop();
    }
    
}

void MoveInsert() {
    int size1 = S1.size();
    int size2 = S2.size();
    int x = posBX(0), y = posBY(0);
    int temp = S1.getFront();
    S1.pop();
    while (y != 225) {
        y -= 20;
        if (y < 225)
            y = 225;
        stringstream strs;
        strs << temp;
        string temp_str = strs.str();
        char* char_type = (char*)temp_str.c_str();

        setcolor(rand() % 15);

        rectangle(x, y, x + 100, y + 50);
        drawContainer();
        drawBlock();
        drawText(x + 35, y, char_type);
        Sleep(5);
        system("cls");

    }
    while (x < posCX(size2)-100) {
        x += 20;
        if (x > sizeContainer()-100)
            x = sizeContainer()-100;
        stringstream strs;
        strs << temp;
        string temp_str = strs.str();
        char* char_type = (char*)temp_str.c_str();

        setcolor(rand() % 15);
        rectangle(x, y, x + 100, y + 50);
        drawContainer();
        drawBlock();
        drawText(x + 35, y, char_type);
        Sleep(5);
        system("cls");

    }
    S2.push(temp);
}

void MoveDelete() {
    int size2 = S2.size();
    int x = posCX(0), y =225 ;
    int temp = S2.getFront();
        S2.pop();


    while (x != sizeContainer()+150) {
        x +=20;
        if (x > sizeContainer() + 150) {
            x = sizeContainer() + 150;
        }

        stringstream strs;
        strs << temp;
        string temp_str = strs.str();
        char* char_type = (char*)temp_str.c_str();

        setcolor(rand() % 15);

        rectangle(x, y, x + 100, y + 50);
        drawContainer();
        drawBlock();
        drawText(x + 35, y, char_type);
        Sleep(5);
        system("cls");
    }
    system("cls");
}



void Nhap() {

    cout << "Nhap so luong phan tu\n";
    cin >> N;
    int t;
    for (int i = 0; i < N; i++) {
        cout << "Nhap gia tri phan thu thu " << i + 1 << "\n";
        cin >> t;
        S1.push(t);
    }
}

void Control() {
    int t;
    drawBlock();
    drawContainer();
    cout << "Nhan 1 De Insert\n";
    cout << "Nhan 2 De Delete\n";
    cout << "Nhan 3 De Ket Thuc!\n";
    cin >> t;
    if (t == 1) {
        MoveInsert();
    }
    else if (t == 2) {
        if (!S2.isEmpty())
            MoveDelete();
        else cout << "UnderFlow!\n";
    }
    else if (t == 3)
    {
        cout << "Ket thuc!";
        exit(1);
    }
    Control();
}

int main() {
    Nhap();
    initgraph();
    drawBlock();
    drawContainer();
    cout << "Nhan phim bat ky de tiep tuc";
    _getch();
    system("cls");
    Control();
}







