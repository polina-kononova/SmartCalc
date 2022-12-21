#include "graph.h"

#include "controller.h"
#include "ui_graph.h"

graph::graph(QWidget *parent, QString str_out)
    : QDialog(parent), ui(new Ui::graph) {
    ui->setupUi(this);
    strOut = str_out;
}

graph::~graph() { delete ui; }

void graph::on_GraphBuilt_clicked() {
    x_start = ui->x_start->value();
    x_end = ui->x_end->value();

    y_start = ui->y_start->value();
    y_end = ui->y_end->value();

    if (x_start >= x_end) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "Error with domain");
        messageBox.setFixedSize(500, 200);
    } else if (y_start >= y_end) {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "Error with codomain");
        messageBox.setFixedSize(500, 200);
    } else {
        ui->widget->xAxis->setRange(x_start, x_end);
        ui->widget->yAxis->setRange(y_start, y_end);

        x_step = (x_end - x_start) / 10000;

        s21::Controller controller;

        for (X = x_start; X <= x_end; X += x_step) {
            x.push_back(X);
            char var_2[500] = {0};
            snprintf(var_2, 400, "%lf", X);
            QByteArray count = strOut.toLocal8Bit();
            count.replace("x", var_2);
            char *cstr = count.data();
            controller.calc(cstr);

            double temp_result = controller.getResult();
            y.push_back(temp_result);
        }
        ui->widget->addGraph();
        ui->widget->graph(0)->addData(x, y);
        ui->widget->replot();
    }
}
