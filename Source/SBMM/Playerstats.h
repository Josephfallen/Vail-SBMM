#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerStats.generated.h"

UCLASS(Blueprintable)
class SKILLBASEDMATCHMAKING_API UPlayerStats : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stats")
    TArray<int32> Scores;

    UFUNCTION(BlueprintCallable, Category="Stats")
    void AddMatchScore(int32 Score);

    UFUNCTION(BlueprintCallable, Category="Stats")
    float CalculateSkill() const;
};
