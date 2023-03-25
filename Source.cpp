#include <string>
using namespace std;

typedef union FormulaMap
{
	unsigned int  Val_32;
	//uint16_t wValue;
	struct Nibble
	{
		unsigned int  nib0 : 4;
		unsigned int  nib1 : 4;
		unsigned int  nib2 : 4;
		unsigned int  nib3 : 4;
		unsigned int  nib4 : 4;
		unsigned int  nib5 : 4;
		unsigned int  nib6 : 4;
		unsigned int  nib7 : 4;
	} uNibble;
} NIBBLE;


enum Segment
{
	UNINITIALIZED = 0,
	SIGN,
	NUMBER,
	PERIOD,
	E,
	INVALID = 0xF,

};


Segment LastToken = INVALID;

bool isNumber(string s)
{
	unsigned long long int Mask = 0;
	FormulaMap MyMap;
	MyMap.Val_32 = 0;


	Segment Format[8];
	memset(Format, 0, 8 * sizeof(Segment));
	int j = 0;

	LastToken = INVALID;
	for (int i = 0; i < s.length(); i++)
	{
		if (j > 7)
		{
			return false;
		}

		if ((s[i] >= 48 && s[i] <= 57))
		{
			if (LastToken != Segment::NUMBER)
			{
				Format[j++] = Segment::NUMBER;
				LastToken = Segment::NUMBER;
			}
		}
		else if (s[i] == '+' || s[i] == '-')
		{
			Format[j++] = Segment::SIGN;
			LastToken = Segment::SIGN;

		}
		else if (s[i] == '.')
		{
			Format[j++] = Segment::PERIOD;
			LastToken = Segment::PERIOD;
		}
		else if (s[i] == 'e' || s[i] == 'E')
		{
			Format[j++] = Segment::E;
			LastToken = Segment::E;
		}
		else
		{
			return false;
		}
	}


	for (int i = 1; i < 8; i++)
	{
		if (Format[i] == Segment::UNINITIALIZED)
			Format[i] = Segment::INVALID;
	}

	MyMap.uNibble.nib0 = Format[0];
	MyMap.uNibble.nib1 = Format[1];
	MyMap.uNibble.nib2 = Format[2];
	MyMap.uNibble.nib3 = Format[3];
	MyMap.uNibble.nib4 = Format[4];
	MyMap.uNibble.nib5 = Format[5];
	MyMap.uNibble.nib6 = Format[6];
	MyMap.uNibble.nib7 = Format[7];
	unsigned int Val = MyMap.Val_32;

	if (Val >= 4061405985 && Val <= 4294967282)
	{
		if (Val == 4280369713 ||
			Val == 4294054947 ||
			Val == 4280369714 ||
			Val == 4280558369 ||
			Val == 4294054962 ||
			Val == 4294066977 ||
			Val == 4294066737 ||
			Val == 4294911026 ||
			Val == 4294911011 ||
			Val == 4294964001 ||
			Val == 4294963762 ||
			Val == 4294967075 ||
			Val == 4294967282 ||
			Val == 4294910753 ||
			Val == 4294967090 ||
			Val == 4294963761 ||
			Val == 4294963778 ||
			Val == 4294911009 ||
			Val == 4294910274 ||
			Val == 4294054945 ||
			Val == 4294066738 ||
			Val == 4294967073 ||
			Val == 4061405985)
		{
			return true;
		}
	}

	return false;
}
