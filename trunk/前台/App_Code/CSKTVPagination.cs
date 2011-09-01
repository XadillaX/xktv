using System;
using System.Data;
using System.Configuration;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;

/// <summary>
///CSKTVPagination 的摘要说明
/// </summary>
/// 由朱凯迪移植自自己编写的PHP CodeIgniter分页类
public class CSKTVPagination
{
    public string first_page = "首页";
    public string last_page = "尾页";
    public string prev_page = "上一页";
    public string next_page = "下一页";
    public string Class = "xpage";
    public string id = "";
    public string a_class = "page_a";
    public string cur_class = "page_cur";
    public string no_link_class = "page_no_link";
    public bool all_link = false;

    public int rim_count = 3;
    public int center_count = 5;

    public int item_count = 0;
    public int per_page = 10;
    public int cur_page = 1;
    public int tot_page = 0;

    public string link_str = "";

    /**
     * Constructure.
     */
    public CSKTVPagination()
    {
        
    }

    /**
     * Set configuration.
     *
     * @param array $config
     */
    //public function set_config($config)
    //{
    //    foreach($config as $key => $value)
    //    {
    //        if(isset($this->$key))
    //        {
    //            $this->$key = $value;
    //        }
    //    }
    //}

    /**
     * Get page url by page number
     *
     * @param int $page The number of page
     * @return string The url
     */
    public String get_page_url(int page)
    {
        //return sprintf(link_str, page);
        return String.Format(link_str, page);
    }

    /**
     * Get page html
     *
     * @param int $page The number of page.
     * @param int $cur Current page.
     * @return string The whole html of each link.
     */
    public String get_page_html(int page, int cur)
    {
        string str = "";
        if(page == cur)
        {
            if(all_link == false)
            {
                str = "<span";
                if(cur_class != "") str += (" class=\"" + cur_class + "\"");
                str += (">" + page + "</span>");
            }
            else
            {
                str = "<a title=\"" + page + "\"";
                if(cur_class != "") str += (" class=\"" + cur_class + "\"");
                str += (" href=\"" + get_page_url(page) + "\">" + page + "</a>");
            }
        }
        else
        {
            str = "<a title=\"" + page + "\"";
            if(a_class != "") str = str + " class=\"" + a_class + "\"";
            str = str + " href=\"" + get_page_url(page) + "\">" + page + "</a>";
        }

        return str;
    }

    /**
     * Create links
     *
     * @return string links.
     */
    public String create_links()
    {
        /** Total page */
        if(per_page <= 0) return "";
        tot_page = (item_count / per_page);
        if(item_count % per_page != 0) tot_page++;
        if(tot_page == 0) tot_page = 1;

        /** Abour current page */
        if(cur_page > tot_page) return "";
        if(center_count % 2 == 0) center_count--;
        if(center_count <= 0) center_count = 1;

        /** Set links */
        String links = __begining_of_wrapper();
        links += __page_left();
        links += __links();
        links += __page_right();
        links += __ending_of_wrapper();

        return links;
    }

    /**
     * Get current page. (call after create_links)
     *
     * @return int Current page.
     */
    public int get_cur_page()
    {
        return cur_page;
    }

    /**
     * Get total page. (call after create_links)
     *
     * @return int Total page.
     */
    public int get_tot_page()
    {
        return tot_page;
    }

    /**
     * Get item count. (call after create_links)
     * 
     * @return int Item count;
     */
    public int get_count()
    {
        return item_count;
    }

    private String __links()
    {
        String str = "";

        /** LEFT */
        int left = rim_count;
        if(tot_page <= left) left = tot_page;
        for(int i = 1; i <= left; i++)
        {
            str += get_page_html(i, cur_page);
            str += " ";
        }
        if(left == tot_page) return str;

        /** CENTER */
        int middle_left = cur_page - (center_count / 2);
        int middle_right = cur_page + (center_count / 2);
        if(middle_left <= left) middle_left = left + 1;
        if(middle_left != left + 1) str += " ... ";
        if(middle_right > tot_page) middle_right = tot_page;
        for(int i = middle_left; i <= middle_right; i++)
        {
            str += get_page_html(i, cur_page);
            str += " ";
        }
        if(middle_right == tot_page) return str;

        /** RIGHT */
        int right = tot_page - rim_count + 1;
        if(right <= middle_right) right = middle_right + 1;
        if(middle_right + 1 != right) str += " ... ";
        for(int i = right; i <= tot_page; i++)
        {
            str += get_page_html(i, cur_page);
            str += " ";
        }

        return str;
    }

    private String __page_left()
    {
        String str = "";
        if(cur_page == 1)
        {
            if(!all_link)
            {
                str += "<span";
                if(no_link_class != "") str = str + " class=\"" + no_link_class + "\"";
                str = str + ">" + first_page + "</span> ";

                str += "<span";
                if(no_link_class != "") str = str + " class=\"" + no_link_class + "\"";
                str = str + ">" + prev_page + "</span> ";
            }
            else
            {
                str = str + "<a title=\"" + first_page + "\" href=\"#\"";
                if(no_link_class != "") str = str + " class=\"" + no_link_class + "\"";
                str = str + ">" + first_page + "</a> ";

                str = str + "<a title=\"" + prev_page + "\" href=\"#\"";
                if(no_link_class != "") str = str + " class=\"" + no_link_class + "\"";
                str = str + ">" + prev_page + "</a> ";
            }
        }
        else
        {
            str = str + "<a title=\"" + first_page + "\" href=\"" + get_page_url(1) + "\"";
            if(a_class != "") str = str + " class=\"" + a_class + "\"";
            str = str + ">" + first_page + "</a> ";

            str = str + "<a title=\"" + prev_page + "\" href=\"" + get_page_url(cur_page - 1) + "\"";
            if(a_class != "") str = str + " class=\"" + a_class + "\"";
            str = str + ">" + prev_page + "</a> ";
        }

        return str;
    }

    private String __page_right()
    {
        String str = "";
        if(cur_page == tot_page)
        {
            if(!all_link)
            {
                str += "<span";
                if(no_link_class != "") str = str + " class=\"" + no_link_class + "\"";
                str = str + ">" + next_page + "</span> ";

                str += "<span";
                if(no_link_class != "") str = str + " class=\"" + no_link_class + "\"";
                str = str + ">" + last_page + "</span> ";
            }
            else
            {
                str = str + "<a title=\"" + next_page + "\" href=\"#\"";
                if(no_link_class != "") str = str + " class=\"" + no_link_class + "\"";
                str = str + ">" + next_page + "</a> ";

                str = str + "<a title=\"" + last_page + "\" href=\"#\"";
                if(no_link_class != "") str = str + " class=\"" + no_link_class + "\"";
                str = str + ">" + last_page + "</a> ";
            }
        }
        else
        {
            str = str + "<a title=\"" + next_page + "\" href=\"" + get_page_url(cur_page + 1) + "\"";
            if(a_class != "") str = str + " class=\"" + a_class + "\"";
            str = str + ">" + next_page + "</a> ";

            str = str + "<a title=\"" + last_page + "\" href=\"" + get_page_url(tot_page) + "\"";
            if(a_class != "") str = str + " class=\"" + a_class + "\"";
            str = str + ">" + last_page + "</a> ";
        }

        return str;
    }

    private String __begining_of_wrapper()
    {
        String str = "<div";
        if(id != "") str = str + " id=\"" + id + "\"";
        if(Class != "") str = str + " class=\"" + Class + "\"";
        str += ">";

        return str;
    }

    private String __ending_of_wrapper()
    {
        return "</div>";
    }
}
