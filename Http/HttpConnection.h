#ifndef HTTPCONNECTION_H
#define HTTPCONNECTION_H
#include<vector>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include "../Buffer/buffer.h"
#include "HttpRequest.h"
#include "HttpResponse.h"

class HttpConnection{
   private:
      int acceptFd_;//a http connecttion
      struct sockaddr_in addr_;//located in unistd.h
      CycleBuffer buff_;
      unique_ptr<HttpRequest> HttpRequest_;
      unique_ptr<HttpResponse> HttpResponse_;

   public:
      HttpConnection(int Fd):buff_(Fd),acceptFd_(Fd),HttpRequest_(new HttpRequest){}
      int ParaseHttpRequest(){
         int ret = buff_.write();
         std::vector<std::string> h = buff_.ReadHttpHeader();
         HttpRequest_->ParaseHeader(h);
         std::string body;
         buff_.readbyte(body, HttpRequest_->GetContentLength());
         HttpRequest_->ParaseBody(body);
         HttpRequest_->ShowHttp();   
         return ret;
      }
      void DoResponse(){
         
      }
};
#endif