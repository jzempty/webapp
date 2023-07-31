#ifndef BUFFER_H
#define BUFFER_H
#include<vector>
#include<string>
#include<unistd.h>
#include<algorithm>
class CycleBuffer{
   private:
      const static unsigned int ALLOCATESIZE=1024;
      std::vector<char> Buff_;
      int last_read_size;
      int Fd_;
      int readpos_ = 0;
      int writepos_=0;
      unsigned int BufferSize ;

      void delline(){
         readpos_ += last_read_size;
         last_read_size = 0;
         BufferSize += last_read_size;
      }
   public:
      CycleBuffer(int Fd){
         Fd_ = Fd;
         Buff_.resize(static_cast<std::size_t>(Buff_.size() + ALLOCATESIZE));
         // init Buff_ size 1024byte
      };

      int write(){
       //write in buffer by read
         int RestSize = ALLOCATESIZE - BufferSize;
         std::cout << "\nRestSize=" << RestSize << "\n";
         int writelen = read(Fd_, &Buff_[writepos_], RestSize);
         writepos_ = (writelen + writepos_) % ALLOCATESIZE;
         BufferSize += writelen;
         std::cout << "\nbuffer" << BufferSize;
         return writelen;
      }

      std::string readall(){
         std::string ans;
         while(BufferSize>0){
            ans += Buff_[readpos_];
            readpos_ = (readpos_ + 1) % ALLOCATESIZE;
            BufferSize -= 1;
         }
         BufferSize = 0;
         return ans;
      }

      int readbyte(std::string& ans,unsigned int size){
         //read size byte from buffer to ans
         if (size>BufferSize){
            return -1;
         }
         for (int i = 0; i < size;i++){
            ans += Buff_[readpos_++];
            BufferSize -= 1;
         }
         return size;
      }

      int readline(std::string& line){
         //read a line by "\r\n"
         const char dest[] = "\r\n";
         char* lineEnd = std::search(&Buff_[readpos_],&Buff_[writepos_],dest, dest + 2);
         line=std::string(&Buff_[readpos_], lineEnd);
         if(lineEnd==&Buff_[writepos_]){
            return -1;
            // don't find "\r\n"
         }
         int readsize=line.size()+2;
         readpos_ += readsize;
         BufferSize -= readsize;
         return readsize;//return linesize
      }

      std::vector<std::string> ReadHttpHeader(){
         const char dest[] = "\r\n\r\n";
         // substract the httpheader and httpreq;
         std::vector<std::string> ans;
         char *lineEnd = std::search(&Buff_[readpos_], &Buff_[writepos_], dest, dest + 4);
         std::string line(&Buff_[readpos_], lineEnd);
         unsigned int header_size = line.size()+4;
         unsigned int read_size = 0;
         // substract
         std::cout << "\nheader_size" << header_size<< "\n";
         while (read_size < header_size)
         {
            std::string s;
            read_size += readline(s);
            ans.emplace_back(s);
         }
         return ans;
      }
      unsigned int getbuffersize(){
         return BufferSize;
      }
      ~CycleBuffer(){};
      
};
#endif