#include<vector>
#include <iostream>
#include<functional>
#include "Thread/threadpool.h"


template <typename T>
void print(T a)
{
   std::cout << "number is:"<<a <<std::endl;
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
      port_= std::stod(std::string(args[1]));
   }
   
//   WebServer web(port_, 10);
//   web.Run();
  ThreadPool* TH=new ThreadPool(20);
  auto f = std::bind(print<int>, 7);
  TH->submit(f);
}
