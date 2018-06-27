#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QFileDialog>

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

    videoplayer_ = new VideoPlayer();
    videoplayer_->Init();
    connect(videoplayer_,SIGNAL(signalGetOneFrame(QImage)),player_renderer_,SLOT(slotGetOneFrame(QImage)));
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
      filename_ = QFileDialog::getOpenFileName(
                 this, "选择要播放的文件",
                  "/");

      if (filename_.isEmpty())
      {
        return;
      }
      qDebug()<<filename_;
      videoplayer_->setFileName(filename_);
    }
    else if (QObject::sender() == ui->pushButtonPlay)
    {
        qDebug()<<"pushButtonPlay";

        player_renderer_->show();

        videoplayer_->start();
    }
}
