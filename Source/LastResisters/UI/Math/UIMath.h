#ifndef UI_MATH_H
#define UI_MATH_H

static class UIMath
{

protected:
	~UIMath();
public:
	//Normalizes a value between 0 and 1 given a range (eg 30 for 0 to 100)
	static float NormalizeValue(float in, float min, float max);

	//Normalizes a value that is already normalized between 0 and 1 to your desired range.
	static float NormalizeValueCustomRange(float in, float minRange, float maxRange);
};

#endif
