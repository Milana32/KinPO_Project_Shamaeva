/*!
 * \file
 * \brief Заголовочный файл с функциями для работы с деревьями и строками.
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <QString>
#include <QList>
#include "Tree.h"
#include "Error.h"

/*!
 * \brief Функция для извлечения строк из файла.
 * \param [in] filePath Путь к файлу.
 * \param [in,out] errors Список ошибок.
 * \return Список строк из файла.
 */
QStringList getStringsFromFile(const QString& filePath, QList<Error>& errors);

/*!
 * \brief Построение дерева разбора логического выражения.
 * \param [in] inequality Строка с логическим выражением.
 * \param [in, out] errors Список ошибок.
 * \return Указатель на корень дерева разбора, или nullptr в случае ошибки.
 */
TreeNode* buildLogicalTree(const QString& inequality, QList<Error>& errors);

/*!
 * \brief Функция для проверки, является ли токен оператором.
 * \param [in] token Токен для проверки.
 * \param [in,out] errors Список ошибок.
 * \return true, если токен является оператором, иначе false.
 */
bool isOperator(const QString& token, QList<Error>& errors);

/*!
 * \brief Функция для проверки, является ли токен операндом.
 * \param [in] token Токен для проверки.
 * \param [in,out] errors Список ошибок.
 * \return true, если токен является операндом, иначе false.
 */
bool isValidOperand(const QString& token, QList<Error>& errors);

/*!
 * \brief Функция для определения приоритета оператора.
 * \param [in] node Узел с оператором.
 * \return Приоритет оператора.
 */
int getPriority(const QString& node);

/*!
 * \brief Функция для преобразования дерева логического выражения в строку в инфиксной записи.
 * \param [in] root Корневой узел дерева.
 * \param [in,out] errors Список ошибок.
 * \return Строковое представление дерева.
 */
QString treeToString(TreeNode* root, QList<Error>& errors);

/*!
 * \brief Функция для преобразования узла дерева с оператором > в узел с оператором <.
 * \param [in,out] root Корневой узел дерева.
 * \param [in,out] errors Список ошибок.
 */
void convertToLess(TreeNode*& root, QList<Error>& errors);

#endif // FUNCTIONS_H
