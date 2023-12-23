#include "PluginHelloWorld.h"
#include "helloWorld.h"

#include "IFCDBInterfaceVersion.hpp"
#include "PluginInterfaceVersion.hpp"
#include "ComponentRegistry.hpp"

using namespace std;
using namespace sdm::plugin;

IMPLEMENT_PLUGIN(PluginHelloWorld);

HelloWorldAction::HelloWorldAction(MessageDialogFeatureHelper& messageDialog)
  : ActionFeature("Hello World Example"), m_messageDialog(messageDialog)
{
}

void HelloWorldAction::execute() const
{
  HelloWorld helloWorld(m_db);
  std::string message = helloWorld.doSomething();

  if (m_messageDialog.show("Hello World Result:\n" + message, MessageDialogFeatureButtons::OK) == MessageDialogFeatureResult::YES)
  {
  }
}

PluginHelloWorld::PluginHelloWorld()
{
  m_documentObserver.attach([this](IfcDB::Populationi* pDB) { m_HelloWorldAction.setDB(pDB); } );
}

Version PluginHelloWorld::getInterfaceVersion() const
{
  return Version();
}

PluginInfo PluginHelloWorld::getInfo() const
{
  PluginInfo info;
  info.name        = "Hello World";
  info.description = "Simple plugin example for using KIT-ModelViewer population";
  info.version     = { 1, 0 };

  return info;
}

std::vector<Feature*> PluginHelloWorld::getFeatures() const
{
  std::vector<Feature*> features;

  features.emplace_back(const_cast<DocumentObserverImpl*>(&m_documentObserver));
  features.emplace_back(const_cast<HelloWorldAction*>(&m_HelloWorldAction));
  features.emplace_back(const_cast<MessageDialogFeatureHelper*>(&m_messageDialog));

  return features;
}

ComponentInfo PluginHelloWorld::getComponentInfo(const RequiredComponent& requiredComponent) const
{
  ComponentRegistry availableComponents;
  availableComponents.addAvailable(IFCDB_INTERFACE_COMPONENT_NAME, IFCDB_INTERFACE_COMPONENT_VERSION, IFCDB_INTERFACE_COMPONENT_HINT);
  availableComponents.addAvailable(PLUGIN_INTERFACE_COMPONENT_NAME, PLUGIN_INTERFACE_COMPONENT_VERSION, PLUGIN_INTERFACE_COMPONENT_HINT);

  return availableComponents.getInfo(requiredComponent);
}

const sdm::plugin::InitializationState& PluginHelloWorld::getInitializationState() const
{
  return m_initState;
}
