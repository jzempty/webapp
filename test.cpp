#include<vector>
#include <iostream>
#include<functional>
#include "Thread/threadpool.h"
#include<algorithm>
using namespace std;

template <typename T>
void print(T a)
{
   std::cout << "number is:"<<a <<std::endl;
}

vector<string> ParaseLine(string line,char c){
      int start = 0;
      vector<string> ans;
      cout << "line[3]" << line[2] << "\n";
      for (int i = 0; i < line.size(); i++)
      {
         string midstr;
         if(line[i]==c&&i>start){
            midstr=line.substr(start, i-start);
            cout << "i=" <<i << "\t";
            ans.push_back(midstr);
            start = i+1;
         }

       }
       if(start<line.size()){
         ans.emplace_back(string(&line[start],&line[line.size()]));
       }
       if(ans.size()==0){
         ans.push_back("error parase");
         return ans;
       }
       return ans;
   }
int main(int argc,char* args[]){
       string test = "GET / HTTP/1.1";
       cout << "cs:" <<string(&test[0],&test[0])<<"\n";
       auto line = ParaseLine(test, ' ');
       cout << "\n";
       for(auto l:line){
         cout << l << "\t";
       }
       if (argc > 2)
       {
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
   char a[] = "kk";
   char b[] = "qrwekfdytkfd";
   char *an = std::search(&b[0], &b[10], a, a + 2);
   if(an==&b[10]){
      std::cout << "null";
      //return container.end() if don't find in container(b)
   }else{
      std::cout<<"??";
   } 
   std::vector<char> Buff_;
   std::cout << "test" << an<< "\n";
   std::cout << "Buff=" << Buff_.size();
   Buff_.resize(Buff_.size() + 1024);
   ThreadPool *TH = new ThreadPool(20);
   auto f = std::bind(print<int>, Buff_.size());
   TH->submit(f);
}
