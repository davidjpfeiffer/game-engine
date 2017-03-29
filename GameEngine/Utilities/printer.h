#ifndef __PRINTER
#define __PRINTER

#include <iostream>
#include <string>

class Printer
{
  public:
  
  Printer(unsigned lineLength_p = 31)
  {
    this->lineLength = lineLength_p;
  }
  
  void printHeader(std::string content)
  {
    printLineBreak();
    printHeaderContent(content);
    printLineBreak();
  }
  
  private:
  
  unsigned lineLength;
  std::string lineBreak;
  
  void printLineBreak()
  {
    if (lineBreak.empty())
    {
      for(unsigned i = 0; i < lineLength; i++)
      {
        lineBreak += "-";
      }
      
      lineBreak += "\n";
    }
    
    std::cout << lineBreak;
  }
  
  void printLine(std::string content)
  {
    std::cout << content << '\n';
  }
  
  void printHeaderContent(std::string content)
  {
    std::string headerContent = "";
    unsigned padding = (lineLength - content.length()) / 2;
    
    for(unsigned i = 0; i < padding; i++)
    {
      headerContent += " ";
    }
    
    headerContent += content;
    
    for(unsigned i = 0; i < padding; i++)
    {
      headerContent += " ";
    }
    
    printLine(headerContent);
  }
  
} printer;

#endif