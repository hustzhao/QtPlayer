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

void PlayerRenderer::paintEvent(QPaintEvent *event) {
    qDebug()<<"paintEvent";

    QPainter painter(this);

    painter.drawLine(QPoint(0,0),QPoint(100,100));

}
