#include<stdio.h>
#include<string.h>

int main(){
    FILE *fp = fopen("test.txt", "r");
    char li[100];
    char lines[1000];
    // while(fscanf(fp, "%s", li) != EOF){    
    while(!feof(fp)){
        fgets(li, 100, fp);
        printf("Got line: %s", li);
        strcat(lines, li);
    }
    printf("%s", lines);
}