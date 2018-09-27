#include <stdio.h>
#include <fcntl.h>			// fopen()
#include "GPIO.h"
// exports desired gpio to 'userland', creates a folder named /sys/class/gpio/gpioX
// where X = gpionum, writing to files in this folder is how we control gpio
int gpio_init(int gpionum) {
	FILE *fp = fopen("/sys/class/gpio/export", "w");	// open export list file
	if(fp == NULL) {	// failed to open file, error to console, return 0 for failure
		perror("gpio_init");
		return(0);
	} else {
		fprintf(fp, "%d", gpionum);			// write gpio num to export list file
		fclose(fp);							// close file to flush write
		return(1);
	}
}
// sets direction of desired gpio
int gpio_direction(int gpionum, enum gpioDIR dir) {
	char fn[35];	// char array to hold filename
	sprintf(fn, "/sys/class/gpio/gpio%d/direction", gpionum); // build filename from desired gpio
	FILE *fp = fopen(fn,"w");	// open file for writing, deleting all contents and placing file position at beginning
	if(fp == NULL) {			// failed to open file, error to console, return 0 for failure
		perror("gpio_direction");
		return(0);
	} else {
		switch(dir) {			// write direction to file
			case IN: fprintf(fp, "in");
			case OUT: fprintf(fp, "out");
		}
		fclose(fp);				// close file to flush write
		return(1);
	}
}
// sets value (HIGH/LOW) of desired gpio
int gpio_write(int gpionum, enum gpioVAL val) {
	char fn[30];	// char array to hold filename
	sprintf(fn, "/sys/class/gpio/gpio%d/value", gpionum); // build filename from desired gpio
	FILE *fp = fopen(fn,"w+");	// open file for writing/reading, deleting all contents, file position at beginning
	if(fp == NULL) {			// failed to open file, error to console, return 0 for failure
		perror("gpio_write");
		return(0);
	} else {
		fprintf(fp,"%d",val);	// write value
		fclose(fp);				// close file to flush write
		return(1);
	}
}
// reads current value of desired gpio
int gpio_read(int gpionum) {
	int val = 9;	// holds value read from file (init to 9 for debugging, only reads 1 or 0 from file)
	char fn[35];	// char array to hold filename
	sprintf(fn, "/sys/class/gpio/gpio%d/value", gpionum);	// build filename from selected gpio
	FILE *fp = fopen(fn,"r+");	// open file for reading/writing, preserve contents, file position at beginning
	if(fp == NULL) {	// failed to open file correctly, put error to console, return -1 to indicate failure
		perror("gpio_read");
		return(-1);
	} else {
		fscanf(fp, "%d", &val);	// read value
		fclose(fp);				// close file
		return(val);
	}	
}