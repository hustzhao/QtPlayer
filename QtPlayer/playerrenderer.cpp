#include "playerrenderer.h"
#include "ui_playerrenderer.h"

#include <QPainter>
#include <QDebug>

PlayerRenderer::PlayerRenderer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayerRenderer)
{
    ui->setupUi(this);
}

PlayerRenderer::~PlayerRenderer()
{
    delete ui;
}

void PlayerRenderer::slotGetOneFrame(QImage image) {
  image_ = image;
  update();
}

void PlayerRenderer::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.setBrush(Qt::black);
  painter.drawRect(0,0,this->width(),this->height());

  if(image_.size().width() <= 0) return;

  QImage img = image_.scaled(this->size(),Qt::KeepAspectRatio);

  int x = this->width() - img.width();
  int y = this->height() - img.height();

  x = x / 2;
  y = y / 2;

  painter.drawImage(QPoint(x,y),img);
}
