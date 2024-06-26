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

// Тесты для функции isValidOperand
void Tests::testisValidOperand()
{
    QFETCH(QString, token);
    QFETCH(bool, expected);

    QList<Error> errors;
    bool result = isValidOperand(token, errors);
    QCOMPARE(result, expected);
}

void Tests::testisValidOperand_data()
{

    QTest::addColumn<QString>("token");
    QTest::addColumn<bool>("expected");

    QTest::newRow("valid_operator") << "123" << true;
    QTest::newRow("valid_negative_number") << "-123" << true;
    QTest::newRow("minimum_number") << "-214747483647" << true;
    QTest::newRow("maximum_number") << "214747483647" << true;
    QTest::newRow("number_out_of_range") << "214747483648" << false;
    QTest::newRow("negative_number_out_of_range") << "-214747483648" << false;
    QTest::newRow("variable_name_with_latin_letters") << "varName" << true;
    QTest::newRow("valid_variable_with_number") << "var123" << true;
    QTest::newRow("variable_name_with_underscore") << "var_name" << true;
    QTest::newRow("invalid_variable_starting_with_number") << "1var" << false;
    QTest::newRow("variable_name_with_a_length_of_20_characters") << "variableName20Chars" << true;
    QTest::newRow("variable_name_longer_than_20_characters") << "variableNameIsTooLong" << false;
    QTest::newRow("empty_string") << QString("") << false;
    QTest::newRow("invalid_variable_with_special_char") << "var@123" << false;
    QTest::newRow("string_with_spaces") << "var name" << false;
    QTest::newRow("string_with_only_numbers") << "1234567890" << true;
    QTest::newRow("string_with_special_characters") << "var$name" << false;
    QTest::newRow("string_with_uppercase") << "VARNAME" << true;
    QTest::newRow("string_in_mixed_case") << "VarName" << true;
}


