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

    return a.exec();
}
