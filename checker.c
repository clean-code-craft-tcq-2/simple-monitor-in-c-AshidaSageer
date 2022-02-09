#include <stdio.h>
#include <assert.h>
#include <string.h>

typedef struct {
  
  char parameterName[20];
  float minimumThreshold;
  float maximumThreshold;
 
} BatteryParameterInfo;

BatteryParameterInfo parameterInfo[2];

void PopulateParameterInfo(){
  
	strcpy(parameterInfo[0].parameterName,"Temperature");
	parameterInfo[0].minimumThreshold = 0;
	parameterInfo[0].maximumThreshold = 45;
	
	strcpy(parameterInfo[1].parameterName, "SOC");
	parameterInfo[1].minimumThreshold = 20;
	parameterInfo[1].maximumThreshold = 80;
	
	strcpy(parameterInfo[2].parameterName, "Charge Rate");  
	parameterInfo[2].minimumThreshold = 0.0;
	parameterInfo[2].maximumThreshold = 0.8;
}

void printToConsole(char message[])
{
printf(message);
}

int checkparamlimits(char parameter[], float value, float minvalue, float maxvalue){
if(value < minvalue){
	printToConsole(strcat(parameter , "is less than lowerlimit \n"));
	return 0;
	}
else if( value > maxvalue){
	printToConsole(strcat(parameter , "exceeds upperlimit \n"));
	return 0;
	}
else {
	return 1;
	}
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
int output;
output = checkparamlimits (parameterInfo[0].parameterName, temperature,parameterInfo[0].minimumThreshold,parameterInfo[0].maximumThreshold)&
checkparamlimits (parameterInfo[1].parameterName, soc,parameterInfo[1].minimumThreshold,parameterInfo[1].maximumThreshold) &
checkparamlimits (parameterInfo[2].parameterName, chargeRate,parameterInfo[2].minimumThreshold,parameterInfo[2].maximumThreshold);

return output;
}

int main() {
  PopulateParameterInfo();
  assert(batteryIsOk(25, 70, 0.7));
  assert(!batteryIsOk(50, 60, 0.7));
  assert(!batteryIsOk(30, 85, 0.1));
  assert(!batteryIsOk(25, 70, 0.9));
}
