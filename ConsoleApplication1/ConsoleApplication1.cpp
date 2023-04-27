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
        cout << "Введено неверное значение. Повторите попытку: ";
    }
}

void Limitations(int min, int max, int& inputValue) 
{
    while (inputValue < min || inputValue > max) 
    {
        cout << "Введенное число не соответствует промежутку. Повторите ввод: ";
        input_correctly_number(inputValue);
    }
}

string GetDataFromFile(string filename)
{
    string text, tmp;
    ifstream in(filename);

    if (!in.is_open())
    {
        throw exception("Ошибка при открытии файла!");
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
        throw exception("Ошибка при открытии файла!");
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
        cout << "Введите путь к файлу, в котором расположен текст: ";
        cin >> filename;
        text = GetDataFromFile(filename);

        cout << text << "\n\n\nМожете начинать печатать: ";

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

        cout << "\n\nПроцент правильности: ";
        SetConsoleTextAttribute(hStdOut, correctPercent < 0.65 ? 12 : correctPercent < 0.85 ? 6 : 10);
        cout << correctPercent * 100 << "%\n\n";
        SetConsoleTextAttribute(hStdOut, 7);
        cout << "Количество ошибок: " << errorsCount;
        AppendDataToFile("statistics.txt", "Процент правильности: " + to_string(correctPercent * 100) 
            + " Количество ошибок: " + to_string(errorsCount) + "\n");
        cout << "\n\nТренировка окончена!\n1 - Повторить тренировку\n0 - Вернуться в главное меню\nВведите ваш выбор: ";
        input_correctly_number(menu);
        Limitations(0, 1, menu);

    } while (menu != 0);

}

void PrintStatistics()
{
    system("cls");
    cout << "Статистика результатов: \n" << GetDataFromFile("statistics.txt") << "\n\nДля выхода нажмите на любую клавишу\n";
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
            cout << "1 - Начать тренировку\n2 - Посмотреть статистику результатов\n0 - Выйти\nВведите ваш выбор: ";
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

