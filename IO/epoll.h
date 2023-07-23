#ifndef EPOLL_H
#define EPOLL_H
#include <sys/epoll.h>
#include<vector>
#include<unistd.h>
#define MAXEVENTNUMBER  50
#define TIMEMS -1  
class Epoll{
   private:
      std::vector<struct epoll_event> event_;
      int EpollFd;
      int TimeMs;

   public:
      Epoll(int number) : event_(MAXEVENTNUMBER) { EpollFd = epoll_create(number); }
      // number discrib the appeoximetly number of monitered fd ,
      // in newe linux the number is meaningless;
      ~Epoll() { close(EpollFd); }
      int Epoll_add(int Fd, uint32_t events)
      {
         struct epoll_event ev;
         ev.data.fd = Fd;
         ev.events = events;
         return epoll_ctl(EpollFd, EPOLL_CTL_ADD, Fd, &ev);
   }
   int Epoll_Mod(int Fd,uint32_t events){
        //modify fd's events
      struct epoll_event ev;
      ev.data.fd = Fd;
      ev.events = events;
      epoll_ctl(EpollFd, EPOLL_CTL_MOD,Fd,&ev);
   }

   int  Epoll_Del(int Fd){
      struct epoll_event ev={};
      return epoll_ctl(EpollFd, EPOLL_CTL_DEL, Fd, &ev);
      // return 0 in case of success,return -1 in case of error;
   }

   int Epoll_Wait(){
      return epoll_wait(EpollFd, &event_[0],static_cast<int>(event_.size()), TIMEMS);
   }

   std::vector<struct epoll_event> Get_Event(){return event_;}
};
#endif