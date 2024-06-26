/*!
 * \file
 * \brief Данный файл содержит реализацию функций класса Tests для тестирования функций программы formSentenceFromUD.
 */

#include "tests.h"

// Добавьте объявления Q_DECLARE_METATYPE
Q_DECLARE_METATYPE(TreeNode*)  // Объявление типа TreeNode* для использования в метаданных Qt
// Q_DECLARE_METATYPE(UnaryTreeNode*)  // Объявление типа UnaryTreeNode* для использования в метаданных Qt
Q_DECLARE_METATYPE(QList<Error>)  // Объявление типа QList<Error> для использования в метаданных Qt


void runTests()
{
    Tests tests;
    QTest::qExec(&tests);
}
