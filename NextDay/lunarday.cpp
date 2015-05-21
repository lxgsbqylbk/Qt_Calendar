#include "lunarday.h"
#include <ctime>
#include <cassert>
#include <cstring>
#include <iostream>

using namespace std;
using lunar::Date;

//使用比特位记录每年的情况
//0~4 共5bit 春节日份
//5~6 共2bit 春节月份
//7~19 共13bit 13个月的大小月情况(如果无闰月，最后位无效)，大月为1,小月为0
//20~23 共4bit 记录闰月的月份，如果没有闰月为0

static const int BEGIN_YEAR = 1901;
static const int NUMBER_YEAR = 199;
static const unsigned int LUNAR_YEARS[199] =
{
     0x04AE53,0x0A5748,0x5526BD,0x0D2650,0x0D9544,
     0x46AAB9,0x056A4D,0x09AD42,0x24AEB6,0x04AE4A, //1901-1910

     0x6A4DBE,0x0A4D52,0x0D2546,0x5D52BA,0x0B544E,
     0x0D6A43,0x296D37,0x095B4B,0x749BC1,0x049754, //1911-1920

     0x0A4B48,0x5B25BC,0x06A550,0x06D445,0x4ADAB8,
     0x02B64D,0x095742,0x2497B7,0x04974A,0x664B3E, //1921-1930

     0x0D4A51,0x0EA546,0x56D4BA,0x05AD4E,0x02B644,
     0x393738,0x092E4B,0x7C96BF,0x0C9553,0x0D4A48, //1931-1940

     0x6DA53B,0x0B554F,0x056A45,0x4AADB9,0x025D4D,
     0x092D42,0x2C95B6,0x0A954A,0x7B4ABD,0x06CA51, //1941-1950

     0x0B5546,0x555ABB,0x04DA4E,0x0A5B43,0x352BB8,
     0x052B4C,0x8A953F,0x0E9552,0x06AA48,0x7AD53C, //1951-1960

     0x0AB54F,0x04B645,0x4A5739,0x0A574D,0x052642,
     0x3E9335,0x0D9549,0x75AABE,0x056A51,0x096D46, //1961-1970

     0x54AEBB,0x04AD4F,0x0A4D43,0x4D26B7,0x0D254B,
     0x8D52BF,0x0B5452,0x0B6A47,0x696D3C,0x095B50, //1971-1980

     0x049B45,0x4A4BB9,0x0A4B4D,0xAB25C2,0x06A554,
     0x06D449,0x6ADA3D,0x0AB651,0x093746,0x5497BB, //1981-1990

     0x04974F,0x064B44,0x36A537,0x0EA54A,0x86B2BF,
     0x05AC53,0x0AB647,0x5936BC,0x092E50,0x0C9645, //1991-2000

     0x4D4AB8,0x0D4A4C,0x0DA541,0x25AAB6,0x056A49,
     0x7AADBD,0x025D52,0x092D47,0x5C95BA,0x0A954E, //2001-2010

     0x0B4A43,0x4B5537,0x0AD54A,0x955ABF,0x04BA53,
     0x0A5B48,0x652BBC,0x052B50,0x0A9345,0x474AB9, //2011-2020

     0x06AA4C,0x0AD541,0x24DAB6,0x04B64A,0x69573D,
     0x0A4E51,0x0D2646,0x5E933A,0x0D534D,0x05AA43, //2021-2030

     0x36B537,0x096D4B,0xB4AEBF,0x04AD53,0x0A4D48,
     0x6D25BC,0x0D254F,0x0D5244,0x5DAA38,0x0B5A4C, //2031-2040

     0x056D41,0x24ADB6,0x049B4A,0x7A4BBE,0x0A4B51,
     0x0AA546,0x5B52BA,0x06D24E,0x0ADA42,0x355B37, //2041-2050

     0x09374B,0x8497C1,0x049753,0x064B48,0x66A53C,
     0x0EA54F,0x06B244,0x4AB638,0x0AAE4C,0x092E42, //2051-2060

     0x3C9735,0x0C9649,0x7D4ABD,0x0D4A51,0x0DA545,
     0x55AABA,0x056A4E,0x0A6D43,0x452EB7,0x052D4B, //2061-2070

     0x8A95BF,0x0A9553,0x0B4A47,0x6B553B,0x0AD54F,
     0x055A45,0x4A5D38,0x0A5B4C,0x052B42,0x3A93B6, //2071-2080

     0x069349,0x7729BD,0x06AA51,0x0AD546,0x54DABA,
     0x04B64E,0x0A5743,0x452738,0x0D264A,0x8E933E, //2081-2090

     0x0D5252,0x0DAA47,0x66B53B,0x056D4F,0x04AE45,
     0x4A4EB9,0x0A4D4C,0x0D1541,0x2D92B5 //2091-2099

};

//计算这个公历日期是一年中的第几天
static int DayOfSolarYear(int year, int month, int day )
{
     //为了提高效率，记录每月一日是一年中的第几天
     static const int NORMAL_YDAY[12] = {1,32,60,91,121,152,
                     182,213,244,274,305,335};
     //闰年的情况
     static const int LEAP_YDAY[12] = {1,32,61,92,122,153,
                 183,214,245,275,306,336};
     const int *t_year_yday_ = NORMAL_YDAY;
     //判断是否是公历闰年
     if( year % 4 ==0 )
     {
         if(year%100 != 0) t_year_yday_ = LEAP_YDAY;
         if(year%400 == 0) t_year_yday_ = LEAP_YDAY;
     }
     return t_year_yday_[month -1] + (day -1);
}
Date lunar::LuanrDate(int solar_year,int solar_month,int solar_day)
{
     Date luanr_date ;
     luanr_date.year = solar_year;
     luanr_date.month = 0;
     luanr_date.day = 0;
     luanr_date.leap = false;
     //越界检查，如果越界，返回无效日期
//     cout<<solar_year<<endl;
     if(solar_year < BEGIN_YEAR || solar_year > BEGIN_YEAR + NUMBER_YEAR - 1 )
     {
//         cout<<"ERROR!!!!"<<endl;
          return luanr_date;
     }
     int year_index = solar_year - BEGIN_YEAR;
     //计算春节的公历日期
     int spring_ny_month = ( LUNAR_YEARS[year_index] & 0x60 ) >> 5;
     int spring_ny_day = ( LUNAR_YEARS[year_index] & 0x1f);
     //计算今天是公历年的第几天
     int today_solar_yd = DayOfSolarYear(solar_year,solar_month,solar_day);
     //计算春节是公历年的第几天
     int spring_ny_yd = DayOfSolarYear(solar_year,spring_ny_month,spring_ny_day);
     //计算今天是农历年的第几天
     int today_luanr_yd = today_solar_yd - spring_ny_yd + 1;
     //如果今天在春节的前面，重新计算today_luanr_yd
     if ( today_luanr_yd < 0)
     {
      //农历年比当前公历年小1
     year_index --;
     luanr_date.year --;
     //越界，返回无效日期
     if(year_index <0)
     return luanr_date;
     spring_ny_month = ( LUNAR_YEARS[year_index] & 0x60 ) >> 5;
     spring_ny_day = ( LUNAR_YEARS[year_index] & 0x1f);
     spring_ny_yd = DayOfSolarYear(solar_year,spring_ny_month,spring_ny_day);
     int year_total_day = DayOfSolarYear(luanr_date.year,12,31);
     today_luanr_yd = today_solar_yd + year_total_day - spring_ny_yd + 1;
     }
     int luanr_month = 1;
     //计算月份和日期
     for(;luanr_month<=13;luanr_month++)
     {
         int month_day = 29;
         if( (LUNAR_YEARS[year_index] >> (6 + luanr_month)) & 0x1 ) month_day = 30;
         if( today_luanr_yd <= month_day ) break;
         else today_luanr_yd -= month_day;
     }
     luanr_date.day = today_luanr_yd;
     //处理闰月
     int leap_month = (LUNAR_YEARS[year_index] >>20) & 0xf;
     if(leap_month > 0 && leap_month < luanr_month )
     {
         luanr_month --;
         //如果当前月为闰月，设置闰月标志

         if( luanr_month == leap_month ) luanr_date.leap = true;
     }
//     assert(leap_month <= 12);
     luanr_date.month = luanr_month;
     return luanr_date;
}
