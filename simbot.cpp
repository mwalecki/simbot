#include <iostream>
#include <stdlib.h>
#include "joystick.h"
#include "PTProxy.h"
using namespace std;

// Prototypes
void printControlScreen(void);
void ptpReadWrite(void);
void control(void);

// Defines
#define DEVICE_VITALS_SZ 2
#define ANALOG_INPUTS_SZ 8
#define SERVOS_NO 4

// Globals
cJoystick *js;
PTProxy *ptp;
int pwm0 = 0;
int pwm1 = 0;
int digital_out = 0;
int device_vitals[DEVICE_VITALS_SZ];
int analog_in[ANALOG_INPUTS_SZ];
int servos_position[SERVOS_NO];

int main(int argc, char *argv[]) {

	js = new cJoystick();
	sleep(1);
	ptp = new PTProxy("/dev/usb-to-serial");
	usleep(1000000);
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
		cout << device_vitals[i] << endl;
	cout << endl;
	for(int i=0; i<ANALOG_INPUTS_SZ; i++)
                cout << analog_in[i] << endl;
	cout << servos_position[0] << endl;
	cout.flush();
}

void ptpReadWrite(void){
	control();
	ptp->getDeviceVitals(device_vitals, DEVICE_VITALS_SZ);
	ptp->getAnalogInputs(analog_in, ANALOG_INPUTS_SZ);
	ptp->setMotorPWM(pwm0, pwm1);
	ptp->setDigitalOutputs(digital_out);
	ptp->setServosPosition(servos_position, 4);
	ptp->nextStep();
}

void control(void){
	digital_out = (js->buttonPressed(9)?(1<<0):0)
		| (js->buttonPressed(7)?(1<<1):0)
		| (js->buttonPressed(6)?(1<<2):0)
		| (js->buttonPressed(8)?(1<<3):0)
		| (js->buttonPressed(4)?(1<<5):0);
	pwm0 = -800*js->axisPosition(3) + 500*js->axisPosition(2);
	pwm1 = -800*js->axisPosition(3) - 500*js->axisPosition(2);
	servos_position[0] = 1500 + 500*js->axisPosition(0);
}


