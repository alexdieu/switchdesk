#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#include <switch.h>

int main(int argc, char *argv[])
{
    Result rc = 0;
    consoleInit(NULL);

    printf(CONSOLE_GREEN "Space Switch\n" CONSOLE_WHITE);
    printf("By Alexdieu\n");
    printf("\nGLP3 LICENSE.");

    consoleUpdate(NULL);

    while (appletMainLoop())
    {
        hidScanInput();

        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        WebCommonConfig config;
        WebCommonReply reply;
        WebExitReason exitReason = 0;

        rc = webOfflineCreate(&config, WebDocumentKind_OfflineHtmlPage, 0, ".htdocs/spaceswitch/index.html");
        printf("webOfflineCreate(): 0x%x\n", rc);

        if (R_SUCCEEDED(rc))
        {
            rc = webConfigSetFooterFixedKind(&config, WebFooterFixedKind_Hidden);
            printf("webConfigSetFooterFixedKind(): 0x%x\n", rc);

            if (R_SUCCEEDED(rc))
            {
                rc = webConfigShow(&config, &reply);
                printf("webConfigShow(): 0x%x\n", rc);
                if(rc == 0x5d59){
                    printf(CONSOLE_RED "!!! There was an issue showing the browser window. Make sure you're running the game through an overridden title and not the album. Hold KEY_PLUS to exit.\n" CONSOLE_WHITE);
                }
            }

            if (R_SUCCEEDED(rc))
            {
                rc = webReplyGetExitReason(&reply, &exitReason);
                printf("webReplyGetExitReason(): 0x%x", rc);
                if (R_SUCCEEDED(rc))
                    printf(", 0x%x", exitReason);
                printf("\n");
                break;
            }
        }

        if(kDown & KEY_PLUS)
            break;
        consoleUpdate(NULL);
    }
    consoleExit(NULL);
    return 0;
}
