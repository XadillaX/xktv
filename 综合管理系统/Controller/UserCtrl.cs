using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using KTV.Model.DataLink;
using KTV.Model.DataRow;

namespace KTV.Controller
{
    #region 登录控制器类
    class UserCtrl : ObjectCtrl
    {
        #region 公共的方法（登录）
        static public String Login(String Username, String Password, int Type)
        {
            if (Username == "" || Password == "")
            {
                return "用户名或者密码不能为空！";
            }
            else
            if (Username.Length > 16)
            {
                return "用户名长度必须小于16！";
            }
            else
            if (Password.Length > 32)
            {
                return "密码长度必须小于32！";
            }

            FrontDeskUserModel FDUM = new FrontDeskUserModel();
            IList<FrontDeskUserInfo> list = FDUM.GetUserInfo(Username);

            /** 查询出错 */
            if (null == list)
            {
                return "系统错误：" + FDUM.LastErr;
            }

            /** 用户名密码错误 */
            if (list.Count == 0 || list[0].Password != Password)
            {
                return "用户名或者密码错误！";
            }

            /** 权限不足 */
            if (list[0].Type < Type)
            {
                return "权限不足！";
            }

            /** 登录 */
            Dictionary<String, String> info = new Dictionary<String, String>();
            info["LoginTime"] = DateTime.Now.ToString();
            FDUM.SetUserInfo(list[0].UID, info);

            return "";
        }
        #endregion

        #region 公共的方法（修改密码）
        static public String ChangePwd(String Username, String Password, String NewPassword, String RePassword)
        {
            if (Username == "" || Password == "" || NewPassword == "" || RePassword == "")
            {
                return "用户名或者密码不能为空！";
            }

            if (Username.Length > 16 || Password.Length > 16 || NewPassword.Length > 16 || RePassword.Length > 16)
            {
                return "用户名长度不能超过16，密码长度不能超过32！";
            }

            if (NewPassword != RePassword)
            {
                return "两次新密码输入不一致！";
            }

            FrontDeskUserModel FDUM = new FrontDeskUserModel();
            IList<FrontDeskUserInfo> list = FDUM.GetUserInfo(Username);

            if (null == list)
            {
                return "系统错误: " + FDUM.LastErr;
            }

            if (list.Count == 0 || list[0]["Password"].ToString() != Password)
            {
                return "用户名或者密码错误。";
            }

            Dictionary<String, String> info = new Dictionary<String, String>();
            info["Password"] = NewPassword;

            return FDUM.SetUserInfo(list[0].UID, info);
        }
        #endregion

        #region 公共的方法 R（获取用户列表）
        static public IList<FrontDeskUserInfo> GetUserList(String condition)
        {
            FrontDeskUserModel FDUM = new FrontDeskUserModel();
            return FDUM.GetUserInfo(condition, true);
        }
        #endregion

        #region 公共的方法 C（插入用户）
        static public String CreateUser(String Username, String Password, bool bAdmin)
        {
            // 只是简单检验一下，包括注入之类的都不检验了
            Username = Username.Trim();
            if (Username == "" || Username.Length > 16)
            {
                return "用户名长度需大于等于1小于16。";
            }
            else
            if (Password == "" || Password.Length > 32)
            {
                return "密码长度需大于等于1小于32。";
            }

            FrontDeskUserModel FDUM = new FrontDeskUserModel();
            return FDUM.CreateUser(Username, Password, Convert.ToInt32(bAdmin));
        }
        #endregion

        #region 公共的方法 U（修改用户资料）
        static public String ModifyUser(String Username, String Password, bool bAdmin)
        {
            FrontDeskUserModel FDUM = new FrontDeskUserModel();
            IList<FrontDeskUserInfo> list = FDUM.GetUserInfo(Username);

            if (null == list)
            {
                return "系统错误: " + FDUM.LastErr;
            }

            Dictionary<String, String> info = new Dictionary<String, String>();
            if (Password != "") info["Password"] = Password;
            info["Type"] = Convert.ToInt32(bAdmin).ToString();

            return FDUM.SetUserInfo(list[0].UID, info);
        }
        #endregion

        #region 公共的方法 D（删除用户）
        static public String DeleteUser(int UID)
        {
            FrontDeskUserModel FDUM = new FrontDeskUserModel();
            if (!FDUM.DeleteUser(UID))
            {
                return FDUM.LastErr;
            }
            else return "";
        }
        #endregion
    }
    #endregion
}
