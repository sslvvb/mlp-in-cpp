#ifndef CPP7_MLP_0_SRC_VIEW_GRAPHREPORT_H
#define CPP7_MLP_0_SRC_VIEW_GRAPHREPORT_H

#include "qcustomplot/qcustomplot.h"

namespace Ui {
class GraphReport;
}

namespace s21 {

class GraphReport : public QDialog {
  Q_OBJECT

 public:
  explicit GraphReport(std::vector<double> graph_report,
                       QDialog *parent = nullptr);
  ~GraphReport();

 private:
  Ui::GraphReport *ui_;
  std::vector<double> graph_report_;
  void DrawGraph();
};

}  // namespace s21

#endif  // CPP7_MLP_0_SRC_VIEW_GRAPHREPORT_H
