#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AudioSettingsSubsystem.generated.h"

class UAudioSettingsConfig;
class USettingsFrameworkUserSettings;
class USoundControlBus;
class UWorld;

USTRUCT()
struct FAudioSettingsState
{
    GENERATED_BODY()

    float Master = 1.0f;
    float Music = 1.0f;
    float SFX = 1.0f;
    float Dialogue = 1.0f;
    float UI = 1.0f;
};

UCLASS()
class SETTINGSFRAMEWORK_API UAudioSettingsSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    UFUNCTION(BlueprintCallable, Category = "Settings|Audio")
    void SetMasterVolume(float Volume);

    UFUNCTION(BlueprintPure, Category = "Settings|Audio")
    float GetMasterVolume() const;

    UFUNCTION(BlueprintCallable, Category = "Settings|Audio")
    void SetMusicVolume(float Volume);

    UFUNCTION(BlueprintPure, Category = "Settings|Audio")
    float GetMusicVolume() const;

    UFUNCTION(BlueprintCallable, Category = "Settings|Audio")
    void SetSFXVolume(float Volume);

    UFUNCTION(BlueprintPure, Category = "Settings|Audio")
    float GetSFXVolume() const;

    UFUNCTION(BlueprintCallable, Category = "Settings|Audio")
    void SetDialogueVolume(float Volume);

    UFUNCTION(BlueprintPure, Category = "Settings|Audio")
    float GetDialogueVolume() const;

    UFUNCTION(BlueprintCallable, Category = "Settings|Audio")
    void SetUIVolume(float Volume);

    UFUNCTION(BlueprintPure, Category = "Settings|Audio")
    float GetUIVolume() const;

    UFUNCTION(BlueprintCallable, Category = "Settings|Audio")
    void ApplyAudioSettings();

    UFUNCTION(BlueprintCallable, Category = "Settings|Audio")
    void CancelAudioSettings();

private:
    static constexpr float VolumeFadeTime = 0.1f;

    UPROPERTY()
    TObjectPtr<UAudioSettingsConfig> AudioSettingsConfig;

    FAudioSettingsState CurrentSettings;
    FAudioSettingsState SavedSettings;

    USettingsFrameworkUserSettings* GetUserSettings() const;
    void HandleWorldBeginPlay(UWorld* World);
    void ApplyVolumeToBus(USoundControlBus* Bus, float Volume);
    void ApplyCurrentSettingsToBuses();
    void UpdateUserSettingsFromCurrentState();
};
