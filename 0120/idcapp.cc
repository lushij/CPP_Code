#include"idcapp.h"
//  把从文件读到的一行数据拆分到_zhobtmind结构体中。
bool CZHOBTMIND::splitbuffer(const string &line,const bool Isxml)
{
    memset(&_zhobtmind,0,sizeof(struct st_zhobtmind));

    // 解析行的内容（*.xml和*.csv的方法不同），把数据存放在结构体中。
    if (Isxml==true)
    {
        getxmlbuffer(line,"obtid",_zhobtmind.obtid,5);
        getxmlbuffer(line,"ddatetime",_zhobtmind.ddatetime,14); 
        char tmp[11];
        getxmlbuffer(line,"t",tmp,10);     if (strlen(tmp)>0) snprintf(_zhobtmind.t,10,"%d",(int)(atof(tmp)*10));
        getxmlbuffer(line,"p",tmp,10);    if (strlen(tmp)>0) snprintf(_zhobtmind.p,10,"%d",(int)(atof(tmp)*10));
        getxmlbuffer(line,"u",_zhobtmind.u,10);
        getxmlbuffer(line,"wd",_zhobtmind.wd,10);
        getxmlbuffer(line,"wf",tmp,10);  if (strlen(tmp)>0) snprintf(_zhobtmind.wf,10,"%d",(int)(atof(tmp)*10));
        getxmlbuffer(line,"r",tmp,10);     if (strlen(tmp)>0) snprintf(_zhobtmind.r,10,"%d",(int)(atof(tmp)*10));
        getxmlbuffer(line,"vis",tmp,10);  if (strlen(tmp)>0) snprintf(_zhobtmind.vis,10,"%d",(int)(atof(tmp)*10));
    }
    else
    {
        ccmdstr cmdstr;
        cmdstr.splittocmd(line,",");
        cmdstr.getvalue(0,_zhobtmind.obtid,5);
        cmdstr.getvalue(1,_zhobtmind.ddatetime,14);
        char tmp[11];
        cmdstr.getvalue(2,tmp,10); if (strlen(tmp)>0) snprintf(_zhobtmind.t,10,"%d",(int)(atof(tmp)*10));
        cmdstr.getvalue(3,tmp,10); if (strlen(tmp)>0) snprintf(_zhobtmind.p,10,"%d",(int)(atof(tmp)*10));
        cmdstr.getvalue(4,_zhobtmind.u,10);
        cmdstr.getvalue(5,_zhobtmind.wd,10);
        cmdstr.getvalue(6,tmp,10); if (strlen(tmp)>0) snprintf(_zhobtmind.wf,10,"%d",(int)(atof(tmp)*10));
        cmdstr.getvalue(7,tmp,10); if (strlen(tmp)>0) snprintf(_zhobtmind.r,10,"%d",(int)(atof(tmp)*10));
        cmdstr.getvalue(8,tmp,10); if (strlen(tmp)>0) snprintf(_zhobtmind.vis,10,"%d",(int)(atof(tmp)*10));
    }

    _line=line;

    return true;
}

// 把_zhobtmind结构体中的数据插入到T_ZHOBTMIND表中。
bool CZHOBTMIND::inserttable()
{
    if (_stmt.isopen()==false)
    {
        // 准备操作表的sql语句，绑定输入参数。
        _stmt.connect(&_conn);
        _stmt.prepare("insert into T_ZHOBTMIND(obtid,ddatetime,t,p,u,wd,wf,r,vis,keyid) "\
                                   "values(:1,to_date(:2,'yyyymmddhh24miss'),:3,:4,:5,:6,:7,:8,:9,SEQ_ZHOBTMIND.nextval)");
        _stmt.bindin(1,_zhobtmind.obtid,5);
        _stmt.bindin(2,_zhobtmind.ddatetime,14);
        _stmt.bindin(3,_zhobtmind.t,10);
        _stmt.bindin(4,_zhobtmind.p,10);
        _stmt.bindin(5,_zhobtmind.u,10);
        _stmt.bindin(6,_zhobtmind.wd,10);
        _stmt.bindin(7,_zhobtmind.wf,10);
        _stmt.bindin(8,_zhobtmind.r,10);
        _stmt.bindin(9,_zhobtmind.vis,10);
    }

    // 把解析后的数据入库（插入到数据库的表中）。
    if (_stmt.execute()!=0)
    {
        // 失败的原因主要有二：一是记录重复，二是数据内容非法。
        // 如果失败的原因是数据内容非法，记录日志后继续；如果是记录重复，不必记录日志，且继续。
        if (_stmt.rc()!=1)
        {
            _logfile.write("line=%s\n",_line.c_str());
            _logfile.write("_stmt.execute() failed.\n%s\n%s\n",_stmt.sql(),_stmt.message());
        }

        return false;
    }

    return true;
}

