#include "testpopup.h"

#include "ui_testpopup.h"

namespace s21 {

TestPopUp::TestPopUp(Controller *controller, std::string testing_file_name,
                     double test_sample, QWidget *parent)
    : QDialog(parent),
      ui_(new Ui::TestPopUp),
      controller_(controller),
      timer_(new QTimer),
      testing_file_name_(testing_file_name),
      test_sample_(test_sample) {
  ui_->setupUi(this);
  controller_->CountFileItems(testing_file_name_);
  controller_->set_progress_percent(0);
  std::thread t(
      [this]() { result_metrics_ = controller_->StartTesting(test_sample_); });
  t.detach();
  timer_->start(100);
  connect(timer_, SIGNAL(timeout()), this, SLOT(ProgressSlot()));
}

void TestPopUp::ProgressSlot() {
  percent_ = controller_->get_progress_percent();
  ui_->progress_test->setValue(percent_);
  ui_->percent->setText(QString::number(percent_) + " %");
  if (percent_ == 100) {
    ui_->time_value->setText(QString::number(result_metrics_.time));
    ui_->accuracy_value->setText(QString::number(result_metrics_.accuracy));
    ui_->precision_value->setText(QString::number(result_metrics_.precision));
    ui_->recall_value->setText(QString::number(result_metrics_.recall));
    ui_->fmeasure_value->setText(QString::number(result_metrics_.fmeasure));
    timer_->stop();
  }
  update();
}

TestPopUp::~TestPopUp() {
  try {
    if (percent_ != 100) {
      is_canceled_ = true;
      controller_->set_cancel_process(is_canceled_);
      controller_->set_progress_percent(0);
      throw std::invalid_argument("Testing was interrupted");
    }
  } catch (const std::exception &ex) {
    QMessageBox::warning(this, "Werror", ex.what());
  }
  is_canceled_ = false;
  percent_ = 0;
  delete ui_;
}

}  // namespace s21
