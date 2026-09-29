#include "AudioSettingsSubsystem.h"

#include "AudioSettingsConfig.h"
#include "AudioSettingsDeveloperSettings.h"
#include "SettingsFrameworkUserSettings.h"
#include "AudioModulationStatics.h"
#include "SoundControlBus.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

void UAudioSettingsSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    const UAudioSettingsDeveloperSettings* DeveloperSettings = GetDefault<UAudioSettingsDeveloperSettings>();
    if (DeveloperSettings)
    {
        AudioSettingsConfig = DeveloperSettings->AudioSettingsConfig.LoadSynchronous();
    }

    if (USettingsFrameworkUserSettings* UserSettings = GetUserSettings())
    {
        UserSettings->LoadSettings(false);

        CurrentSettings.Master = UserSettings->GetMasterVolume();
        CurrentSettings.Music = UserSettings->GetMusicVolume();
        CurrentSettings.SFX = UserSettings->GetSFXVolume();
        CurrentSettings.Dialogue = UserSettings->GetDialogueVolume();
        CurrentSettings.UI = UserSettings->GetUIVolume();
    }

    SavedSettings = CurrentSettings;
    FWorldDelegates::OnWorldBeginPlay.AddUObject(this, &UAudioSettingsSubsystem::HandleWorldBeginPlay);
}

void UAudioSettingsSubsystem::Deinitialize()
{
    FWorldDelegates::OnWorldBeginPlay.RemoveAll(this);
    Super::Deinitialize();
}

USettingsFrameworkUserSettings* UAudioSettingsSubsystem::GetUserSettings() const
{
    return Cast<USettingsFrameworkUserSettings>(UGameUserSettings::GetGameUserSettings());
}

void UAudioSettingsSubsystem::HandleWorldBeginPlay(UWorld* World)
{
    ApplyCurrentSettingsToBuses();
}

void UAudioSettingsSubsystem::ApplyVolumeToBus(USoundControlBus* Bus, float Volume)
{
    if (!Bus)
    {
        return;
    }

    UAudioModulationStatics::SetGlobalBusMixValue(this, Bus, Volume, VolumeFadeTime);
}

void UAudioSettingsSubsystem::ApplyCurrentSettingsToBuses()
{
    if (!AudioSettingsConfig)
    {
        return;
    }

    ApplyVolumeToBus(AudioSettingsConfig->MasterBus, CurrentSettings.Master);
    ApplyVolumeToBus(AudioSettingsConfig->MusicBus, CurrentSettings.Music);
    ApplyVolumeToBus(AudioSettingsConfig->SFXBus, CurrentSettings.SFX);
    ApplyVolumeToBus(AudioSettingsConfig->DialogueBus, CurrentSettings.Dialogue);
    ApplyVolumeToBus(AudioSettingsConfig->UIBus, CurrentSettings.UI);
}

void UAudioSettingsSubsystem::UpdateUserSettingsFromCurrentState()
{
    if (USettingsFrameworkUserSettings* UserSettings = GetUserSettings())
    {
        UserSettings->SetMasterVolume(CurrentSettings.Master);
        UserSettings->SetMusicVolume(CurrentSettings.Music);
        UserSettings->SetSFXVolume(CurrentSettings.SFX);
        UserSettings->SetDialogueVolume(CurrentSettings.Dialogue);
        UserSettings->SetUIVolume(CurrentSettings.UI);
    }
}

void UAudioSettingsSubsystem::SetMasterVolume(float Volume)
{
    if (!AudioSettingsConfig)
    {
        return;
    }

    CurrentSettings.Master = FMath::Clamp(Volume, 0.0f, 1.0f);
    ApplyVolumeToBus(AudioSettingsConfig->MasterBus, CurrentSettings.Master);

    if (USettingsFrameworkUserSettings* UserSettings = GetUserSettings())
    {
        UserSettings->SetMasterVolume(CurrentSettings.Master);
    }
}

float UAudioSettingsSubsystem::GetMasterVolume() const
{
    return CurrentSettings.Master;
}

void UAudioSettingsSubsystem::SetMusicVolume(float Volume)
{
    if (!AudioSettingsConfig)
    {
        return;
    }

    CurrentSettings.Music = FMath::Clamp(Volume, 0.0f, 1.0f);
    ApplyVolumeToBus(AudioSettingsConfig->MusicBus, CurrentSettings.Music);

    if (USettingsFrameworkUserSettings* UserSettings = GetUserSettings())
    {
        UserSettings->SetMusicVolume(CurrentSettings.Music);
    }
}

float UAudioSettingsSubsystem::GetMusicVolume() const
{
    return CurrentSettings.Music;
}

void UAudioSettingsSubsystem::SetSFXVolume(float Volume)
{
    if (!AudioSettingsConfig)
    {
        return;
    }

    CurrentSettings.SFX = FMath::Clamp(Volume, 0.0f, 1.0f);
    ApplyVolumeToBus(AudioSettingsConfig->SFXBus, CurrentSettings.SFX);

    if (USettingsFrameworkUserSettings* UserSettings = GetUserSettings())
    {
        UserSettings->SetSFXVolume(CurrentSettings.SFX);
    }
}

float UAudioSettingsSubsystem::GetSFXVolume() const
{
    return CurrentSettings.SFX;
}

void UAudioSettingsSubsystem::SetDialogueVolume(float Volume)
{
    if (!AudioSettingsConfig)
    {
        return;
    }

    CurrentSettings.Dialogue = FMath::Clamp(Volume, 0.0f, 1.0f);
    ApplyVolumeToBus(AudioSettingsConfig->DialogueBus, CurrentSettings.Dialogue);

    if (USettingsFrameworkUserSettings* UserSettings = GetUserSettings())
    {
        UserSettings->SetDialogueVolume(CurrentSettings.Dialogue);
    }
}

float UAudioSettingsSubsystem::GetDialogueVolume() const
{
    return CurrentSettings.Dialogue;
}

void UAudioSettingsSubsystem::SetUIVolume(float Volume)
{
    if (!AudioSettingsConfig)
    {
        return;
    }

    CurrentSettings.UI = FMath::Clamp(Volume, 0.0f, 1.0f);
    ApplyVolumeToBus(AudioSettingsConfig->UIBus, CurrentSettings.UI);

    if (USettingsFrameworkUserSettings* UserSettings = GetUserSettings())
    {
        UserSettings->SetUIVolume(CurrentSettings.UI);
    }
}

float UAudioSettingsSubsystem::GetUIVolume() const
{
    return CurrentSettings.UI;
}

void UAudioSettingsSubsystem::ApplyAudioSettings()
{
    USettingsFrameworkUserSettings* UserSettings = GetUserSettings();
    if (!UserSettings)
    {
        return;
    }

    UserSettings->SaveSettings();
    SavedSettings = CurrentSettings;
}

void UAudioSettingsSubsystem::CancelAudioSettings()
{
    CurrentSettings = SavedSettings;
    ApplyCurrentSettingsToBuses();
    UpdateUserSettingsFromCurrentState();
}
