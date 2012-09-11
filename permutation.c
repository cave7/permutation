#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/***recursive permutation module***/
int permutation_recursive(const char *s){
    /*recursive way to do permutation*/
    int len=strlen(s);
    char* result=(char *)malloc((len+1)*sizeof(char));
    if(!result)
        return -1;
    int* mask=(int *)malloc(len*sizeof(int));
    if(!mask)
        return -1;
    memset(mask,0,len*sizeof(int));
    memset(result,0,(len+1)*sizeof(char));
    int pos=0;
    permutation_r(s,len,pos,result,mask);
    free(result);
    free(mask);
    printf("\n");
    return 0;
}
int permutation_r(const char* s,int len,int pos,char* result,int* mask){
    if(pos==len){
        printf("%s\t",result);
        return 0;
    }
    int i=0;
    while(i<len){
        if(mask[i]!=1){
            result[pos]=s[i];
            mask[i]=1;
            permutation_r(s,len,pos+1,result,mask);
            mask[i]=0;
        }
        i++;
    }
    return 0;
}

/***non recursive permutation module***/
int permutation_non_recursive(const char* s){
    int len=strlen(s);
    char* tmp=(char *)malloc((len+1)*sizeof(char));
    if(!tmp)
        return -1;
    int* address=(int *)malloc(len*sizeof(int));
    if(!address)
        return -1;
    strcpy(tmp,s);
    permutation_init(s,address,len);
    while (permutation_next(s,address,tmp,len)!=-1) {
        continue;
    }
    free(tmp);
    free(address);
    printf("\n");
    
}
int permutation_init(char* s,int* address,int len){
    int i;
    for (i=0; i<len; i++) {
        address[i]=i;
    }
    printf("%s\t",s);
    return 0;
}

int permutation_next(char *s,int *address,char* one,int len){
    int swp,i,j,k;
    for (i=len-1; i>0; i--) {
        if (address[i]>address[i-1]) {
            k=len-1;
            while(address[i-1]>address[k]){
                k--;
            }
            
            swp=address[i-1];
            address[i-1]=address[k];
            address[k]=swp;
            
            int start=i;
            int end=len-1;
            while (start<end) {
                swp=address[start];
                address[start]=address[end];
                address[end]=swp;
                start++;
                end--;
            }
            for (j=i-1; j<len; j++) {
                one[j]=s[address[j]];
            }
            one[len]='\0';
            printf("%s\t",one);
            return 0;
        }
        
    }
    return -1;
}
/***main function***/
int main(){
    char s[50];
    puts("Please input a string(input \'q\' to exit): ");
    scanf("%s",s);
    while(strcmp(s,"q")!=0){
        printf("recursive:\n");
        time_t t=clock();
        permutation_recursive(s);
        double diff=(double)(clock()-t)/CLOCKS_PER_SEC;
        printf("time consumed: %f\n",diff);
        printf("non recursive:\n");
        t=clock();
        permutation_non_recursive(s);
        diff=(double)(clock()-t)/CLOCKS_PER_SEC;
        printf("time consumed: %f\n",diff);
        puts("Please input a string(input \'q\' to exit): ");
        scanf("%s",s);
    }
    puts("Goodbye!");
    return 0;
}

