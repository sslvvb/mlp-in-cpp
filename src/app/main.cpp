#include <QApplication>
#include <clocale>

#include "controller/controller.h"
#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  std::setlocale(LC_NUMERIC, "C");
  s21::Controller controller;
  s21::MainWindow w(&controller);
  w.show();
  return a.exec();
}
