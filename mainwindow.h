#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "graph.h"
#include "model.h"
#include "question.h"

// extern "C"
//{
//#include "calc.h"
// }

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QByteArray qarray;
    bool x_var = false;
    ;
    bool number_pr = false;
    ;
    bool dot_pr = false;
    bool unary_pr = false;
    bool func_pr = false;
    bool unary_first = true;
    bool operator_pr = true;
    bool error = false;
    bool empty = true;
    bool x_var_pr = false;
    int br_r = 0;
    int br_l = 0;

    double x_question;

   private:
    Ui::MainWindow *ui;
    Question *question;
    //    Graf *grafic;

   private slots:
    void exp_number();
    void dot();
    void unary();
    void operators();
    void exp_operator();
    void expression();
    void exp_br_r();
    void exp_br_l();
    void exp_x();
    void start_bool();
    void calculation();
    void print_button();
    void on_pushButton_eq_clicked();
    void clear();

    void on_pushButton_graf_clicked();

   public slots:
    void slotQuestion(QString a);
};

#endif  // MAINWINDOW_H
