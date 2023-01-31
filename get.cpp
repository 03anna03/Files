#include "get.h"
#include <iostream>
#include <conio.h>
using namespace std;

double get_double(const char* ask)
{
    cout << ask;
    const int LIMIT = 10;
    char var[LIMIT];
    char ch;
    int i = 0;
    char prev = '\0';
    bool is_here_e_or_a_dot = false;

    while (true)
    {
        ch = _getch();
        if (ch == 13)// enter
        {
            if (i == 0) continue;
            break;
        }

        if (ch != '.' && ch != '-' && !isdigit(ch) && ch != 'e') continue; // ����  �� ����� �� ����� �� ����� �� ����� - ����������
        if (ch == '-' && i > 0)//���� ����� �� ������
        {
            if (prev == 'e')//� �� ����� �
            {
                prev = ch;
                var[i] = ch;
                cout << ch;
                i++;
                if (i == LIMIT - 1) break;
            }
            continue;
        }
        if ((ch == '.')  || (ch == 'e'))//���� ���� ����� ��� �
        {
            if ((i == 0) || (is_here_e_or_a_dot)) continue;
            is_here_e_or_a_dot = true;
        }

        if (ch == '0' && prev == '0' && i == 1) continue;//���� ���� ����� ������� ����
        prev = ch;
        var[i] = ch;
        cout << ch;
        i++;
        if (i == LIMIT - 1) break;
    }
    var[i] = '\0';
    cout << endl;
    return stod(var);
}


int get_int(const char* ask)
{
    cout << ask;

    const int LENINT = 11;
    char var[LENINT];
    char ch;
    int i = 0;
    while(true)
    {
        ch = _getch();

        if (ch == 13)//enter
        {
            if (i == 0) continue;
            break;
        }
        if (ch != '-' && !isdigit(ch)) continue; //���� �� ����� � �� �����
        if (ch == '-' && i > 0) continue; //���� ����� �� ������

        if (i == 0 && ch == '0')//���� 0 - �� ��. ����� �������
        {
            var[i] = ch;
            cout << ch;
            i++;
            break;
        }
        var[i] = ch;
        cout << ch;
        i++;
        if (i == LENINT - 1) break;
    }
    var[i] = '\0';
    cout << endl;
    return stoi(var);
}