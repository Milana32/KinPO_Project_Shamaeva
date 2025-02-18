/*!
* \file
* \brief Данный файл является заголовочным файлом класса Tests для тестирования функций программы.
*/

#ifndef TESTS_H
#define TESTS_H

#include <QCoreApplication>
#include <QtTest/QtTest>
#include "functions.h"
#include "tree.h"

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

    void testisOperator();
    void testisOperator_data();

    void testisValidOperand();
    void testisValidOperand_data();

    void testbuildLogicalTree();
    void testbuildLogicalTree_data();

    void testConvertToLess();
    void testConvertToLess_data();

    void testTreeToString();
    void testTreeToString_data();

private:
    bool compareTrees(TreeNode* tree1, TreeNode* tree2);
    bool compareNodes(TreeNode* node1, TreeNode* node2);
};

#endif // TESTS_H
