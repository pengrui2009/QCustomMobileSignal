/**
 * @file qcustommobilesignal.h
 * @author rui.peng (pengrui_2009@163.com)
 * @brief qt custom mobile signal plugin
 * @version 0.1
 * @date 2023-03-18
 * 
 * @copyright Copyright none (c) 2023
 * 
 */

#ifndef QCUSTOMMOBILESIGNAL_H
#define QCUSTOMMOBILESIGNAL_H

#include <QWidget>
#include <QPainter>
#include <QTimer>


/**
 * @brief Feature:
 * Support user defination of title
 * Support user defination of Mobile Signal Position
 * Support user defination of Time Cost
 * Support Auto Change Mobile Signal by TimeCost value
 */
#ifdef quc
#if (QT_VERSION < QT_VERSION_CHECK(5,0,0))
#include <QtDesigner/QDesignerExportWidget>
#else
#include <QtUiPlugin/QDesignerExportWidget>
#endif

class QDESIGNER_WIDGET_EXPORT QCustomMobileSignal : public QWidget
#else
class QCustomMobileSignal : public QWidget
#endif
{
    Q_OBJECT
    Q_PROPERTY(double m_rssi_ READ getTimeCost WRITE setTimeCost)
    Q_PROPERTY(QString m_title_ READ getTitle WRITE setTitle)
    Q_PROPERTY(QColor m_background_color_ READ getBackgroundColor WRITE setBackgroundColor)
public:
    enum Position {
        POSITION_LEFT_TOP = 0,
        POSITION_RIGHT_TOP = 1,
        POSITION_CENTER_TOP = 2,
    };
    explicit QCustomMobileSignal(QWidget *parent = nullptr);
    ~QCustomMobileSignal();

    QColor getBackgroundColor()     const;
    QString getTitle()              const;
    double getTimeCost()                const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;
protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

    void drawBackground(QPainter *painter);
    void drawTitle(QPainter *painter);
    void drawTimeCost(QPainter *painter);
    void drawSystemTime(QPainter *painter);
private:
    QTimer *m_timer_ptr_;

    QColor m_background_color_;
    QString m_title_{""};
    double m_timecost_{0.0};     // unit:1ms
    Position m_position_{POSITION_RIGHT_TOP};

signals:
    void valueChanged(int value);
public slots:
    void updateValue();
    void updateValue(double value);

    void setBackgroundColor(const QColor value);
    void setTitle(const QString value);
    void setTimeCost(const double value);
    void setPosition(const Position value);
};

#endif // QCUSTOMMOBILESIGNAL_H
