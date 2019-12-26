#ifndef _SETTINGS_H
#define _SETTINGS_H
#include <windows.h>
#include "../cJSON/cJSON.h"

typedef struct
{
    WORD consoleDefaultAttr;
    WORD tagAttr;
    WORD contentAttrA,contentAttrB;
    int autoSave;
}Settings;

void SetConsoleDefaultColor(WORD attr);

int DecodeSettings_JSON(cJSON *settingObj, Settings *output);
int EncodeSettings_JSON(Settings settings, cJSON *output);
int GetSettings_JSON(const char *fileName, Settings *settings);
int SaveSettings_JSON(char *fileName, Settings settings);

void PrintSettings(Settings settings);
void ApplySettings(Settings settings);
WORD AskForColorAttr();
#endif // _SETTINGS_H
