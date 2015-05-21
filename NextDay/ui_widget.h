/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_5;
    QCalendarWidget *m_Calendar;
    QVBoxLayout *verticalLayout;
    QLabel *m_ShowDateLabel;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *m_YearComboBox;
    QLabel *m_YearLabel;
    QComboBox *m_MonthComboBox;
    QLabel *m_MonthLabel;
    QComboBox *m_DayComboBox;
    QLabel *m_DayLabel;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *m_ToPreDayButton;
    QToolButton *m_NextDayButton;
    QToolButton *m_TotodayButton;
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout;
    QToolButton *m_StarButton;
    QToolButton *m_ZodiacButton;
    QLabel *m_ShowTimeLabel;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(816, 196);
        layoutWidget = new QWidget(Widget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 798, 177));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        m_Calendar = new QCalendarWidget(layoutWidget);
        m_Calendar->setObjectName(QStringLiteral("m_Calendar"));
        m_Calendar->setAutoFillBackground(true);
        m_Calendar->setGridVisible(true);
        m_Calendar->setNavigationBarVisible(false);
        m_Calendar->setDateEditEnabled(false);

        horizontalLayout_5->addWidget(m_Calendar);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        m_ShowDateLabel = new QLabel(layoutWidget);
        m_ShowDateLabel->setObjectName(QStringLiteral("m_ShowDateLabel"));
        QFont font;
        font.setFamily(QStringLiteral("DejaVu Sans Mono"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        m_ShowDateLabel->setFont(font);
        m_ShowDateLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(m_ShowDateLabel);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        m_YearComboBox = new QComboBox(layoutWidget);
        m_YearComboBox->setObjectName(QStringLiteral("m_YearComboBox"));

        horizontalLayout_3->addWidget(m_YearComboBox);

        m_YearLabel = new QLabel(layoutWidget);
        m_YearLabel->setObjectName(QStringLiteral("m_YearLabel"));
        m_YearLabel->setLayoutDirection(Qt::LeftToRight);
        m_YearLabel->setAutoFillBackground(false);
        m_YearLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(m_YearLabel);

        m_MonthComboBox = new QComboBox(layoutWidget);
        m_MonthComboBox->setObjectName(QStringLiteral("m_MonthComboBox"));

        horizontalLayout_3->addWidget(m_MonthComboBox);

        m_MonthLabel = new QLabel(layoutWidget);
        m_MonthLabel->setObjectName(QStringLiteral("m_MonthLabel"));
        m_MonthLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(m_MonthLabel);

        m_DayComboBox = new QComboBox(layoutWidget);
        m_DayComboBox->setObjectName(QStringLiteral("m_DayComboBox"));

        horizontalLayout_3->addWidget(m_DayComboBox);

        m_DayLabel = new QLabel(layoutWidget);
        m_DayLabel->setObjectName(QStringLiteral("m_DayLabel"));
        m_DayLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(m_DayLabel);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        m_ToPreDayButton = new QToolButton(layoutWidget);
        m_ToPreDayButton->setObjectName(QStringLiteral("m_ToPreDayButton"));
        m_ToPreDayButton->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon;
        icon.addFile(QStringLiteral(":/operation/ico/left.ico"), QSize(), QIcon::Normal, QIcon::Off);
        m_ToPreDayButton->setIcon(icon);
        m_ToPreDayButton->setIconSize(QSize(32, 16));
        m_ToPreDayButton->setAutoRaise(true);

        horizontalLayout_2->addWidget(m_ToPreDayButton);

        m_NextDayButton = new QToolButton(layoutWidget);
        m_NextDayButton->setObjectName(QStringLiteral("m_NextDayButton"));
        m_NextDayButton->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/operation/ico/right.ico"), QSize(), QIcon::Normal, QIcon::Off);
        m_NextDayButton->setIcon(icon1);
        m_NextDayButton->setAutoRaise(true);

        horizontalLayout_2->addWidget(m_NextDayButton);

        m_TotodayButton = new QToolButton(layoutWidget);
        m_TotodayButton->setObjectName(QStringLiteral("m_TotodayButton"));
        m_TotodayButton->setCursor(QCursor(Qt::PointingHandCursor));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/operation/ico/today.ico"), QSize(), QIcon::Normal, QIcon::Off);
        m_TotodayButton->setIcon(icon2);
        m_TotodayButton->setIconSize(QSize(16, 16));
        m_TotodayButton->setPopupMode(QToolButton::DelayedPopup);
        m_TotodayButton->setAutoRaise(true);

        horizontalLayout_2->addWidget(m_TotodayButton);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        m_StarButton = new QToolButton(layoutWidget);
        m_StarButton->setObjectName(QStringLiteral("m_StarButton"));
        m_StarButton->setIconSize(QSize(48, 48));
        m_StarButton->setAutoRaise(true);

        horizontalLayout->addWidget(m_StarButton);

        m_ZodiacButton = new QToolButton(layoutWidget);
        m_ZodiacButton->setObjectName(QStringLiteral("m_ZodiacButton"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/zodiac/ico/7.ico"), QSize(), QIcon::Normal, QIcon::Off);
        m_ZodiacButton->setIcon(icon3);
        m_ZodiacButton->setIconSize(QSize(48, 48));
        m_ZodiacButton->setAutoRaise(true);

        horizontalLayout->addWidget(m_ZodiacButton);


        horizontalLayout_4->addLayout(horizontalLayout);

        m_ShowTimeLabel = new QLabel(layoutWidget);
        m_ShowTimeLabel->setObjectName(QStringLiteral("m_ShowTimeLabel"));
        QFont font1;
        font1.setFamily(QStringLiteral("DejaVu Sans Mono"));
        font1.setPointSize(13);
        font1.setBold(true);
        font1.setWeight(75);
        m_ShowTimeLabel->setFont(font1);
        m_ShowTimeLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(m_ShowTimeLabel);


        verticalLayout->addLayout(horizontalLayout_4);


        horizontalLayout_5->addLayout(verticalLayout);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        m_ShowDateLabel->setText(QApplication::translate("Widget", "Label", 0));
        m_YearLabel->setText(QApplication::translate("Widget", "\345\271\264", 0));
        m_MonthLabel->setText(QApplication::translate("Widget", "\346\234\210", 0));
        m_DayLabel->setText(QApplication::translate("Widget", "\346\227\245", 0));
#ifndef QT_NO_TOOLTIP
        m_ToPreDayButton->setToolTip(QApplication::translate("Widget", "\345\211\215\344\270\200\345\244\251", 0));
#endif // QT_NO_TOOLTIP
        m_ToPreDayButton->setText(QApplication::translate("Widget", "...", 0));
#ifndef QT_NO_TOOLTIP
        m_NextDayButton->setToolTip(QApplication::translate("Widget", "\345\220\216\344\270\200\345\244\251", 0));
#endif // QT_NO_TOOLTIP
        m_NextDayButton->setText(QApplication::translate("Widget", "...", 0));
#ifndef QT_NO_TOOLTIP
        m_TotodayButton->setToolTip(QApplication::translate("Widget", "\344\273\212\345\244\251", 0));
#endif // QT_NO_TOOLTIP
        m_TotodayButton->setText(QApplication::translate("Widget", "...", 0));
        m_StarButton->setText(QString());
        m_ZodiacButton->setText(QString());
        m_ShowTimeLabel->setText(QApplication::translate("Widget", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
