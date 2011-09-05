using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace KTV.Model.DataRow
{
    #region 登录用户信息类
    class FrontDeskUserInfo : DataRow.ObjectInfo
    {
        public int UID = 0;
        public String Username = "";
        public String Password = "";
        public DateTime LoginTime = DateTime.Now;
        public int Type = 0;

        public FrontDeskUserInfo()
        {
        }
        public FrontDeskUserInfo(int _UID, String _Username, String _Password, DateTime _LoginTime, int _Type)
        {
            UID = _UID;
            Username = _Username;
            Password = _Password;
            LoginTime = _LoginTime;
            Type = _Type;
        }

        #region 公开的索引指示器
        new public Object this[String Key]
        {
            get
            {
                switch (Key)
                {
                    case "UID": return UID;
                    case "Username": return Username;
                    case "Password": return Password;
                    case "LoginTime": return LoginTime;
                    case "Type": return Type;

                    default: return null;
                }
            }

            set
            {
                switch (Key)
                {
                    case "UID": UID = (int)value; break;
                    case "Username": Username = (String)value; break;
                    case "Password": Password = (String)value; break;
                    case "LoginTime": LoginTime = (DateTime)value; break;
                    case "Type": Type = (int)value; break;

                    default: break;
                }
            }
        }
        #endregion
    }
    #endregion
}
