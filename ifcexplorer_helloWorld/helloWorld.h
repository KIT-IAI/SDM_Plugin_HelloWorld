#pragma once

#include <ifcdb/IfcDbInclude.h>

class HelloWorld
{
  public:
    HelloWorld(IfcDB::Populationi* pDB);
    ~HelloWorld() = default;

    std::string doSomething();

  private:
    IfcDB::Populationi* m_pDB = nullptr;
};


