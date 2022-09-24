/*
	ArduinoKit 1.0.0

*/
#include "ArduinoKitModule.h"
#include "ArduinoKitPCH.h"

IMPLEMENT_MODULE(ArduinoKitModule, ArduinoKit);

DEFINE_LOG_CATEGORY(ModuleLog)

#define LOCTEXT_NAMESPACE "ArduinoKit"

ArduinoKitModule::ArduinoKitModule()
{
}

void ArduinoKitModule::StartupModule()
{
	UE_LOG(ModuleLog, Warning, TEXT("ArduinoKit: Plugin Started"));
}

void ArduinoKitModule::ShutdownModule()
{
	UE_LOG(ModuleLog, Warning, TEXT("ArduinoKit: Plugin Ended"));
}

