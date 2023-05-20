
#include <iostream>
#include <stack>
#include <string>
#include <cstdint>

int64_t precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

int64_t apply_op(int64_t a, int64_t b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

int64_t evaluate(const std::string &expression) {
    std::stack<int64_t> values;
    std::stack<char> ops;

    for (int i = 0; i < expression.length(); i++) {
        if (isdigit(expression[i])) {
            int64_t value = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                value = value * 10 + (expression[i] - '0');
                i++;
            }
            i--;
            values.push(value);
        } else {
            while (!ops.empty() && precedence(expression[i]) <= precedence(ops.top())) {
                int64_t b = values.top(); values.pop();
                int64_t a = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(apply_op(a, b, op));
            }
            ops.push(expression[i]);
        }
    }

    while (!ops.empty()) {
        int64_t b = values.top(); values.pop();
        int64_t a = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(apply_op(a, b, op));
    }

    return values.top();
}

int main() {
    std::string expression1, expression2;
    std::cin >> expression1 >> expression2;

    int64_t result1 = evaluate(expression1);
    int64_t result2 = evaluate(expression2);

    std::cout << std::max(result1, result2) << std::endl;

    return 0;
}
