#include "PLN.h"

bool PolishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable) {
    // Определение приоритетов операторов
    std::map<char, int> precedence = { {'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}, {'^', 3} };
    std::set<char> left_associative = { '+', '-', '*', '/' };

    std::string expression;

    for (int i = lextable_pos; lextable.table[i].lexema != ';'; i++) {
        if (lextable.table[i].lexema == 'v') {
            expression += '+';
        }
        else
            expression += lextable.table[i].lexema;
    }

    // Стек для операторов и результирующий список
    std::stack<char> stack;
    std::string output;

    // Разделяем строку на токены (операнды и операторы)

    for (int i = 0; i <= expression.length(); i++) {
        if (std::isalnum(expression[i])) { // Операнд
            output.push_back(expression[i]);
        }
        else if (expression[i] == '(') {
            stack.push('(');
        }
        else if (expression[i] == ')') {
            while (!stack.empty() && stack.top() != '(') {
                output.push_back(stack.top());
                stack.pop();
            }
            if (!stack.empty() && stack.top() == '(') {
                stack.pop(); // Удаляем '('
            }
        }
        else if (precedence.find(expression[i]) != precedence.end()) { // Оператор
            char op = expression[i];
            while (!stack.empty() && stack.top() != '(' &&
                (precedence[stack.top()] > precedence[op] ||
                    (precedence[stack.top()] == precedence[op] && left_associative.count(op)))) {
                output.push_back(stack.top());
                stack.pop();
            }
            stack.push(op);
        }
    }

    // Выталкиваем оставшиеся операторы из стека
    while (!stack.empty()) {
        output.push_back(stack.top());
        stack.pop();
    }


    // Добавляем $ до нужной длины
    for (int i = output.length(); i < expression.length(); i++) {
        output += '$';
    }
    std::cout << output << std::endl;
    return true;
}