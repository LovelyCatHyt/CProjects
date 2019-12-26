#include "Settings.h"
#include <string.h>
#include <stdio.h>
#include "../Toolkit/FlexibleArray.h"
#include "../Toolkit/FileIO.h"
#include "../Toolkit/Debugger.h"
#include "../Toolkit/MsgBox.h"
#include "../Toolkit/MenuMgr.h"

Settings defaultSettings = {0x0f, 0x09, 0x8f, 0x0f, 1};

//将Arrribute转化为相应的color命令,并设置相关模块的默认背景色
void SetConsoleDefaultColor(WORD attr)
{
    //用一个数组保存数据
    char decToHex[] = "0123456789abcdef";
    //前景色取1~4位数据
    char foreColor = decToHex[attr & 0xf];
    //背景色取5~8位数据并移位到最低
    char bgColor = decToHex[(attr & 0xf0)>>4];
    char colorCmd[9] = "color ";
    //补全命令
    colorCmd[6] = bgColor;
    colorCmd[7] = foreColor;
    colorCmd[8] = 0;
    //应用命令
    system(colorCmd);
    DBG_SetDefaultBg(attr);
    MsgBox_SetDefaultBg(attr);
    MenuMgr_SetDefaultBg(attr);
}

//从JSON对象解析设置
int DecodeSettings_JSON(cJSON *settingObj, Settings *output)
{
    cJSON *consoleDefaultAttr,*tagAttr,*contentAttrA,*contentAttrB,*autoSave;
    consoleDefaultAttr = cJSON_GetObjectItem(settingObj,"consoleDefaultAttr");
    tagAttr = cJSON_GetObjectItem(settingObj,"tagAttr");
    contentAttrA = cJSON_GetObjectItem(settingObj,"contentAttrA");
    contentAttrB = cJSON_GetObjectItem(settingObj,"contentAttrB");
    autoSave = cJSON_GetObjectItem(settingObj,"autoSave");
    if(consoleDefaultAttr == NULL ||
       tagAttr == NULL ||
       contentAttrA == NULL ||
       contentAttrB == NULL ||
       autoSave == NULL)
    {
        return 0;
    }
    output->consoleDefaultAttr = consoleDefaultAttr->valueint;
    output->tagAttr = tagAttr->valueint;
    output->contentAttrA = contentAttrA->valueint;
    output->contentAttrB = contentAttrB->valueint;
    output->autoSave = autoSave->valueint;
    return 1;
}

//将Settings编码为JSON
int EncodeSettings_JSON(Settings settings, cJSON *output)
{
    if(output==NULL) return 0;
    cJSON_AddNumberToObject(output,"consoleDefaultAttr",settings.consoleDefaultAttr);
    cJSON_AddNumberToObject(output,"tagAttr",settings.tagAttr);
    cJSON_AddNumberToObject(output,"contentAttrA",settings.contentAttrA);
    cJSON_AddNumberToObject(output,"contentAttrB",settings.contentAttrB);
    cJSON_AddNumberToObject(output,"autoSave",settings.autoSave);
    return 1;
}

//从指定JSON文件获取设置
int GetSettings_JSON(const char *fileName, Settings *settings)
{
    cJSON *root;
    FArray buf;
    if(!CheckJSONFileValid(fileName))
    {
        //不是有效的JSON文件
        PrintError("设置文件是无效JSON文件!将自动生成设置文件.");
        SaveSettings_JSON(fileName, defaultSettings);
    }
    GetWholeFile(&buf,fileName);
    root = cJSON_Parse((char *)buf.array);
    DecodeSettings_JSON(root,settings);
    FArray_Free(&buf);
    cJSON_Delete(root);
    return 1;
}

int SaveSettings_JSON(char *fileName, Settings settings)
{
    FILE *fSettings_JSON;
    cJSON *root;
    char *output;
    fSettings_JSON = fopen(fileName,"wb");
    if(!fSettings_JSON)
    {
        return 0;
    }
    root = cJSON_CreateObject();
    EncodeSettings_JSON(settings,root);
    output = cJSON_Print(root);
    fwrite(output,1,strlen(output),fSettings_JSON);
    fclose(fSettings_JSON);
    cJSON_Delete(root);
    free(output);
    return 1;
}

//打印设置
void PrintSettings(Settings settings)
{
    printf("控制台默认颜色:%d\n工资表表头:%d\n工资表颜色A:%d\n工资表颜色B:%d\n自动保存数据:%d",
           settings.consoleDefaultAttr,
           settings.tagAttr,
           settings.contentAttrA,
           settings.contentAttrB,
           settings.autoSave
           );
}







