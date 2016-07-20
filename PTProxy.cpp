/*
 * PTProxy.cpp
 *
 *  Created on: 29-11-2012
 *      Author: wacek
 */

#include "PTProxy.h"

PTProxy::PTProxy(std::string port) : portName(port) {
	NFv2_Config2(&NFComBuf, NF_MasterAddress, NF_AddressBase);
	NFv2_CrcInit();
	CommPort = new SerialComm(portName, DEFAULT_NFV2_BAUD);
	if (! (CommPort->isConnected()) ) {
		std::cout << "Connection failed!" << std::endl;
	} else{
		std::cout << "Connected to " << port << std::endl;
	}
	rxCnt = 0;
	commandCnt = 0;
}

PTProxy::~PTProxy() {
}

bool PTProxy::isConnected() const {
	return (CommPort->isConnected());
}

void PTProxy::nextStep(void){
	// Always read:
	commandArray[commandCnt++] = NF_COMMAND_ReadDeviceVitals;
	commandArray[commandCnt++] = NF_COMMAND_ReadAnalogInputs;

	// Try to receive a reply to the previous command
	while(CommPort->read(&(rxBuf[rxCnt]), 1) > 0){
		NF_Interpreter(&NFComBuf, (uint8_t*)rxBuf, (uint8_t*)&rxCnt, rxCommandArray, &rxCommandCnt);
	}

	// If a command send requested
	if(commandCnt > 0) {
		txCnt = NF_MakeCommandFrame(&NFComBuf, txBuf, (const uint8_t*)commandArray, commandCnt, NF_AddressBase);
		// Clear communication request
		commandCnt = 0;
		// Send command frame to motor controllers
		CommPort->write(txBuf, txCnt);
	}
}

void PTProxy::setMotorPWM(int pwm1, int pwm2){
	NFComBuf.SetDrivesPWM.data[0] = pwm1;
	NFComBuf.SetDrivesPWM.data[1] = pwm2;
	commandArray[commandCnt++] = NF_COMMAND_SetDrivesPWM;

	if((NFComBuf.SetDrivesMode.data[0] != NF_DrivesMode_PWM)
			|| (NFComBuf.SetDrivesMode.data[1] != NF_DrivesMode_PWM)){
		NFComBuf.SetDrivesMode.data[0] = NF_DrivesMode_PWM;
		NFComBuf.SetDrivesMode.data[1] = NF_DrivesMode_PWM;
		commandArray[commandCnt++] = NF_COMMAND_SetDrivesMode;
	}
}

void PTProxy::setServosPosition(int *pos, int len){
	for(int i=0; i<len; i++)
	        NFComBuf.SetServosPosition.data[i] = pos[i];
        commandArray[commandCnt++] = NF_COMMAND_SetServosPosition;
}

void PTProxy::setDigitalOutputs(int out){
	NFComBuf.SetDigitalOutputs.data[0] = out;
	commandArray[commandCnt++] = NF_COMMAND_SetDigitalOutputs;
}

void PTProxy::getAnalogInputs(int *ain, int len) {
	commandArray[commandCnt++] = NF_COMMAND_ReadAnalogInputs;
	for(int i=0; (i<len) && (i<NF_BUFSZ_ReadAnalogInputs); i++)
		ain[i] = NFComBuf.ReadAnalogInputs.data[i];
}

void PTProxy::getDeviceVitals(int *devv, int len) {
        commandArray[commandCnt++] = NF_COMMAND_ReadDeviceVitals;
        for(int i=0; (i<len) && (i<NF_BUFSZ_ReadDeviceVitals); i++)
                devv[i] = NFComBuf.ReadDeviceVitals.data[i];
}

