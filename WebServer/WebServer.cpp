#include "WebServer.h"

WebServer::WebServer(int port,int ThNum) : port_(port),ThreadPool_(new ThreadPool(ThNum))
{
   if(!Init()){
      std::cout << "init server fail";
      IsClose_ = true;
   }else{
      IsClose_ = false;
   }

}

void WebServer::Run(){
   if(!IsClose_) 
    {
        std::cout<<"============================";
        std::cout<<"Server Start!";
        std::cout<<"============================";
        std::cout<<std::endl;
    }
    while (1&&!IsClose_){
        struct sockaddr_in addr;
        socklen_t len = sizeof(addr);
        int acceptFd = accept(listenFd, (struct sockaddr *)&addr, &len);
        if(acceptFd == -1) { return;}
       while(1){
         char buf[1024];
         int ret = read(acceptFd, buf, sizeof(buf));
         if(ret==-1){
            perror("read error");
         }else{
            // std::cout << "data from client" << std::endl;
            std::cout << "acceptFd" << acceptFd <<"\nbuf="<< buf;
            ;
         }
       }
    }
}

bool WebServer::Init(){
   int ret;
   struct sockaddr_in addr;
   listenFd = socket(AF_INET, SOCK_STREAM, 0);
   if(listenFd==-1){
        std::cout << "listen error";
        return false;
        // std::runtime_error("fail to create a socket");
   }
   addr.sin_family=AF_INET;
   addr.sin_port = htons(port_);
   addr.sin_addr.s_addr = htonl(INADDR_ANY);

   ret = bind(listenFd, (struct sockaddr *)&addr, sizeof(addr));
   if(ret==-1){
        std::cout << "bind error";
        perror("bind");
        return false;
   }
   ret = listen(listenFd, 6);//_n is the max of the sum of noconnection and conncted
   if(ret==-1){
        std::cout << "listen fail" << std::endl;
        return false;
   }
   return true;
}
WebServer::~WebServer(){
   IsClose_ = true;
   close(listenFd);
}