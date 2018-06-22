#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    player_renderer_ = new PlayerRenderer(this);
    ui->horizontalLayout->addWidget(player_renderer_);
    player_renderer_->hide();

    connect(ui->pushButtonOpen,SIGNAL(clicked()),this,SLOT(slotButtonClick()));
    connect(ui->pushButtonPlay,SIGNAL(clicked()),this,SLOT(slotButtonClick()));
}

Dialog::~Dialog()
{
    delete player_renderer_;
    delete ui;
}

void Dialog::slotButtonClick() {
    if (QObject::sender() == ui->pushButtonOpen)
    {
        qDebug()<<"pushButtonOpen";
    }
    else if (QObject::sender() == ui->pushButtonPlay)
    {
        qDebug()<<"pushButtonPlay";

        player_renderer_->show();

        player_renderer_->update();
    }
}
