#include <stdio.h>
#define TEST_LEN 20

/*获取字符串长度*/
int strlen(char c[],int arrayLen)
{
    int i;
    for(i=0;i<arrayLen;i++)
    {
        if(c[i]=='\0')
        {
            return i;
        }
    }
}

/*小写字母数目*/
int LwCaseNum(char c[],int arrayLen)
{
    int i;
    int count = 0;
    for(i=0;i<arrayLen;i++)
    {
        if(c[i]>96 && c[i]<129)
        {

            count++;
        }
    }
    return count;
}

/*大写字母数目*/
int UpCaseNum(char c[],int arrayLen)
{

    int i;
    int count = 0;
    for(i=0;i<arrayLen;i++)
    {
        if(c[i]>64 && c[i]<97)
        {
            count++;
        }
    }
    return count;
}

/*字符串连接*/
void strcat(char c1[],int arrayLen1, char c2[],int arrayLen2)
{
    int i;
    int len1 = strlen(c1,arrayLen1), len2 = strlen(c2,arrayLen2);
    for(i = len1;i<len1+len2;i++)
    {
        c1[i]=c2[i-len1];
    }
}

/*比较字符串的大小*/
int strcmp(char c1[],int arrayLen1, char c2[],int arrayLen2)
{
    int i=0;
    /*int len1 = strlen(c1,arrayLen1), len2 = strlen(c2,arrayLen2);*/
    while(c1[i]==c2[i])
    {
        if(c1[i]==0)
        {
            return 0;
        }
        i++;
    }
    /*if(c1[i+1]==0) return 0;*/
    return c1[i]>c2[i]?1:-1;

}

int main()
{
    char c1[TEST_LEN] = "aabbcc";
    char c2[TEST_LEN] = "AABBCC";
    /*Print c1, c2*/
    printf("c1 = \"%s\", c2 = \"%s\"\n",c1,c2);
    /*Print the length of two strings.*/
    printf("strlen\(c1\) = %d, strlen\(c2\) = %d\n",strlen(c1,TEST_LEN),strlen(c2,TEST_LEN));
    /*Print the uppercase numbers of two strings.*/
    printf("The number of uppercase in c1 is %d, in c2 is %d.\n",UpCaseNum(c1,TEST_LEN),UpCaseNum(c2,TEST_LEN));
    /*Print the lowercase numbers of two strings.*/
    printf("The number of lowercase in c1 is %d, in c2 is %d.\n",LwCaseNum(c1,TEST_LEN),LwCaseNum(c2,TEST_LEN));
    /*Print the result of strcmp()*/
    printf("The result of strcmp\(\) is %d\n",strcmp(c1,TEST_LEN,c2,TEST_LEN));
    /*Print c1 after strcat.*/
    strcat(c1,TEST_LEN,c2,TEST_LEN);
    printf("After strcat\(\), c1 = %s\n",c1);
    return 0;
}
