#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/ioctl.h>

#include <termios.h>

enum arrows
{
	ARROW_UP = 1001,
	ARROW_DOWN,
	ARROW_RIGHT,
	ARROW_LEFT
};

struct winsize ws;

char *num0[5] = {"#######", "#     #", "#     #", "#     #", "#######"};
char *num1[5] = {"   #", "#  #", "   #", "   #", "#######"};
char *num2[5] = {"#######", "      #", "#######", "#", "#######"};
char *num3[5] = {"#######", "      #", "#######", "      #", "#######"};
char *num4[5] = {"#     #", "#     #", "#######", "      #", "      #"};
char *num5[5] = {"#######", "#      ", "#######", "      #", "#######"};
char *num6[5] = {"#######", "#      ", "#######", "#     #", "#######"};
char *num7[5] = {"#######", "      #", "     #", "    #", "   #"};
char *num8[5] = {"#######", "#     #", "#######", "#     #", "#######"};
char *num9[5] = {"#######", "#     #", "#######", "      #", "#######"};

int col = 50;
int line = 1;

void raw();
void disable_raw();
char **get_array(int t);
int num_digits(int number);
char **print_number(int time, int iterations);
void die(const char *s);
/*Designs
	Normal columns: 0, lines: 1
	Center columns: 50, linens: 7
	C Top columns: 50, lines: 1
	C Left columns: 0, lines: 50
	C Right columns: 0, lines 100
	C Bottom columns: -50, lines: 1
	3D effect column++, lines: anything
	Diagonal columns: 50, lines: 50*/
void init()
{
	raw();
	setvbuf(stdout, NULL, _IONBF, 0);
	
	system("clear");
}
int main(int argc, char *argv[])
{

	
	if(argc < 2){
		fprintf(stderr, "Command error: ./detox <time in seconds>\n");
		exit(-1);
	}
	init();

	int time = atoi(argv[1]);
	char **char_list;

	while (time)
	{
		char_list = get_array(time);
		for (size_t i = 0; i < num_digits(time); i++)
		{
			char_list;
		}
		usleep(1 * 1000000);
		time--;
	}
	printf("\x1b[%d;%df The Timer has finished!", line, col);
	printf("\r\n");
	return 0;
}



char **print_number(int time, int iterations)
{
	int digit;
	digit = (time / iterations);
	unsigned short res = (unsigned short)round(digit) % 10;
	switch (res)
	{
	case 0:
		return num0;
		break;
	case 1:
		return num1;
		break;
	case 2:
		return num2;
		break;
	case 3:
		return num3;
		break;
	case 4:
		return num4;
		break;
	case 5:
		return num5;
		break;
	case 6:
		return num6;
		break;
	case 7:
		return num7;
		break;
	case 8:
		return num8;
		break;
	case 9:
		return num9;
		break;
	default:
		fprintf(stdout, "There was an erro printing the number");
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

	if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws)) exit(-1);
	else{
		col = ws.ws_col/2;
		
	}

	const int SIZE = 3;
	while (1)
	{
		line = ws.ws_row/2;
		int power = pow(10, j - 1);

		if (j == 0)
			break;
		array = print_number(time, power);
		for (int i = 0; i < 5; i++)
		{
			printf("\x1b[%d;%df%s", line, col, array[i]);
			if(time < 5){
				printf("\x1b[31m\x1b[%d;%df%s", line, col, array[i]);
			}
			printf("\x1b[0m");
			line++;
		}
		col += 10;
		j--;
		k++;
	}
	return array;
}

struct termios origin;

void die(const char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}
void disable_raw()
{
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &origin) == -1)
	{
		die("tcsetattr");
	}
}

void raw()
{
	tcgetattr(STDIN_FILENO, &origin);
	atexit(disable_raw);

	struct termios raw = origin;
	raw.c_iflag &= ~(IXOFF | BRKINT | ICRNL);
	raw.c_oflag &= ~(OPOST);
	raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, &raw);
	raw.c_cc[VTIME] = 0;
	raw.c_cc[VMIN] = 0;
}