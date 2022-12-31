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
    Node* next;
    Node* prev;

    Node(int n)
    {
        this->data = n;
        this->next = NULL;
        this->prev = NULL;
    }
};
struct Dequeue
{
    Node* rightMost;
    Node* leftMost;
    int Size;
    Dequeue()
    {
        rightMost = leftMost = NULL;
        Size = 0;
    }
    bool isEmpty()
    {
        return leftMost == NULL;
    }
    int size()
    {
        return Size;
    }
    void insertRightMost(int data)
    {
        Node* temp = new Node(data);
        if (temp == NULL)
            cout << "\nOverFlow";
        else
        {
            if (rightMost == NULL)
                leftMost = rightMost = temp;
            else
            {
                temp->next = rightMost;
                rightMost->prev = temp;
                rightMost = temp;
            }
            Size++;
        }

    }
    void insertLeftMost(int data)
    {
        Node* temp = new Node(data);
        if (temp == NULL)
            cout << "\nOverFlow";
        else
        {
            if (leftMost == NULL)
                rightMost = leftMost = temp;
            else
            {
                temp->prev = leftMost;
                leftMost->next = temp;
                leftMost = temp;
            }
            Size++;
        }
    }
    void deleteRightMost()
    {
        if (isEmpty())
        {
            cout << "\nUnderFlow";
        }
        else
        {
            rightMost = rightMost->next;
            if (rightMost == NULL)
                leftMost = NULL;
            else
                rightMost->prev = NULL;
            Size--;
        }
    }
    void deleteLeftMost()
    {
        if (isEmpty())
            cout << "\nUnderFlow";
        else
        {
            leftMost = leftMost->prev;
            if (leftMost == NULL)
                rightMost = NULL;
            else
                leftMost->next = NULL;
            Size--;
        }
    }
    int getRightMost()
    {
        if (isEmpty())
            exit(1);

        else
            return rightMost->data;
    }
    int getLeftMost()
    {
        if (isEmpty())
            exit(1);
            
        else
            return leftMost->data;
    }
    Node* RightMost()
    {
        return rightMost;
    }

};
int N;
Dequeue S1;
Dequeue S2;

int posBX(int i) {
    return 100 + 100 * (i / 5);
}

int posBY(int i) {
    return 400 + 100 * (i % 5);
}

int sizeContainer() {
    int size = 1300;
    if (N > 5)
        size += 100 * (N - 5);
    return size;
}

int posCX(int i) {
    return sizeContainer() - (i + 1) * 104;
}

void drawBlock() {
    int i = S1.size();
    Dequeue temp = S1;
    setcolor(0);
    for (int i = 0; i <= S1.size() - 1; i++) {
        int number = temp.getRightMost();
        stringstream strs;
        strs << number;
        string temp_str = strs.str();
        char* char_type = (char*)temp_str.c_str();
        int x = posBX(i);
        int y = posBY(i);
        rectangle(x, y, x + 100, y + 50);
        drawText(x + 35, y, char_type);
        temp.deleteRightMost();
    }
}

void drawContainer() {
    setcolor(15);
    int x = sizeContainer();

    line(650, 200, x, 200);
    line(650, 300, x, 300);
    if (S2.isEmpty() == false)
    {
        line(posCX(0) - 100 + 45, 222, posCX(0) - 100 + 45, 150);
        line(posCX(0), 100, posCX(0), 150);
        line(posCX(0), 100, posCX(0) - 100, 100);
        line(posCX(0) - 100, 100, posCX(0) - 100, 150);
        line(posCX(0), 150, posCX(0) - 100, 150);
        drawText(posCX(0) - 100 , 105, "Right Most");
        line(posCX(S2.size() - 1) - 100 + 45, 282, posCX(S2.size() - 1) - 100 + 45, 350);
        line(posCX(S2.size() - 1), 400, posCX(S2.size() - 1), 350);
        line(posCX(S2.size() - 1), 400, posCX(S2.size() - 1) - 100, 400);
        line(posCX(S2.size() - 1) - 100, 400, posCX(S2.size() - 1) - 100, 350);
        line(posCX(S2.size() - 1), 350, posCX(S2.size() - 1) - 100, 350);
        drawText(posCX(S2.size() - 1) - 100 + 18, 355, "Left Most");
    };

    Node* temp1 = S2.RightMost();
    int i = 0;
    while (temp1 != NULL) {
        int number = temp1->data;
        stringstream strs;
        strs << number;
        string temp_str = strs.str();
        char* char_type = (char*)temp_str.c_str();
        rectangle(posCX(i), 225, posCX(i) - 100, 225 + 50);
        drawText(posCX(i) - 100 + 35, 225, char_type);
        temp1 = temp1->next;
        i++;
    }

}

void MoveInsertLeftMost() {
    int size1 = S1.size();
    int size2 = S2.size();

    int x = posBX(0), y = posBY(0);
    int temp = S1.getRightMost();
    S1.deleteRightMost();
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
        Sleep(10);
        system("cls");

    }
    while (x < posCX(size2) - 100) {
        x += 20;
        if (x > sizeContainer() - 100)
            x = sizeContainer() - 100;
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
    S2.insertLeftMost(temp);

}
void MoveInsertRightMost() {
    int size1 = S1.size();
    int size2 = S2.size();
    int x = posBX(0), y = posBY(0);
    int temp = S1.getRightMost();
    S1.deleteRightMost();

    while (x != sizeContainer() + 100)
    {
        x += 20;
        if (x > sizeContainer() + 100)
            x = sizeContainer() + 100;
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
        Sleep(10);
        system("cls");

    }
    while (x > posCX(0)) {
        x -= 20;
        if (x < posCX(0))
            x = posCX(0);
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
    S2.insertRightMost(temp);
}

void MoveDeleteLeftMost() {
    int size2 = S2.size();
    int x = posCX(size2), y = 225;
    int temp = S2.getLeftMost();
    S2.deleteLeftMost();
    while (x != 600) {
        x -= 20;
        if (x < 600) {
            x = 600;
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
void MoveDeleteRightMost() {
    int size2 = S2.size();
    int x = posCX(0), y = 225;
    int temp = S2.getRightMost();
    S2.deleteRightMost();
    while (x != sizeContainer() + 150) {
        x += 20;
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
        S1.insertLeftMost(t);
    }
}

void Control() {

    drawBlock();
    drawContainer();
    cout << "Nhan 1 De Insert ben trai\n";
    cout << "Nhan 2 De Insert ben phai\n";
    cout << "Nhan 3 De Delete ben trai\n";
    cout << "Nhan 4 De Delete ben phai\n";
    cout << "Nhan 5 De Ket Thuc\n";
    int t;
    cin >> t;
    switch (t)
    {
    case 1:
        MoveInsertLeftMost();  break;
    case 2:
        MoveInsertRightMost();  break;
    case 3:
        if (S2.isEmpty() != true)
            MoveDeleteLeftMost();
        else cout << "UnderFlow!\n";
        break;
    case 4:
        if (S2.isEmpty() != true)
            MoveDeleteRightMost();
        else cout << "UnderFlow!\n";
        break;
    case 5:
        cout << "Ket thuc!";
        exit(1);
    default:
        break;
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







