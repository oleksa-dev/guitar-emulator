/* For correct execution of this code use Dev-C++ 5.11 or higher */
#include <string.h>
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>


#pragma comment(lib, "Winmm.lib")
using namespace std;

//------------------------------------------------------------------------------------------------------------------------------
/* DEFINE GLOBAL SETTINGS */
#define PAUSE getchar();

// Define nec array's size
#define Row 29 // Rows
#define Col 29 // Cols
#define CHORDS_AMOUNT  7 
#define STRINGS_AMOUNT 6 

// Define string's indexes
#define sE1 0
#define sB2 1
#define sG3 2
#define sD4 3
#define sA5 4
#define sE6 5

// Define major chords indexes
#define C 0
#define D 1
#define E 2
#define F 3
#define G 4
#define A 5
#define B 6

// Define minor chords indexes
#define Cm 0
#define Dm 1
#define Em 2
#define Fm 3
#define Gm 4
#define Am 5
#define Bm 6

// Struct settings
#define x 9
#define y 2
typedef struct
{
	char title[10];       // Chors title
	int  position[x][y];  // Notes position on strings	
} chord; 
//END---------------------------------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------------------------------------
/* SOUND SECTION */

void  soundsSet(char key);                      // Set of sounds that are used in programm
char  chooseSoundToPlay();                      // Choose sound for playing while pressing keys
char* writeKeys(char guitarNeck[Row][Col], char buf, chord* pStructArr0, chord* pStructArr1, chord* pStructArr2);// Writing keys during it pressing
char* playAndShowFromMem(char *pForKeysInMem, char guitarNeck[Row][Col]  // Play³ sounds by reading keys from memory and displays chords
				, char key, char buf, chord* pStructArr0
				, chord* pStructArr1, chord* pStructArr2);         
void* writeToFileBin(char *pForKeysInMem);      // Writing keys from memory to the binary file
char* readFile();				                // Reading chords from file
//------------------------------------------------------------------------------------------------------------------------------
/* NECK SECTION */

void printGuitarNeck(char guitarNeck[Row][Col]);                                         // Print guitar neck
void clearGuitarNeck(char guitarNeck[Row][Col]);					     				 // Clear guitar neck
void arrSymbolChanger(char guitarNeck[Row][Col], int chordIndex, chord* pStructArr);     // Change symbols in array 
void changeChordsOnNeck(char guitarNeck[Row][Col], char key, char buf, chord* pStructArr); // Change guitar's chords 
void isCleanAndChangeChord(char guitarNeck[Row][Col], int chordIndex, chord* pStructArr); // Is cleaned the neck and changed chords positions
//------------------------------------------------------------------------------------------------------------------------------
/* MENU SECTION */

void printHeader(chord *pSomeStuct, int chordIndex);  // This header is printed while pressing chords
void printDefaultHeader();                            // This header is printed by default
//void printHeaderForPlay();                            // This header will be printed in the next program version
//void printHeaderForRecord();                          // This header will be printed in the next program version
void printDefaultBody(char guitarNeck[Row][Col]);         // This body is printed by defoult
void printBody();				      				  // This body is printed in screen function						
void printDefaultFooter();                            // Footer section is contained menu    
void defaultScreen(char guitarNeck[Row][Col]);            // Is contained default header, default body and footer
void outputScreen();                                  // Is contained  header, body and footer that are changed during program

//int argc, char **argv
int main(){
	
	/* Handle display settings */
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  	SetConsoleTitle("Guitar Emulator v1.0");            
  	system("mode con lines=48 cols=55");
	
	
    //--------------------------------------------------------------------------------------------------------------------------
    /* Guitat neck declaretion and initialisation */
	
	 
	char guitarNeck[Row][Col] = 
    {
//                                    (7)             (11)            (15)            (19)            (23)            (27) 	   	
		 {' ',' ',' ',' ',' ',' ',' ','E',' ',' ',' ','A',' ',' ',' ','D',' ',' ',' ','G',' ',' ',' ','B',' ',' ',' ','E',' '}
		,{' ',' ',' ',' ',' ',' ',' ','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=',' '}	
		,{' ',' ',' ',' ',' ',' ',' ','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=','=',' '}
		,{' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' '}
		,{' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' '}
		,{' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' '}
		,{' ',' ',' ','1',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' '}// (6)
		,{' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' '}
		,{' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' '}
		,{' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' '}
		,{' ',' ',' ',' ',' ',' ',' ','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',' '}
		,{' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' '}
		,{' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' '}
		,{' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' '}
		,{' ',' ',' ','2',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' '}// (14)
		,{' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' '}
		,{' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' '}	
		,{' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' '}
		,{' ',' ',' ',' ',' ',' ',' ','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',' '}
		,{' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' '}
		,{' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' '}
		,{' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' '}
		,{' ',' ',' ','3',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' '}// (22)
		,{' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' '}
		,{' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' '}
		,{' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' ',' ',' ','|',' '}
		,{' ',' ',' ',' ',' ',' ',' ','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',' '}
		,{' ',' ',' ',' ',' ',' ',' ','6',' ',' ',' ','5',' ',' ',' ','4',' ',' ',' ','3',' ',' ',' ','2',' ',' ',' ','1',' '}
		,{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}// (28)
	};//	                          (7)             (11)            (15)            (19)            (23)            (27)
    //--------------------------------------------------------------------------------------------------------------------------
	
	
    //--------------------------------------------------------------------------------------------------------------------------
	/* Declaretion and initialisation struct's chords arrays */
	
	// Strings and chords indexes
	// strings	E  B  G  D  A  E
	// chords   Cm Dm Em Fm Gm Am Bm
	//			C  D  E  F  G  A  B
	// indexes  0  1  2  3  4  5  6	
	
	chord strings[STRINGS_AMOUNT]= // Strings's structs's array initialisation 
    //    Title  Position  
	{//            X  Y      
	    { "E", {{28, 27}} }
	   ,{ "B", {{28, 23}} }                    
	   ,{ "G", {{28, 19}} }                    
	   ,{ "D", {{28, 15}} }                                       
	   ,{ "A", {{28, 11}} }                    
	   ,{ "E", {{28,  7}} }                    
	};
	
	chord majorChords[CHORDS_AMOUNT] =  // Minor chord's structs's array initialisation
    //    Title               Position  
	{//            X  Y      X  Y      X  Y      X  Y       X  Y      X  Y
	    { "C", {{  6, 23}, {14, 15}, {22, 11}                               } }
	   ,{ "D", {{ 14, 19}, {14, 27}, {22, 23}                               } }                     
	   ,{ "E", {{  6, 19}, {14, 11}, {14, 15}                               } }                     
	   ,{ "F", {{  6,  7}, { 6, 23}, { 6, 27}, {14, 19}, { 22, 11}, {22, 15}} }                     
	   ,{ "G", {{ 14, 11}, {22,  7}, {22, 27}                               } }                     
	   ,{ "A", {{ 14, 15}, {14, 19}, {14, 23}                               } }                     
	   ,{ "B", {{  6, 11}, { 6, 27}, {22, 15}, {22, 19}, {22, 23}           } }                     
	};
	
	chord minorChords[CHORDS_AMOUNT] =  // Major chord's structs's array initialisation
	//     Title              Position 
	{//             X  Y      X  Y      X  Y      X  Y      X  Y      X  Y      
		 { "Cm", {{ 6, 11}, { 6, 27}, {14, 23}, {22, 15}, {22, 19}          } }
	    ,{ "Dm", {{ 6, 27}, {14, 19}, {22, 23}                              } }
        ,{ "Em", {{14, 11}, {14, 15}                                        } }
        ,{ "Fm", {{ 6,  7}, { 6, 19}, { 6, 23}, { 6, 27}, {22, 11}, {22, 15}} }
        ,{ "Gm", {{ 6, 11}, { 6, 19}, {22,  7}, {22, 23}, {22, 27}          } }
        ,{ "Am", {{ 6, 23}, {14, 19}, {14, 15}                              } }
        ,{ "Bm", {{ 6, 11}, { 6, 27}, {14, 23}, {22, 15}, {22, 19}          } }
                             
	};
    //--------------------------------------------------------------------------------------------------------------------------
	
	
    //--------------------------------------------------------------------------------------------------------------------------
	/* Struct's array pointer initialisation */
//	chord* pStrings=strings;
//	chord* pMajChords=majorChords;
//	chord* pMinChords=minorChords;
	//--------------------------------------------------------------------------------------------------------------------------
	char *pKeysInMem, key, buf=0;
	
	defaultScreen(guitarNeck);
	
	int i, count=0;

	do
	{
		key = getch();
		
		switch(key)
		{
			case 'a'...'g' : 	changeChordsOnNeck(guitarNeck, key, buf, minorChords);
								soundsSet(key); break;
			
			case 'A'...'G' : 	changeChordsOnNeck(guitarNeck, key, buf, majorChords);
								soundsSet(key); break;
			
			case '1'...'6' : 	changeChordsOnNeck(guitarNeck, key, buf,  strings);
								soundsSet(key); break;			
						        
						
			case 'r' : 	pKeysInMem=writeKeys(guitarNeck, buf, minorChords, majorChords, strings); 
						writeToFileBin(pKeysInMem); 
						break;
			
			case 'p' :  pKeysInMem=readFile();
						playAndShowFromMem(pKeysInMem, guitarNeck, key, buf, minorChords, majorChords, strings);
						break;
			
			case 's' :  system("cls");
						defaultScreen(guitarNeck);
						break;
		}		
		buf = key;
	}while(key != 'q');	
	
	return 0;
}

//------------------------------------------------------------------------------------------------------------------------------
/* SOUND SECTION */
//------------------------------------------------------------------------------------------------------------------------------

/* Sounds set */
 void soundsSet(char key)
 {
	switch(key) 
	{	// Single notes sounds
		case '1' : PlaySound("1_str_E.wav", NULL, SND_SYNC); break;	
		case '2' : PlaySound("2_str_B.wav", NULL, SND_SYNC); break;	
		case '3' : PlaySound("3_str_G.wav", NULL, SND_SYNC); break;	
		case '4' : PlaySound("4_str_D.wav", NULL, SND_SYNC); break;	
		case '5' : PlaySound("5_str_A.wav", NULL, SND_SYNC); break;	
		case '6' : PlaySound("6_str_E.wav", NULL, SND_SYNC); break;	
		// Major chords	sounds
		case 'C' : PlaySound("C.wav", NULL, SND_SYNC); break;	
		case 'D' : PlaySound("D.wav", NULL, SND_SYNC); break;	
		case 'E' : PlaySound("E.wav", NULL, SND_SYNC); break;
		case 'F' : PlaySound("F.wav", NULL, SND_SYNC); break;
		case 'G' : PlaySound("G.wav", NULL, SND_SYNC); break;
		case 'A' : PlaySound("B.wav", NULL, SND_SYNC); break;
		case 'B' : PlaySound("E.wav", NULL, SND_SYNC); break;
			
		// Minor chords	sounds	
		case 'c' : PlaySound("Cm.wav", NULL, SND_SYNC); break;	
		case 'd' : PlaySound("Dm.wav", NULL, SND_SYNC);	break;
		case 'e' : PlaySound("Em.wav", NULL, SND_SYNC); break;
		case 'f' : PlaySound("Fm.wav", NULL, SND_SYNC); break;
		case 'g' : PlaySound("Gm.wav", NULL, SND_SYNC); break;
		case 'a' : PlaySound("Am.wav", NULL, SND_SYNC); break;
		case 'b' : PlaySound("Bm.wav", NULL, SND_SYNC); break;
							
		// Quit
		case 'q' : break;						
	} 
 }
//------------------------------------------------------------------------------------------------------------------------------

/* Choose sound for playing while pressing keys */
char chooseSoundToPlay()
{	
	char key;
	
	do
	{	// Filtering unwanted keys
		key = getch();
		if (key == 'a' || key == 'e' || key == 'd' || key == 'c' || key == 'f' || key == 'g' || key == 'b' || 
			key == 'C' || key == 'D' || key == 'E' || key == 'F' || key == 'G' || key == 'A' || key == 'B' || 
			key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6' || key == 'r' || 
			key == 'p' || key == 's')  break;
		else continue;	
	}while(key != 's');
	soundsSet(key);
	return key;
}
//------------------------------------------------------------------------------------------------------------------------------

/* Writing keys to memory during it pressing */
char* writeKeys(char guitarNeck[Row][Col], char buf, chord* pStructArr0, chord* pStructArr1, chord* pStructArr2)
{
	int i=2;
	char *pKname, pressedKey;
	
	pKname = (char*)calloc(1,sizeof(char));		// Memory allocation for saving keys
	if (pKname == NULL)	                        // Cheking if allocation wasn't successful 
	{   
		printf("Memory allocation error!");
		return NULL;                 
	}
	
	do
	{	
		pressedKey=getch();
		
	
		switch(pressedKey)
		{
			case 'a'...'g' :	changeChordsOnNeck(guitarNeck, pressedKey, buf, pStructArr0);
								soundsSet(pressedKey); 
							  	pKname[i-2]=pressedKey;	break; // Is showing minor chords
			case 'A'...'G' : 	changeChordsOnNeck(guitarNeck, pressedKey, buf, pStructArr1); 
								soundsSet(pressedKey); 
							  	pKname[i-2]=pressedKey; break; // Is showing major chords
			case '1'...'6' : 	changeChordsOnNeck(guitarNeck, pressedKey, buf, pStructArr2); 
								soundsSet(pressedKey); 
							  	pKname[i-2]=pressedKey; break; // Is showing strings that play
			case 's' :  		pKname[i-2]=pressedKey; 
								system("cls");                  // Is cleaning the screen
						    	defaultScreen(guitarNeck); break;  // Is printing defoult screenbreak;
		}
		
		if (pKname[i-2] != 's')
		{
			pKname = (char*)realloc(pKname, i*sizeof(char));	// Memory reallocation for writing every new key
			if (pKname == NULL)                                 // Cheking if allocation wasn't successful 
			{      
			    printf("Memory reallocation error!");	    	
		        return NULL;                 
			}		
		}
		i++;
	}while(pKname[i-3] != 's');	   // Continue writing to memory while key isn't - 's'	
	i=0;	
	return pKname;
}
//------------------------------------------------------------------------------------------------------------------------------

/* Play sounds by reading keys from memory and shows chords */

char* playAndShowFromMem(char *pForKeysInMem, char guitarNeck[Row][Col], char key, char buf, chord* pStructArr0, chord* pStructArr1, chord* pStructArr2)
{
	int i;
	char keyName;
	for (i = 0; i<_msize(pForKeysInMem); i++) 
	{ 
		switch(*(pForKeysInMem+i))
		{
		
			case 'a'...'g'  :   changeChordsOnNeck(guitarNeck, *(pForKeysInMem+i), buf, pStructArr0); // Is changing guitar's chords on neck
								soundsSet(*(pForKeysInMem+i));                                        // Is playing apropriate sound
								break;
			case 'A'...'G'	:	changeChordsOnNeck(guitarNeck, *(pForKeysInMem+i), buf, pStructArr1);
								soundsSet(*(pForKeysInMem+i));
								break;
			case '1'...'6'	:	changeChordsOnNeck(guitarNeck, *(pForKeysInMem+i), buf, pStructArr2);
								soundsSet(*(pForKeysInMem+i)); 
								break;
			case 's'	    : 	system("cls"); // Is cleaning the screen
						    	defaultScreen(guitarNeck);  // Is printing defoult screen
		}
	}  	
}
//------------------------------------------------------------------------------------------------------------------------------

/* Writing keys from memory to the binary file*/
void* writeToFileBin(char *pForKeysInMem)
{
	FILE* chordsFile=fopen("Chords_combination.bin","wb");
	fwrite(pForKeysInMem, _msize(pForKeysInMem), 1, chordsFile); 
	fclose(chordsFile);
	free(pForKeysInMem);
}
//------------------------------------------------------------------------------------------------------------------------------

/* Reading chords from file */
char* readFile()
{					
	FILE* chordsFile=fopen("Chords_combination.bin","rb"); // Open binary file
	fseek(chordsFile, 0, SEEK_END);
	int fileSize = ftell(chordsFile)+1;
	char *pForKeysInMem = (char*)calloc(fileSize, 1);
	 
	if (pForKeysInMem == NULL)                            // Cheking if  memory eallocation wasn't successful
	{   
		printf("Memory allocation error!");
		return NULL;                 
	}
	rewind(chordsFile);
	fread(pForKeysInMem, fileSize, 1, chordsFile);

	return pForKeysInMem;
}
//END SECTION-------------------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------------------------------
/* NECK SECTION */
//------------------------------------------------------------------------------------------------------------------------------

/* Print guitar neck */
void printGuitarNeck(char guitarNeck[Row][Col])
{
	int i, j;
	
	for(i=0; i<Row; i++){
	    for(j=0; j<Col; j++) {
			printf("%c", guitarNeck[i][j]);
	    }
	    printf("\n");
	}
}
//------------------------------------------------------------------------------------------------------------------------------

/* Clear guitar neck */
void clearGuitarNeck(char guitarNeck[Row][Col])
{
	int i, j;
	
	for (i=0; i<Row; i++)
	{
		for (j=0; j<Col; j++)
		{
			if ( guitarNeck[i][j] == 'X' ||  guitarNeck[i][j] == '*' )
			{
				guitarNeck[i][j] = '|'; 
			}else if( guitarNeck[i][j] == '(' || guitarNeck[i][j] == ')' || guitarNeck[i][j] == '^')
			{
				guitarNeck[i][j] = ' ';
			}
		}
	}
	// Set defoult tref numbers
	guitarNeck[6][3]  = '1';			
	guitarNeck[14][3] = '2';
	guitarNeck[22][3] = '3';
}
//------------------------------------------------------------------------------------------------------------------------------

/* Change symbols in array */ 
void arrSymbolChanger(char guitarNeck[Row][Col], int chordIndex, chord* pStructArr)
{
	int i = 0;
	do
	{
		if (guitarNeck[pStructArr[chordIndex].position[i][0]][pStructArr[chordIndex].position[i][1]] == '|')
		{
			// Makr chord position on neck
			guitarNeck[pStructArr[chordIndex].position[i][0]][pStructArr[chordIndex].position[i][1]-1] = '(';
			guitarNeck[pStructArr[chordIndex].position[i][0]][pStructArr[chordIndex].position[i][1]]   = '*';
			guitarNeck[pStructArr[chordIndex].position[i][0]][pStructArr[chordIndex].position[i][1]+1] = ')';			
		}else guitarNeck[pStructArr[chordIndex].position[i][0]][pStructArr[chordIndex].position[i][1]] = '^';
		i++;
			// Change symbols while chord`s position =! 0
	}while(pStructArr[chordIndex].position[i][0] != 0);		
}
//------------------------------------------------------------------------------------------------------------------------------

/* Is cleaning the neck and changing chord's possitions */
void isCleanAndChangeChord(char guitarNeck[Row][Col], int chordIndex, chord* pStructArr)
{
	system("cls");                                          // Clean console
	printHeader(pStructArr,  chordIndex);                   // Print header
	clearGuitarNeck(guitarNeck);                            // Clean guitar neck
	arrSymbolChanger(guitarNeck, chordIndex, pStructArr);   // Strings that should play

}
//------------------------------------------------------------------------------------------------------------------------------

/* Change guitar's chords on neck */
void changeChordsOnNeck(char guitarNeck[Row][Col], char key, char buf, chord* pStructArr)
{
	int i=0;
	
	if (key != buf) 
	
	switch(key)
	{			
		// Strings
		case '1' :  isCleanAndChangeChord(guitarNeck, sE1, pStructArr); // Is cleaning the neck and changing chord's possitions                            
				    printGuitarNeck(guitarNeck);                        // Ptrint chord position on neck
					printDefaultFooter();                               // Is printing footer
					break;
		case '2' :  isCleanAndChangeChord(guitarNeck, sB2, pStructArr);                             
				    printGuitarNeck(guitarNeck);                      
					printDefaultFooter();                             
					break;
		case '3' :  isCleanAndChangeChord(guitarNeck, sG3, pStructArr);                             
				    printGuitarNeck(guitarNeck);                      
					printDefaultFooter();                             
					break;
		case '4' :  isCleanAndChangeChord(guitarNeck, sD4, pStructArr);                             
				    printGuitarNeck(guitarNeck);                      
					printDefaultFooter();                             
					break;
		case '5' :  isCleanAndChangeChord(guitarNeck, sA5, pStructArr);                             
				    printGuitarNeck(guitarNeck);                      
					printDefaultFooter();                             
					break;
		case '6' :  isCleanAndChangeChord(guitarNeck, sE6, pStructArr);                            
				    printGuitarNeck(guitarNeck);                      
					printDefaultFooter();                             
					break;
		// For major chords
		case 'C' :  isCleanAndChangeChord(guitarNeck, C, pStructArr);                             
				    printGuitarNeck(guitarNeck);                      
					guitarNeck[6][7]  = 'X';  // String that should't play 
					printDefaultFooter();     // Print footer
					break;
		case 'D' :  isCleanAndChangeChord(guitarNeck, D, pStructArr);                         			
					guitarNeck[6][7] = 'X';  // String that should't play
					printGuitarNeck(guitarNeck);                      
					printDefaultFooter();                             
					break;
		case 'E' :  isCleanAndChangeChord(guitarNeck, E, pStructArr);                    
					printGuitarNeck(guitarNeck);                      
					printDefaultFooter();                     
					break;
		case 'F' :  isCleanAndChangeChord(guitarNeck, F, pStructArr);                    
					printGuitarNeck(guitarNeck);                      
					printDefaultFooter();                     
					break;
		case 'G' :  isCleanAndChangeChord(guitarNeck, G, pStructArr);                    
					printGuitarNeck(guitarNeck);                      
					printDefaultFooter();                     
					break;
		case 'A' :  isCleanAndChangeChord(guitarNeck, A, pStructArr);                    
					printGuitarNeck(guitarNeck);                      
					printDefaultFooter();                     
					break;
		case 'B' :  isCleanAndChangeChord(guitarNeck, B, pStructArr); 
					guitarNeck[6][7]  = 'X';  // String that should't play                   
					guitarNeck[6][3]  = '2';  // Change tref numbers
					guitarNeck[14][3] = '3'; 
					guitarNeck[22][3] = '4'; 
					printGuitarNeck(guitarNeck);                      
					printDefaultFooter();                     
					break;
		
		// For minor chords
		case 'c' :  isCleanAndChangeChord(guitarNeck, Cm, pStructArr); 
					guitarNeck[6][7]  = 'X';  // String that should't play                   
					guitarNeck[6][3]  = '3';  // Change tref numbers
					guitarNeck[14][3] = '4'; 
					guitarNeck[22][3] = '5'; 
					printGuitarNeck(guitarNeck);                      
					printDefaultFooter();                     
					break;
		case 'd' :  isCleanAndChangeChord(guitarNeck, Dm, pStructArr); 
					guitarNeck[6][7]   = 'X';  // String that should't play                   
					guitarNeck[6][11]  = 'X';  // Change tref numbers
					printGuitarNeck(guitarNeck);                      
					printDefaultFooter();                     
					break;
		case 'e' :  isCleanAndChangeChord(guitarNeck, Em, pStructArr); 
					guitarNeck[6][7]   = 'X';  // String that should't play                   
					
					printGuitarNeck(guitarNeck);                      
					printDefaultFooter();                     
					break;
		case 'f' :  isCleanAndChangeChord(guitarNeck, Fm, pStructArr); 
					printGuitarNeck(guitarNeck);                      
					printDefaultFooter();                     
					break;
		case 'g' : 	isCleanAndChangeChord(guitarNeck, Gm, pStructArr); 
					printGuitarNeck(guitarNeck);                      
					printDefaultFooter();                     
					break;
		case 'a' :  isCleanAndChangeChord(guitarNeck, Am, pStructArr); 
					guitarNeck[14][7]   = 'X';  // String that should't play               
					printGuitarNeck(guitarNeck);           
					printDefaultFooter();                    
					break;
		case 'b' :  isCleanAndChangeChord(guitarNeck, Bm, pStructArr); 
					printGuitarNeck(guitarNeck);                      
					printDefaultFooter();                     
					break;
	}
}


//END SECTION-------------------------------------------------------------------------------------------------------------------
	

//------------------------------------------------------------------------------------------------------------------------------
/* MENU SECTION */
//------------------------------------------------------------------------------------------------------------------------------	

/* Is printed default header */
void printDefaultHeader()
{
	printf("+----------------------------------------------------+\n");
	printf("|        START PRESSING KEYS TO HEAR THE SOUND       |\n");
	printf("+----------------------------------------------------+\n");
}
//------------------------------------------------------------------------------------------------------------------------------

/* This header is printed to start playing recorded set of keys */
void printHeaderForPlay()
{
	printf("+----------------------------------------------------+\n");
	printf("|        PRESS KEY 'p' TO PLAY YOUR RECORD           |\n");
	printf("+----------------------------------------------------+\n");
}
//------------------------------------------------------------------------------------------------------------------------------

/* This header is printed befor recording  */
void printHeaderForRecord()
{
	printf("+----------------------------------------------------+\n");
	printf("|                     RECORD                         |\n");
	printf("+----------------------------------------------------+\n");
}
//------------------------------------------------------------------------------------------------------------------------------

/* This header is printed while pressing chords */
void printHeader(chord* pSomeStuct, int chordIndex)
{
	printf("+----------------------------------------------------+\n");
	printf("|  %2s  |  IS PLAYING                                 |\n", pSomeStuct[chordIndex].title );
	printf("+----------------------------------------------------+\n");
}	
//------------------------------------------------------------------------------------------------------------------------------

/* This body is printed by default */
void printDefaultBody(char guitarNeck[Row][Col])
{
	printGuitarNeck(guitarNeck);
}							 
//------------------------------------------------------------------------------------------------------------------------------
/* Is printed menu inside footer */
void printDefaultFooter()
{
	printf("+----------------------------------------------------+\n");
	printf("| CONTROL KEYS                                       |\n");
	printf("+----------------------------------------------------+\n");
	printf(" STRINGS: 1-E  2-H  3-G  4-D  5-A  6-E                \n");
	printf("                                                      \n"); 
	printf(" KEYS:    C  D  E  F  G  A  H  c  d  e  f  g  a  h    \n");
	printf("          |  |  |  |  |  |  |  |  |  |  |  |  |  |    \n");
	printf(" CHORDS:  C  D  E  F  G  A  H  Cm Dm Em Fm Gm Am Hm   \n");
	printf("+----------------------------------------------------+\n");
	printf("| RECORD AND PLAY                                    |\n");
	printf("+----------------------------------------------------+\n");
	printf("| r - Record           p - Play            s - Stop  |\n");
	printf("+----------------------------------------------------+\n");
}
//------------------------------------------------------------------------------------------------------------------------------

/* Is printed default screen */

void defaultScreen(char guitarNeck[Row][Col])
{
	clearGuitarNeck(guitarNeck);  // Is clear guitar neck
	printDefaultHeader();         // Is printed default header
	printDefaultBody(guitarNeck); // This body is printed by default	
	printDefaultFooter();         // Is printed menu inside footer
	
} 
//END SECTION-------------------------------------------------------------------------------------------------------------------

