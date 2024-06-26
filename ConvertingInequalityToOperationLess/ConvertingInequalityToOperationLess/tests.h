/*!
* \file
* \brief Данный файл является заголовочным файлом класса Tests для тестирования функций программы.
*/

#ifndef TESTS_H
#define TESTS_H

#include <QCoreApplication>
#include <QtTest/QtTest>
#include "functions.h"
#include "Tree.h"

/*!
 * \brief Запускает тестирование всех функций
 */
void runTests();

/*!
 * \brief Класс для тестирования функций
 */
class Tests : public QObject
{
    Q_OBJECT

private slots:


};

#endif // TESTS_H
