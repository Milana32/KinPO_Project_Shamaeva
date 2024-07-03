/*!
 * \file
 * \brief Заголовочный файл, содержащий определения структур TreeNode и UnaryTreeNode.
 */

#ifndef TREE_H
#define TREE_H

#include <QString>
#include <QList>

/*!
 * \brief Перечисление типов узлов дерева.
 */
enum class TreeNodeType {
    VAR,                     /*!< Переменная */
    VALUE,                   /*!< Значение */
    OPER_PLUS,               /*!< Оператор сложения */
    OPER_MINUS,              /*!< Оператор вычитания */
    OPER_LESS_THAN,          /*!< Оператор меньше */
    OPER_LESS_OR_EQUAL,      /*!< Оператор меньше или равно */
    OPER_GREATER_THAN,       /*!< Оператор больше */
    OPER_GREATER_OR_EQUAL,   /*!< Оператор больше или равно */
    OPER_MULTIPLICATION,     /*!< Оператор умножения */
    OPER_DIVISION,           /*!< Оператор деления */
    OPER_NEGATION,           /*!< Оператор отрицания */
    OPER_REMAINDER_OF_DIVISION, /*!< Оператор остатка от деления */
    OPER_UNARY_MINUS,        /*!< Унарный минус */
    OPER_UNARY_PLUS,         /*!< Унарный плюс */
    OPER_UNARY,              /*!< Унарный оператор */
    OPER_BINARY              /*!< Бинарный оператор */
};

/*!
 * \brief Структура, представляющая узел дерева.
 */
struct TreeNode {
    QString value;          /*!< Значение узла */
    TreeNode* left;         /*!< Левый дочерний узел */
    TreeNode* right;        /*!< Правый дочерний узел */
    TreeNodeType type;      /*!< Тип узла */

    /*!
     * \brief Конструктор узла дерева.
     * \param val Значение узла.
     * \param t Тип узла.
     * \param l Левый дочерний узел.
     * \param r Правый дочерний узел.
     */
    TreeNode(const QString& val, TreeNodeType t, TreeNode* l = nullptr, TreeNode* r = nullptr)
        : value(val), left(l), right(r), type(t) {}

    /*!
* \brief Статический метод для определения типа оператора на основе токена.
*/
    static TreeNodeType getOperatorType(const QString& token);

    // Виртуальный деструктор
    virtual ~TreeNode() {}
    /*!
* \brief Перегрузка оператора ==
*/
    bool operator==(const TreeNode& other) const {
        return value == other.value && type == other.type &&
               ((left == nullptr && other.left == nullptr) || (left && other.left && *left == *other.left)) &&
               ((right == nullptr && other.right == nullptr) || (right && other.right && *right == *other.right));
    }
};

#endif // TREE_H
