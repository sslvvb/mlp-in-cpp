#ifndef CPP7_MLP_0_SRC_VIEW_TESTPOPUP_H
#define CPP7_MLP_0_SRC_VIEW_TESTPOPUP_H

#include <QDialog>
#include <QMessageBox>
#include <QThread>
#include <QTimer>

#include "../controller/controller.h"

namespace Ui {
class TestPopUp;
}

namespace s21 {

class TestPopUp : public QDialog {
  Q_OBJECT

 public:
  explicit TestPopUp(Controller *controller, std::string testing_file_name,
                     double test_sample, QWidget *parent = nullptr);
  ~TestPopUp();

 private slots:
  void ProgressSlot();

 private:
  Ui::TestPopUp *ui_;
  Controller *controller_;
  QTimer *timer_;
  std::string testing_file_name_;
  bool is_canceled_{};
  std::atomic<int> percent_;
  double test_sample_;
  Metrics result_metrics_;
};

}  // namespace s21

#endif  // CPP7_MLP_0_SRC_VIEW_TESTPOPUP_H
