// GPIO.h

enum gpioDIR {
	IN,
	OUT
};

enum gpioVAL {
	LOW = 0,
	HIGH = 1
};

int gpio_init(int gpionum);
int gpio_direction(int gpionum, enum gpioDIR);
int gpio_write(int gpionum, enum gpioVAL);
int gpio_read(int gpionum);
