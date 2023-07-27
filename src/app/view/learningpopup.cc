#include "learningpopup.h"

#include "ui_learningpopup.h"

namespace s21 {

LearningPopUp::LearningPopUp(Controller *controller, bool learning_type,
                             std::string learning_file_name, QDialog *parent)
    : QDialog(parent),
      ui_(new Ui::LearningPopUp),
      controller_(controller),
      timer_(new QTimer),
      learning_file_name_(learning_file_name),
      learning_type_(learning_type) {
  ui_->setupUi(this);
  ui_->show_report->setEnabled(false);
  ui_->save_weights->setEnabled(false);
  controller_->CountFileItems(learning_file_name_);
  controller_->set_progress_percent(0);
  if (learning_type) {
    std::thread t([this]() { controller_->StartEpochTrain(); });
    t.detach();
  } else {
    std::thread t([this]() { controller_->StartCrossValidationTrain(); });
    t.detach();
  }
  timer_->start(100);
  connect(timer_, SIGNAL(timeout()), this, SLOT(ProgressSlot()));
}

void LearningPopUp::ProgressSlot() {
  percent_ = controller_->get_progress_percent();
  ui_->learning_progress->setValue(percent_);
  ui_->percent->setText(QString::number(percent_) + " %");
  if (percent_ == 100) {
    auto vector = controller_->get_report_vector_for_learning();
    double error = vector[vector.size() - 1];
    ui_->last_error->setText(QString::number(error) + " %");
    ui_->show_report->setEnabled(true);
    ui_->save_weights->setEnabled(true);
    timer_->stop();
  }
  update();
}

void LearningPopUp::on_show_report_clicked() {
  GraphReport graph_report_(controller_->get_report_vector_for_learning());
  graph_report_.setWindowTitle("Error report");
  graph_report_.exec();
}

void LearningPopUp::on_save_weights_clicked() {
  char hidden_layers = controller_->get_hidden_layers() + '0';
  QString FileName = QFileDialog::getSaveFileName(
      this, "Open a file",
      QDir::homePath() + "/" + hidden_layers + "_new_hidden_layers_",
      "(*.weights)");
  if (!FileName.isNull() && !FileName.isEmpty()) {
    qDebug() << FileName;
    controller_->SaveWeights(FileName.toStdString());
  }
}

LearningPopUp::~LearningPopUp() {
  try {
    if (percent_ != 100) {
      is_canceled_ = true;
      controller_->set_cancel_process(is_canceled_);
      throw std::invalid_argument(
          "Training was interrupted, so the weights were not saved.\nTry "
          "training again or load ready-made weights");
    }
  } catch (const std::exception &ex) {
    QMessageBox::warning(this, "Werror", ex.what());
  }
  is_canceled_ = false;
  percent_ = 0;
  delete ui_;
}

}  // namespace s21
