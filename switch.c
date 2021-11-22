#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>

#define MONITOR_OUT 4
#define KEY_IN 6
#define MIC_IN 1
#define MIC_DEBOUNCE 1000
#define CLAP_DELAY 0.25

int read_button(int button, int debounce_time);
void toggle_display(int mode);

int main(void){
	wiringPiSetup();
	pinMode(MONITOR_OUT, OUTPUT);
	pinMode(KEY_IN, INPUT);
	pinMode(MIC_IN, INPUT);

	int display = 1;
	int button_pressed = 0;
	clock_t first = 0;

	while(1){
		// button toggling code
		if(read_button(KEY_IN, 5000) && button_pressed == 0){
			button_pressed = 1;
			display = !display;
			toggle_display(display);
			//printf("display toggled\n");
		}
		if(button_pressed == 1 && !read_button(KEY_IN, 5000)){
			button_pressed = 0;
		}

		// mic toggling code
		/*	
		if(!digitalRead(MIC_IN)){
			first = clock();
			while(digitalRead(MIC_IN) != 1); // wait until sound is no longer picked up
			//printf("Single clap\n");
			delay(100);
			while((clock() - first)/CLOCKS_PER_SEC < CLAP_DELAY){
				if(!digitalRead(MIC_IN)){
						//printf("Double clap detected\n");
						toggle_display(display);
						break;			
				}
			}
		}
		*/
	}


	return 0;
}

void toggle_display(int mode){
	digitalWrite(MONITOR_OUT, 1);
	delay(250);
	digitalWrite(MONITOR_OUT, 0);
}

int read_button(int button, int debounce_time){
    int x = 0;
    int last_switch = 0;
    while(x < debounce_time){
        last_switch = digitalRead(button); // read SW0
        for(x = 0; x < debounce_time; x++){
            if(digitalRead(button) != last_switch){
                break;
            }
        }
    }
    return last_switch;
}
