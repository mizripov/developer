#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#define CLEAR system("cls")
#define PAUSE system("pause")
using namespace std;

void new_record(fstream& file, const string path, const int& size)
{
    int value;
    file.open(path, fstream::binary | fstream::out | fstream::trunc);
    if (!file.is_open())
    {
        cout << "Файл " << path << " не найден...\n";
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            value = rand() % 100 - 50;
            file.write((char*)&value, sizeof(int));
        }
    }
    file.close();
}

void show_data(fstream& file, const string path)
{
    int value;
    file.open(path, fstream::binary | fstream::in);
    if (!file.is_open())
    {
        cout << "Файл " << path << " не найден...\n";
    }
    else
    {
        cout << "Данные из файла " << path << ":\n";
        while (file.read((char*)&value, sizeof(int)))
        {
            cout << value << " ";
        }
        cout << endl;
    }
    file.close();
}

void recursive(fstream& f1, fstream& f2)
{
    int temp;
    f1.read((char*)&temp, sizeof(int));
    if (f1)
    {
        recursive(f1, f2);
    }
    if ((temp != -858993460) && (temp >= 0))
    {
        f2.write((char*)&temp, sizeof(int));
    }
}

void over_write(fstream& f1, fstream& f2, const string path1, const string path2)
{
    f1.open(path1, ifstream::binary | fstream::in);
    if (f1.is_open())
    {
        f2.open(path2, fstream::binary | fstream::out);
        recursive(f1, f2);
        f2.close();
    }
    f1.close();
}

int main()
{
    setlocale(LC_ALL, "ru");
    srand((unsigned)time(NULL));
    fstream f1, f2;
    string path1 = "first.bin", path2 = "second.bin";
    int SIZE;
    SIZE = rand() % 30 + 10;
    cout << "Количество целых чисел для записи в бинарный файл: " << SIZE << endl;
    PAUSE;
    CLEAR;
    cout << "Сформирован бинарный файл " << path1 << " целых чисел в диапазоне от -50 до 50...\n\n";
    new_record(f1, path1, SIZE);
    PAUSE;
    CLEAR;
    show_data(f1, path1);
    PAUSE;
    CLEAR;
    cout << "Целые числа (за исключением ОТРИЦАТЕЛЬНЫХ) переписываются в другой файл в обратном порядке...\n\n";
    over_write(f1, f2, path1, path2);
    PAUSE;
    CLEAR;
    cout << "Сформирован бинарный файл " << path2 << "...\n\n";
    PAUSE;
    CLEAR;
    show_data(f2, path2);
    show_data(f1, path1);
    PAUSE;
    return 0;
}