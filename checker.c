#include <stdio.h>
#include <assert.h>
#include <string.h>

#define LOWER_THRESHOLD_BATT_TEMP 0
#define UPPER_THRESHOLD_BATT_TEMP 45
#define LOWER_THRESHOLD_BATT_SOC 20
#define UPPER_THRESHOLD_BATT_SOC 80
#define UPPER_THRESHOLD_BATT_CHARGE_RATE 0.8
#define LOWER_THRESHOLD_BATT_CHARGE_RATE 0.5
#define TOLERANCE_PERCENTAGE 0.05

typedef struct {
  
  char parameterName[20];
  float minimumThreshold;
  float maximumThreshold;
  float warningLimitHigh;
  float warningLimitLow;
} BatteryParameterInfo;

BatteryParameterInfo parameterInfo[3];

void PopulateParameterInfo(){
  
	strcpy(parameterInfo[0].parameterName,"Temperature");
	parameterInfo[0].minimumThreshold = LOWER_THRESHOLD_BATT_TEMP;
	parameterInfo[0].maximumThreshold = UPPER_THRESHOLD_BATT_TEMP;
	parameterInfo[0].warningLimitHigh = (UPPER_THRESHOLD_BATT_TEMP + (UPPER_THRESHOLD_BATT_TEMP * TOLERANCE_PERCENTAGE);
	parameterInfo[0].warningLimitLow = (LOWER_THRESHOLD_BATT_TEMP - (LOWER_THRESHOLD_BATT_TEMP * TOLERANCE_PERCENTAGE);
	
	strcpy(parameterInfo[1].parameterName, "SOC");
	parameterInfo[1].minimumThreshold = LOWER_THRESHOLD_BATT_SOC;
	parameterInfo[1].maximumThreshold = UPPER_THRESHOLD_BATT_SOC;
	parameterInfo[1].warningLimitHigh = (UPPER_THRESHOLD_BATT_SOC + (UPPER_THRESHOLD_BATT_SOC * TOLERANCE_PERCENTAGE);
	parameterInfo[1].warningLimitLow = (LOWER_THRESHOLD_BATT_SOC - (LOWER_THRESHOLD_BATT_SOC * TOLERANCE_PERCENTAGE);
	
	strcpy(parameterInfo[2].parameterName, "Charge Rate");  
	parameterInfo[2].minimumThreshold = LOWER_THRESHOLD_BATT_CHARGE_RATE;
	parameterInfo[2].maximumThreshold = UPPER_THRESHOLD_BATT_CHARGE_RATE;
	parameterInfo[2].warningLimitHigh = (UPPER_THRESHOLD_BATT_CHARGE_RATE + (UPPER_THRESHOLD_BATT_CHARGE_RATE * TOLERANCE_PERCENTAGE);
	parameterInfo[2].warningLimitLow = (LOWER_THRESHOLD_BATT_CHARGE_RATE - (LOWER_THRESHOLD_BATT_CHARGE_RATE * TOLERANCE_PERCENTAGE);
}

void printToConsole(char message[])
{
printf(message);
}


int checkparamlimits(BatteryParameterInfo parameterInfo,  float value){	
if(value < parameterInfo.minimumThreshold){
	printToConsole(strcat(parameterInfo.parameterName , "is less than lowerlimit \n"));
	return 0;
	}
else if( value > parameterInfo.maximumThreshold){
	printToConsole(strcat(parameterInfo.parameterName , "exceeds upperlimit \n"));
	return 0;
	}
else {
	return 1;
	}
}

int checkForWarnings(BatteryParameterInfo parameterInfo,  float value){	
if(value < parameterInfo.warningLimitLow){
	printToConsole(strcat(parameterInfo.parameterName , "is approaching lowerlimit \n"));
	return 0;
	}
else if( value > parameterInfo.warningLimitHigh){
	printToConsole(strcat(parameterInfo.parameterName , "is approaching upperlimit \n"));
	return 0;
	}
else {
	return 1;
	}
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
int output;
/* Check for breaches */	
output = checkparamlimits (parameterInfo[0], temperature)&
checkparamlimits (parameterInfo[1], soc) &
checkparamlimits (parameterInfo[2], chargeRate);

/* If there are no breaches, check for warnings */
if(output==1)
{
output = checkForWarnings (parameterInfo[0], temperature)&
checkForWarnings (parameterInfo[1], soc) &
checkForWarnings (parameterInfo[2], chargeRate);
}

return output;
}

int main() {
  PopulateParameterInfo();
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 60, 0.7));
  assert(!batteryIsOk(30, 85, 0.1));
  assert(!batteryIsOk(25, 70, 0.9));
}
