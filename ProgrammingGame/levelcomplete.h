#ifndef LEVELCOMPLETE_H
#define LEVELCOMPLETE_H


#include <QWidget>
#include <Box2D/Box2D.h>
#include <QTimer>
#include <QVector>
#include <QPixmap>
#include <vector>
#include <time.h>
#include <stdlib.h>

class levelcomplete : public QWidget
{

    Q_OBJECT

public:

    const int CONFETTI_COUNT = 150;

    explicit levelcomplete(QWidget *parent = nullptr);

    ~levelcomplete();

    void paintEvent(QPaintEvent *);

    void resetAnimation();

    void stopAnimation();

signals:



public slots:

    void updateWorld();

private:

    b2World world;
    b2Body* completeImage;
    std::vector<b2Body*> confetti;

    QTimer timer;
    QImage image;

    QPixmap confettiImg;

    bool shouldAnimate;

};

#endif // LEVELCOMPLETE_H
