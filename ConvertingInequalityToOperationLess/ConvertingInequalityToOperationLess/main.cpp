/*!
 * \file
 * \brief Главная функция программы convertingInequalityToLess.
 *
 * Этот файл содержит главную функцию программы для преобразования операций сравнения
 * «>», «>=», «<=» к операции «<».
 *
 * \mainpage Документация для программы "Converting inequality to operation “less” (convertingInequalityToLess)"
 * Программа предназначена для преобразования операций сравнения «>», «>=», «<=» к операции «<».
 * Для функционирования программы необходима операционная система Windows 7 или выше.
 * Программа разработана на языке С++ с использованием стандартных библиотек C++, библиотеки Qt и фреймворка Qt Creator.
 * Программа должна получать два параметра командной строки: имя входного файла с деревом разбора выражений,
 * имя файла для записи результата.
 *
 * Пример команды запуска программы:
 * \code
 * ./convertingInequalityToLess.exe ./input.txt ./output.txt
 * \endcode
 *
 * \author Shamaeva Milana
 * \date June 2024
 * \version 1.0
 */
#include <QCoreApplication>
#include <QDebug>
#include <QString>
#include <QList>
#include <QFile>
#include <QTextStream>
#include <iostream> // Для использования std::cin

#include "Functions.h"
#include "Error.h"
#include "Tree.h"
#include "Tests.h"

/*!
 * \brief Главная функция программы.
 * \param [in] argc Количество переданных аргументов командной строки.
 * \param [in] argv Массив аргументов командной строки.
 * \param [in] argv[0] Аргумент запуска программы.
 * \param [in] argv[1] Путь к файлу с логическим выражением (.txt).
 * \param [in] argv[2] Путь к выходному файлу (.txt) для сохранения результата.
 * \return 0, если программа завершилась успешно, -1 в случае ошибки.
 */

int main(int argc, char *argv[])
{
    runTests();
    QCoreApplication a(argc, argv);

    // Включить поддержку русских символов в консоли
    setlocale(LC_ALL, "Russian");

    // QList<Error> errors;
    // QString filePath;
    // QString outputPath;

    // // Вывод запроса на ввод пути к файлу
    // std::cout << "Input path to file (.txt): ";
    // std::flush(std::cout); // Сбрасываем буфер вывода, чтобы сообщение появилось сразу

    // // Считываем ввод с консоли
    // std::string tempPath;
    // std::getline(std::cin, tempPath);

    // // Преобразуем std::string в QString
    // filePath = QString::fromStdString(tempPath);

    // // Удаляем символы перевода строки или другие пробельные символы в конце строки, если они есть
    // filePath = filePath.trimmed();

    // // Проверяем существование файла
    // QFile file(filePath);
    // if (!file.exists())
    // {
    //     errors.append(Error(ErrorType::FILE_NOT_FOUND, 0, filePath));
    //     qDebug() << "FILE_NOT_FOUND: Файл по пути не найден";
    //     return -1;
    // }

    // if (argc != 3)
    // {
    //     qDebug() << "Неверное количество аргументов. Использование: ./convertingInequalityToLess.exe <input_file> <output_file>";
    //     return -1;
    // }

    QList<Error> errors;
    QString filePath = argv[1];
    QString outputPath = argv[2];

    // Проверяем существование файла
    QFile file(filePath);
    if (!file.exists())
    {
        errors.append(Error(ErrorType::FILE_NOT_FOUND, 0, filePath));
        qDebug() << "FILE_NOT_FOUND: Файл по пути не найден";
        return -1;
    }

    // Получение строк из файла
    QStringList fileContent = getStringsFromFile(filePath, errors);

    if (fileContent.isEmpty())
    {
        for (const Error& error : errors)
        {
            qDebug() << ErrorToString(error);
        }
        return -1;
    }

    QString inequality = fileContent.first();

    // Построение дерева логического выражения
    TreeNode* logicalTree = buildLogicalTree(inequality, errors);

    if (!logicalTree)
    {
        for (const Error& error : errors)
        {
            qDebug() << ErrorToString(error);
        }
        return -1;
    }

    QString inequality_result = treeToString(logicalTree, errors);

    // Преобразование операторов сравнения
    convertToLess(logicalTree, errors);

    // Преобразование дерева в строку
    QString result = treeToString(logicalTree, errors);

    if (result.isEmpty())
    {
        for (const Error& error : errors)
        {
            qDebug() << ErrorToString(error);
        }
        return -1;
    }

    qDebug() << "Исходное неравенство в инфиксной форме:" << inequality_result;
    qDebug() << "Полученное неравенство в инфиксной форме:" << result;

    // Вывод запроса на ввод пути к выходному файлу
    std::cout << "Input path to output file (.txt): ";
    std::flush(std::cout); // Сбрасываем буфер вывода, чтобы сообщение появилось сразу

    // Считываем ввод с консоли
    std::string tempOutputPath;
    std::getline(std::cin, tempOutputPath);

    // Преобразуем std::string в QString
    outputPath = QString::fromStdString(tempOutputPath);

    // Удаляем символы перевода строки или другие пробельные символы в конце строки, если они есть
    outputPath = outputPath.trimmed();

    // Записываем результат в выходной файл
    QFile outputFile(outputPath);
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        errors.append(Error(ErrorType::FILE_NOT_OPENED, 0, outputPath));
        qDebug() << "FILE_NOT_OPENED: Не удалось открыть файл для записи";
        return -1;
    }

    QTextStream out(&outputFile);
    out << result;
    outputFile.close();

    qDebug() << "Результат успешно записан в файл:" << outputPath;

    return 0;
}
