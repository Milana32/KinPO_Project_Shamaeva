/*!
* \file
* \brief Данный файл содержит в себе реализацию функций, которые используются в ходе работы программы convertingInequalityToLess.
*/

#include "Functions.h"
#include <QFile>
#include <QTextStream>

// Функция для извлечения строк из файла
QStringList getStringsFromFile(const QString& filePath, QList<Error>& errors) {
    QStringList result;
    QFile file(filePath);

    // Проверка существования файла
    if (!file.exists()) {
        errors.append(Error(ErrorType::FILE_NOT_FOUND, 0, ""));
        return result; // Возвращаем пустой список, так как файла нет
    }

    // Попытка открыть файл для чтения
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        errors.append(Error(ErrorType::FILE_NOT_OPENED, 0, ""));
        return result; // Возвращаем пустой список, если файл не удалось открыть
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        result.append(in.readLine()); // Читаем строки из файла и добавляем в список
    }

    file.close(); // Закрываем файл после чтения

    // Проверяем, что в файле была только одна строка
    if (result.size() > 1) {
        errors.append(Error(ErrorType::MORE_THAN_ONE_STRING, 0, ""));
        return QStringList(); // Возвращаем пустой список, если в файле больше одной строки
    }

    return result; // Возвращаем список строк из файла (должен содержать одну строку)
}

// Функция для проверки, является ли токен оператором
bool isOperator(const QString& token, QList<Error>& errors) {
    // Список допустимых операторов
    QStringList operators = {">", ">=", "<", "<=", "+", "-", "*", "/", "%", "!", "_-", "_+"};
    // Проверяем, содержится ли токен в списке операторов
    return operators.contains(token);
}

// Функция для проверки, является ли токен операндом
bool isValidOperand(const QString& token, QList<Error>& errors) {
    // Проверяем, является ли токен пустым
    if (token.isEmpty()) {
        errors.append(Error(ErrorType::EMPTY_NODE, 0, token));
        return false;
    }

    bool isNumber;
    // Пробуем преобразовать токен в число
    qint64 number = token.toLongLong(&isNumber);

    if (isNumber) {
        // Проверяем, входит ли число в допустимый диапазон
        if (number >= -214747483647LL && number <= 214747483647LL) {
            return true;
        } else {
            // Если число выходит за границы, добавляем ошибку
            errors.append(Error(ErrorType::NUMBER_OUT_OF_RANGE, 0, token));
            return false;
        }
    } else {
        // Проверяем, соответствует ли токен формату переменной (буква в начале, далее буквы и цифры)
        if (token.length() <= 20 && token[0].isLetter() && token.mid(1).contains(QRegExp("^[A-Za-z0-9_]*$"))) {
            return true;
        } else {
            // Если токен не соответствует формату, добавляем ошибку
            errors.append(Error(ErrorType::INVALID_TOKEN, 0, token));
            return false;
        }
    }
}

// Функция для преобразования неравенства в дерево разбора выражегия
TreeNode* buildLogicalTree(const QString& inequality, QList<Error>& errors) {
    // Разделяем входную строку на токены, используя пробел в качестве разделителя.
    QStringList tokens = inequality.split(' ', QString::SkipEmptyParts);
    QList<TreeNode*> stack;
    int operandCount = 0; // Счетчик операндов

    // Если входная строка пустая, добавляем соответствующую ошибку и возвращаем nullptr.
    if (tokens.isEmpty()) {
        errors.append(Error(ErrorType::EMPTY_STRING, 0, ""));
        return nullptr;
    }

    // Проходим по каждому токену.
    for (int i = 0; i < tokens.size(); ++i) {
        const QString& token = tokens[i];

        // Если токен является допустимым операндом, добавляем его в стек.
        if (isValidOperand(token, errors)) {
            stack.append(new TreeNode(token, TreeNodeType::VALUE));
            ++operandCount;
        }
        // Если токен является оператором, обрабатываем его.
        else if (isOperator(token, errors)) {
            TreeNodeType operatorType = TreeNode::getOperatorType(token);
            TreeNode* node = new TreeNode(token, operatorType);

            // Обработка унарных операторов.
            if (token == "!" || token == "_-" || token == "_+") {
                // Проверка на наличие операндов для унарного оператора.
                if (stack.isEmpty()) {
                    errors.append(Error(ErrorType::NOT_ENOUGH_ARGUMENTS_FOR_UNARY_OPERATOR, i, ""));
                    return nullptr;
                }
                // Дополнительная проверка для корректного использования отрицания
                if (token == "!" && stack.size() < 2) {
                    errors.append(Error(ErrorType::INCORRECT_USE_OF_NEGATION, i, ""));
                    return nullptr;
                }
                node->right = stack.takeLast();
            }
            // Обработка бинарных операторов.
            else {
                // Проверка на наличие двух операндов для бинарного оператора.
                if (stack.size() < 2) {
                    errors.append(Error(ErrorType::NOT_ENOUGH_ARGUMENTS, i, ""));
                    return nullptr;
                }
                node->right = stack.takeLast();
                node->left = stack.takeLast();
            }
            stack.append(node);
        }
        // Если токен не является ни операндом, ни оператором, добавляем ошибку и возвращаем nullptr.
        else {
            errors.append(Error(ErrorType::UNKNOWN_CHARACTER, i, ""));
            return nullptr;
        }
    }

    // Проверка на корректность построенного дерева.
    if (operandCount == 1 || stack.size() != 1) {
        // Если количество операндов не равно 1 или в стеке больше одного узла, значит, есть ошибка.
        errors.append(Error(ErrorType::NOT_ENOUGH_OPERATORS, tokens.size(), ""));
        return nullptr;
    }

    // Возвращаем построенное дерево.
    return stack.takeFirst();
}


// Функция для преобразования неравенства к операции "меньше"
void convertToLess(TreeNode*& root, QList<Error>& errors) {
    if (root==nullptr) {
        // Если корневой узел пуст, добавляем ошибку в список и возвращаемся
        errors.append(Error(ErrorType::EMPTY_NODE, 0, ""));
        return;
    }

    if (root->type == TreeNodeType::VALUE) {
        // Если узел является операндом(значением), а не оператором, добавляем ошибку
        errors.append(Error(ErrorType::COMPARISON_OPERATOR_NOT_FOUND, 0, ""));
        return;
    }

    if (root->type == TreeNodeType::OPER_GREATER_THAN) {
        // Преобразуем оператор > в <
        root->value = "<";
        root->type = TreeNodeType::OPER_LESS_THAN;
        // Меняем местами левый и правый дочерние узлы
        TreeNode* temp = root->left;
        root->left = root->right;
        root->right = temp;
    }
    else if (root->type == TreeNodeType::OPER_GREATER_OR_EQUAL) {
        // Преобразуем оператор >= в < и добавляем отрицание
        root->value = "<";
        root->type = TreeNodeType::OPER_LESS_THAN;
        // Создаем новый узел для отрицания и устанавливаем его правым дочерним узлом текущего узла
        TreeNode* negateNode = new TreeNode("!", TreeNodeType::OPER_NEGATION, nullptr, root);
        root = negateNode;
    } else if (root->type == TreeNodeType::OPER_LESS_OR_EQUAL) {
        // Преобразуем оператор <= в < и добавляем отрицание
        root->value = "<";
        root->type = TreeNodeType::OPER_LESS_THAN;
        // Меняем местами левый и правый дочерние узлы
        TreeNode* temp = root->left;
        root->left = root->right;
        root->right = temp;
        // Создаем новый узел для отрицания и устанавливаем его правым дочерним узлом текущего узла
        TreeNode* negateNode = new TreeNode("!", TreeNodeType::OPER_NEGATION, nullptr, root);
        root = negateNode;
    }

    // Рекурсивно обрабатываем левый и правый дочерние узлы
    convertToLess(root->left, errors);
    convertToLess(root->right, errors);
}
























// // Функция для преобразования неравенства к операции "меньше"
// void convertToLess(TreeNode*& root, QList<Error>& errors) {
//     if (!root) {
//         // Если текущий узел пустой, добавляем ошибку и возвращаемся
//         errors.append(Error(ErrorType::EMPTY_NODE, 0, ""));
//         return;
//     }

//     if (root->type == TreeNodeType::VALUE) {
//         // Если текущий узел является значением, а не оператором, добавляем ошибку и возвращаемся
//         errors.append(Error(ErrorType::COMPARISON_OPERATOR_NOT_FOUND, 0, ""));
//         return;
//     }

//     if (root->value == ">") {
//         // Если узел содержит оператор ">", меняем его на "<"
//         root->value = "<";
//         root->type = TreeNodeType::OPER_LESS_THAN;
//         // Меняем местами левое и правое поддерево
//         TreeNode* temp = root->left;
//         root->left = root->right;
//         root->right = temp;
//     } else if (root->value == ">=") {
//         // Если узел содержит оператор ">=", меняем его на "<"
//         root->value = "<";
//         root->type = TreeNodeType::OPER_LESS_THAN;
//         // Создаем новый узел унарного отрицания
//         UnaryTreeNode* negateNode = new UnaryTreeNode("!");
//         // Правым потомком унарного узла становится текущий узел
//         negateNode->right = root;
//         // Корнем дерева становится унарный узел
//         root = negateNode;
//     } else if (root->value == "<=") {
//         // Если узел содержит оператор "<=", меняем его на "<"
//         root->value = "<";
//         root->type = TreeNodeType::OPER_LESS_THAN;
//         // Меняем местами левое и правое поддерево
//         TreeNode* temp = root->left;
//         root->left = root->right;
//         root->right = temp;
//         // Создаем новый узел унарного отрицания
//         UnaryTreeNode* negateNode = new UnaryTreeNode("!");
//         // Правым потомком унарного узла становится текущий узел
//         negateNode->right = root;
//         // Корнем дерева становится унарный узел
//         root = negateNode;
//     }

//     // Рекурсивно обрабатываем левое и правое поддеревья
//     convertToLess(root->left, errors);
//     convertToLess(root->right, errors);
// }



//C:\Users\shama\Desktop\inequality.txt


// void convertToLess(TreeNode*& root, QList<Error>& errors) {
//     if (!root) {
//         // Если корневой узел пуст, добавляем ошибку в список и возвращаемся
//         errors.append(Error(ErrorType::EMPTY_NODE, 0, ""));
//         return;
//     }

//     if (root->type == TreeNodeType::VALUE) {
//         // Если узел является операндом(значением), а не оператором, добавляем ошибку
//         errors.append(Error(ErrorType::COMPARISON_OPERATOR_NOT_FOUND, 0, ""));
//         return;
//     }

//     if (root->type == TreeNodeType::OPER_GREATER_THAN) {
//         // Преобразуем оператор > в <
//         root->value = "<";
//         root->type = TreeNodeType::OPER_LESS_THAN;
//         // Меняем местами левый и правый дочерние узлы
//         TreeNode* temp = root->left;
//         root->left = root->right;
//         root->right = temp;
//     }
//     else if (root->type == TreeNodeType::OPER_GREATER_OR_EQUAL) {
//         // Преобразуем оператор >= в < и добавляем отрицание
//         root->value = "<";
//         root->type = TreeNodeType::OPER_LESS_THAN;
//         // Меняем местами левый и правый дочерние узлы
//         TreeNode* temp = root->left;
//         root->left = root->right;
//         root->right = temp;
//         // Создаем новый узел для отрицания и устанавливаем его правым дочерним узлом текущего узла
//         UnaryTreeNode* negateNode = new UnaryTreeNode("!");
//         negateNode->right = root;
//         root = negateNode;
//     } else if (root->type == TreeNodeType::OPER_LESS_OR_EQUAL) {
//         // Преобразуем оператор <= в < и добавляем отрицание
//         root->value = "<";
//         root->type = TreeNodeType::OPER_LESS_THAN;
//         // Меняем местами левый и правый дочерние узлы
//         TreeNode* temp = root->left;
//         root->left = root->right;
//         root->right = temp;
//         // Создаем новый узел для отрицания и устанавливаем его правым дочерним узлом текущего узла
//         UnaryTreeNode* negateNode = new UnaryTreeNode("!");
//         negateNode->right = root;
//         root = negateNode;
//     }

//     // Рекурсивно обрабатываем левый и правый дочерние узлы
//     convertToLess(root->left, errors);
//     convertToLess(root->right, errors);
// }
