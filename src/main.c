#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>

#define N0 "#########\n#       #\n#       #\n#       #\n#########\n"
#define N1 "\t#\n   #\t#\n#\t#\n\t#\n   ##########\n"
#define N2 "#########\n\t#\n#########\n#\n#########\n"
#define N3 "#########\n\t#\n#########\n\t#\n#########\n"
#define N4 "4\n"
#define N5 "5\n"
#define N6 "6\n"
#define N7 "7\n"
#define N8 "8\n"
#define N9 "9\n"
#define P "####\n####\n####\n####"

char *print_number(int time, int iterations)
{
	unsigned digit = 0;
	digit = (time / iterations);
	if (!digit && iterations == 10)
		return "end";
	unsigned short res = (unsigned short)round(digit) % 10;
	switch (res)
	{
	case 0:
		return N0;
		break;
	case 1:
		return N1;
		break;
	case 2:
		return N2;
		break;
	case 3:
		return N3;
		break;
	case 4:
		return N4;
		break;
	case 5:
		return N5;
		break;
	case 6:
		return N6;
		break;
	case 7:
		return N7;
		break;
	case 8:
		return N8;
		break;
	case 9:
		return N9;
		break;
	default:
		return P;
		break;
	}
}

int num_digits(int number)
{
	int count = 0;
	do
	{
		count++;
		number /= 10;
	} while (number != 0);

		return count;
}

int main(int argc, char *argv[])
{

	if (argc < 2)
	{
		fprintf(stderr, "No time has been specified\nUse : detox <time in seconds>\n");
		exit(-1);
	}
	// printf("%s\n", print_number(argv));
	int time = atoi(argv[1]);
	bool Ended = false;
	while (!Ended)
	{

		for (size_t i = 0; i < atoi(argv[1]); i++)
		{
			system("clear");
			int j = num_digits(time);
			while (1)
			{
				int power = pow(10, j);
				if (print_number(time, power) == "end")
					break;
				printf("%s", print_number(time, power));
				j--;
				usleep(1 * 1000000);
			}
			time--;
			if (time == -1)
			{
				Ended = true;
				break;
			}
		}
	}
	return 0;
}
