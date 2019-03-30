#include <iostream>
#include <fstream>
#include <map>

using namespace std;

/*
*实验一：C++源代码单词扫描程序（词法分析）
*
*标识符，关键字，数（包括整数、浮点数），字符串、注释、特殊符号（分界符）和运算符号等
*打印出所有以上的记号
*去掉空行、空格、缩进、注释，以压缩文本
*进一步实现减小源文件大小的压缩功能
*
*
*/

string JudgeKI(string KWorID,map<string,string> mapp){
    try
    {
      string KI=mapp.at(KWorID);
      return "关键字";
    }
    catch(const std::exception& e)
    {
      return "标识符";
    }
}

bool IsNumber(char ch){
      if(ch>47 && ch<58){
        return true;
      }
      else
      {
         return false;
      }
}

bool IsLetter(char ch){
    if((ch>64&&ch<91)||(ch>96&&ch<122)){
      return true;
    }else
    {
      return false;
    }
    
}

int main()
{
    //使用的是无序的haspmap，实现了logN的时间复杂度
    // << >> += -= 等另外处理
    map<char,char> Sign_map{{'#','#'},{'+','+'},{'-','-'},{'*','*'},{'/','/'},{'%','%'},{'=','='},
                                {'<','<'},{'>','>'},{'{','{'},{';',';'},{'(','('},{')',')'},{'}','}'}
    };
    // .h 结尾的关键字另外处理
    map<string,string> KeyWord_map{{"main","main"},{"include","include"},{"main","main"},{"int","int"},
                                  {"double","double"},{"long","long"},{"float","float"},{"cin","cin"},
                                  {"cout","cout"},{"using","using"},{"namespace","namespace"},{"std","std"},
                                  {"bool","bool"},{"if","if"},{"else","else"},{"class","class"},{"break","break"},
                                  {"const","const"},{"continue","continue"},{"public","public"},{"for","for"},
                                  {"while","while"},{"void","void"},{"do","do"},{"switch","switch"},{"char","char"},
                                  };//持续添加中……

    //注释另外处理
    //空格不处理
    string line; //以行为单位进行分析
    string KWorID; //存储关键字或者标识符
    
    ifstream LexicalFile ("TestCode.cpp");//词法分析测试文件
    ofstream CompressFile("TestCodeCompress.cpp");//压缩文件
    CompressFile.clear();

    if(LexicalFile.is_open()){
        while( getline (LexicalFile,line) )
    {
      //add 压缩功能，直接在cout后加输出就行
      int i=0;
      
      string keyW="";
      string number="";
      string Cuan="";
      // int num[50];   不打算用数组了，比较繁琐
      // fill_n(num,52,-1);  初始化填充为-1

      for(i;i<line.size();i++){
          char ch=line[i];

          if(IsLetter(ch)||ch=='.'){
            keyW+=ch;
            continue;
          }

          if(!(IsLetter(ch)) && keyW!=""){//空格为32；没考虑类似“int x=9；”即标识符后连着其他特殊符号的情况
            cout<<keyW<<"  "<<JudgeKI(keyW,KeyWord_map)<<endl;
            CompressFile<<keyW;
            keyW="";
          };

          if(IsNumber(ch) || (!(IsNumber(ch))&&ch=='.')){//float or double
            number+=ch;
            continue;
          }

          if(!(IsNumber(ch)) && number!=""){
            cout<<number<<"  "<<"数字"<<endl;
            CompressFile<<number;
            number="";
          }

          if(ch==34){//34为双引号，里面的东西输出为串；没有考虑换行输出的情况
            int j=i+1,p=i,q;
            for(j;j<line.size();j++){
              if(line[j]==34){
                q=j;
                break;
              }
            }
            while(p!=q+1){
              Cuan+=line[p++];
            }
            cout<<Cuan<<"  "<<"串"<<endl;
            CompressFile<<Cuan;
            i=q+1;
            
          }

          try
          {
            char c=Sign_map.at(ch);
            // char cc=Sign_map.at(line[i+1]);
             try
            {
              char cc=Sign_map.at(line[i+1]);
              cout<<c<<cc<<"  "<<"特殊符号"<<endl;
              CompressFile<<c<<cc;
              i++;
              
            }
            catch(const std::exception& e)
            {
              cout<<c<<"  "<<"特殊符号"<<endl;
              CompressFile<<c;
            }
            
          }
          catch(const std::exception& e)
          {   //Nothing
          }

      }


    }
    LexicalFile.close();
    CompressFile.close();
    }


    cout<<endl<<"   感谢您的使用，词法分析完成！"<<endl;
    cout<<"***压缩功能完成，请查看TestCodeCompress.cpp文件！***"<<endl;
    cout<<endl<<"  @Erving \n All Rights Reserved \n "<<endl;
    
    return 0;
}
