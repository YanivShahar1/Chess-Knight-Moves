#include "template.h"

void blue() {
	printf("\033[0;34m");
}
void red() {
	printf("\033[1;31m");
}
void yellow() {
	printf("\033[2;33m");
}
void purple() {
	printf("\033[0;35m");
}
void green() {
	printf("\033[1;32m");
}
void cyan() {
	printf("\033[1;36m");
}
void reset() {
	printf("\033[0m");
}
void boardBackGround() {
	printf("\033[0;30;47m");
}