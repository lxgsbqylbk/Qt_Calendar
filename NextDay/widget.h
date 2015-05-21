#ifndef WIDGET_H
#define WIDGET_H
#include "ui_widget.h"
#include <QCalendarWidget>
#include <QGridLayout>
//#include <QDateTime>
#include <QWidget>
#include <QTime>
#include <QAction>
#include <QtCore>
#include <QString>
#include <QSystemTrayIcon>

const QString ZOX[] = {"鼠","牛","虎","兔","龙","蛇","马","羊","猴","鸡","狗","猪"};
const QString LUNAR_YEAR0[] = {"甲","乙","丙","丁","戊","己","庚","辛","壬","癸"};
const QString LUNAR_YEAR1[] = {"子","丑","寅","卯","辰","巳","午","未","申","酉","戌","亥"};

const int BEGIN_YEAR = 1900;
const int END_YEAR = 2100;
const int daynum[] = {31,28,31,30,31,30,31,31,30,31,30,31};

class Widget : public QWidget,public Ui::Widget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


private:
    QPair<QString,QString> starx[13][33];
    QString lunar_year[61];
//    QCalendarWidget *m_Calendar;
    QGridLayout *m_GridLayout;
    QDate m_Today;
    QTimer *m_timer;
    QPoint pos;
    QAction *hideAction,*quitAction;
    QMenu *menu;
    QSystemTrayIcon *trayIcon;
    QPalette pe;
    bool bDrag;
    void SetUI();
    void SetZodiac(int);
    void SetStar(int,int);
    void SetConnect();
    void SetLunarShow(int,QString);
    void InitComboBox();
    void SetUpContextMenu();
    void GoToCertainDay(QDate);
//    int drt;

private slots:
//    void paintEvent(QPaintEvent*);
    void ReturnToday();
    void HideToggle();
    void ToNextDay();
    void GetDateData();
    void ToPreDay();
    void SetCBDay();
    void DateChanged();
    void ToCertainDate();
    void SetCurrentTime();
    void contextMenuEvent(QContextMenuEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
};

#endif // WIDGET_H
