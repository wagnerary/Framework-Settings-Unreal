#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AudioSettingsConfig.generated.h"

class USoundControlBus;

UCLASS(BlueprintType)
class SETTINGSFRAMEWORK_API UAudioSettingsConfig : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio Buses")
    TObjectPtr<USoundControlBus> MasterBus;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio Buses")
    TObjectPtr<USoundControlBus> MusicBus;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio Buses")
    TObjectPtr<USoundControlBus> SFXBus;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio Buses")
    TObjectPtr<USoundControlBus> DialogueBus;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Audio Buses")
    TObjectPtr<USoundControlBus> UIBus;
};
