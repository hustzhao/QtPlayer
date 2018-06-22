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

private:
    Ui::PlayerRenderer *ui;

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // PLAYERRENDERER_H
