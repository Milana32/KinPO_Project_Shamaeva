#include "Tree.h"
/*!
* \brief Статический метод для определения типа оператора на основе токена.
* \param token Токен оператора.
* \return Тип оператора в виде значения TreeNodeType.
*/
TreeNodeType TreeNode::getOperatorType(const QString& token) {
    if (token == ">")
        return TreeNodeType::OPER_GREATER_THAN;
    else if (token == ">=")
        return TreeNodeType::OPER_GREATER_OR_EQUAL;
    else if (token == "<")
        return TreeNodeType::OPER_LESS_THAN;
    else if (token == "<=")
        return TreeNodeType::OPER_LESS_OR_EQUAL;
    else if (token == "+")
        return TreeNodeType::OPER_PLUS;
    else if (token == "-")
        return TreeNodeType::OPER_MINUS;
    else if (token == "*")
        return TreeNodeType::OPER_MULTIPLICATION;
    else if (token == "/")
        return TreeNodeType::OPER_DIVISION;
    else if (token == "%")
        return TreeNodeType::OPER_REMAINDER_OF_DIVISION;
    else if (token == "!")
        return TreeNodeType::OPER_NEGATION;
    else if (token == "_-")
        return TreeNodeType::OPER_UNARY_MINUS;
    else if (token == "_+")
        return TreeNodeType::OPER_UNARY_PLUS;
    else
        return TreeNodeType::OPER_BINARY; // По умолчанию считаем бинарным оператором
}
