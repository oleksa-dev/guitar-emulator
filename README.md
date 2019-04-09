# Guitar Emulator


## 1. System requirements

The program will be stable working on OS Windows 98 or higher with minimum system requirements:
  - PC with processor speed 100 MHz and higher;
  - Monitor with VGA support;
  - 16 Mb RAM and higher;
  - Keyboard, mouse.



## 2. About


The main idea of the program is: 
  - to play strings and chords’ sounds of the acoustic guitar while pushing control keys on the keyboard; 
  - the feature is to record the sequence of pressed keys with additional sounds and playback responses the recorded keys sequence. 

The audio files' output is realized by utilizing Windows API (application programming interfaces) PlaySound function. It means that, when the user pushes control key, for example: 'A'; it requests the PlaySound function that forces "A.wav" file from the project's root and performs the A major chord.



## 3. User guide

The main data of the program contains in the 2D array - guitarNeck, that outputs the visual representation of a guitar neck; the arrays of structures majorChords and minorChords that contain information about chords names and positions on the guitar neck and variable soundsSet that contains set of strings and chord sounds that executed PlaySound function.
Program management occurs by pressing the control keys:
  - keys from '1' to '6' response for sounding of six strings: 
    - '1' - 1-st string (note E);
    - '2' - 2-nd string (note H);
    - '3' - 3-rd string (note G);
    - '4' - 4-th string (note D);
    - '5' - 5-th string (note A);
    - '6' - 6-th string (note E).
  - use uppercase to response for major chords and lowercase for minor chords: 
    - 'C' - C major; 
    - 'D' - D major;
    - 'E' - E major;
    - 'F' - F major;
    - 'G' - G major;
    - 'A' - A major;
    - 'H' - H major; 
    - 'c' - Cm minor; 
    - 'd' - Dm minor;
    - 'e' - Em minor;
    - 'f' - Fm minor;
    - 'g' - Gm minor;
    - 'a' - Am minor;
    - 'h' - Hm minor.
 - recording, playback and stopping occur due to keystrokes:
    - 'r' - record;
    - 'p' - play;
    - 's' - stop;
    - 'q' - quit the program.



###### 4. Programmer instruction

The program was realized in IDE "Dev C++". The main advantages are:
  - The low system requirements;
  - The low weight of IDE (~50 Mb of installing the program and ~360 Mb disk space requirements);
  - The high performance of the work, stability;
  - The simplicity and clearness at work;

The project consists of additional functions which can be grouped together conditionally into three sections:  
**SOUND, NECK** and **MENU SECTIONS**.
  - **SOUND SECTION** - functions that implement work with sound:
    - **soundsSet** : set of sounds that are used in program;
    - **chooseSoundToPlay** : function chooses sounds for playing while pressing keys;
    - **writeKeys** : writes keys into the memory during the pressing;
    - **playAndShowFromMem** : plays sound by reading keys from the memory displays chords;
    - **writeToFileBin** : writes keys from memory to the binary file;
    - **readFile** : reads chords from the file.
  - **NECK SECTION**  -  functions that implement mapping and changing chords on a guitar neck:
    - **printGuitarNeck** : prints guitarNeck array into console;
    - **clearGuitarNeck** : clears guitarNeck array from changes;
    - **arrSymbolChanger** : changes symbols in the guitarNeck array;
    - **changeChordsOnNeck** :  guitar chords changing function;
    - **isCleanAndChangeChord** : cleans the neck and changes chord's positions;
  - **MENU SECTIONS** -  functions that implement the displaying of chords names and the main menu of the program:
    - **printHeader** : this header is printed while pressing chords;
    - **printDefaultHeader** : this header is printed by default;
    - **printDefaultBody** : this body is printed by default;
    - **printBody** : this body is printed in screen function;                      
    - **printDefaultFooter** : footer section contains menu;    
    - **defaultScreen** : contains default header, default body, and default footer;
    - **outputScreen** : contains the header, body, and footer that are changes during program execution;
Calling out, performing and libraries switching of the functions above takes place in the main function.

## 5. About author

This project was realized by Oleksii Shevchuk, student of ITA, group A18.

## License
MIT
