#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameUserSettings.h"
#include "SettingsFrameworkUserSettings.generated.h"

UCLASS(BlueprintType)
class SETTINGSFRAMEWORK_API USettingsFrameworkUserSettings : public UGameUserSettings
{
    GENERATED_BODY()

public:
    UPROPERTY(Config)
    float MasterVolume = 1.0f;

    UPROPERTY(Config)
    float MusicVolume = 1.0f;

    UPROPERTY(Config)
    float SFXVolume = 1.0f;

    UPROPERTY(Config)
    float DialogueVolume = 1.0f;

    UPROPERTY(Config)
    float UIVolume = 1.0f;

    void SetMasterVolume(float Volume);
    float GetMasterVolume() const;

    void SetMusicVolume(float Volume);
    float GetMusicVolume() const;

    void SetSFXVolume(float Volume);
    float GetSFXVolume() const;

    void SetDialogueVolume(float Volume);
    float GetDialogueVolume() const;

    void SetUIVolume(float Volume);
    float GetUIVolume() const;
};
