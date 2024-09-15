#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>
#include <clocale>

// СОЗДАНИЕ НАЧАЛЬНЫХ СЕГМЕНТОВ ИЗ ВХОДНОГО ФАЙЛА
void createInitialRuns(const std::string& input_file, int runSize)
{
    std::ifstream input(input_file);    // Открываем входной файл для чтения
    std::vector<int> buffer(runSize);    // Создаем буфер для хранения чисел

    std::string filename;   // Имя файла для записи сегмента
    int runNo = 0;    // Счетчик номера сегмента

    while (!input.eof())    // Читаем числа из файла
    {
        int count = 0;
        for (; count < runSize && input >> buffer[count]; ++count);

        if (count == 0)
            break;

        std::sort(buffer.begin(), buffer.begin() + count);  // Сортируем числа в буфере

        filename = "run" + std::to_string(runNo++) + ".txt";  // Генерируем имя файла
        std::ofstream outfile(filename);   // Открываем файл для записи
        for (int i = 0; i < count; i++)
        {
            outfile << buffer[i] << " ";    // Записываем отсортированные числа
        }
        outfile.close();     // Закрываем файл
    }
    input.close();        // Закрываем входной файл
}

// ОБЪЕДИНЕНИЕ ФАЙЛОВ СЕГМЕНТОВ
void mergeFiles(const std::string& output_file, const std::vector<std::string>& runFiles)
{
    std::vector<std::ifstream> files(runFiles.size());    // Открываем файлы сегментов
    std::vector<int> current(runFiles.size(), INT_MAX); // Храним текущие значения из каждого сегмента

    for (int i = 0; i < runFiles.size(); ++i)
    {
        files[i].open(runFiles[i]); // Открываем файл сегмента
        if (files[i] >> current[i])
        {
            // Успешно прочитан первый элемент
        }
        else
        {
            current[i] = INT_MAX;   // Помечаем файл как пустой
        }
    }

    std::ofstream output(output_file);    // Открываем выходной файл
    while (true)
    {
        int minIndex = -1;
        for (int i = 0; i < current.size(); ++i)
        {
            if (current[i] != INT_MAX && (minIndex == -1 || current[i] < current[minIndex]))
            {
                minIndex = i;     // Находим минимальное значение
            }
        }

        if (minIndex == -1) break;  // Все файлы исчерпаны

        output << current[minIndex] << " ";  // Записываем минимальное значение
        if (!(files[minIndex] >> current[minIndex]))
        {
            current[minIndex] = INT_MAX;  // Этот файл исчерпан
        }
    }

    for (auto& file : files)
    {
        file.close();  // Закрываем файлы сегментов
    }
    output.close();  // Закрываем выходной файл
}

int main()
{
    std::setlocale(LC_ALL, "Russian");
    std::string input_file = "input.txt";
    int runSize = 10;

    createInitialRuns(input_file, runSize);

    std::vector<std::string> runFiles = {"run0.txt", "run1.txt", "run2.txt"};
    mergeFiles("sorted_output.txt", runFiles);

    std::cout << "Внешняя сортировка завершена. Отсортированные данные находятся в sorted_output.txt" << std::endl;
    return 0;
}
