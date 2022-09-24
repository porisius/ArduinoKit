/*
	ArduinoKit 1.0.0

*/

#pragma once

DECLARE_LOG_CATEGORY_EXTERN(ModuleLog, Log, All)

class ArduinoKitModule : public IModuleInterface
{
private:

public:
	ArduinoKitModule();
	
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};