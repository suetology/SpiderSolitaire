#pragma once

#define MAXINT 0x7FFFFFFF

#define CMATH_N 624
#define CMATH_M 397
#define CMATH_MATRIX_A 0x9908b0df   /* constant vector a */
#define CMATH_UPPER_MASK 0x80000000 /* most significant w-r bits */
#define CMATH_LOWER_MASK 0x7fffffff /* least significant r bits */

#define CMATH_TEMPERING_MASK_B 0x9d2c5680
#define CMATH_TEMPERING_MASK_C 0xefc60000
#define CMATH_TEMPERING_SHIFT_U(y)  (y >> 11)
#define CMATH_TEMPERING_SHIFT_S(y)  (y << 7)
#define CMATH_TEMPERING_SHIFT_T(y)  (y << 15)
#define CMATH_TEMPERING_SHIFT_L(y)  (y >> 18)


class Random
{
private:
	unsigned int		rseed;
	unsigned int		rseed_sp;
	unsigned long mt[CMATH_N]; /* the array for the state vector  */
	int mti; /* mti==N+1 means mt[N] is not initialized */

public:
	Random();

	unsigned int	Next(unsigned int n);
	float			Next();
	//void			SetRandomSeed(unsigned int n);
	//unsigned int	GetRandomSeed(void);
	//void			Randomize(void);
};

class SetTraversal
{
private:
	static int prime_array[];
	int skip;
	int currentPosition;
	int maxElements;
	int* currentPrime;
	int searches;

public:
	SetTraversal(int elements);
	int GetNext(bool restart = false);
	bool Done() { return (searches == *currentPrime); }
	void Restart() { currentPosition = 0; searches = 0; }
};

