#ifndef PLAYERRENDERER_H
#define PLAYERRENDERER_H

#include <QDialog>

namespace Ui {
class PlayerRenderer;
}

class PlayerRenderer : public QDialog
{
    Q_OBJECT

public:
    explicit PlayerRenderer(QWidget *parent = 0);
    ~PlayerRenderer();

public slots:
    void slotGetOneFrame(QImage);

private:
    Ui::PlayerRenderer *ui;
    QImage image_;

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // PLAYERRENDERER_H
