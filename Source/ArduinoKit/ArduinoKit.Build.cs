using UnrealBuildTool;

public class ArduinoKit : ModuleRules
{
    public ArduinoKit(ReadOnlyTargetRules Target) : base(Target)
    {
        bEnableUndefinedIdentifierWarnings = false;

        PrivatePCHHeaderFile = "Private/ArduinoKitPCH.h";

        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PrivateIncludePaths.AddRange(new[] { "ArduinoKit/Private" });

        PrivateDependencyModuleNames.AddRange(
            new[]
            {
                "Engine",
                "InputCore",
                "Core",
                "Slate",
                "SlateCore",
                "CoreUObject"
            }
        );
    }
}

