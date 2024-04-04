#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *to_lower(char *input)
{

    if (input == NULL)
    {
        return NULL;
    }
    size_t len = strlen(input);
    char *output = static_cast<char *>(malloc((len + 1) * sizeof(char))); // +1 for the null terminator
    if (output == NULL)
    {
        return NULL; // malloc failed
    }

    for (size_t i = 0; i < len; ++i)
    {
        output[i] = tolower((unsigned char)input[i]); // Cast to unsigned char to avoid signedness issues
    }
    output[len] = '\0'; // Add null terminator
    return output;
}

struct lession
{
    int english;
    int mash;
};

struct info
{
    char *name;
    int age;
    struct lession lession;
};

bool equal(char *n1, char *n2)
{
    size_t len = strlen(n1);
    size_t i = 0;
    while (i < len)
    {
        if (n1[i] != n2[i])
            return false;
        i++;
    }
    return true;
}

int num1 = 20;
int *num = &num1;

int getNum()
{
    return *num;
}

void setNum(int n)
{
    num = &n;
}

int main()
{
    char *a = "hello";
    char *b = to_lower(a);
    printf("%s <-> %s, %d %d\n", a, b, equal(a, b), equal(a, "dafda")); // 这里将输出 "hello world"

    struct lession l;
    l.english = 20;
    l.mash = 22;
    struct info i;
    i.name = "Ben";
    i.age = 20;
    i.lession = l;
    printf("lession: english: %d mash: %d\n", l.english, l.mash);
    printf("info: name:%s age:%d english: %d mash: %d\n", i.name, i.age, i.lession.english, i.lession.mash);

    printf("num -> %d %d %d\n", *num, num1, getNum());
    setNum(4);
    printf("num -> %d %d %d\n", *num, num1, getNum());

    return 0;
}