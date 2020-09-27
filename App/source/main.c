#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <switch.h>

void spaceswitch() 
{
    Result rc;
    WebCommonConfig config;

    rc = webPageCreate(&config, "index.html");

    if (R_SUCCEEDED(rc)) {
        if (R_SUCCEEDED(rc)) { 
            rc = webConfigShow(&config, NULL);
        } else {
            printf("The hell ? couldn't launch the app");
        }
    }
    else {
        printf("the config object has a problem .");
    }
}

int main(int argc, char* argv[])
{
    consoleInit(NULL);

    printf("switchdesk\n\nPress PLUS to close.\n");

    bool isApp = true;
    if (!(appletGetAppletType() == AppletType_Application)) {
        printf(CONSOLE_RED "Not running in APPLICATION mode. couldn't launch switchdesk\n");
        printf("Launch this program from APPLICATION mode instead.\n");
        printf(CONSOLE_YELLOW "If you are using Atmosphere (you should),\nTry to use homebrew NSP or launch it from an app.\n\n");
        isApp = false;
    } else {
        printf(CONSOLE_GREEN "Press A to start spaceswitch (needed if you manually exited).\n\n");
    }
    printf(CONSOLE_RESET "SPACE SWITCH BY ALEXDIEU / BASED ON SPACEDESK BY DATRONICSOFT");

    if (isApp)
        spaceswitch();
    while (appletMainLoop())
    {
        hidScanInput();

        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if (kDown & KEY_PLUS)
            break;

        if (kDown & KEY_A)
            if (isApp)
                spaceswitch();
        consoleUpdate(NULL);
    }
    consoleExit(NULL);
    return 0;
}