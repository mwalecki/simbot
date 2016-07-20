#include "nfv2.h"

void NFv2_Config2(NF_STRUCT_ComBuf *NFComBuf, uint8_t myAddress, uint8_t slaveAddress){

NFComBuf->myAddress = myAddress;
NFComBuf->ReadDeviceVitals.addr[0] = slaveAddress;
NFComBuf->ReadDeviceVitals.addr[1] = slaveAddress;

NFComBuf->SetServosPosition.addr[0] = slaveAddress;
NFComBuf->SetServosPosition.addr[1] = slaveAddress;
//NFComBuf->SetServosPosition.addr[2] = slaveAddress;
//NFComBuf->SetServosPosition.addr[3] = slaveAddress;
//NFComBuf->SetServosPosition.addr[4] = slaveAddress;
//NFComBuf->SetServosPosition.addr[5] = slaveAddress;
//NFComBuf->SetServosPosition.addr[6] = slaveAddress;
//NFComBuf->SetServosPosition.addr[7] = slaveAddress;

NFComBuf->SetDrivesMode.addr[0] = slaveAddress;
NFComBuf->SetDrivesMode.addr[1] = slaveAddress;
NFComBuf->SetDrivesMode.addr[2] = slaveAddress;
NFComBuf->SetDrivesMode.addr[3] = slaveAddress;

NFComBuf->SetDrivesPWM.addr[0] = slaveAddress;
NFComBuf->SetDrivesPWM.addr[1] = slaveAddress;

//NFComBuf->SetDrivesSpeed.addr[0] = slaveAddress;
//NFComBuf->SetDrivesSpeed.addr[1] = slaveAddress;

//NFComBuf->SetDrivesPosition.addr[0] = slaveAddress;
//NFComBuf->SetDrivesPosition.addr[1] = slaveAddress;

//NFComBuf->ReadDrivesPosition.addr[0] = slaveAddress;
//NFComBuf->ReadDrivesPosition.addr[1] = slaveAddress;

//NFComBuf->ReadDrivesSpeed.addr[0] = slaveAddress;
//NFComBuf->ReadDrivesSpeed.addr[1] = slaveAddress;

//NFComBuf->ReadDrivesStatus.addr[0] = slaveAddress;
//NFComBuf->ReadDrivesStatus.addr[1] = slaveAddress;

NFComBuf->ReadAnalogInputs.addr[0] = slaveAddress;
NFComBuf->ReadAnalogInputs.addr[1] = slaveAddress;
NFComBuf->ReadAnalogInputs.addr[2] = slaveAddress;
NFComBuf->ReadAnalogInputs.addr[3] = slaveAddress;
NFComBuf->ReadAnalogInputs.addr[4] = slaveAddress;
NFComBuf->ReadAnalogInputs.addr[5] = slaveAddress;
NFComBuf->ReadAnalogInputs.addr[6] = slaveAddress;
NFComBuf->ReadAnalogInputs.addr[7] = slaveAddress;

NFComBuf->SetDigitalOutputs.addr[0] = slaveAddress;
NFComBuf->SetDigitalOutputs.addr[1] = slaveAddress;
}

