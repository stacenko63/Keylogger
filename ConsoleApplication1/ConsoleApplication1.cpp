#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <map>
#include <windows.h>
using namespace std;

void input_correctly_number(int& inputValue) 
{
    while (!(cin >> inputValue) || cin.peek() != '\n') 
    {
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail());
        cout << "������� �������� ��������. ��������� �������: ";
    }
}

void Limitations(int min, int max, int& inputValue) 
{
    while (inputValue < min || inputValue > max) 
    {
        cout << "��������� ����� �� ������������� ����������. ��������� ����: ";
        input_correctly_number(inputValue);
    }
}

string GetDataFromFile(string filename)
{
    string text, tmp;
    ifstream in(filename);

    if (!in.is_open())
    {
        throw exception("������ ��� �������� �����!");
    }

    while (!in.eof())
    {
        getline(in, tmp);
        text += tmp;

        if (!in.eof())
        {
            text += "\n";
        }
    }

    return text;
}

void AppendDataToFile(string filename, string text)
{
    ofstream out;
    out.open(filename, ios_base::app); 

    if (!out.is_open())
    {
        throw exception("������ ��� �������� �����!");
    }

    out << text;
}

void StartTraining()
{
    int menu = 0;
    do
    {
        system("cls");
        string filename, text;
        int errorsCount = 0;
        cout << "������� ���� � �����, � ������� ���������� �����: ";
        cin >> filename;
        text = GetDataFromFile(filename);

        cout << text << "\n\n\n������ �������� ��������: ";

        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

        for (auto symbol : text)
        {
            if ((int)symbol == _getch())
            {
                SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
            }
            else
            {
                SetConsoleTextAttribute(hStdOut, FOREGROUND_RED);
                errorsCount++;
            }

            cout << symbol;
        }

        SetConsoleTextAttribute(hStdOut, 7);

        double correctPercent = (text.size() - double(errorsCount)) / double(text.size());

        cout << "\n\n������� ������������: ";
        SetConsoleTextAttribute(hStdOut, correctPercent < 0.65 ? 12 : correctPercent < 0.85 ? 6 : 10);
        cout << correctPercent * 100 << "%\n\n";
        SetConsoleTextAttribute(hStdOut, 7);
        cout << "���������� ������: " << errorsCount;
        AppendDataToFile("statistics.txt", "������� ������������: " + to_string(correctPercent * 100) 
            + " ���������� ������: " + to_string(errorsCount) + "\n");
        cout << "\n\n���������� ��������!\n1 - ��������� ����������\n0 - ��������� � ������� ����\n������� ��� �����: ";
        input_correctly_number(menu);
        Limitations(0, 1, menu);

    } while (menu != 0);

}

void PrintStatistics()
{
    system("cls");
    cout << "���������� �����������: \n" << GetDataFromFile("statistics.txt") << "\n\n��� ������ ������� �� ����� �������\n";
    _getch();
}

int main()
{
    setlocale(LC_ALL, "RUS");
    try
    {
        int menu = 0;
        do
        {
            system("cls");
            cout << "1 - ������ ����������\n2 - ���������� ���������� �����������\n0 - �����\n������� ��� �����: ";
            input_correctly_number(menu);
            Limitations(0, 2, menu);

            if (menu == 1)
            {
                StartTraining(); 
            }
            else if (menu == 2)
            {
                PrintStatistics();
            }

        } while (menu != 0);
    }
    catch (exception ex)
    {
        cout << ex.what();
    }

}

