#include <iostream>
#include <conio.h>
#include <cstdio>
#include <io.h>
#include "get.h"
#pragma warning(disable: 4996)
using namespace std;

typedef struct
{
    int fiz;
    int maths;
    int cs;
    int chem;
} mark;

typedef struct
{
    char fam[30];
    char im[30];
    int b_year;
    char nomer[7];
    mark marks;
    float sr_b;
} stud;
typedef struct node
{
    char ch;
    node* next;
 }node;



stud In(void);
mark In_mark(void);
void fIn(FILE*, stud);
void fOut(FILE* file);
bool are_same(char* s1, char* s2);
bool is_not_one_word(char* str);
void outgruppa(FILE*, char*, FILE*);
void get_string(char* arr, int n);

char* from_node_to_str(node*);
node* get_node(void);
int length_of_node(node* x);
void delete_node(node*);


int main(void)
{
    system("chcp 1251");
    setlocale(LC_ALL, "ru");

    while (true)
    {
        int i;
        cout << "\n\n\nМеню:\n 1 - создать список студентов\n 2 - просмотреть список студентов\n 3 - добавить новые записи\n 4 - распечатать анкетные данные студентов интересующей вас группы\n другая кнопочка - выход\n";
        switch (_getch())
        {
        case '1':
        {
            cout << "Это удалит предыдущие записи. Продолжить?\n 1 - продолжить \n другая кнопочка - не продолжать\n";
            if (_getch() != '1')
                break;
            stud students;

            FILE* file = fopen("students.txt", "w");
            if (file == NULL)
            {
                return 1;
            }
            while(true)
            {
                students = In();
                fIn(file, students);
                cout << "Нажмите 1, если хотите ввести ещё одного студента\nЕсли хотите закончить вводить - нажмите любую другую кнопку\n";
                if (_getch() != '1')
                    break;
            }
            fclose(file);
            break;
        }
        case '2':
        {
            FILE* file = fopen("students.txt", "r");
            if (file == NULL)
            {
                return 1;
            }
            fOut(file);
            fclose(file);
            break;
        }
        case '3':
        {
            stud students;

            FILE* file = fopen("students.txt", "a");
            if (file == NULL)
            {
                return 1;
            }
            while (true)
            {
                students = In();
                fIn(file, students);
                cout << "Нажмите 1, если хотите ввести ещё одного студента\nЕсли хотите закончить вводить - нажмите любую другую кнопку\n";
                if (_getch() != '1')
                    break;
            }
            fclose(file);
            break;
        }
        case '4':
        {

            FILE* input = fopen("students.txt", "r");
            if (input == NULL)
            {
                return 1;
            }
            FILE* output = fopen("gruppa.txt", "w+");
            if (output == NULL)
            {
                return 1;
            }
            cout << "Введите номер группы:  ";
            char gruppa[7];
            get_string(gruppa, 7);
            outgruppa(input, gruppa, output);
            cout << "Готово!\n";
        }
        default:
            return 0;
        }

    }


}


void get_string(char* arr, int n)
{
    int len_str;

    node* tmp;
    char* arr1;
    while (true)
    {
        tmp = get_node();

        len_str = length_of_node(tmp);

        if (len_str < n)
        {
            break;
        }
        delete_node(tmp);
        cout << "Введите строку размером " << (n - 1) << " или меньше\n";
    }
    arr1 = from_node_to_str(tmp);
    arr1[len_str] = '\0';
    for (int i = 0; i < len_str + 1; i++)
    {
        arr[i] = arr1[i];
    }
    delete_node(tmp);
    return;
}

node* get_node(void)
{
    node* x = new node[1];
    x->ch = _getch();
    if (x->ch == 13)
    {
        cout << endl;
        x->next = NULL;
    }
    else
    {
        cout << x->ch;
        x->next = get_node();
    }
    return x;
}
char* from_node_to_str(node* x)
{
    int n = length_of_node(x);
    char* str = new char[n + 1];
    node* p = x;
    int i;
    for (i = 0; i < n; i++)
    {
        str[i] = p->ch;
        p = p->next;
    }
    str[i] = '\0';
    return str;
}

int length_of_node(node* x)
{

    int n = 0;
    for (node* p = x; p->next != NULL; p = p->next)
    {
        n++;
    }
    return n;
}

void delete_node(node* x)
{
    if (x == NULL)
    {
        return;
    }
    delete_node(x->next);
    delete[]x;
}

stud In(void)
{
    stud res;
    while (true)
    {
        cout << "Введите Фамилию:  ";
        get_string(res.fam, 30);
        if (is_not_one_word(res.fam))
        {
            cout << "Введите одно слово\n";
            continue;
        }
        break;
    }
    while (true)
    {
        cout << "Введите Имя:  ";
        get_string(res.im, 30);
        if (is_not_one_word(res.fam))
        {
            cout << "Введите одно слово\n";
            continue;
        }
        break;
    }


    do
    {
        res.b_year = get_int("Введите год рождения:  ");
    } while (res.b_year < 1922 || res.b_year > 2012);
     
    cout << "Введите номер группы:  ";
    get_string(res.nomer, 7);
    res.marks = In_mark();
    res.sr_b = (res.marks.chem + res.marks.cs + res.marks.fiz + res.marks.maths) / 4.;
    cout << "Средний балл: " << res.sr_b << endl;
    return res;
}
mark In_mark(void)
{
    mark res;
    cout << "Введите оценки по: \n";
    do
    {
        res.chem = get_int("  химии: ");
    } while (res.chem > 10 || res.chem < 0);
    do
    {
        res.cs = get_int("  информатике:  ");
    } while (res.cs > 10 || res.cs < 0);
    do
    {
        res.fiz = get_int("  физике:  ");
    } while (res.fiz > 10 || res.fiz < 0);
    do
    {
        res.maths = get_int("  математике:  ");
    } while (res.maths > 10 || res.maths < 0);
     

    return res;
}


void fIn(FILE* file, stud z)
{

    fprintf(file, "ФИО: %s %s\n год рождения:%i\n номер группы:%s\n оценки:\n   химия: %i\n   информатика: %i\n   физика: %i\n   математика: %i\n Средний балл: %f\n--------------------\n", z.fam, z.im, z.b_year, z.nomer, z.marks.chem, z.marks.cs, z.marks.fiz, z.marks.maths, z.sr_b);
    return;
}

void fOut(FILE* file)
{
    char c;
    while (fread(&c, sizeof(char), 1, file))
    {
        cout << c;
    }
}

void outgruppa(FILE* in, char* str, FILE* out)
{
    stud z;
    while (fscanf(in, "ФИО: %s %s\n год рождения:%i\n номер группы:%s\n оценки:\n   химия: %i\n   информатика: %i\n   физика: %i\n   математика: %i\n Средний балл: %f\n--------------------\n", z.fam, z.im, &z.b_year, z.nomer, &z.marks.chem, &z.marks.cs, &z.marks.fiz, &z.marks.maths, &z.sr_b) != EOF)
    {
        if (are_same(z.nomer, str))
        {
            fprintf(out, "ФИО: %s %s\n год рождения:%i\n номер группы:%s\n оценки:\n   химия: %i\n   информатика: %i\n   физика: %i\n   математика: %i\n Средний балл: %f\n--------------------\n", z.fam, z.im, z.b_year, z.nomer, z.marks.chem, z.marks.cs, z.marks.fiz, z.marks.maths, z.sr_b);
        }

    }
}

bool are_same(char* s1, char* s2)
{
    int i;
    for (i = 0; (s1[i] != '\0') || (s2[i] != '\0'); i++)
    {
        if (s1[i] != s2[i])
        {
            return false;
        }
    }
    if (s1[i] != s2[i])
    {
        return false;
    }
    return true;
}

bool is_not_one_word(char* str)
{
    for (int i = 0, n = strlen(str); i < n; i++)
    {
        if (str[i] == ' ') return true;
    }
    return false;
}
