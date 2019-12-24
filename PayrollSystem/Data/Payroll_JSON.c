#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../cJSON/cJSON.h"
#include "../Toolkit/FlexibleArray.h"
#include "../Toolkit/Debugger.h"
#include "Payroll_JSON.h"
#include "../Toolkit/MsgBox.h"

//数据的文件名
char dataFileName[] = "data.json";

int CheckDataFileValid(const char * fileName)
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
    //获取文件长度
    unsigned int size;
    fseek(fileTemp, 0, SEEK_END);
    size = ftell(fileTemp);
    //初始化缓冲器
    FArray_Initialize(buffer, 1, size);
    //重置文件读取位置
    fseek(fileTemp, filePos, SEEK_SET);
    //读取对应长度
    fread(buffer->array, 1, size, fileTemp);
    return 0;
}

void CreateNewDataFile(char *fileName)
{
    FILE *fData;
    cJSON *root;
    //创建新文件并写入基本JSON框架
    fData = fopen(dataFileName, "w");
    root = cJSON_CreateObject();
    //cJSON_AddNumberToObject(root, "Count", 0);
    cJSON_AddItemToObject(root,"Payrolls", cJSON_CreateArray());
    char *buf = cJSON_Print(root);
    fwrite(buf, 1, strlen(buf), fData);
    //清理现场
    free(buf);
    fclose(fData);
    cJSON_Delete(root);
}

//保存数据
int SaveData(FArray payrollList)
{
    FILE *fData = fopen(dataFileName,"w");
    cJSON *root;
    cJSON *payrollarray_JSON;
    char *output;
    if(fData == NULL)
    {
        PrintError("错误!无法写入文件.");
        return 0;
    }
    root = cJSON_CreateObject();
    payrollarray_JSON = cJSON_CreateArray();
    //遍历每个工资表
    int i;
    Payroll *list = (Payroll *)payrollList.array;
    for (i = 0; i < payrollList.arraySize;i++)
    {
        cJSON *currentPayroll = cJSON_CreateObject();
        cJSON_AddStringToObject(currentPayroll,"name",(char *)list[i].name.array);
        cJSON_AddStringToObject(currentPayroll, "ID", (char *)list[i].ID.array);
        cJSON_AddNumberToObject(currentPayroll, "baseWage",list[i].baseWage);
        cJSON_AddNumberToObject(currentPayroll, "dutyWage", list[i].dutyWage);
        cJSON_AddNumberToObject(currentPayroll, "bonus", list[i].bonus);
        cJSON_AddNumberToObject(currentPayroll, "healthInsurance", list[i].healthInsurance);
        cJSON_AddNumberToObject(currentPayroll, "endowmentInsurance", list[i].endowmentInsurance);
        cJSON_AddNumberToObject(currentPayroll, "unemploymentInsurance", list[i].unemploymentInsurance);
        cJSON_AddNumberToObject(currentPayroll, "providentFund", list[i].providentFund);
        cJSON_AddNumberToObject(currentPayroll, "salary", list[i].salary);
        cJSON_AddNumberToObject(currentPayroll, "incomeTax", list[i].incomeTax);
        cJSON_AddNumberToObject(currentPayroll, "takeHomePay", list[i].takeHomePay);
        cJSON_AddItemToArray(payrollarray_JSON, currentPayroll);
    }
    cJSON_AddItemToObject(root, "Payrolls", payrollarray_JSON);
    output = cJSON_Print(root);
    fwrite(output, 1, strlen(output), fData);
    fclose(fData);
    cJSON_Delete(root);
    free(output);
    return 1;
}

//读取数据
int LoadData(FArray *out)
{
    FILE *fData = NULL;
    FArray prJSON;
    cJSON *root;
    //cJSON *count;
    int count = 0;
    cJSON *payrollArray;
    if(!(fData = fopen(dataFileName,"r")))
    {
        //文件不存在或不可读
        PrintLog("工资表文件不存在!创建一个新的文件保存数据.");
        CreateNewDataFile(dataFileName);
    }
    if(!CheckDataFileValid(dataFileName))
    {
        //文件不是有效的JSON
        PrintLog("文件不是有效的JSON文件!是否新建?");
        if(ShowMsgBox(""))
        {
            //新建
            CreateNewDataFile(dataFileName);
        }
    }

    //尝试读取json对象
    GetWholeFile(&prJSON, dataFileName);
    root = cJSON_Parse((char *)prJSON.array);
    payrollArray = cJSON_GetObjectItem(root,"Payrolls");
    count = cJSON_GetArraySize(payrollArray);
    //读取Payrolls
    FArray_Initialize(out, sizeof(Payroll), 0);
    int i;
    for (i = 0; i < count;i++)
    {
        Payroll toAdd;
        cJSON *currentPayroll = cJSON_GetArrayItem(payrollArray,i);
        cJSON *name, *ID, *baseWage, *dutyWage, *bonus, *healthInsurance, *endowmentInsurance, *unemploymentInsurance, *providentFund, *salary, *incomeTax, *takeHomePay;
        name = cJSON_GetObjectItem(currentPayroll, "name");
        ID = cJSON_GetObjectItem(currentPayroll, "ID");
        baseWage = cJSON_GetObjectItem(currentPayroll, "baseWage");
        dutyWage = cJSON_GetObjectItem(currentPayroll, "dutyWage");
        bonus = cJSON_GetObjectItem(currentPayroll, "bonus");
        healthInsurance = cJSON_GetObjectItem(currentPayroll, "healthInsurance");
        endowmentInsurance = cJSON_GetObjectItem(currentPayroll, "endowmentInsurance");
        unemploymentInsurance = cJSON_GetObjectItem(currentPayroll, "unemploymentInsurance");
        providentFund = cJSON_GetObjectItem(currentPayroll, "providentFund");
        salary = cJSON_GetObjectItem(currentPayroll, "salary");
        incomeTax = cJSON_GetObjectItem(currentPayroll, "incomeTax");
        takeHomePay = cJSON_GetObjectItem(currentPayroll, "takeHomePay");
        if(
            name==NULL ||
            ID == NULL ||
            baseWage == NULL ||
            dutyWage == NULL ||
            bonus == NULL ||
            healthInsurance == NULL ||
            endowmentInsurance == NULL ||
            unemploymentInsurance == NULL ||
            providentFund == NULL ||
            salary == NULL ||
            incomeTax == NULL ||
            takeHomePay == NULL
        )
        {
            //存在NULL
            PrintError("文件不完整!请检查数据文件完整性.");
            return 0;
        }
        Payroll_Initialize(&toAdd,name->string,
            ID->string,
            baseWage->valuedouble,
            dutyWage->valuedouble,
            bonus->valuedouble,
            healthInsurance->valuedouble,
            endowmentInsurance->valuedouble,
            unemploymentInsurance->valuedouble,
            providentFund->valuedouble,
            salary->valuedouble,
            incomeTax->valuedouble,
            takeHomePay->valuedouble);
        Payroll_FillContent(&toAdd);
        FArray_Add(out, &toAdd);
    }
    cJSON_Delete(root);
    return 1;
}
