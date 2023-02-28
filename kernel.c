#include "kernel.h"
#include "screen.h"


#define TXT_WHITE 0x07 //blanco sobre negro


char *video_memory = (char *) 0xb8000;

unsigned int line = 0;

void kernel_main(){
    clear_screen();


    print_screen(".__           .__");
    print_screen("|  |__   ____ |  | _____              ____  ______");
    print_screen("|  |  \\ /  _ \\|  | \\__  \\    ______  /  _ \\/  ___/");
    print_screen("|   Y  (  <_> )  |__/ __ \\_ /_____/ (  <_> )___ \\");
    print_screen("|___|  /\\____/|____(____  /          \\____/____  >");
    print_screen("\\/                 \\/                     \\/");


}



void clear_screen(){
    unsigned int i = 0;
    while (i < (80*25*2)){
        video_memory[i] = ' ';
        i++;
        video_memory[i] = TXT_WHITE;
        i++;
    }
}



unsigned int print_screen(char *string){

    unsigned int i = 0;

    i = (line*80*2);

    while(*string != 0){
        if (*string == '\n'){
            line++;
            i = (line*80*2);
            *string++;
        } else {
            video_memory[i] = *string;
            *string++;
            i++;
            video_memory[i] = TXT_WHITE;
            i++;
        }
    }
    line++;

    return(1);
}
