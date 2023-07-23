#include <sys/socket.h>
#include <netinet/in.h>
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include <arpa/inet.h>
#include<string>
int main(int argc,char* args[]){
   int port;
   if (argc <= 1)
   {
      port = 9999;
   }else{
      port = std::stod(std::string(args[1]));
   }
   int listenFd = socket(AF_INET, SOCK_STREAM, 0);

   if(listenFd==-1){
      std::cout << "fail to set a socket";
   }
   struct sockaddr_in addr;
   inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);
   addr.sin_family = AF_INET;
   addr.sin_port = htons(port);

   std::cout << "listenFd=" << listenFd<<"port="<<port<<std::endl;

   int ret = connect(listenFd, (struct sockaddr *)&addr, sizeof(addr));

   if (ret == -1)
   {
      perror("connect");
      exit(-1);
   }
      const char buf[1024] = "this a massege from client\n";
      int len = sizeof(buf);
      while(1){
      sleep(1);
      ssize_t sta = write(listenFd, buf, sizeof(buf));
      if (sta == -1)
      {
         perror("send");
         std::cout << "fail to send";
         exit(-1);
         }else{
            std::cout << "\nsuccess to send:"<<len<<"\nsta"<<sta;
         }
      }
}
   