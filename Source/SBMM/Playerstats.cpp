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
