#include "qcustommobilesignal.h"


#include <QDateTime>
#include <qmath.h>

QCustomMobileSignal::QCustomMobileSignal(QWidget *parent) : QWidget(parent)
{
    m_position_ = POSITION_RIGHT_TOP;
    m_background_color_ = QColor(55,107,154, 30);
    m_timecost_ = 0.0;

    m_timer_ptr_ = new QTimer(this);
    m_timer_ptr_->setInterval(100);
    connect(m_timer_ptr_, SIGNAL(timeout()), this, SLOT(updateValue()));
    m_timer_ptr_->start();
}

QCustomMobileSignal::~QCustomMobileSignal()
{
    if (m_timer_ptr_->isActive())
    {
        m_timer_ptr_->stop();
    }
    delete m_timer_ptr_;
}

void QCustomMobileSignal::resizeEvent(QResizeEvent *)
{
    this->repaint();
}

void QCustomMobileSignal::paintEvent(QPaintEvent *)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
//    painter.scale(side / 200.0, side / 200.0);

    drawBackground(&painter);

    drawTitle(&painter);

    drawTimeCost(&painter);

    drawSystemTime(&painter);
}

void QCustomMobileSignal::drawBackground(QPainter *painter)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    painter->save();

    painter->setBrush(m_background_color_);
    painter->drawRect(-width, -height, width * 2, height * 2);

    painter->restore();
}

void QCustomMobileSignal::drawTitle(QPainter *painter)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);
    QString title_str = "";

    QFont font;
    painter->save();
    font.setPixelSize(15);
    painter->setFont(font);
    painter->setPen(QColor(51, 223, 35));

    title_str = m_title_;
    if (m_position_ == POSITION_RIGHT_TOP)
    {
        painter->drawText(QRect(-width/2+5, -height/2+40, 60, 40), Qt::AlignLeft, title_str);
    } else if (m_position_ == POSITION_LEFT_TOP) {
        painter->drawText(QRect(width/2-65, -height/2+40, 60, 40), Qt::AlignLeft, title_str);
    } else {
        painter->drawText(QRect(-width/2+5, -height/2+40, 60, 40), Qt::AlignLeft, title_str);
    }

    painter->restore();
}

void QCustomMobileSignal::drawTimeCost(QPainter *painter)
{
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);
    int draw_signal_strenght_value = 5;

    QString video_timecost_str = "";

    if (m_position_ == POSITION_RIGHT_TOP)
    {
        QLine lines[] = {
            {-width/2 + 80,  -height/2+30, -width/2 + 80,  -height/2 + 25},
            {-width/2 + 90,  -height/2+30, -width/2 + 90,  -height/2 + 20},
            {-width/2 + 100, -height/2+30, -width/2 + 100, -height/2 + 15},
            {-width/2 + 110, -height/2+30, -width/2 + 110, -height/2 + 10},
            {-width/2 + 120, -height/2+30, -width/2 + 120, -height/2 + 5},
        };

        if ((m_timecost_ > 0) && (m_timecost_ < 100.0))
        {
            draw_signal_strenght_value = 5;
        } else if ((m_timecost_ > 100.0) && (m_timecost_ < 200.0)) {
            draw_signal_strenght_value = 4;
        } else if ((m_timecost_ > 200.0) && (m_timecost_ < 500.0)) {
            draw_signal_strenght_value = 3;
        } else if (m_timecost_ > 1000.0) {
            draw_signal_strenght_value = 1;
        } else {
            draw_signal_strenght_value = 0;
        }

        painter->save();
        painter->setPen(QPen(Qt::white,4));
        painter->drawLines(lines, draw_signal_strenght_value);
        painter->restore();

        painter->save();
        painter->setPen(QPen(Qt::gray,4));
        painter->drawLines(&lines[draw_signal_strenght_value], ((sizeof(lines)/ sizeof(lines[0])) - draw_signal_strenght_value));
        painter->restore();


        QFont font;
        painter->save();
        font.setPixelSize(15);
        painter->setFont(font);
        painter->setPen(QColor(51, 223, 35));
        if (m_timecost_ != 0)
        {
            video_timecost_str = QString("%1ms").arg(m_timecost_, 0, 'f', 0);
        } else {
            video_timecost_str = QString("N/A");
        }
        painter->drawText(QRect(-width/2+80, -height/2+40, 60, 40), Qt::AlignLeft, video_timecost_str);
        painter->restore();
    } else {
        QLine lines[] = {
            {width/2 - 80,  -height/2+30, width/2 - 80,  -height/2 + 25},
            {width/2 - 90,  -height/2+30, width/2 - 90,  -height/2 + 20},
            {width/2 - 100, -height/2+30, width/2 - 100, -height/2 + 15},
            {width/2 - 110, -height/2+30, width/2 - 110, -height/2 + 10},
            {width/2 - 120, -height/2+30, width/2 - 120, -height/2 + 5},
        };

        if ((m_timecost_ > 0) && (m_timecost_ < 100.0))
        {
            draw_signal_strenght_value = 5;
        } else if ((m_timecost_ > 100.0) && (m_timecost_ < 200.0)) {
            draw_signal_strenght_value = 4;
        } else if ((m_timecost_ > 200.0) && (m_timecost_ < 500.0)) {
            draw_signal_strenght_value = 3;
        } else if (m_timecost_ > 1000.0) {
            draw_signal_strenght_value = 1;
        } else {
            draw_signal_strenght_value = 0;
        }


        painter->save();
        painter->setPen(QPen(Qt::white,4));
        painter->drawLines(lines,  draw_signal_strenght_value);
        painter->restore();

        painter->save();
        painter->setPen(QPen(Qt::gray,4));
        painter->drawLines(&lines[draw_signal_strenght_value], ((sizeof(lines)/sizeof(lines[0])) - draw_signal_strenght_value));
        painter->restore();



        QFont font;
        painter->save();
        font.setPixelSize(15);
        painter->setFont(font);
        painter->setPen(QColor(51, 223, 35));
        if (m_timecost_ != 0)
        {
            video_timecost_str = QString("%1ms").arg(m_timecost_, 0, 'f', 0);
        } else {
            video_timecost_str = QString("N/A");
        }
        painter->drawText(QRect(width/2-120, -height/2+40, 60, 40), Qt::AlignLeft, video_timecost_str);
        painter->restore();
    }
}

void QCustomMobileSignal::drawSystemTime(QPainter *painter)
{
    int width = this->width();
    int height = this->height();
    QFont font;
    QString current_datetime_str = "";
    QDateTime datetimestamp = QDateTime::currentDateTime();

    painter->save();
    font.setPixelSize(15);
    painter->setFont(font);
    painter->setPen(QColor(51, 223, 35));
    current_datetime_str = datetimestamp.toString("yyyy-MM-dd hh:mm:ss");
    if (m_position_ == POSITION_RIGHT_TOP)
    {
        painter->drawText(QRect(-width/2 + 140, -height/2+40, 140, 40), Qt::AlignLeft, current_datetime_str);
    } else if (m_position_ == POSITION_LEFT_TOP) {
        painter->drawText(QRect(width/2 - 280, -height/2+40, 140, 40), Qt::AlignRight, current_datetime_str);
    } else {
        painter->drawText(QRect(width/4 - 300, -height/2+40, 200, 40), Qt::AlignLeft, current_datetime_str);
    }
    painter->restore();
}

void QCustomMobileSignal::updateValue()
{
    this->update();
}

void QCustomMobileSignal::updateValue(double value)
{
    this->m_timecost_ = value;
    this->update();
}

QColor QCustomMobileSignal::getBackgroundColor() const
{
    return this->m_background_color_;
}

QString QCustomMobileSignal::getTitle() const
{
    return this->m_title_;
}

double QCustomMobileSignal::getTimeCost() const
{
    return this->m_timecost_;
}

QSize QCustomMobileSignal::sizeHint() const
{
    return QSize(150, 150);
}

QSize QCustomMobileSignal::minimumSizeHint() const
{
    return QSize(30, 30);
}

void QCustomMobileSignal::setBackgroundColor(const QColor value)
{
    if (this->m_background_color_ != value)
    {
        this->m_background_color_ = value;
        this->update();
    }
}

void QCustomMobileSignal::setTitle(const QString value)
{
    if (this->m_title_ != value)
    {
        this->m_title_ = value;
        this->update();
    }
}

void QCustomMobileSignal::setTimeCost(const double value)
{
    if (this->m_timecost_ != value)
    {
        this->m_timecost_ = value;
        this->update();
    }
}

void QCustomMobileSignal::setPosition(const Position value)
{
    if (this->m_position_ != value)
    {
        this->m_position_ = value;
        this->update();
    }
}
