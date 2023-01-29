#ifndef __MyIni_h__
#define __MyIni_h__
#include <iostream>
#include <string.h>
#include <map>
#include<bits/stdc++.h>
namespace lexcber {
class Value {
public:
  Value();
  Value(int val);
  Value(double val);
  Value(float val);
  Value(const char* val);
  Value(const std::string& val);
  
  Value& operator = (int val);
  Value& operator = (double val);
  Value& operator = (float val);
  Value& operator = (const std::string& val);
  Value& operator = (const char* val);

  operator int();
  operator double();
  operator std::string();
  operator float();

private:
  std::string m_value;

};


typedef std::map<std::string, Value> Section;

class IniFile {
public:
  IniFile();

  void show();
  void load(const std::string filename);
  Value& getValue(const std::string& section, const std::string key);
  Section& operator [](const std::string& key);
  void setValue(const std::string& section, const std::string& key, const Value& val);
  bool has(std::string section, std::string key);
  void remove(const std::string& section);
  void remove(const std::string& section, const std::string& key);
  void clear();
  std::string sstr();
  void save(const std::string& filename );
private:
   std::string trip(std::string s);
   std::ifstream m_out;
   std::string m_filename;
   std::map<std::string, Section> m_sections;
};

}

#endif
