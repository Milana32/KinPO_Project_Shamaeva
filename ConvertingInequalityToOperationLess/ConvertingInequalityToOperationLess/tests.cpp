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

// Тесты для функции isOperator
void Tests::testisOperator()
{
    QFETCH(QString, token);
    QFETCH(bool, expected);

    QList<Error> errors;
    bool result = isOperator(token, errors);
    QCOMPARE(result, expected);
}

void Tests::testisOperator_data()
{
    QTest::addColumn<QString>("token");
    QTest::addColumn<bool>("expected");

    QTest::newRow("plus") << "+" << true;
    QTest::newRow("minus") << "-" << true;
    QTest::newRow("multiply") << "*" << true;
    QTest::newRow("division") << "/" << true;
    QTest::newRow("remainder of division") << "%" << true;
    QTest::newRow("greater than") << ">" << true;
    QTest::newRow("greater_or_equal") << ">=" << true;
    QTest::newRow("less_than") << "<" << true;
    QTest::newRow("less_or_equal") << "<=" << true;
    QTest::newRow("negation") << "!" << true;
    QTest::newRow("unary_plus") << "_-" << true;
    QTest::newRow("unary_minus") << "_+" << true;
    QTest::newRow("empty_row") << " " << false;
    QTest::newRow("space_operator") << " > " << false;
    QTest::newRow("unknown_character") << "&" << false;
    QTest::newRow("unknown_character") << "++" << false;
    QTest::newRow("unknown_character") << "--" << false;
    QTest::newRow("unknown_character") << "**" << false;
}
