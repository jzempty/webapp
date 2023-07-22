#ifndef WEBSERVER
#define WEBSERVER
#include<iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include<unistd.h>
#include <arpa/inet.h>
#include<pthread.h>
#include "../Thread/threadpool.h"
class WebServer{
   private:
      ThreadPool* ThreadPool_;
      int port_;
      bool IsClose_;
      bool Init();

   public:
      int listenFd;
      void Run();
      WebServer(int port, int ThNum);
      ~WebServer();
      
};

#endif