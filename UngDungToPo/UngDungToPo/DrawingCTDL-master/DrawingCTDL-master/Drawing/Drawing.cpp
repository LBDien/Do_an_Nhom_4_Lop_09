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
class Node {
public:
    int data;
    Node* link;

    Node(int n)
    {
        this->data = n;
        this->link = NULL;
    }
};

class Stack {
    Node* top;
public:
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
    int peek()
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

class Queue {
    Node* top;
    Node* rear;
public:
    Queue() {
        top = NULL;
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
            top = rear = temp;
            return;
        }

        rear->link = temp;

        rear = temp;
    }
    bool isEmpty()
    {
        return top == NULL;
    }
    int peek()
    {
        if (!isEmpty())
            return top->data;
        else
            exit(1);
    }

    void pop()
    {
        if (top == NULL) {
            cout << "\nQueue Underflow" << endl;
            exit(1);
        }
        top = top->link;
        if (top == NULL)
            rear = NULL;
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
        int number = temp.peek();
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
    line(x, 150, x, 200);
    line(x - 100, 150, x - 100, 200);
    line(x - 100, 150, x, 150);

    Queue temp = S2;
    drawText(x - 80,160, "QUEUE");
    for (int i = 0; i <= S2.size() - 1; i++) {
        int number = temp.peek();
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
    int temp = S1.peek();
    S1.pop();
    while (y != 225) {
        y -= 25;
        stringstream strs;
        strs << temp;
        string temp_str = strs.str();
        char* char_type = (char*)temp_str.c_str();

        setcolor(rand() % 15);

        rectangle(x, y, x + 100, y + 50);
        drawContainer();
        drawBlock();
        drawText(x + 35, y, char_type);
        Sleep(10);
        system("cls");

    }
    while (x < posCX(size2)-100) {
        x += 10;
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
        Sleep(10);
        system("cls");

    }
    S2.push(temp);
}

void MoveDelete() {
    int size2 = S2.size();
    int x = posCX(0), y =225 ;

    int temp = S2.peek();
    S2.pop();

    while (x != sizeContainer()+150) {
        x += 5;
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
        Sleep(10);
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
    cin >> t;
    if (t == 1) {
        MoveInsert();
    }
    else if (t == 2) {
        if (!S2.isEmpty())
            MoveDelete();
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







