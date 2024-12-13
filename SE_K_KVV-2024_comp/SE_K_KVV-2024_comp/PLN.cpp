#include "PLN.h"
#define LEN 50
namespace PLN {

    void findN(LT::LexTable& lextable, IT::IdTable& idtable) {
        int pos = 0;
        for (int i = 0; i <= lextable.size; i++) {
            if (lextable.table[i].lexema == '=') {
                pos = i + 1;
                PolishNotation(pos, lextable, idtable);
            }
        }
    }

    bool PolishNotation(int lextable_pos, LT::LexTable& lextable, IT::IdTable& idtable) {

        std::map<char, int> precedence = { {'!', 1}, {'&', 2}, {'|', 3}, {'^', 2} };
        std::set<char> left_associative = { '!', '&', '|', '^' };

        LT::LexTable expression = LT::Create(LEN);
        int length = 0;

        for (int i = lextable_pos; lextable.table[i].lexema != ';'; i++) {
            LT::Add(expression, lextable.table[i]);
            length++;
        }


        std::stack<LT::Entry> stack;
        LT::LexTable output = LT::Create(LEN);



        for (int i = 0; i <= length; i++) {
            if (std::isalnum(expression.table[i].lexema)) {
                LT::Add(output, expression.table[i]);
            }
            else if (expression.table[i].lexema == '(') {
                stack.push(expression.table[i]);
            }
            else if (expression.table[i].lexema == ')') {
                while (!stack.empty() && stack.top().lexema != '(') {
                    LT::Add(output, stack.top());
                    stack.pop();
                }
                if (!stack.empty() && stack.top().lexema == '(') {
                    stack.pop();
                }
            }
            else if (precedence.find(expression.table[i].lexema) != precedence.end()) {
                LT::Entry op = expression.table[i];
                while (!stack.empty() && stack.top().lexema != '(' &&
                    (precedence[stack.top().lexema] > precedence[op.lexema] ||
                        (precedence[stack.top().lexema] == precedence[op.lexema] && left_associative.count(op.lexema)))) {
                    LT::Add(output, stack.top());
                    stack.pop();
                }
                stack.push(op);
            }
        }


        while (!stack.empty()) {
            LT::Add(output, stack.top());
            stack.pop();
        }



        for (int i = output.size; i < length; i++) {
            LT::Add(output, { '$', LT::GetEntry(output, output.size - 1).sn });
        }

        for (int i = 0; i < length; i++) {
            lextable.table[i + lextable_pos] = output.table[i];
        }
        return true;
    }
}