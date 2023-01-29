#include "Myini.h"
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdlib.h>

using namespace lexcber;

Value::Value(int val) {
 (*this) = val;
}

Value::Value(double val) {
   (*this) = val;
}

Value::Value(float val) {
  (*this) = val;
}

Value::Value(const char* val) {
  (*this) = val;
}

Value::Value(const std::string& val) {
  (*this) = val;
}

Value& Value::operator = (int val) {
  std::stringstream ss;
  ss<<val;
  ss>> m_value;
  return (*this);
}

Value& Value::operator = (double val) {
  std::stringstream ss;
  ss<<val;
  ss>> m_value;
  return (*this);
}

Value& Value:: operator = (float val) {
  std::stringstream ss;
  ss<<val;
  ss>> m_value;
  return (*this);
}

Value& Value::operator = (const std::string& val) {
  m_value = val; 
  return (*this);
}

Value& Value::operator = (const char* val) {
   m_value = val;
   return (*this);
}

Value::operator int() {
 return std::atoi(m_value.c_str()); 
}

Value::operator double() {
  return std::atof(m_value.c_str());
}

Value::operator  std::string() {
  return m_value;
}


Value::operator float() {
  return std::atof(m_value.c_str());
}

void IniFile::load(const std::string filename) {
  m_filename = filename;
  m_out.open(filename);
  if(m_out.fail()) {
    throw std::logic_error("error\n");
    return; 
  }
  std::string line;
  int pos;
  std::string key;
  std::string section;
  std::string value;
   while(std::getline(m_out, line)) {
    if(line ==  " ") {
      continue;
    }
    if(line[0] == '[') {
      
      pos = line.find(']');
      section  = line.substr(1, pos-1);
      section = trip(section);
      m_sections[section] = Section();
    } 
    else {
     pos = line.find('=');
     key = line.substr(0, pos);
     key = trip(key);
     value = line.substr(pos+1, line.length()-pos);
     value = trip(value);
     m_sections[section][key] = value;
     

    }  
  }
  m_out.close();
}  

Value& IniFile::getValue(const std::string& section, const std::string key) {
  return m_sections[section][key]; 
}
Value::Value() {

}

Section& IniFile::operator [](const std::string& key ) {
  return m_sections[key];
}

void IniFile::setValue(const std::string& section, const std::string& key, const Value& val) {
    m_sections[section][key] = val;
}

std::string IniFile::trip(std::string s) {
  if(s.empty()) {
    return s;
  }
  s.erase(0, s.find_first_not_of(" \n\r"));
  s.erase(s.find_last_not_of(" \n\r")+1);
  return s;

}

IniFile::IniFile() {

}

bool IniFile::has(std::string section, std::string key) {
  auto it = m_sections.find(section);
  if(it != m_sections.end()) {
    return  (it->second.find(key) != it->second.end());
  }
  return false;
}

void IniFile::remove(const std::string& section, const std::string& key) {
  //  auto it = m_sections.find(section);
  //  if(it != m_sections.end()) {
  //   it->second.erase(key);
  // }
  
  
  std::string test1 = m_sections[section][key];
  std::cout<< "test = "<< test1 << std::endl;
}

void IniFile::remove(const std::string& section ) {
  m_sections.erase(section);

}

void IniFile::clear() {
  m_sections.clear();
}

std::string IniFile::sstr() {
  std::stringstream  ss;
  for(auto it = m_sections.begin(); it != m_sections.end(); it++) {
     ss<<"[" << it->first <<"]" << std::endl;
    for(auto iter = it->second.begin(); iter != it->second.end(); iter++) {
     ss<< iter->first <<" = " << std::string(iter->second) <<std::endl ;
    }
  }
  return ss.str();
}

void IniFile::save(const std::string& filename ) {
  std::ofstream ofs;
  ofs.open(filename);
  if(ofs.fail()) {
    throw std::logic_error(" save open error\n");
    return;
  }
  ofs << sstr();
  
  ofs.close();

}

void IniFile::show() {
  std::cout << sstr()<< std::endl;

} 

int main() {
//
//  IniFile inifile;
//  std::cout<<"hello wowow"<<std::endl;
//  inifile.load("./ini");
//  std::string ip = inifile["server"]["ip"];
//  std::cout<<(std::string) inifile.getValue("server","ip")<<std::endl;
//  inifile.setValue("server", "time out", 10000);
//
//  inifile.show();
//  inifile.save("./inisss");
//  std::cout<<ip<<std::endl;
  
IniFile inifile;
inifile.load("./ini");
inifile.remove("ip", "port");

     return 0;
}
