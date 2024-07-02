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
    //runTests();
    //QCoreApplication a(argc, argv);

    if (argc != 3)
    {
        qDebug() << "Incorrect number of arguments";
        return -1;
    }

    QList<Error> errors;
    QString filePath = argv[1];
    QString outputPath = argv[2];

    // Проверяем существование файла
    QFile file(filePath);
    if (!file.exists())
    {
        errors.append(Error(ErrorType::FILE_NOT_FOUND, 0, filePath));
        qDebug() << "FILE_NOT_FOUND";
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

    QString original_expression = treeToString(logicalTree, errors);

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

    // Записываем результат в выходной файл
    QFile outputFile(outputPath);
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        errors.append(Error(ErrorType::FILE_NOT_OPENED, 0, outputPath));
        qDebug() << "FILE_NOT_OPENED";
        return -1;
    }

    QTextStream out(&outputFile);
    out << original_expression;
    out << "\n";
    out << result;
    outputFile.close();

    return 0;
}
