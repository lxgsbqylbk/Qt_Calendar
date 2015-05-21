#include "widget.h"
#include "lunar.h"

#include <ctime>
#include <QDebug>
#include <QMenu>
#include <QPainter>
#include <QBitmap>
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QTextCharFormat>

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    SetUI();
    SetConnect();
    //初始化星座
    GetDateData();
}
void Widget::SetUI()
{
    bDrag=false;
    setupUi(this);
    setWindowFlags (Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    this->move( (QApplication::desktop()->width()-this->width())/2 ,
                (QApplication::desktop()->height()-this->height())/2 );
    m_Calendar->setMinimumDate(QDate(BEGIN_YEAR,1,1));
    m_Calendar->setMaximumDate(QDate(END_YEAR,12,31));
    m_Calendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);
    m_Today = m_Calendar->selectedDate().currentDate();
    SetUpContextMenu();
    QTextCharFormat format;
    format.setBackground(Qt::yellow);
    m_Calendar->setDateTextFormat(m_Today,format);
    InitComboBox();
    m_timer = new QTimer(this);
    m_timer->start(1000);
}

void Widget::SetUpContextMenu()
{
    menu = new QMenu(this);
    hideAction = new QAction(tr("隐藏界面"),this);
    hideAction->setIcon(QIcon(":/operation/ico/hide.ico"));
    quitAction = new QAction(tr("退出程序"),this);
    quitAction->setIcon(QIcon(":/operation/ico/quit.ico"));
    menu->addSeparator();
    menu->addAction(hideAction);
    menu->addSeparator();
    menu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setToolTip("Nextday");
    trayIcon->setContextMenu(menu);
    trayIcon->setIcon(QIcon(":/operation/ico/calendar.ico"));
    trayIcon->show();
    trayIcon->showMessage("Nextday","今天是公历"+QString::number(m_Today.year())+"年"
                          +QString::number(m_Today.month())+"月"+QString::number(m_Today.day())+"日"
                          ,QSystemTrayIcon::Information,2000);
    connect(hideAction,SIGNAL(triggered()),this,SLOT(HideToggle()));
    connect(quitAction,SIGNAL(triggered()),this,SLOT(close()));
}
void Widget::HideToggle()
{
    if(this->isHidden())
    {
        this->showNormal();
        hideAction->setText("隐藏界面");
    }
    else
    {
        this->hide();
        hideAction->setText("显示界面");
        trayIcon->showMessage("Nextday","点击此处恢复界面",QSystemTrayIcon::Information,2000);
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        bDrag=true;
        pos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(bDrag && (event->buttons() & Qt::LeftButton))
    {
        move(event->globalPos() - pos);
        event->accept();
    }
}
void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    bDrag=false;
    event->accept();
}

void Widget::SetCurrentTime()
{
    QDateTime datetime = QDateTime::currentDateTime();
    m_ShowTimeLabel->setText(datetime.time().toString());
    if(datetime.time().hour()==0 && datetime.time().minute()==0 && datetime.time().second()<=1)
    {
        QTextCharFormat format;
        format.setBackground(Qt::transparent);
        m_Calendar->setDateTextFormat(m_Today,format);
        m_Today=datetime.date();
        format.setBackground(Qt::yellow);
        m_Calendar->setDateTextFormat(m_Today,format);
    }
}

void Widget::SetConnect()
{
    //每秒显示时间
    connect(m_timer,SIGNAL(timeout()),this,SLOT(SetCurrentTime()));
    //返回今天
    connect(m_TotodayButton,SIGNAL(clicked()),this,SLOT(ReturnToday()));

    connect(m_Calendar,SIGNAL(selectionChanged()),this,SLOT(DateChanged()));
    connect(m_NextDayButton,SIGNAL(clicked()),this,SLOT(ToNextDay()));
    connect(m_ToPreDayButton,SIGNAL(clicked()),this,SLOT(ToPreDay()));

    connect(m_YearComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(ToCertainDate()));
    connect(m_MonthComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(ToCertainDate()));
    connect(m_DayComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(ToCertainDate()));
    connect(m_YearComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(SetCBDay()));
    connect(m_MonthComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(SetCBDay()));

    QTimer::singleShot(0,this,SLOT(SetCurrentTime()));
    QTimer::singleShot(0,this,SLOT(DateChanged()));
}
void Widget::ToNextDay()
{
    QDate today= m_Calendar->selectedDate();
    int year=today.year();
    int month=today.month();
    int day=today.day();

    //计算下一天

    //闰年的二月
    if(((year%4==0 && year%100!=0) || year%400==0) && month==2 && day==28)
    {
        day++;
    }
    else
    {
        day++;
        if(day>daynum[month-1])
        {
            day=1;
            month++;
            if(month>12)
            {
                year++;
                month=1;
                if(year>END_YEAR) return;
            }
        }
    }
    m_Calendar->setSelectedDate(QDate(year,month,day));
    m_Calendar->setFocus();
}
void Widget::ToPreDay()
{
    m_Calendar->setSelectedDate(m_Calendar->selectedDate().addDays(-1));
    m_Calendar->setFocus();
}
void Widget::SetZodiac(int year)
{
    int index=(year-1900+12)%12;
    m_ZodiacButton->setIcon(QIcon(":/zodiac/ico/"+QString::number(index)+".ico"));
    m_ZodiacButton->setToolTip(QString::number(year)+"年是"+ZOX[index]+"年");
}
void Widget::SetStar(int month,int day)
{
    m_StarButton->setIcon(QIcon(starx[month][day].second));
    m_StarButton->setToolTip(starx[month][day].first);
}
void Widget::DateChanged()
{
    m_Calendar->setFocus();
    int year=m_Calendar->selectedDate().year();
    int month=m_Calendar->selectedDate().month();
    int day=m_Calendar->selectedDate().day();

    int lunaryear=0,lunarmonth=0,lunarday=0;
    QString lunarstring = GetLunarStringX(year,month,day,lunaryear,lunarmonth,lunarday);

    SetLunarShow(lunaryear,lunarstring);
    SetZodiac(lunaryear);
    SetStar(month,day);
    if(m_YearComboBox->currentIndex()+BEGIN_YEAR==year && m_MonthComboBox->currentIndex()+1==month
            && m_DayComboBox->currentIndex()+1==day ) return;
    m_YearComboBox->setCurrentIndex(year-BEGIN_YEAR);
    m_MonthComboBox->setCurrentIndex(month-1);
    m_DayComboBox->setCurrentIndex(day-1);
}
void Widget::InitComboBox()
{
    for(int year=BEGIN_YEAR;year<=END_YEAR;year++)
    {
        m_YearComboBox->addItem(QString::number(year));
    }
    for(int month=1;month<=12;month++)
    {
        m_MonthComboBox->addItem(QString::number(month));
    }
    SetCBDay();
}
void Widget::SetCBDay()
{
    m_Calendar->setFocus();
    int year = m_YearComboBox->currentIndex()+BEGIN_YEAR;
    int month = m_MonthComboBox->currentIndex()+1;
    int tmpdayindex=m_DayComboBox->currentIndex();

    m_DayComboBox->clear();
    for(int day=1;day<=daynum[month-1];day++)
    {
        m_DayComboBox->addItem(QString::number(day));
    }
    if(month==2 && ((year%4==0 && year%100!=0) || year%400==0))
    {
        m_DayComboBox->addItem(QString::number(29));
    }
    if(m_DayComboBox->count()>tmpdayindex) m_DayComboBox->setCurrentIndex(tmpdayindex);
    else m_DayComboBox->setCurrentIndex(m_DayComboBox->count()-1);
}
void Widget::ToCertainDate()
{
    m_Calendar->setFocus();
    int year=m_YearComboBox->currentIndex()+BEGIN_YEAR;
    int month=m_MonthComboBox->currentIndex()+1;
    int day=m_DayComboBox->currentIndex()+1;
    QComboBox *s = qobject_cast<QComboBox *>(sender());
    if(s==m_YearComboBox && m_Calendar->selectedDate().year()==year) return;
    if(s==m_MonthComboBox && m_Calendar->selectedDate().month()==month) return;
    if(s==m_DayComboBox && m_Calendar->selectedDate().day()==day) return;
    m_Calendar->setSelectedDate(QDate(year,month,day));
}
void Widget::GetDateData()
{
    //初始化星座
    for(int month=1;month<=12;month++)
    {
        for(int day=1;day<=31;day++)
        {
            if((month==3 && day>=21) || (month==4 && day<=19)) starx[month][day]=qMakePair(QString("白羊座"),QString(":/zodiac/ico/")+QString("aries.ico"));
            else if((month==4 && day>=20) || (month==5 && day<=20)) starx[month][day]=qMakePair(QString("金牛座"),QString(":/zodiac/ico/")+QString("taurus.ico"));
            else if((month==5 && day>=21) || (month==6 && day<=21)) starx[month][day]=qMakePair(QString("双子座"),QString(":/zodiac/ico/")+QString("gemini.ico"));
            else if((month==6 && day>=22) || (month==7 && day<=22)) starx[month][day]=qMakePair(QString("巨蟹座"),QString(":/zodiac/ico/")+QString("cancer.ico"));
            else if((month==7 && day>=23) || (month==8 && day<=22)) starx[month][day]=qMakePair(QString("狮子座"),QString(":/zodiac/ico/")+QString("lion.ico"));
            else if((month==8 && day>=23) || (month==9 && day<=22)) starx[month][day]=qMakePair(QString("处女座"),QString(":/zodiac/ico/")+QString("virgo.ico"));
            else if((month==9 && day>=23) || (month==10 && day<=23)) starx[month][day]=qMakePair(QString("天秤座"),QString(":/zodiac/ico/")+QString("libra.ico"));
            else if((month==10 && day>=24) || (month==11 && day<=22)) starx[month][day]=qMakePair(QString("天蝎座"),QString(":/zodiac/ico/")+QString("scorpio.ico"));
            else if((month==11 && day>=23) || (month==12 && day<=21)) starx[month][day]=qMakePair(QString("射手座"),QString(":/zodiac/ico/")+QString("sagittarius.ico"));
            else if((month==12 && day>=22) || (month==1 && day<=19)) starx[month][day]=qMakePair(QString("摩羯座"),QString(":/zodiac/ico/")+QString("capricorn.ico"));
            else if((month==1 && day>=20) ||  (month==2 && day<=18)) starx[month][day]=qMakePair(QString("水瓶座"),QString(":/zodiac/ico/")+QString("aquarius.ico"));
            else if((month==2 && day>=19) ||  (month==3 && day<=20)) starx[month][day]=qMakePair(QString("双鱼座"),QString(":/zodiac/ico/")+QString("pisces.ico"));
        }
    }
    int tot=0;
    for(int i=0;i<10;i++)
    {
        for(int j=i;;)
        {
            lunar_year[tot++] = LUNAR_YEAR0[i] + LUNAR_YEAR1[j];
            if((j+10)%12==i) break;
            j=(j+10)%12;
        }
    }
}
void Widget::SetLunarShow(int year,QString lunarstring)
{
    int x=(year-1864)%60;
    QString yearName = lunar_year[x%10 * 6 + (int)(x/10)];
    m_ShowDateLabel->setText(yearName+"年"+" "+lunarstring);
}

void Widget::ReturnToday()
{
    if(m_Calendar->selectedDate()!=m_Today) m_Calendar->setSelectedDate(m_Today);
    else m_Calendar->setFocus();
}
void Widget::contextMenuEvent(QContextMenuEvent *event)
{
    menu->exec(event->globalPos());
}

Widget::~Widget()
{
}
