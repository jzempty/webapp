#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H
#include<vector>
#include<string>
#include <unordered_map>
#include<memory>
#include<iostream>
#include<regex>
#include "HttpConnection.h"
#include "../Buffer/buffer.h"
using namespace std;
class HttpRequest
{
private:
   struct RequestLine{
      std::string Method;
      std::string Url;
      string Version;
   }Rline;
   
   std::unordered_map<string, string> Headers_;
   unordered_map<string, string> JSONS;
   unordered_map<string, string> Get_Parase;
   std::string body;
   // unique_ptr defined in memory

public:
   HttpRequest(){};
   ~HttpRequest(){};
   vector<string> ParaseLine(string line,char c){
      //tr line by c
      int start = 0;
      vector<string> ans;
      for (int i = 0; i < line.size(); i++)
      {
         string midstr;
         if(line[i]==c&&i>start){
            midstr = line.substr(start,i-start);  
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
   void ParaseHeader( std::vector<string> Header){
       // parase requestline and header;
       vector<string> line = ParaseLine(Header[0], ' ');
       // std::cout <<"\nline"<< line[0]<<"\tline[2]"<<"header[0]\n";
       // std::cout <<"size="<< line.size();
       if (line.size() == 3)
       {
         Rline.Method = line[0];
         Rline.Url = line[1];
         Rline.Version = line[2];
      }

      if(Rline.Method=="GET"){
         ParaseUrl();
      }
      for (int i = 1; i < Header.size(); i++)
      {
         vector<string> H = ParaseLine(Header[i], ':');   
        if(H.size()>=2){
            for (int i = 1; i < H.size();i++)
            {
               Headers_[H[0]] += H[i];
            }
         }
      }

      // std::regex regexstr("^() () ()$");
      // std::smatch match;
      // if(std::regex_match(Header[0], match, regexstr)){
      //    //parase HttpRequest Line
      //    string m = match[1];
      //    Url = match[2];
      //    Version = match[3];
      // }
      // cout << "\nmatch" << match[1] << "\n";
      // for (int i = 1; i < Header.size(); i++)
      // {
      //    std::regex reg("^():()$");
      //    std::smatch m;
      //     if(std::regex_match(Header[i], m, reg)){
      //        // parase HttpRequest Header;
      //        Headers[m[1]] = m[2];
      //     }
      // }
   }
    void ShowHttp(){
      cout << "\nRequetLie\n";
      cout << Rline.Method << "\t" << Rline.Url << "\t" << Rline.Version << endl;
      cout << "\nHeader:\n";
      for (auto it : Headers_)
      {
         cout << it.first << ":" << it.second << "\r\n";
      }
      cout << "\nBodydate\n";
      for (auto it : JSONS)
      {
         cout << it.first << ":" << it.second << "\r\n";
      }
      cout << "\nGetDate\n";
      for (auto it:Get_Parase){
          cout << it.first << "=" << it.second << "\r\n";
      }
    }

   void ParaseBody(string body){
      if(body.size()<=2){
          return;
      }
      vector<string> b=ParaseLine(body.substr(1,body.size()-2), ',');
      for(string map:b){
         vector<string> json = ParaseLine(map, ':');
         if(json.size()==2&&json[0].size()>2&&json[1].size()>2){
            JSONS[json[0].substr(1,json[0].size()-2)] = json[1].substr(1,json[1].size()-2);
         }
      }
   }
   unsigned int GetContentLength(){
      return stoi(Headers_["Content-Length"].c_str());
   }
   int ParaseUrl(){
      vector<string> parase=ParaseLine(Rline.Url, '?');
      if(parase.size()!=2){
         return -1;
         // parase error;
      }
      Rline.Url = parase[0];
      vector<string> parase_1 = ParaseLine(parase[1], '&');
      for(auto it:parase_1){
         vector<string> ans = ParaseLine(it, '=');
         if(ans.size()!=2){
            return -1;
         }
         Get_Parase[ans[0]] = ans[1];
      }
      return 1;
   }
   template<typename F> 
   void Bind(F& st){

   }
};
#endif