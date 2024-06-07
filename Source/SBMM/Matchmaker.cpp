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
