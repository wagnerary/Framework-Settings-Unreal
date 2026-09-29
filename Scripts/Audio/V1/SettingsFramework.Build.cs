using UnrealBuildTool;

public class SettingsFramework : ModuleRules
{
    public SettingsFramework(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "InputCore",
                "AudioModulation"
            }
        );
    }
}
