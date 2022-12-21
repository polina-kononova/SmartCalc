#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "model.h"

namespace s21 {
class Controller {
   private:
    Model model;

   public:
    void calc(char *str) { model.calc(str); }
    double getResult() { return model.getResult(); }
};
}  // namespace s21

#endif  // CONTROLLER_H
