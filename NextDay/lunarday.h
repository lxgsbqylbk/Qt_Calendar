#ifndef LUNARDAY_H
#define LUNARDAY_H


namespace lunar
{
     //保存一个农历日期

     typedef struct T_Date
     {
     //年
     int year;
     //月
     int month;
     //日
     int day;
     //是否闰月
     bool leap;
     }Date;
     //公历转农历
     Date LuanrDate(int solar_year,int solar_month,int solar_day);
}

#endif // LUNARDAY_H
