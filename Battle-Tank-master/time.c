#include "tank.h"

int delay_s(int timeToDelay, unsigned short mm, unsigned short pp, int phase){
	if (phase == 1){
		return 1;
	}
	if (mm - pp > 0){
		if (mm - pp >= timeToDelay)	{
			return 1;
		}
	}
	else if (mm - pp < 0){
		if (1000 - pp + mm >= timeToDelay){
			return 1;
		}
	}
	return 0;
}

void time_now(){
	time_t pIntTime;
	struct tm* currentLocalTime;
	char* dateTimeString = (char*)calloc(100 + 1, sizeof(char));
	pIntTime = time(NULL);
	currentLocalTime = localtime(&pIntTime);
	attron(COLOR_PAIR(1));
	if (currentLocalTime && dateTimeString)
		strftime(dateTimeString, 100, "%H:%M:%S", currentLocalTime);
	mvaddstr(1, 42, dateTimeString);
	refresh();
	free(dateTimeString);
}
