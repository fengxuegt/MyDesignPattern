/*
 * Created 2022-07-22 23:03:23
 * Author : fengxuegt
 * Email : fengxuegt@163.com
 * 
 * 代理模式：通过代理类，来控制实际对象的访问权限
 * 客户    助理proxy    老板
 */

#include<iostream>
using namespace std;

class VideoSite {
public:
    virtual void freeMovie() = 0; // free
    virtual void vipMovie() = 0; // vip 
    virtual void ticketMovie() = 0; // ticket
    virtual ~VideoSite() {}
};



class FixBugVideoSite : public VideoSite{
public:
    virtual void freeMovie() {
        cout << "freeMovie" << endl;
    }
    virtual void vipMovie() {
        cout << "vipMovie" << endl;
    }
    virtual void ticketMovie() {
        cout << "ticketMovie" << endl;
    }
};

class FreeVideoSite : public VideoSite {
public:
    FreeVideoSite() {
        p = new FixBugVideoSite();
    }
    ~FreeVideoSite() {
        delete p;
    }
    virtual void freeMovie() {
        p->freeMovie();
    }
    virtual void vipMovie() {
        cout << "You need to become a vip" << endl;
    }
    virtual void ticketMovie() {
        cout << "You need to buy a ticket first" << endl;
    }
private:
    VideoSite *p;
};

void watchMovie(unique_ptr<VideoSite> &ptr)
{
    ptr->freeMovie();
    ptr->vipMovie();
    ptr->ticketMovie();
}

int main()
{
    // 普通场景，能做所有的事情
    // VideoSite *p1 = new FixBugVideoSite();
    // p1->freeMovie();
    // p1->vipMovie();
    // p1->ticketMovie();
    unique_ptr<VideoSite> p(new FreeVideoSite());
    watchMovie(p);
    return 0;
}
