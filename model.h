#ifndef SRC_MODEL_H_
#define SRC_MODEL_H_

#include <stdio.h>
#include <string.h>

#include <cctype>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>

namespace s21 {
class Model {
   private:
    double result = 0;
    std::stack<double> st;
    std::stack<char *> stc;

    void calculate(char *action);
    void calculate_func(char *action);
    int priority(char *istr);

   public:
    Model() {}
    ~Model() {}
    double getResult() { return result; };
    void calc(char *str);
};
}  // namespace s21
#endif  // SRC_MODEL_H_
