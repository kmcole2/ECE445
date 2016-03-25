#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
char** str_split(char* a_str, const char a_delim);
// struct ctrl_word decomp(char* token);

struct ctrl_word{
    int arr_size;           //ingredients to print out 
    char canister[10];          //canister
    char ref_weight[10];        //reference weight
};
void initialize(struct ctrl_word * ctrl);
void decomp(struct ctrl_word * ctrl, char *** token);

int main()
{
    struct ctrl_word ctrl1;
    char ctrl[] = "2,3,10,P,12,P,2,3,P,**";
    char** tokens;
    printf("ctrl=[%s]\n\n", ctrl);
    tokens = str_split(ctrl, ',');
    initialize(&ctrl1);

    // print out ctrl word, should be initialized
    printf("arr_size: %d \n", ctrl1.arr_size);
    printf("arr_size: %s \n", ctrl1.canister);
    printf("arr_size: %s \n", ctrl1.ref_weight);

    //set values
    // decomp(&ctrl1, &tokens);
    ctrl1.arr_size = atoi(*(tokens));
    
    // ctr1.canister[0] = *(tokens + 1);
    // char arr2[10];
    // arr2[0] = *(tokens + 2);


    // printf("arr_size: %d \n", arr1[0]);
    // printf("arr_size: %d \n", ctrl1.arr_size);
    // for(int i = 0; i < ctrl1.arr_size; i ++){
    //     printf("arr_size: %s \n", ctrl1.canister[i]);
    //     printf("arr_size: %s \n", ctrl1.ref_weight[i]);
    // }    

if (tokens)
{
    int i;
    for (i = 0; *(tokens + i); i++)
    {
        printf("month=[%s]\n", *(tokens + i));
        free(*(tokens + i));
    }
    printf("\n");
    free(tokens);
}

    return 0;
}

void decomp(struct ctrl_word * ctrl, char *** token){
    // ctrl->arr_size = atoi(*token[0]);
    // *(ctrl->canister)[0] = '1';//*token[1];
    // ctrl->ref_weight[0] = "3";//*token[2];
    // ctrl->canister = atoi(*token[1]);
    // ctrl->canister = atoi(*token[1]);
    return;
}    

void initialize(struct ctrl_word * ctrl){
    ctrl->arr_size = 0;
    // ctrl->ref_weight = 0;
    strcpy(ctrl->ref_weight,"0");
    strcpy(ctrl->canister,"0");
    // ctrl->canister = [0,0,0,0,0,0,0,0,0,0];
    // ctrl =
    return;
}
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