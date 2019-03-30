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

void Sign(char ch,map<char,char> mapp){
    // try
    // {
    //   char c=mapp.at(ch);
    //   cout<<ch<<"  "<<"特殊字符"<<endl;
    // }
    // catch(const std::exception& e)
    // {
    //   cerr<<
    // }
    
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
  
    string line;
    string KWorID;
    // << 另外处理
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

    //<> 特殊字符的判断先存起来，该行找到另一个匹配则不判断为操作符；注释另外处理
    //移位和输出"<< >>"判读？ 后面一个是数字
    //空格不处理
    int s=1;
    
    ifstream LexicalFile ("TestCode.cpp");
    if(LexicalFile.is_open()){
        while( getline (LexicalFile,line) )
    {
      int i=0;
      
      string keyW="";
      string number="";
      // int num[50];
      // fill_n(num,52,-1);

      for(i;i<line.size();i++){
          char ch=line[i];

          if(IsLetter(ch)||ch=='.'){
            keyW+=ch;
            continue;
          }

          if(!(IsLetter(ch)) && keyW!=""){//空格为32；没考虑类似“int x=9；”即标识符后连着其他特殊符号的情况
            cout<<keyW<<"  "<<JudgeKI(keyW,KeyWord_map)<<endl;
            keyW="";
          };

          if(IsNumber(ch)){
            number+=ch;
            continue;
          }

          if(!(IsNumber(ch)) && number!=""){
            cout<<number<<"  "<<"数字"<<endl;
            number="";
          }

          try
          {
            char c=Sign_map.at(ch);
            // char cc=Sign_map.at(line[i+1]);
             try
            {
              char cc=Sign_map.at(line[i+1]);
              cout<<c<<cc<<"  "<<"特殊符号"<<endl;
              i++;
              
            }
            catch(const std::exception& e)
            {
              cout<<c<<"  "<<"特殊符号"<<endl;
            }
            
          }
          catch(const std::exception& e)
          {   
          }
          
          
          // string s=ch+"";
          // Sign(ch,Sign_map);

          
          
          
          

      }



    }
    LexicalFile.close();
    }
    








    cout<<endl<<"@Erving__All Rights Reserved__感谢您的使用，词法分析完成！"<<endl;
    return 0;
}
