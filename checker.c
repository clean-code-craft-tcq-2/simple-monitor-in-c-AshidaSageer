#include <stdio.h>
#include <assert.h>
#include <string.h>

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
	parameterInfo[0].minimumThreshold = 0;
	parameterInfo[0].maximumThreshold = 45;
	parameterInfo[0].warningLimitHigh = 45;
	parameterInfo[0].warningLimitLow = 45;
	
	strcpy(parameterInfo[1].parameterName, "SOC");
	parameterInfo[1].minimumThreshold = 20;
	parameterInfo[1].maximumThreshold = 80;
	parameterInfo[1].warningLimitHigh = 45;
	parameterInfo[1].warningLimitLow = 45;
	
	strcpy(parameterInfo[2].parameterName, "Charge Rate");  
	parameterInfo[2].minimumThreshold = 0.0;
	parameterInfo[2].maximumThreshold = 0.8;
	parameterInfo[2].warningLimitHigh = 45;
	parameterInfo[2].warningLimitLow = 45;
}

void printToConsole(char message[])
{
printf(message);
}


/*int checkparamlimits(BatteryParameterInfo parameterInfo,  float value){	
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
}*/

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
