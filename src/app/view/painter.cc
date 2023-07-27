#include "painter.h"

Painter::Painter(QWidget *parent) : QWidget(parent) {
  image_ = QImage(QSize(280, 280), QImage::Format_RGB16);
  image_.fill(qRgb(255, 255, 255));
  update();
}

void Painter::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);
  QPainter painter(this);
  QRect dirtyRect = event->rect();
  painter.drawImage(dirtyRect, image_, dirtyRect);
}

void Painter::mousePressEvent(QMouseEvent *event) {
  mBtn_ = event->button();
  if (mBtn_ == Qt::LeftButton) {
    pick_point_ = event->pos();
  } else {
    image_ = QImage(QSize(280, 280), QImage::Format_RGB16);
    image_.fill(qRgb(255, 255, 255));
    update();
  }
}
void Painter::mouseMoveEvent(QMouseEvent *event) {
  if (mBtn_ == Qt::LeftButton) {
    QPainter painter(&image_);
    painter.setPen(
        QPen(Qt::black, 30, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(pick_point_, event->pos());
    update();
    pick_point_ = event->pos();
  }
}

void Painter::mouseReleaseEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    Predict();
  }
}

void Painter::Predict() {
  pixel_vector_.clear();
  for (int i = 0; i < 28; i++) {
    for (int j = 0; j < 28; j++) {
      QRgb color = image_.pixel(i * 280 / 28, j * 280 / 28);
      pixel_vector_.push_back((255 - (color & 0x000000ff)) / 255);
    }
  }
  emit signalSaveImage(pixel_vector_);
}
