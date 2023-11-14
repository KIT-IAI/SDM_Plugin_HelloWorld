#include "helloWorld.h"

HelloWorld::HelloWorld(IfcDB::Populationi* pDB)
  : m_pDB(pDB)
{
}

std::string HelloWorld::doSomething()
{
  IfcDB::IfcEntityList entities;

  m_pDB->getAll(entities);

  IfcDB::Point min{ HUGE_VAL , HUGE_VAL , HUGE_VAL }, max{ -HUGE_VAL ,-HUGE_VAL ,-HUGE_VAL };

  size_t nProcessedEntities(0);
  bool hasGeometry(false);

  for (auto pEntity : entities)
  {
    ++nProcessedEntities;

    const IfcDB::Geometry* pGeometry = pEntity->getGeometry();

    if (pGeometry != nullptr)
    {
      hasGeometry = true;

      IfcDB::Point minLocal{ HUGE_VAL , HUGE_VAL , HUGE_VAL }, maxLocal{ -HUGE_VAL ,-HUGE_VAL ,-HUGE_VAL };

      if (pGeometry->getBoundingBox(minLocal, maxLocal))
      {
        min.minValues(minLocal);
        max.maxValues(maxLocal);

        IfcDB::Matrix4* pPlacement = pEntity->getPlacement();

        if (pPlacement != nullptr)
        {
          pPlacement->transformBoundingBox(minLocal, maxLocal);
        }
      }
    }
  }

  std::tstringstream message;

  if (hasGeometry)
  {
    message << "Processed entities: " << nProcessedEntities << std::endl;

    message << "Bounding box:" << std::endl;

    message << "  Min " << min << std::endl;
    message << "  Max " << max << std::endl;
  }
  else
  {
    message << "No geometry available!" << std::endl;
  }

  return toUtf8(message.str());
}
