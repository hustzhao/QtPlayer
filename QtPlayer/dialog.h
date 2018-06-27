#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "playerrenderer.h"
#include "videoplayer.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Ui::Dialog *ui;
    PlayerRenderer* player_renderer_{NULL};
    VideoPlayer* videoplayer_{NULL};
    QString filename_{};
private slots:
    void slotButtonClick();
};

#endif // DIALOG_H
