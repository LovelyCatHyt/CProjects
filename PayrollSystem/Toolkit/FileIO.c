#include "FileIO.h"
#include "FlexibleArray.h"
#include "Debugger.h"
#include "../cJSON/cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int CheckJSONFileValid(const char * fileName)
{
    int valid = 1;
    FArray buf;
    GetWholeFile(&buf, fileName);
    cJSON *testJSON = cJSON_Parse((char *)buf.array);
    valid = testJSON != NULL;
    cJSON_Delete(testJSON);
    return valid;
}

int GetWholeFile(FArray *buffer,const char *fileName)
{
    FILE *fileTemp = fopen(fileName, "r");
    if(!fileTemp)
    {
        PrintError("File not exist!");
        FArray_Initialize(buffer, 1, 0);
        return 0;
    }
    unsigned int filePos = ftell(fileTemp);
    //��ȡ�ļ�����
    unsigned int size;
    fseek(fileTemp, 0, SEEK_END);
    size = ftell(fileTemp);
    //��ʼ��������
    FArray_Initialize(buffer, 1, size);
    //�����ļ���ȡλ��
    fseek(fileTemp, filePos, SEEK_SET);
    //��ȡ��Ӧ����
    fread(buffer->array, 1, size, fileTemp);
    return 0;
}

//�����µ�JSON�ļ�
int CreateEmptyJSON(const char *fileName)
{
    cJSON *empty = cJSON_CreateObject();
    char *printed = cJSON_Print(empty);
    FILE *pFile = fopen(fileName,"wb");
    fwrite(printed,1,strlen(printed),pFile);
    fclose(pFile);
    free(printed);
    cJSON_Delete(empty);
    return 1;
}
