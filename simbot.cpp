#include <iostream>
#include <stdlib.h>
#include "joystick.h"
using namespace std;

int main(int argc, char *argv[]) {
	cJoystick js;
	
	while(1) {
		system("clear");
		for(int i=0; i<6; i++)
			cout << js.axisPosition(i) << endl;
		cout.flush();
		usleep(100000);
	}
	return 0;
}
