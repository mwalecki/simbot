#include <iostream>
#include <stdlib.h>
#include "joystick.h"
#include "PTProxy.h"
using namespace std;

// Prototypes
void printControlScreen(void);
void ptpReadWrite(void);

// Defines
#define DEVICE_VITALS_SZ 6
#define ANALOG_INPUTS_SZ 8

// Globals
cJoystick *js;
PTProxy *ptp;

int _G_device_vitals[DEVICE_VITALS_SZ];
int _G_analog_inputs[ANALOG_INPUTS_SZ];

int main(int argc, char *argv[]) {

	js = new cJoystick();
	sleep(1);
	ptp = new PTProxy("/dev/usb-to-serial");
	sleep(1);	

	while(1) {
		ptpReadWrite();
		printControlScreen();
		usleep(100000);
	}
	return 0;
}

void printControlScreen(void){
	system("clear");
	for(int i=0; i<6; i++)
		cout << js->axisPosition(i) << endl;
	for(int i=0; i<10; i++)
                cout << (js->buttonPressed(i)?"[#] ":"[ ] ");
	cout << endl;
        for(int i=0; i<DEVICE_VITALS_SZ; i++)
		cout << _G_device_vitals[i] << endl;
	for(int i=0; i<ANALOG_INPUTS_SZ; i++)
                cout << _G_analog_inputs[i] << endl;
	cout.flush();
}

void ptpReadWrite(void){
	ptp->getDeviceVitals(_G_device_vitals, DEVICE_VITALS_SZ);
	ptp->getAnalogInputs(_G_analog_inputs, ANALOG_INPUTS_SZ);
	ptp->nextStep();
}

