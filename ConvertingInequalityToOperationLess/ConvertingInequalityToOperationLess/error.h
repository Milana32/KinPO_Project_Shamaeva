/*!
 * \file
 * \brief Заголовочный файл для класса Error, описывающего ошибки.
 */

#ifndef ERROR_H
#define ERROR_H

#include <QCoreApplication>

/*!
 * \brief Перечисление типов ошибок.
 */
enum ErrorType {
    PATH_NOT_FOUND,                      /*!< Путь не найден */
    FILE_NOT_FOUND,                      /*!< Файл не найден */
    FILE_NOT_OPENED,                     /*!< Файл не удалось открыть */
    MORE_THAN_ONE_STRING,                /*!< В файле больше одной строки */
    UNKNOWN_CHARACTER,                   /*!< Неизвестный символ */
    NOT_ENOUGH_OPERATORS,                /*!< Недостаточно операторов */
    NOT_ENOUGH_ARGUMENTS,                /*!< Недостаточно аргументов */
    NO_SPACE_BETWEEN_OPERANDS,           /*!< Нет пробела между операндами */
    EMPTY_TREE,                          /*!< Пустое дерево */
    EMPTY_NODE,                          /*!< Пустой узел */
    COMPARISON_OPERATOR_NOT_FOUND,       /*!< Оператор сравнения не найден */
    INCORRECT_USE_OF_NEGATION,           /*!< Некорректное использование знака отрицания */
    MORE_THAN_ONE_COMPARISON_OPERATOR,   /*!< Больше одного оператора сравнения */
    NOT_ENOUGH_ARGUMENTS_FOR_UNARY_OPERATOR,  /*!< Недостаточно аргументов для унарного оператора*/
    EMPTY_STRING,                         /*!< Пустая строка*/
    EMPTY_TOKEN,                          /*!< Пустой токен*/
    NUMBER_OUT_OF_RANGE,                  /*!< Число вне допустимого диапазона*/
    INVALID_TOKEN                         /*!< Токен не соответствует нужному формату*/

};

/*!
 * \brief Класс для хранения информации об ошибках.
 */
struct Error {
    ErrorType type;       /*!< Тип ошибки */
    int position;         /*!< Позиция ошибки в исходном коде или данных */
    QString symbol;       /*!< Символ, вызвавший ошибку */

    /*!
     * \brief Конструктор для инициализации ошибки.
     * \param t Тип ошибки.
     * \param pos Позиция ошибки.
     * \param sym Символ, вызвавший ошибку.
     */
    Error(ErrorType t, int pos, const QString& sym)
        : type(t), position(pos), symbol(sym) {}
};

/*!
 * \brief Метод для преобразования ошибку в строку.
 */
QString ErrorToString(const Error& error);

#endif // ERROR_H

