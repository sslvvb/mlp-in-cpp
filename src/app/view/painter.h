#ifndef CPP7_MLP_0_SRC_VIEW_PAINTER_H
#define CPP7_MLP_0_SRC_VIEW_PAINTER_H

#include <QImage>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>
#include <QWidget>

class Painter : public QWidget {
 public:
  explicit Painter(QWidget *parent = nullptr);
  QImage &LoadImage() { return image_; }
  void Predict();

 signals:
  void signalSaveImage(std::vector<double> pixel_vector);

 private:
  Q_OBJECT
  void paintEvent(QPaintEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  QTimer timer_;
  QImage image_;
  Qt::MouseButton mBtn_;
  QPoint pick_point_;
  std::vector<double> pixel_vector_;
};

#endif  // CPP7_MLP_0_SRC_VIEW_PAINTER_H
