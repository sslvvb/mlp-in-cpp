#ifndef CPP7_MLP_0_SRC_VIEW_MAINWINDOW_H
#define CPP7_MLP_0_SRC_VIEW_MAINWINDOW_H

#include "../controller/controller.h"
#include "learningpopup.h"
#include "painter.h"
#include "testpopup.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(Controller *controller, QWidget *parent = nullptr);
  ~MainWindow();

 signals:
  void start_lerning_signal();

 public slots:
  void probable_letter_slot(std::vector<double> pixel_array);
 private slots:
  void on_type_matrix_clicked();
  void on_type_graph_clicked();
  void on_hidden_layers_valueChanged(int arg1);
  void on_path_to_learning_file_clicked();
  void on_number_epochs_valueChanged(int arg1);
  void on_number_k_groups_valueChanged(int arg1);
  void on_start_learning_clicked();
  void on_load_image_clicked();
  void on_load_weights_clicked();
  void on_load_test_file_clicked();
  void on_start_testing_clicked();

 private:
  Ui::MainWindow *ui_;
  Controller *controller_;
  bool learning_type_{}, is_learned_{};
  QString qlearning_file_name_, test_file_name_;
};

}  // namespace s21

#endif  // CPP7_MLP_0_SRC_VIEW_MAINWINDOW_H
