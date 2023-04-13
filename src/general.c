#include "general.h"

int RoundUp(int NumberToRound, int NumberToRoundItTo)
{
	if (NumberToRoundItTo == 0)
		return NumberToRound;

	int remainder = NumberToRound % NumberToRoundItTo;
	if (remainder == 0)
		return NumberToRound;

	return NumberToRound + NumberToRoundItTo - remainder;
}
int RoundDown(int NumberToRound, int NumberToRoundItTo)
{
	if (NumberToRound % NumberToRoundItTo == 0)
		return RoundUp(NumberToRound, NumberToRoundItTo);
	else
		return RoundUp(NumberToRound, NumberToRoundItTo) - NumberToRoundItTo;
}
