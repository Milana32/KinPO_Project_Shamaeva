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

// Тесты для функции buildLogicalTree
void Tests::testbuildLogicalTree()
{
    QFETCH(QString, inequality);
    QFETCH(QString, expectedErrorMessage);
    QFETCH(TreeNode*, expectedTree);

    QList<Error> errors;
    TreeNode* result = buildLogicalTree(inequality, errors);

    if (!expectedErrorMessage.isEmpty()) {
        QVERIFY2(result == nullptr, "Expected nullptr for error cases");
        QString errorStr;
        for (const auto& error : errors) {
            errorStr += ErrorToString(error) + "\n";
        }
        errorStr = errorStr.trimmed();
        QCOMPARE(errorStr, expectedErrorMessage);
    } else {
        QVERIFY2(result != nullptr, "Expected non-null result for valid inequality");
        QVERIFY(compareTrees(result, expectedTree));
    }
}

void Tests::testbuildLogicalTree_data()
{
    QTest::addColumn<QString>("inequality");
    QTest::addColumn<QString>("expectedErrorMessage");
    QTest::addColumn<TreeNode*>("expectedTree");

    // Test 1
    TreeNode* emptyTree = nullptr;
    // Test 2
    TreeNode* singleOperatorTree = nullptr;
    // Test 3
    TreeNode* singleOperandTree = nullptr;

    // Test 4 Базовый тест: 7 5 >
    TreeNode* basicLeft = new TreeNode("7", TreeNodeType::VALUE);
    TreeNode* basicRight = new TreeNode("5", TreeNodeType::VALUE);
    TreeNode* basicTree = new TreeNode(">", TreeNodeType::OPER_GREATER_THAN, basicLeft, basicRight);

    // Test 5 Только переменные: A B C
    TreeNode* varTree = nullptr;

    // Test 6 Только операторы: + !
    TreeNode* opTree = nullptr;

    // Test 7 Ошибка только в начале: \ A B + >
    TreeNode* errorStartTree = nullptr;

    // Test 8 Ошибка только в конце: A B + > *
    TreeNode* errorEndTree = nullptr;

    // Test 9 Отрицание переменной: 5 !
    TreeNode* negLeft = new TreeNode("5", TreeNodeType::VALUE);
    TreeNode* negTree = new TreeNode("!", TreeNodeType::OPER_NEGATION, negLeft, nullptr);

    // Test 10 Пример сложного дерева: 3 10 * 1 + 51 <=
    TreeNode* complexLeft1 = new TreeNode("3", TreeNodeType::VALUE);
    TreeNode* complexRight1 = new TreeNode("10", TreeNodeType::VALUE);
    TreeNode* complexNode1 = new TreeNode("*", TreeNodeType::OPER_MULTIPLICATION, complexLeft1, complexRight1);
    TreeNode* complexRight2 = new TreeNode("1", TreeNodeType::VALUE);
    TreeNode* complexNode2 = new TreeNode("+", TreeNodeType::OPER_PLUS, complexNode1, complexRight2);
    TreeNode* complexRight3 = new TreeNode("51", TreeNodeType::VALUE);
    TreeNode* complexTree = new TreeNode("<=", TreeNodeType::OPER_LESS_OR_EQUAL, complexNode2, complexRight3);

    // Test 11 Недостаток операторов: A B C <
    TreeNode* insufficientOpTree = nullptr;

    // Тесты
    QTest::newRow("Empty string") << "" << "EMPTY_STRING" << emptyTree;
    QTest::newRow("Single operator token") << "!" << "INVALID_TOKEN\nNOT_ENOUGH_ARGUMENTS_FOR_UNARY_OPERATOR" << singleOperatorTree;
    QTest::newRow("Single operand token") << "4" << "NOT_ENOUGH_OPERATORS" << singleOperandTree;
    QTest::newRow("Basic test") << "7 5 >" << "" << basicTree;
    QTest::newRow("Only variables") << "A B C" << "NOT_ENOUGH_OPERATORS" << varTree;
    QTest::newRow("Only operators") << "+ !" << "INVALID_TOKEN\nNOT_ENOUGH_ARGUMENTS" << opTree;
    QTest::newRow("Error at start") << "\ A B + >" << "INVALID_TOKEN\nINVALID_TOKEN\nNOT_ENOUGH_ARGUMENTS" << errorStartTree;
    QTest::newRow("Error at end") << "A B + > *" << "INVALID_TOKEN\nINVALID_TOKEN\nNOT_ENOUGH_ARGUMENTS" << errorEndTree;
    QTest::newRow("Negation of variable") << "5 !" << "INVALID_TOKEN\nINCORRECT_USE_OF_NEGATION" << negTree;
    QTest::newRow("Complex expression") << "3 10 * 1 + 51 <=" << "" << complexTree;
    QTest::newRow("Insufficient operators") << "A B C <" << "INVALID_TOKEN\nNOT_ENOUGH_OPERATORS" << insufficientOpTree;
}

bool Tests::compareTrees(TreeNode* tree1, TreeNode* tree2)
{
    if (tree1 == nullptr && tree2 == nullptr)
        return true;
    if (tree1 == nullptr || tree2 == nullptr)
        return false;
    if (tree1->value != tree2->value || tree1->type != tree2->type)
        return false;
    return compareTrees(tree1->left, tree2->left) && compareTrees(tree1->right, tree2->right);
}


