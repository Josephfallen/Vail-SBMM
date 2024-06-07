#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerStats.h"
#include "Matchmaker.generated.h"

UCLASS(Blueprintable)
class SKILLBASEDMATCHMAKING_API UMatchmaker : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Matchmaking")
    void AddPlayer(UPlayerStats* PlayerStats);

    UFUNCTION(BlueprintCallable, Category="Matchmaking")
    TArray<UPlayerStats*> FindMatch();

private:
    TArray<UPlayerStats*> Players;
};
    static bool CompareSkill(UPlayerStats* A, UPlayerStats* B);