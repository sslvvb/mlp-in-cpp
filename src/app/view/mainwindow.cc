#include "mainwindow.h"

#include "ui_mainwindow.h"

namespace s21 {

MainWindow::MainWindow(Controller *controller, QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow), controller_(controller) {
  ui_->setupUi(this);

  connect(ui_->paint_widget, SIGNAL(signalSaveImage(std::vector<double>)), this,
          SLOT(probable_letter_slot(std::vector<double>)));
  controller_->InitNetwork(ui_->type_matrix->isChecked());
}

MainWindow::~MainWindow() { delete ui_; }

void MainWindow::on_type_matrix_clicked() {
  ui_->weights_file->setText("No weights file selected");
  ui_->learning_file->setText("No learning file selected");
  controller_->InitNetwork(ui_->type_matrix->isChecked());
}

void MainWindow::on_type_graph_clicked() {
  ui_->weights_file->setText("No weights file selected");
  ui_->learning_file->setText("No learning file selected");
  controller_->InitNetwork(false);
}

void MainWindow::on_hidden_layers_valueChanged(int arg1) {
  controller_->set_hidden_layers(arg1);
}

void MainWindow::on_number_epochs_valueChanged(int arg1) {
  controller_->set_epochs_count(arg1);
}

void MainWindow::on_number_k_groups_valueChanged(int arg1) {
  controller_->set_cross_validation_group(arg1);
}

void MainWindow::on_path_to_learning_file_clicked() {
  try {
    qlearning_file_name_ = QFileDialog::getOpenFileName(this, "Выбрать файл");
    if (qlearning_file_name_.mid(qlearning_file_name_.size() - 4) != ".csv") {
      qlearning_file_name_.clear();
      throw std::invalid_argument(
          "Invalid file format: file format must be .csv");
    }
    QString correct_file_name = qlearning_file_name_;
    size_t index = correct_file_name.lastIndexOf('/');
    correct_file_name = correct_file_name.mid(index + 1);
    ui_->learning_file->setText(correct_file_name);
    ui_->test_file->setText("No test file selected");
  } catch (const std::exception &ex) {
    QMessageBox::warning(this, "Werror", ex.what());
    ui_->learning_file->setText("No learning file selected");
  }
}

void MainWindow::on_start_learning_clicked() {
  try {
    if (ui_->learning_file->text() != "No learning file selected") {
      ui_->weights_file->setText("No weights file selected");
    }
    LearningPopUp learning_pop_up(controller_, ui_->type_epoch->isChecked(),
                                  qlearning_file_name_.toStdString());
    learning_pop_up.setWindowTitle("Learning");
    learning_pop_up.exec();
  } catch (const std::exception &ex) {
    QMessageBox::warning(this, "Werror", ex.what());
  }
}

void MainWindow::probable_letter_slot(std::vector<double> pixel_array) {
  try {
    if (ui_->weights_file->text() == "No weights file selected" &&
        !controller_->get_report_vector_for_learning().size()) {
      throw std::invalid_argument(
          "You should set weights: \nuse ready weights or create new by "
          "learning");
    } else {
      int answer_predict = controller_->GetPredictedValue(pixel_array);
      ui_->probable_letter->setText((QString)((char)(answer_predict + 64)));
    }
  } catch (const std::exception &ex) {
    QMessageBox::warning(this, "Werror", ex.what());
  }
}

void MainWindow::on_load_image_clicked() {
  try {
    if (ui_->weights_file->text() == "No weights file selected" &&
        !controller_->get_report_vector_for_learning().size()) {
      throw std::invalid_argument(
          "You should set weights:\nuse ready weights or create new by "
          "learning");
    } else {
      QString file_name = QFileDialog::getOpenFileName(this, "Open a file");
      if (file_name.mid(file_name.size() - 4, 4) == ".bmp" ||
          file_name.mid(file_name.size() - 4, 4) == ".BMP") {
        QImage tmp_img(file_name, "BMP");
        ui_->paint_widget->LoadImage() =
            tmp_img.scaled(QSize(280, 280))
                .convertToFormat(QImage::Format_RGB16);
        ui_->paint_widget->Predict();
        ui_->paint_widget->update();
        QString correct_file_name = file_name;
        correct_file_name =
            correct_file_name.mid(correct_file_name.lastIndexOf('/') + 1);
        ui_->image_file->setText(correct_file_name);
      } else {
        throw std::invalid_argument(
            "Invalid file format: file format must be .bmp");
      }
    }
  } catch (const std::exception &ex) {
    QMessageBox::warning(this, "Werror", ex.what());
  }
}

void MainWindow::on_load_weights_clicked() {
  QString file_name = QFileDialog::getOpenFileName(this, "Open a file");
  try {
    ui_->test_file->setText("No test file selected");
    ui_->learning_file->setText("No learning file selected");
    qlearning_file_name_.clear();
    controller_->LoadWeights(file_name.toStdString());
    size_t index = file_name.lastIndexOf('/');
    file_name = file_name.mid(index + 1);
    ui_->weights_file->setText(file_name);
    ui_->hidden_layers->setValue(controller_->get_hidden_layers());
  } catch (const std::exception &ex) {
    QMessageBox::warning(this, "Werror", ex.what());
    ui_->weights_file->setText("No weights file selected");
  }
}

void MainWindow::on_load_test_file_clicked() {
  try {
    if (ui_->weights_file->text() == "No weights file selected" &&
        !controller_->get_report_vector_for_learning().size()) {
      throw std::invalid_argument(
          "You should set weights:\nuse ready weights or create new by "
          "learning");
    } else {
      controller_->set_progress_percent(0);
      test_file_name_ = QFileDialog::getOpenFileName(this, "Open a file");
      if (test_file_name_.mid(test_file_name_.size() - 4) == ".csv") {
        QString correct_file_name = test_file_name_;
        correct_file_name =
            correct_file_name.mid(correct_file_name.lastIndexOf('/') + 1);
        ui_->test_file->setText(correct_file_name);
      } else {
        throw std::invalid_argument(
            "Invalid file format: file format must be .csv");
        test_file_name_.clear();
      }
    }
  } catch (const std::exception &ex) {
    QMessageBox::warning(this, "Werror", ex.what());
    ui_->test_file->setText("No test file selected");
  }
}

void MainWindow::on_start_testing_clicked() {
  try {
    if (!test_file_name_.size() &&
        ui_->test_file->text() != "No test file selected") {
      throw std::invalid_argument("You should choose file for testing");
    } else {
      TestPopUp test_pop_up(controller_, test_file_name_.toStdString(),
                            ui_->test_sample->value());
      test_pop_up.setWindowTitle("Testing");
      test_pop_up.exec();
    }
  } catch (const std::exception &ex) {
    QMessageBox::warning(this, "Werror", ex.what());
  }
}

}  // namespace s21
