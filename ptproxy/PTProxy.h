/*
 * PTProxy.h
 *
 *  Created on: 29-11-2012
 *      Author: wacek
 */

#ifndef PTPROXY_H_
#define PTPROXY_H_

#include "nf/nfv2.h"
#include "serialcomm/serialcomm.h"
#include <iostream>
#include <math.h>

#define DEFAULT_NFV2_BAUD B57600
#define COMM_BUFSZ 256
#define COMMAND_ARRAY_SZ 16

class PTProxy {
public:
	PTProxy(std::string port);
	virtual ~PTProxy();
	bool isConnected() const;
	void nextStep(void);
	void setMotorPWM(int pwm1, int pwm2);
	void setDigitalOutputs(int out);
	void getAnalogInputs(int *ain, int len);
private:
	NF_STRUCT_ComBuf NFComBuf;
	SerialComm *CommPort;
	std::string portName;
	uint8_t rxBuf[COMM_BUFSZ];
	uint8_t txBuf[COMM_BUFSZ];
	uint8_t commandArray[COMMAND_ARRAY_SZ];
	uint8_t rxCommandArray[COMMAND_ARRAY_SZ];
	uint8_t rxCnt, txCnt, commandCnt, rxCommandCnt;
};

#endif /* PTPROXY_H_ */
