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
    bool result = isValidOperand(token, 0, errors);
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

    // Test 7 Ошибка только в начале: * A B + >
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
    QTest::newRow("Single operator token") << "!" << "INVALID_TOKEN 0 !\nNOT_ENOUGH_ARGUMENTS_FOR_UNARY_OPERATOR" << singleOperatorTree;
    QTest::newRow("Single operand token") << "4" << "NOT_ENOUGH_OPERATORS" << singleOperandTree;
    QTest::newRow("Basic test") << "7 5 >" << "" << basicTree;
    QTest::newRow("Only variables") << "A B C" << "NOT_ENOUGH_OPERATORS" << varTree;
    QTest::newRow("Only operators") << "+ !" << "INVALID_TOKEN 0 +\nNOT_ENOUGH_ARGUMENTS" << opTree;
    QTest::newRow("Error at start") << "* A B + >" << "INVALID_TOKEN 0 *\nNOT_ENOUGH_ARGUMENTS" << errorStartTree;
    QTest::newRow("Error at end") << "A B + > *" << "INVALID_TOKEN 2 +\nINVALID_TOKEN 3 >\nNOT_ENOUGH_ARGUMENTS" << errorEndTree;
    QTest::newRow("Negation of variable") << "5 !" << "INVALID_TOKEN 1 !\nINCORRECT_USE_OF_NEGATION" << negTree;
    QTest::newRow("Complex expression") << "3 10 * 1 + 51 <=" << "" << complexTree;
    QTest::newRow("Insufficient operators") << "A B C <" << "INVALID_TOKEN 3 <\nNOT_ENOUGH_OPERATORS" << insufficientOpTree;
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

void Tests::testTreeToString()
{
    QFETCH(TreeNode*, root);
    QFETCH(QString, expected);

    QList<Error> errors;
    QString result = treeToString(root, errors);
    QCOMPARE(result, expected);
}

void Tests::testTreeToString_data()
{
    QTest::addColumn<TreeNode*>("root");
    QTest::addColumn<QString>("expected");

    // Test 1: Проверка пустого узла
    QTest::newRow("empty_node") << static_cast<TreeNode*>(nullptr) << "EMPTY_NODE";

    // Test 2: Проверка узла без потомков
    TreeNode* node2 = new TreeNode("<", TreeNodeType::OPER_LESS_THAN);
    QTest::newRow("node_without_children") << node2 << "<";

    // Test 3: Проверка простого бинарного дерева
    TreeNode* node3 = new TreeNode("<", TreeNodeType::OPER_LESS_THAN);
    node3->left = new TreeNode("3", TreeNodeType::VALUE);
    node3->right = new TreeNode("4", TreeNodeType::VALUE);
    QTest::newRow("simple_binary_tree") << node3 << "3 < 4";

    // Test 4: Проверка дерева с унарным оператором
    TreeNode* unaryNode4 = new TreeNode("!", TreeNodeType::OPER_UNARY);
    unaryNode4->right = new TreeNode("x", TreeNodeType::VALUE);
    QTest::newRow("unary_operator_tree") << unaryNode4 << "! x";

    // Test 5: Проверка сложного дерева
    TreeNode* node5 = new TreeNode(">=", TreeNodeType::OPER_GREATER_OR_EQUAL);
    node5->left = new TreeNode("*", TreeNodeType::OPER_MULTIPLICATION);
    node5->left->left = new TreeNode("+", TreeNodeType::OPER_PLUS);
    node5->left->left->left = new TreeNode("1", TreeNodeType::VALUE);
    node5->left->left->right = new TreeNode("2", TreeNodeType::VALUE);
    node5->left->right = new TreeNode("3", TreeNodeType::VALUE);
    node5->right = new TreeNode("0", TreeNodeType::VALUE);
    QTest::newRow("complex_tree") << node5 << "(1 + 2) * 3 >= 0";

    // Test 6: Проверка дерева с унарным и бинарным операторами
    TreeNode* unaryNode6 = new TreeNode("!", TreeNodeType::OPER_UNARY);
    unaryNode6->right = new TreeNode("<", TreeNodeType::OPER_LESS_THAN);
    unaryNode6->right->left = new TreeNode("x", TreeNodeType::VALUE);
    unaryNode6->right->right = new TreeNode("y", TreeNodeType::VALUE);
    QTest::newRow("unary_and_binary_operators_tree") << unaryNode6 << "! (x < y)";

    // Test 7: Проверка дерева с вложенными операторами
    TreeNode* node7 = new TreeNode(">", TreeNodeType::OPER_GREATER_THAN);
    node7->left = new TreeNode("+", TreeNodeType::OPER_PLUS);
    node7->left->left = new TreeNode("*", TreeNodeType::OPER_MULTIPLICATION);
    node7->left->left->left = new TreeNode("2", TreeNodeType::VALUE);
    node7->left->left->right = new TreeNode("3", TreeNodeType::VALUE);
    node7->left->right = new TreeNode("1", TreeNodeType::VALUE);
    node7->right = new TreeNode("0", TreeNodeType::VALUE);
    QTest::newRow("nested_operators_tree") << node7 << "2 * 3 + 1 > 0";

    // Test 8: Проверка дерева с несколькими уровнями вложенности
    TreeNode* node8 = new TreeNode("<", TreeNodeType::OPER_LESS_THAN);
    node8->left = new TreeNode("+", TreeNodeType::OPER_PLUS);
    node8->left->left = new TreeNode("1", TreeNodeType::VALUE);
    node8->left->right = new TreeNode("2", TreeNodeType::VALUE);
    node8->right = new TreeNode("*", TreeNodeType::OPER_MULTIPLICATION);
    node8->right->left = new TreeNode("3", TreeNodeType::VALUE);
    node8->right->right = new TreeNode("4", TreeNodeType::VALUE);
    QTest::newRow("multiple_levels_tree") << node8 << "1 + 2 < 3 * 4";

    // Test 9: Проверка дерева с вложенными скобками
    TreeNode* node9 = new TreeNode(">", TreeNodeType::OPER_GREATER_THAN);
    node9->left = new TreeNode("-", TreeNodeType::OPER_MINUS);
    node9->left->left = new TreeNode("*", TreeNodeType::OPER_MULTIPLICATION);
    node9->left->left->left = new TreeNode("+", TreeNodeType::OPER_PLUS);
    node9->left->left->left->left = new TreeNode("2", TreeNodeType::VALUE);
    node9->left->left->left->right = new TreeNode("5", TreeNodeType::VALUE);
    node9->left->left->right = new TreeNode("3", TreeNodeType::VALUE);
    node9->left->right = new TreeNode("11", TreeNodeType::VALUE);
    node9->right = new TreeNode("9", TreeNodeType::VALUE);
    QTest::newRow("nested_parentheses_tree") << node9 << "(2 + 5) * 3 - 11 > 9";
}

// Тесты для функции ConvertToLess
void Tests::testConvertToLess()
{
    QFETCH(TreeNode*, root);
    QFETCH(TreeNode*, expected);

    QList<Error> errors;
    convertToLess(root, errors);

    // Сравниваем полученное дерево с ожидаемым
    QVERIFY(compareNodes(root, expected));
}

void Tests::testConvertToLess_data()
{
    QTest::addColumn<TreeNode*>("root");
    QTest::addColumn<TreeNode*>("expected");

    // Test 1: Преобразование оператора >
    TreeNode* node1 = new TreeNode("31", TreeNodeType::VALUE);
    TreeNode* node2 = new TreeNode("15", TreeNodeType::VALUE);
    TreeNode* node3 = new TreeNode(">", TreeNodeType::OPER_GREATER_THAN, node1, node2);
    TreeNode* expected1 = new TreeNode("<", TreeNodeType::OPER_LESS_THAN, node2, node1);
    QTest::newRow("greater_than") << node3 << expected1;

    // Test 2: Преобразование оператора >=
    node1 = new TreeNode("15", TreeNodeType::VALUE);
    node2 = new TreeNode("10", TreeNodeType::VALUE);
    node3 = new TreeNode(">=", TreeNodeType::OPER_GREATER_OR_EQUAL, node1, node2);
    TreeNode* negateNode2 = new TreeNode("!", TreeNodeType::OPER_NEGATION, nullptr, node3);
    QTest::newRow("greater_or_equal") << node3 << negateNode2;

    // Test 3: Преобразование оператора <=
    node1 = new TreeNode("10", TreeNodeType::VALUE);
    node2 = new TreeNode("16", TreeNodeType::VALUE);
    node3 = new TreeNode("<=", TreeNodeType::OPER_LESS_OR_EQUAL,node2 , node1);
    TreeNode* negateNode3 = new TreeNode("!", TreeNodeType::OPER_NEGATION, nullptr, node3);
    QTest::newRow("less_or_equal") << node3 << negateNode3;

    // Test 4: Отсутствие операторов сравнения
    TreeNode* node4 = new TreeNode("+", TreeNodeType::OPER_PLUS);
    QTest::newRow("no_comparison_operator") << node4 << node4;

    // Test 5: Пустой узел
    QTest::newRow("empty_node") << static_cast<TreeNode*>(nullptr) << static_cast<TreeNode*>(nullptr);

    // Test 6: Узел без детей
    TreeNode* node6 = new TreeNode("<", TreeNodeType::OPER_LESS_THAN);
    QTest::newRow("node_without_children") << node6 << node6;

    // Test 7: Преобразование сложного дерева с ">"
    node1 = new TreeNode("15", TreeNodeType::VALUE);
    node2 = new TreeNode("1", TreeNodeType::VALUE);
    TreeNode* node7_left = new TreeNode("*", TreeNodeType::OPER_MULTIPLICATION, new TreeNode("3", TreeNodeType::VALUE), new TreeNode("10", TreeNodeType::VALUE));
    TreeNode* expected7_left = new TreeNode("+", TreeNodeType::OPER_PLUS, node7_left , node2);
    TreeNode* node7 = new TreeNode(">", TreeNodeType::OPER_GREATER_THAN, expected7_left, node1);
    TreeNode* expected7 = new TreeNode("<", TreeNodeType::OPER_LESS_THAN, node1, expected7_left);
    QTest::newRow("complex_greater_than") << node7 << expected7;

    // Test 8: Преобразование сложного дерева с ">="
    node1 = new TreeNode("15", TreeNodeType::VALUE);
    node2 = new TreeNode("1", TreeNodeType::VALUE);
    TreeNode* node8_left = new TreeNode("*", TreeNodeType::OPER_MULTIPLICATION, new TreeNode("3", TreeNodeType::VALUE), new TreeNode("10", TreeNodeType::VALUE));
    TreeNode* node8 = new TreeNode(">=", TreeNodeType::OPER_GREATER_OR_EQUAL, node8_left, node1);
    TreeNode* negateNode8 = new TreeNode("!", TreeNodeType::OPER_NEGATION, nullptr, node8);
    QTest::newRow("complex_greater_or_equal") << node8 << negateNode8;

    // Test 9: Преобразование сложного дерева с "<="
    node1 = new TreeNode("51", TreeNodeType::VALUE);
    node2 = new TreeNode("1", TreeNodeType::VALUE);
    TreeNode* node9_left = new TreeNode("*", TreeNodeType::OPER_MULTIPLICATION, new TreeNode("3", TreeNodeType::VALUE), new TreeNode("10", TreeNodeType::VALUE));
    TreeNode* node9 = new TreeNode("<=", TreeNodeType::OPER_LESS_OR_EQUAL, node9_left, node1);
    TreeNode* negateNode9 = new TreeNode("!", TreeNodeType::OPER_NEGATION, nullptr, node9);
    QTest::newRow("complex_less_or_equal") << node9 << negateNode9;

    // Test 10: Отсутствие оператора сравнения в глубоком дереве
    node1 = new TreeNode("*", TreeNodeType::OPER_MULTIPLICATION, new TreeNode("10", TreeNodeType::VALUE), new TreeNode("3", TreeNodeType::VALUE));
    node2 = new TreeNode("+", TreeNodeType::OPER_PLUS, new TreeNode("1", TreeNodeType::VALUE), node1);
    QTest::newRow("no_comparison_operator_deep") << node2 << node2;

    // Test 11: Несколько операций сравнения
    node1 = new TreeNode(">=", TreeNodeType::OPER_GREATER_OR_EQUAL, new TreeNode("10", TreeNodeType::VALUE), new TreeNode(">", TreeNodeType::OPER_GREATER_THAN, new TreeNode("3", TreeNodeType::VALUE), new TreeNode("*", TreeNodeType::OPER_MULTIPLICATION, new TreeNode("3", TreeNodeType::VALUE), new TreeNode("4", TreeNodeType::VALUE))));
    TreeNode* negateNode11 = new TreeNode("!", TreeNodeType::OPER_NEGATION, nullptr, node1);
    QTest::newRow("multiple_comparison_operators") << node1 << negateNode11;
}

// Функция для сравнения узлов TreeNode
bool Tests::compareNodes(TreeNode* node1, TreeNode* node2) {
    if (!node1 && !node2) {
        return true; // Оба дерева пусты
    } else if (!node1 || !node2) {
        return false; // Одно из деревьев пустое, другое нет
    } else if (node1->value != node2->value || node1->type != node2->type) {
        return false; // Значения или типы узлов не совпадают
    } else {
        // Рекурсивно сравниваем левые и правые поддеревья
        bool leftEqual = compareNodes(node1->left, node2->left);
        bool rightEqual = compareNodes(node1->right, node2->right);
        return leftEqual && rightEqual;
    }
}

