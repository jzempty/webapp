#include<vector>
#include<memory>
#include <iostream>
#include<functional>
#include<thread>
#include<condition_variable>
#include<mutex>
#include<queue>
#include<future>
#include<string>
#include <sys/socket.h>
#include <netinet/in.h>
#include<unistd.h>
#include <arpa/inet.h>
#include<pthread.h>
#include "Thread/threadpool.h"
#include "WebServer/WebServer.h"

using namespace std;

template <typename T>
void print(T a)
{
   std::cout << "number is:"<<a << endl;
}

int main(int argc,char* args[]){
   if(argc>2){
      std::cout << "Input error";
   }
   int port_;
   // char[0] equal to pwd show now directory
   if (argc <=1)
   {
      std::cout << "USE DEFOULT PORT";
      port_ = 9999;
   }else{
      port_= stod( string(args[1]));
   }
   
  WebServer web(port_, 10);
  web.Run();
   
}