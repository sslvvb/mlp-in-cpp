#ifndef CPP7_MLP_0_SRC_VIEW_LEARNINGPOPUP_H
#define CPP7_MLP_0_SRC_VIEW_LEARNINGPOPUP_H

#include "../controller/controller.h"
#include "graphreport.h"

namespace Ui {
class LearningPopUp;
}

namespace s21 {

class LearningPopUp : public QDialog {
  Q_OBJECT

 public:
  explicit LearningPopUp(Controller *controller, bool learning_type,
                         std::string learning_file_name,
                         QDialog *parent = nullptr);
  ~LearningPopUp();

 private slots:
  void ProgressSlot();
  void on_show_report_clicked();
  void on_save_weights_clicked();

 private:
  Ui::LearningPopUp *ui_;
  Controller *controller_;
  QTimer *timer_;
  std::string learning_file_name_;
  bool learning_type_{}, is_canceled_{};
  std::atomic<int> percent_;
};

}  // namespace s21

#endif  // CPP7_MLP_0_SRC_VIEW_LEARNINGPOPUP_H
