#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "AudioSettingsDeveloperSettings.generated.h"

class UAudioSettingsConfig;

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Audio Settings"))
class SETTINGSFRAMEWORK_API UAudioSettingsDeveloperSettings : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    UPROPERTY(Config, EditAnywhere, Category = "Configuration")
    TSoftObjectPtr<UAudioSettingsConfig> AudioSettingsConfig;
};
