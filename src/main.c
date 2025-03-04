#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <termios.h>


#define N0 "#######\n#     #\n#     #\n#     #\n#######"
#define N1 "   #\n#  #\n   #\n   #\n#######"
#define N2 "#######\n      #\n#######\n#\n#######"
#define N3 "#######\n      #\n#######\n      #\n#######"
#define N4 "4"
#define N5 "5"
#define N6 "6"
#define N7 "7"
#define N8 "8"
#define N9 "9\t"
#define P "####\n####\n####\n####"

char *print_number(int time, int iterations)
{
	unsigned digit = 0;
	digit = (time / iterations);
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

char **get_array(int t)
{
	int time = t;
	char **array = (char **)calloc(1, sizeof(char *));
	for (size_t i = 0; i < num_digits(time); i++)
	{
		array[i] = (char *)calloc(num_digits(time), sizeof(char));
	}

	system("clear");
	int j = num_digits(time);
	int k = 0;
	while (1)
	{
		int power = pow(10, j - 1);
		if (j == 0)
			break;
		array[k] = print_number(time, power);
		j--;
		k++;
	}
	return array;
}

struct termios origin;
void disable_raw(){
	tcgetattr(STDIN_FILENO, &origin);
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &origin);
}

void raw(){
	struct termios raw = origin;
	atexit(disable_raw);
	tcgetattr(STDIN_FILENO, &raw);
	raw.c_iflag &= ~( IXOFF | BRKINT | ICRNL );
	raw.c_oflag &= ~(OPOST);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &raw);
}

int main(int argc, char *argv[])
{
	raw();
	//Waiting for input from the user;
	// if (argc < 2)
	// {
	// 	fprintf(stderr, "No time has been specified\nUse : detox <time in seconds>\n");
	// 	exit(-1);
	// }
	// printf("%s\n", print_number(argv));
	int time = 121;
	while (time)
	{
		char **char_list = get_array(time);
		printf("DETOX TIMER");
		for (size_t i = 0; i < num_digits(time); i++)
		{
			printf("\r\n%s", char_list[i]);
		}
		printf("\r\n");
		usleep(1 * 1000000);
		time--;
	}

	// for(size_t i = 0; i < num_digits(atoi(argv[1])); i++){
	// 	free(char_list[i]);
	// }
	// free(char_list);

	return 0;
}
