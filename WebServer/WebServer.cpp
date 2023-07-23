#include "WebServer.h"

WebServer::WebServer(int port, int ThNum) : port_(port), ThreadPool_(new ThreadPool(ThNum)), Epoll_(new Epoll(50))
{
   if (!Init())
   {
      std::cout << "init server fail";
      exit(-1);
   }
   else
   {
      IsClose_ = false;
   }
}

void WebServer::Run()
{
   if (!IsClose_)
   {
      std::cout << "============================";
      std::cout << "Server Start!";
      std::cout << "============================";
      std::cout << std::endl;
   }
   Epoll_->Epoll_add(listenFd, EPOLLIN | EPOLLLT);
   while (1 && !IsClose_)
   {
      int evcnt = Epoll_->Epoll_Wait();
      std::vector<struct epoll_event> evs;
      evs = std::move(Epoll_->Get_Event());
      auto pev = [&]()
         {
            for (int i = 0; i < evcnt;i++){
               std::cout << "\n\nfd=\t" << evs[i].data.fd << "\tevents\t" << evs[i].events << "len" << evcnt;
            }
         };
      pev();

      for (int i = 0; i < evcnt; i++)
      {
         int fd = evs[i].data.fd;
         int events = evs[i].events;
         if (fd ==listenFd)
         {
            std::cout << "fd=" << fd << "listen=" << listenFd << std::endl;
            auto f = std::bind(&WebServer::HandleListen, this);
            ThreadPool_->submit(f);
            continue;
         }
         else if (events & EPOLLIN)
         {
            std::cout << "fd=" << fd << "HandleRead=" << listenFd << std::endl;
            auto f = std::bind(&WebServer::HandleRead, this, fd);
            ThreadPool_->submit(f);
            continue;
         }
         else if (events & EPOLLOUT)
         {
            HandleWrite();
            continue;
         }
      }
      //   struct sockaddr_in addr;
      //   socklen_t len = sizeof(addr);
      //   int acceptFd = accept(listenFd, (struct sockaddr *)&addr, &len);
      //   if(acceptFd == -1) { return;}
      //  while(1){
      //    char buf[1024];
      //    int ret = read(acceptFd, buf, sizeof(buf));
      //    if(ret==-1){
      //       perror("read error");
      //    }else{
      //       // std::cout << "data from client" << std::endl;
      //       std::cout << "acceptFd" << acceptFd <<"\nbuf="<< buf;
      //       ;
      //    }
      //  }
   }
}
void WebServer::HandleRead(int acceptFd)
{
   while (1)
   {
      char buf[1024];
      int ret = read(acceptFd, buf, sizeof(buf));
      if (ret == -1)
      {
         perror("read error");
         exit(-1);
      }
      if(ret==0){
         Epoll_->Epoll_Del(acceptFd);
         std::cout << "acceptFd" << acceptFd << " is closed\n";
         return;
      }
      else if (ret > 0)
      {
         // std::cout << "data from client" << std::endl;
 
        std::cout << "acceptFd" << acceptFd << "\nbuf=" << buf;
      }
   }
}
void WebServer::HandleWrite()
{
   std::cout << "on writing" << std::endl;
}
void WebServer::HandleListen()
{
   struct sockaddr_in addr;
   socklen_t len = sizeof(addr);
   int acceptFd = accept(listenFd, (struct sockaddr *)&addr, &len);
   Epoll_->Epoll_add(acceptFd, EPOLLIN);
   std::cout << "HandleListen" << acceptFd << "\n";
}
// InitSocket return true/false in case of true/false
bool WebServer::Init()
{
   int ret;
   struct sockaddr_in addr;
   listenFd = socket(AF_INET, SOCK_STREAM, 0);
   if (listenFd == -1)
   {
      std::cout << "listen error";
      return false;
      // std::runtime_error("fail to create a socket");
   }
   addr.sin_family = AF_INET;
   addr.sin_port = htons(port_);
   addr.sin_addr.s_addr = htonl(INADDR_ANY);

   ret = bind(listenFd, (struct sockaddr *)&addr, sizeof(addr));
   if (ret == -1)
   {
      std::cout << "bind error";
      perror("bind");
      return false;
   }
   ret = listen(listenFd, 6); //_n is the max of the sum of noconnection and conncted
   if (ret == -1)
   {
      std::cout << "listen fail" << std::endl;
      return false;
   }
   return true;
}
WebServer::~WebServer()
{
   IsClose_ = true;
   close(listenFd);
}