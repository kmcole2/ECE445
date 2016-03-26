//"3,2,5,N,2,5,N,2,5,N,2,5,N,**";
//"2,3,10,P,1,2,P,2,3,P,**";
//"1,2,10,P,2,10,P,**"
//"0,2,10,P,**"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

char** str_split(char* a_str, const char a_delim);
// struct ctrl_word decomp(char* token);
// void initialize(struct ctrl_word * ctrl);
void decomp(char *** token);
int arr_size;
char * ref_weight[10];
char * canister[10];
char * endchar = "*";
int main(){
    char sampl[] = "0,2,10,**";
    char** tokens;
    printf("ctrl=[%s]\n\n", sampl);
    tokens = str_split(sampl, ',');

    decomp(&tokens);
    
    int idx = 0;
    int j = 1;
    arr_size = (atoi(tokens[0])+1);

    while(j < 12){
        canister[idx] = tokens[j];
        ref_weight[idx] = tokens[j+1];

        if(strstr(tokens[j+2],endchar) != NULL)
            break;
        j += 2;
        idx+=2;
    }

printf("array size %d\n", arr_size);

int index;
printf("canister: [");
for( index = 0; index <arr_size; index++){
        printf( "%s,", canister[index] );
   }
        printf( "]\n" );
printf("ref_weight: [");
for( index = 0; index <arr_size; index++){
        printf( "%s,", ref_weight[index] );
   }
        printf( "]\n" );

    // if (tokens){
    //     int i;
    //     for (i = 0; *(tokens + i); i++)
    //     {
    //         printf("tokens=[%s]\n", *(tokens + i));
    //         // blak[i] = *(tokens + i);
    //         free(*(tokens + i));
    //     }
    //     printf("\n");
    //     free(tokens);
    // }

    return 0;
}

void decomp(char *** token){
    // arr_size = atoi(*token[2])*2;
    // printf("%d\n\n\n", arr_size);
    // int i = 1;
    // int idx = 0;
    // char * a = **(token+1);

    // while(i < 2){//){
    //     printf("canister idx: %d\n", i);
    //     printf("ref_weight idx: %d\n", i+1);
    //     printf("pause enable idx: %d\n", i+2);

    //     canister[0] = *token[1];
    //     // ref_weight[i] = token[i+1];

    //     // ref_weight[i] = token[i+2];
    //     // canister[i] =   token[i+2];

    //     // if(strstr(*token[i+3],endchar) != NULL)
    //     //     break;
    //     i += 3;
    //     idx++;
    // }
        printf("canister:%s\n",*token[0]);

// for(int j = 0; j < arr_size; j++){
//         printf("canister %d: %s",j,canister[j]);
//         printf("ref_weight %d: %s",j,ref_weight[j]);
//     }
    return;
}    

// void initialize(struct ctrl_word * ctrl){
//     // ctrl->arr_size = 0;
//     // ctrl->ref_weight = 0;
//     // strcpy(ctrl->ref_weight,"0");
//     // strcpy(ctrl->canister,"0");
//     // ctrl->canister = [0,0,0,0,0,0,0,0,0,0];
//     // ctrl =
//     return;
// }
// struct ctrl_word decomp(char* token){
//     // ctrl1.arr_size = token[0];
//     return ctrl1;
// }

char** str_split(char* a_str, const char a_delim){
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}