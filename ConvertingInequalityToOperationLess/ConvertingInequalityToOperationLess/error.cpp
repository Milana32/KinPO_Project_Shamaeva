/*!
 * \file
 * \brief Реализация метода для преобразования типа ошибки в строку.
 */

#include "Error.h"

/*!
 * \brief Преобразует тип ошибки в строку.
 * \param [in] error Объект типа Error, содержащий информацию об ошибке.
 * \return Строковое представление ошибки.
 */
// Метод для преобразования типа ошибки в строку
QString ErrorToString(const Error& error) {
    switch (error.type) {
    case ErrorType::PATH_NOT_FOUND:
        return "PATH_NOT_FOUND";
    case ErrorType::FILE_NOT_FOUND:
        return "FILE_NOT_FOUND";
    case ErrorType::FILE_NOT_OPENED:
        return "FILE_NOT_OPENED";
    case ErrorType::MORE_THAN_ONE_STRING:
        return "MORE_THAN_ONE_STRING";
    case ErrorType::UNKNOWN_CHARACTER:
        return "UNKNOWN_CHARACTER";
    case ErrorType::NOT_ENOUGH_OPERATORS:
        return "NOT_ENOUGH_OPERATORS";
    case ErrorType::NOT_ENOUGH_ARGUMENTS:
        return "NOT_ENOUGH_ARGUMENTS";
    case ErrorType::NOT_ENOUGH_ARGUMENTS_FOR_UNARY_OPERATOR:
        return "NOT_ENOUGH_ARGUMENTS_FOR_UNARY_OPERATOR";
    case ErrorType::NO_SPACE_BETWEEN_OPERANDS:
        return "NO_SPACE_BETWEEN_OPERANDS";
    case ErrorType::EMPTY_TREE:
        return "EMPTY_TREE";
    case ErrorType::EMPTY_NODE:
        return "EMPTY_NODE";
    case ErrorType::COMPARISON_OPERATOR_NOT_FOUND:
        return "COMPARISON_OPERATOR_NOT_FOUND";
    case ErrorType::INCORRECT_USE_OF_NEGATION:
        return "INCORRECT_USE_OF_NEGATION";
    case ErrorType::MORE_THAN_ONE_COMPARISON_OPERATOR:
        return "MORE_THAN_ONE_COMPARISON_OPERATOR";
    case ErrorType::EMPTY_STRING:
        return "EMPTY_STRING";
    case ErrorType::EMPTY_TOKEN:
        return "EMPTY_TOKEN";
    case ErrorType::NUMBER_OUT_OF_RANGE:
        return "NUMBER_OUT_OF_RANGE";
    case ErrorType::INVALID_TOKEN:
        return "INVALID_TOKEN";
    default:
        return "UNKNOWN_ERROR";
    }
}
