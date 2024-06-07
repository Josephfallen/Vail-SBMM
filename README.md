### README.md
```markdown
# Skill-Based Matchmaking System Integration

This document provides instructions for integrating a skill-based matchmaking system into an existing Unreal Engine project using C++. The system calculates player skill based on their performance over the last 5 matches and pairs players with similar skill levels.

## Files and Classes

### PlayerStats

- **Location:** `Source/YourProject/PlayerStats.h` and `Source/YourProject/PlayerStats.cpp`
- **Description:** Manages player scores and calculates their skill based on recent matches.
- **Key Functions:**
  - `AddMatchScore(int32 Score)`: Adds a match score to the player's stats.
  - `CalculateSkill() const`: Calculates the player's skill based on the average score of the last 5 matches.

### Matchmaker

- **Location:** `Source/YourProject/Matchmaker.h` and `Source/YourProject/Matchmaker.cpp`
- **Description:** Adds players to a matchmaking pool and finds matches based on player skills.
- **Key Functions:**
  - `AddPlayer(UPlayerStats* PlayerStats)`: Adds a player to the matchmaking pool.
  - `FindMatch()`: Finds and returns a match of players with similar skill levels.

## Integration Steps

### 1. Add the PlayerStats Class

Create the `PlayerStats` class to manage player stats and calculate skill:

**PlayerStats.h**
```cpp
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerStats.generated.h"

UCLASS(Blueprintable)
class YOURPROJECT_API UPlayerStats : public UObject
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
```

**PlayerStats.cpp**
```cpp
#include "PlayerStats.h"

void UPlayerStats::AddMatchScore(int32 Score)
{
    Scores.Add(Score);
    if (Scores.Num() > 5)
    {
        Scores.RemoveAt(0);
    }
}

float UPlayerStats::CalculateSkill() const
{
    if (Scores.Num() == 0)
    {
        return 0.0f;
    }

    float TotalScore = 0.0f;
    for (int32 Score : Scores)
    {
        TotalScore += Score;
    }

    return TotalScore / Scores.Num();
}
```

### 2. Add the Matchmaker Class

Create the `Matchmaker` class to handle matchmaking based on player skills:

**Matchmaker.h**
```cpp
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PlayerStats.h"
#include "Matchmaker.generated.h"

UCLASS(Blueprintable)
class YOURPROJECT_API UMatchmaker : public UObject
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category="Matchmaking")
    void AddPlayer(UPlayerStats* PlayerStats);

    UFUNCTION(BlueprintCallable, Category="Matchmaking")
    TArray<UPlayerStats*> FindMatch();

private:
    TArray<UPlayerStats*> Players;
    static bool CompareSkill(UPlayerStats* A, UPlayerStats* B);
};
```

**Matchmaker.cpp**
```cpp
#include "Matchmaker.h"

void UMatchmaker::AddPlayer(UPlayerStats* PlayerStats)
{
    Players.Add(PlayerStats);
}

TArray<UPlayerStats*> UMatchmaker::FindMatch()
{
    TArray<UPlayerStats*> SortedPlayers = Players;
    SortedPlayers.Sort(CompareSkill);

    TArray<UPlayerStats*> Match;
    const int32 MatchSize = 2; // Example match size

    for (int32 i = 0; i < MatchSize && i < SortedPlayers.Num(); ++i)
    {
        Match.Add(SortedPlayers[i]);
    }

    return Match;
}

bool UMatchmaker::CompareSkill(UPlayerStats* A, UPlayerStats* B)
{
    return A->CalculateSkill() < B->CalculateSkill();
}
```

### 3. Modify Your Build File

Ensure the new classes are included in your project's build process by modifying your build file:

**YourProject.Build.cs**
```csharp
using UnrealBuildTool;

public class YourProject : ModuleRules
{
    public YourProject(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine" });

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
```

### 4. Use the Matchmaking System

#### Creating PlayerStats Instances

In your game mode or player controller, create instances of `UPlayerStats` for each player and store these instances for easy access:

```cpp
UPlayerStats* Player1Stats = NewObject<UPlayerStats>();
Player1Stats->AddMatchScore(100);
Player1Stats->AddMatchScore(150);

UPlayerStats* Player2Stats = NewObject<UPlayerStats>();
Player2Stats->AddMatchScore(120);
Player2Stats->AddMatchScore(130);
```

#### Adding Scores and Calculating Skill

After each match, update the player's stats:

```cpp
Player1Stats->AddMatchScore(160);
Player2Stats->AddMatchScore(140);
```

Calculate the player's skill:

```cpp
float Player1Skill = Player1Stats->CalculateSkill();
float Player2Skill = Player2Stats->CalculateSkill();
```

#### Matchmaking

Create an instance of `UMatchmaker`, add players, and find matches:

```cpp
UMatchmaker* Matchmaker = NewObject<UMatchmaker>();
Matchmaker->AddPlayer(Player1Stats);
Matchmaker->AddPlayer(Player2Stats);

TArray<UPlayerStats*> Match = Matchmaker->FindMatch();
// Handle the match (e.g., start the game with the matched players)
```

### Example Game Mode Usage

Here’s an example of how you might use the `PlayerStats` and `Matchmaker` classes in your game mode:

```cpp
void AYourGameMode::SetupMatchmaking()
{
    UPlayerStats* Player1Stats = NewObject<UPlayerStats>();
    Player1Stats->AddMatchScore(100);
    Player1Stats->AddMatchScore(150);

    UPlayerStats* Player2Stats = NewObject<UPlayerStats>();
    Player2Stats->AddMatchScore(120);
    Player2Stats->AddMatchScore(130);

    UMatchmaker* Matchmaker = NewObject<UMatchmaker>();
    Matchmaker->AddPlayer(Player1Stats);
    Matchmaker->AddPlayer(Player2Stats);

    TArray<UPlayerStats*> Match = Matchmaker->FindMatch();
    // Handle the match (e.g., start the game with the matched players)
}
```

## License

This project is licensed under the MIT License.
```

This single README file provides all the necessary instructions for integrating the skill-based matchmaking system into an existing Unreal Engine project.