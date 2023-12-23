#pragma once

#include <Plugin.hpp>
#include <ActionFeature.hpp>
#include <DocumentObserver.hpp>
#include <MessageDialogFeature.hpp>
#include <MessageDialogFeatureHelper.hpp>
#include <LogDialogFeature.hpp>
#include <LogDialogFeatureHelper.hpp>
#include <ifcdb/IfcDbInclude.h>

class HelloWorldAction : public sdm::plugin::ActionFeature
{
  public:
    HelloWorldAction(sdm::plugin::MessageDialogFeatureHelper& messageDialog);
    ~HelloWorldAction() override = default;

    void execute() const override;

    void setDB(IfcDB::Populationi* pDB) { m_db = pDB; }

  protected:
    IfcDB::Populationi* m_db = nullptr;

    sdm::plugin::MessageDialogFeatureHelper& m_messageDialog;
};

class PluginHelloWorld : public sdm::plugin::Plugin
{
  public:
    PluginHelloWorld();
    ~PluginHelloWorld() override = default;

    sdm::plugin::Version getInterfaceVersion() const override;
    sdm::plugin::PluginInfo getInfo() const override;
    std::vector<sdm::plugin::Feature*> getFeatures() const override;

    sdm::plugin::ComponentInfo getComponentInfo(const sdm::plugin::RequiredComponent& requiredComponent) const override;
    const sdm::plugin::InitializationState& getInitializationState() const override;

    IfcDB::Populationi* m_db = nullptr;

  private:
    sdm::plugin::DocumentObserverImpl m_documentObserver;
    sdm::plugin::MessageDialogFeatureHelper m_messageDialog;
    HelloWorldAction m_HelloWorldAction{ m_messageDialog };
    sdm::plugin::InitializationState m_initState;
};