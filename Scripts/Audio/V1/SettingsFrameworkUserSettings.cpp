#include "SettingsFrameworkUserSettings.h"

void USettingsFrameworkUserSettings::SetMasterVolume(float Volume)
{
    MasterVolume = FMath::Clamp(Volume, 0.0f, 1.0f);
}

float USettingsFrameworkUserSettings::GetMasterVolume() const
{
    return MasterVolume;
}

void USettingsFrameworkUserSettings::SetMusicVolume(float Volume)
{
    MusicVolume = FMath::Clamp(Volume, 0.0f, 1.0f);
}

float USettingsFrameworkUserSettings::GetMusicVolume() const
{
    return MusicVolume;
}

void USettingsFrameworkUserSettings::SetSFXVolume(float Volume)
{
    SFXVolume = FMath::Clamp(Volume, 0.0f, 1.0f);
}

float USettingsFrameworkUserSettings::GetSFXVolume() const
{
    return SFXVolume;
}

void USettingsFrameworkUserSettings::SetDialogueVolume(float Volume)
{
    DialogueVolume = FMath::Clamp(Volume, 0.0f, 1.0f);
}

float USettingsFrameworkUserSettings::GetDialogueVolume() const
{
    return DialogueVolume;
}

void USettingsFrameworkUserSettings::SetUIVolume(float Volume)
{
    UIVolume = FMath::Clamp(Volume, 0.0f, 1.0f);
}

float USettingsFrameworkUserSettings::GetUIVolume() const
{
    return UIVolume;
}
