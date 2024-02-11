#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <tchar.h>
#include <ctime>
#include <cstdlib>

INT WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow) {
    srand(time(NULL));
    int rNum = 0, msg = 0, menu = 0, counter = 0;
    do {
        char num[35] = " ", att[35] = " ";
        do {
            rNum = rand() % 100 + 1;
            _itoa(rNum, num, 10);
            strcat(num, " is your number?");
            msg = MessageBoxA(0, num, TEXT("NumberGuesser"), MB_YESNO);
            counter++;
        } while (msg != IDYES);
        _itoa(counter, att, 10);
        strcat(att, " attempts. Wanna try again?");
        menu = MessageBox(0, att, TEXT("NumberGuesser"), MB_YESNO);
    } while (menu != IDNO);
}
