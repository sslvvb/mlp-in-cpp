#include "graphreport.h"

#include "ui_graphreport.h"

namespace s21 {

GraphReport::GraphReport(std::vector<double> graph_report, QDialog *parent)
    : QDialog(parent), ui_(new Ui::GraphReport), graph_report_(graph_report) {
  ui_->setupUi(this);
  DrawGraph();
}
void GraphReport::DrawGraph() {
  ui_->graph_report->yAxis->setLabel("error");
  ui_->graph_report->xAxis->setRange(0, graph_report_.size() + 1);
  ui_->graph_report->yAxis->setRange(0, 100);
  QCPAxis *x_axis = ui_->graph_report->xAxis;
  QCPAxis *y_axis = ui_->graph_report->yAxis;
  QCPBars *fossil = new QCPBars(x_axis, y_axis);
  QVector<double> ticks{};
  for (size_t i = 1; i <= graph_report_.size(); i++) {
    ticks.push_back(i);
  }
  QVector<double> fossilData =
      QVector<double>(graph_report_.begin(), graph_report_.end());
  fossil->setData(ticks, fossilData);
  ui_->graph_report->setInteraction(QCP::iRangeZoom, true);
  ui_->graph_report->setInteraction(QCP::iRangeDrag, true);
}

GraphReport::~GraphReport() { delete ui_; }

}  // namespace s21
