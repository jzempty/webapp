#ifndef WEBSERVER
#define WEBSERVER
#include<iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<pthread.h>

#include "../Thread/threadpool.h"
#include "../IO/epoll.h"

class WebServer{
   private:
      std::unique_ptr<ThreadPool> ThreadPool_;
      
      int port_;
      int listenFd;
      bool IsClose_;
      bool Init();

      void HandleListen();
      void HandleRead(int acceptFd);
      void HandleWrite();

   public:
      std::unique_ptr<Epoll> Epoll_;
      void Run();
      WebServer(int port, int ThNum);
      ~WebServer();
      
};

#endif