#include "model.h"

namespace s21 {
void Model::calculate(char *action) {
    double result = 0;
    double b = st.top();
    st.pop();
    double a = st.top();
    st.pop();
    if (strcmp(action, "+") == 0) {
        result = a + b;
    } else if (strcmp(action, "-") == 0) {
        result = a - b;
    } else if (strcmp(action, "/") == 0) {
        result = a / b;
    } else if (strcmp(action, "*") == 0) {
        result = a * b;
    } else if (strcmp(action, "mod") == 0) {
        result = fmod(a, b);
    } else if (strcmp(action, "^") == 0) {
        result = pow(a, b);
    }
    st.push(result);
}

void Model::calculate_func(char *action) {
    double result = 0;
    double a = st.top();
    st.pop();
    if (strcmp(action, "cos") == 0) {
        result = cos(a);
    } else if (strcmp(action, "sin") == 0) {
        result = sin(a);
    } else if (strcmp(action, "tan") == 0) {
        result = tan(a);
    } else if (strcmp(action, "acos") == 0) {
        result = acos(a);
    } else if (strcmp(action, "asin") == 0) {
        result = asin(a);
    } else if (strcmp(action, "atan") == 0) {
        result = atan(a);
    } else if (strcmp(action, "sqrt") == 0) {
        result = sqrt(a);
    } else if (strcmp(action, "ln") == 0) {
        result = log(a);
    } else if (strcmp(action, "log") == 0) {
        result = log10(a);
    }
    st.push(result);
}

int Model::priority(char *istr) {
    int priority = 0;
    if ((strcmp(istr, "+") == 0) || (strcmp(istr, "-") == 0)) {
        priority = 1;
    } else if ((strcmp(istr, "*") == 0) || (strcmp(istr, "/") == 0) ||
               (strcmp(istr, "mod") == 0)) {
        priority = 2;
    } else if (strcmp(istr, "^") == 0) {
        priority = 3;
    } else if (istr[0] >= 'a' && istr[0] <= 'z') {
        priority = 4;
    }
    return priority;
}

void Model::calc(char *str) {
    double number = 0;
    char *istr;
    istr = strtok(str, " ");
    int priority_c = 0;

    while (istr != NULL) {
        if ((((istr[0] != '+') || (istr[0] != '-')) &&
             (istr[1] >= '0' && istr[1] <= '9')) ||
            (istr[0] >= '0' && istr[0] <= '9')) {
            number = atof(istr);
            st.push(number);
            if ((!stc.empty()) && (priority(stc.top()) == 4)) {
                calculate_func(stc.top());
                if (!stc.empty()) stc.pop();
            }
        } else {
            if (strcmp(istr, "(") == 0) {
                stc.push(istr);
            } else if (strcmp(istr, ")") == 0) {
                while ((!stc.empty()) && (strcmp(stc.top(), "(")) != 0) {
                    calculate(stc.top());
                    if (!stc.empty()) stc.pop();
                }
                if (!stc.empty()) stc.pop();
                while ((!stc.empty()) && (priority(stc.top()) == 4)) {
                    calculate_func(stc.top());
                    if (!stc.empty()) stc.pop();
                }
            } else {
                priority_c = priority(istr);
                while ((!stc.empty()) && (priority_c <= priority(stc.top()))) {
                    calculate(stc.top());
                    if (!stc.empty()) stc.pop();
                }
                stc.push(istr);
            }
        }
        istr = strtok(NULL, " ");
    }

    while (!stc.empty()) {
        calculate(stc.top());
        stc.pop();
    }
    if (!st.empty()) {
        result = st.top();
    }
}
}  // namespace s21
