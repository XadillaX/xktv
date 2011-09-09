using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace KTV.Model.DataRow
{
    enum TYPE_PRICE_ENUM
    {
        TPE_WEEKDAY_DAY = 0,
        TPE_WEEKDAY_GOLD = 1,
        TPE_WEEKDAY_NIGHT = 2,
        TPE_WEEKEND_DAY = 3,
        TPE_WEEKEND_GOLD = 4,
        TPE_WEEKEND_NIGHT = 5
    };

    class MachineTypeInfo : ObjectInfo
    {
        public String TypeNo { set; get; }
        public String TypeName { set; get; }

        public Double PriceWeekdaysDay { set; get; }
        public Double PriceWeekdaysGold { set; get; }
        public Double PriceWeekdaysNight { set; get; }

        public Double PriceWeekendDay { set; get; }
        public Double PriceWeekendGold { set; get; }
        public Double PriceWeekendNight { set; get; }

        #region 公共的方法（分配价格）
        public void SetPrice(Double Price, TYPE_PRICE_ENUM time)
        {
            switch (time)
            {
                case TYPE_PRICE_ENUM.TPE_WEEKDAY_DAY:
                    {
                        PriceWeekdaysDay = Price;
                        break;
                    }

                case TYPE_PRICE_ENUM.TPE_WEEKDAY_GOLD:
                    {
                        PriceWeekdaysGold = Price;
                        break;
                    }

                case TYPE_PRICE_ENUM.TPE_WEEKDAY_NIGHT:
                    {
                        PriceWeekdaysNight = Price;
                        break;
                    }

                case TYPE_PRICE_ENUM.TPE_WEEKEND_DAY:
                    {
                        PriceWeekendDay = Price;
                        break;
                    }

                case TYPE_PRICE_ENUM.TPE_WEEKEND_GOLD:
                    {
                        PriceWeekendGold = Price;
                        break;
                    }

                case TYPE_PRICE_ENUM.TPE_WEEKEND_NIGHT:
                    {
                        PriceWeekendNight = Price;
                        break;
                    }
            }
        }
        #endregion

        #region 公共的方法（分配价格）
        public void SetPrice(Decimal Price, TYPE_PRICE_ENUM time)
        {
            SetPrice(Convert.ToDouble(Price), time);
        }
        #endregion

        #region 公共的属性（分配价格）
        public String Price
        {
            set
            {
                String[] p = value.Split('|');

                SetPrice(Convert.ToDouble(p[0]), TYPE_PRICE_ENUM.TPE_WEEKDAY_DAY);
                SetPrice(Convert.ToDouble(p[1]), TYPE_PRICE_ENUM.TPE_WEEKDAY_GOLD);
                SetPrice(Convert.ToDouble(p[2]), TYPE_PRICE_ENUM.TPE_WEEKDAY_NIGHT);
                SetPrice(Convert.ToDouble(p[3]), TYPE_PRICE_ENUM.TPE_WEEKEND_DAY);
                SetPrice(Convert.ToDouble(p[4]), TYPE_PRICE_ENUM.TPE_WEEKEND_GOLD);
                SetPrice(Convert.ToDouble(p[5]), TYPE_PRICE_ENUM.TPE_WEEKEND_NIGHT);
            }

            get
            {
                String str = PriceWeekdaysDay.ToString() + "|";
                str += (PriceWeekdaysGold.ToString() + "|");
                str += (PriceWeekdaysNight.ToString() + "|");
                str += (PriceWeekendDay.ToString() + "|");
                str += (PriceWeekendGold.ToString() + "|");
                str += (PriceWeekendNight.ToString() + "|");

                return str;
            }
        }
        #endregion

        #region 公开的索引指示器
        new public Object this[String Key]
        {
            get
            {
                switch (Key)
                {
                    case "TypeNo": return TypeNo;
                    case "TypeName": return TypeName;
                    case "PriceWeekdaysDay": return PriceWeekdaysDay;
                    case "PriceWeekdaysGold": return PriceWeekdaysGold;
                    case "PriceWeekdaysNight": return PriceWeekdaysNight;
                    case "PriceWeekendDay": return PriceWeekendDay;
                    case "PriceWeekendGold": return PriceWeekendGold;
                    case "PriceWeekendNight": return PriceWeekendNight;
                    case "Price": return Price;

                    default: return null;
                }
            }

            set
            {
                switch (Key)
                {
                    case "TypeNo": TypeNo = (String)value; break;
                    case "TypeName": TypeName = (String)value; break;
                    case "PriceWeekdaysDay": PriceWeekdaysDay = (Double)value; break;
                    case "PriceWeekdaysGold": PriceWeekdaysGold = (Double)value; break;
                    case "PriceWeekdaysNight": PriceWeekdaysNight = (Double)value; break;
                    case "PriceWeekendDay": PriceWeekendDay = (Double)value; break;
                    case "PriceWeekendGold": PriceWeekendGold = (Double)value; break;
                    case "PriceWeekendNight": PriceWeekendNight = (Double)value; break;
                    case "Price": Price = (String)value; break;

                    default: break;
                }
            }
        }
        #endregion
    }
}
