#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <Windows.h>
#include <conio.h>
#include <ctime>

char* memory;
char* now;
unsigned long long MEMORY_SIZE = 1048576;

unsigned long long WHILE_STACK[65536];
unsigned long long stack;

FILE* fp;

char mode;
unsigned long long cen;

char r;

unsigned long long mertime;

int main(int count, char* strings[]) {
	unsigned long long tmp;
	if (count >= 2) {
		fp = fopen(strings[1], "rb");
		if (!fp) {
			perror("Cannot open file ");
			return -1;
		}
		if (count > 2) {
			for (int i = 2; i < count; i++) {
				if (!strcmp(strings[i], "step"))mode |= 1;
				else if (!strcmp(strings[i], "show"))mode |= 2;
				else MEMORY_SIZE = atoi(strings[i]);
			}
		}
	}
	else {
		puts("BrainFuck <file> [option]");
		puts("[option] : ");
		puts("<Number>  Memory Size");
		puts("step      Single Step Execution");
		puts("show      Show the text");
		return 2;
	}
	if (!MEMORY_SIZE) {
		puts("Illegal memory allocation size");
		return -2;
	}

	memory = (char*)calloc(MEMORY_SIZE, 1);
	now = memory;

	if (!memory) {
		puts("[FATAL]: Failed to allocate memory.");
		return -3;
	}

	mertime = clock();
	while (fread(&r, 1, 1, fp)) {
		if (mode & 1 && !cen)_getch();
		if (cen) {
			if (r == '[')cen += 1;
			else if (r == ']')cen -= 1;
		}
		else {
			if (mode & 2)printf("%lu (%c) \n", ftell(fp), r);
			switch (r)
			{
			case '>':
				if (now - memory + 1 >= MEMORY_SIZE) {
					printf("[FATAL]:%lu(%c) -> Pointer out of bounds", ftell(fp), r);
					free(memory);
					return 1;
				}
				now++;
				break;
			case '<':
				if (now - 1 < memory) {
					printf("[FATAL]:%lu(%c) -> Pointer out of bounds", ftell(fp), r);
					free(memory);
					return 1;
				}
				now--;
				break;
			case '+':
				*now += 1;
				break;
			case '-':
				*now -= 1;
				break;
			case '.':
				putchar(*now);
				break;
			case ',':
				*now = getchar();
				break;
			case '[':
				if (stack == 65535) {
					printf("[FATAL]:%lu(%c) -> Circular stack overflow. (The cycle is too deep.)", ftell(fp), r);
					free(memory);
					return 1;
				}
				if (*now) {
					stack++;
					WHILE_STACK[stack] = ftell(fp)-1;
				}
				else {
					cen += 1;
				}
				break;
			case ']':
				if (!stack) {
					printf("[FATAL]:%lu(%c) -> The circula stack is empty.(The ']' paired with this' ['cannot be found.)", ftell(fp), r);
					free(memory);
					return 1;
				}
				fseek(fp, WHILE_STACK[stack], SEEK_SET);
				stack--;
				break;
			default:
				break;
			}
		}
	}
	mertime = clock() - mertime;
	mertime = mertime * 1000 / CLOCKS_PER_SEC;
	printf("\n\n    [%llu]ms", mertime);
	if(cen)printf("[FATAL]: Error: The loop did not end.");

	return 0;
}