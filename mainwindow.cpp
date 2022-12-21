#include "mainwindow.h"

#include "controller.h"
#include "graph.h"
#include "question.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(exp_number()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(exp_number()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(exp_number()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(exp_number()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(exp_number()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(exp_number()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(exp_number()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(exp_number()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(exp_number()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(exp_number()));
    connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(dot()));
    connect(ui->pushButton_unary, SIGNAL(clicked()), this, SLOT(unary()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(exp_operator()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this,
            SLOT(exp_operator()));
    connect(ui->pushButton_br_l, SIGNAL(clicked()), this, SLOT(exp_br_l()));
    connect(ui->pushButton_br_r, SIGNAL(clicked()), this, SLOT(exp_br_r()));
    connect(ui->pushButton_mul, SIGNAL(clicked()), this, SLOT(exp_operator()));
    connect(ui->pushButton_degree, SIGNAL(clicked()), this,
            SLOT(exp_operator()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(exp_operator()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(expression()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(expression()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(expression()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(expression()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(expression()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(expression()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(exp_operator()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(expression()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(expression()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(expression()));
    connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(exp_x()));
    connect(ui->pushButton_clear, SIGNAL(clicked()), this, SLOT(clear()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::exp_x() {
    if(!number_pr && !x_var_pr && unary_first) {
        x_var = true;
        x_var_pr = true;
        operator_pr = false;
        print_button();
    }
}

void MainWindow::exp_number() {
    if (!x_var_pr) {
        operator_pr = false;
        number_pr = true;
        print_button();
    }
}

void MainWindow::print_button() {
    if (error) {
        clear();
    }
    QPushButton *button = (QPushButton *)sender();
    QString str;
    str = (ui->result_show->text() + button->text());
    ui->result_show->setText(str);
}

void MainWindow::dot() {
    if (number_pr && !dot_pr) {
        print_button();
        dot_pr = true;
    }
}

void MainWindow::unary() {
    QString str = ui->result_show->text();
    if (!number_pr && !x_var_pr) {
        if (unary_first) {
            str = (ui->result_show->text() + '-');
        } else {
            str = str.left(str.count() - 1);
            ui->result_show->setText(str);
            if (unary_pr)
                str = (ui->result_show->text() + '+');
            else
                str = (ui->result_show->text() + '-');
        }

        unary_pr = !unary_pr;
        ui->result_show->setText(str);
    }
    unary_first = false;
}

void MainWindow::operators() {
    print_button();
    x_var_pr = false;
    number_pr = false;
    dot_pr = false;
    unary_pr = false;
    unary_first = true;
    func_pr = false;
}

void MainWindow::exp_operator() {
    if (number_pr || x_var_pr)  {
        operators();
        operator_pr = true;
    }
}

void MainWindow::expression() {
    if ((operator_pr) && (!func_pr)) {
        operators();
        func_pr = true;
    }
}

void MainWindow::exp_br_l() {
    if (operator_pr) {
        operators();
        br_l++;
        func_pr = false;
    }
}

void MainWindow::exp_br_r() {
    if ((number_pr) && (br_l > br_r)) {
        operators();
        number_pr = true;
        br_r++;
    }
}

void MainWindow::on_pushButton_eq_clicked() {
    if (number_pr || x_var_pr) {
        QString equal = ui->result_show->text();
        qarray = equal.toLocal8Bit();
        if (br_r != br_l) {
            error = true;
            QMessageBox messageBox;
            messageBox.critical(0, "Error", "Something wrong with brackets");
            messageBox.setFixedSize(500, 200);
        } else {
            if (x_var) {
                question = new Question;
                question->show();
                connect(question, &Question::signalQuestion, this,
                        &MainWindow::slotQuestion);
            } else {
                calculation();
            }
        }
    }
}

void MainWindow::calculation() {
    char *cStr = qarray.data();
    s21::Controller controller;
    controller.calc(cStr);

    char res_char[100] = {0};
    sprintf(res_char, "%.7f", controller.getResult());
    ui->result_new->setText(res_char);
}

void MainWindow::start_bool() {
    x_var = false;
    number_pr = false;
    dot_pr = false;
    unary_pr = false;
    unary_first = true;
    operator_pr = true;
    func_pr = false;
    br_r = 0;
    br_l = 0;
    error = false;
    x_var_pr = false;
}

void MainWindow::clear() {
    ui->result_show->setText("");
    ui->result_new->setText("");
    start_bool();
}

void MainWindow::slotQuestion(QString str) {
    QString x_a = str;
    bool ok;
    x_a.toDouble(&ok);
    if (ok) {
        QByteArray byteArray = x_a.toLocal8Bit();
        char *var = byteArray.data();
        char var_2[500] = {0};
        snprintf(var_2, 400, "%s", var);

        qarray.replace("x", var_2);

        calculation();
    } else {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "Something wrong with data for X");
        messageBox.setFixedSize(500, 200);
        error = true;
    }
}

void MainWindow::on_pushButton_graf_clicked() {
    if (number_pr || x_var_pr) {
        graph window(nullptr, ui->result_show->text());
        window.setModal(true);
        window.exec();
    } else {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "Error. Enter a function!");
        messageBox.setFixedSize(500, 200);
    }
}
