#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
//structs
typedef struct Node {
    char chr;
    struct Node* next;
} Node;

typedef struct {
    Node* top; 
} Stack;

//vars
FILE* input;
Stack* stack;
char atom;
int flag_reduce = 0;
int offset_string_terminal=0;

//functions
void state_cero();
void state_one();
void state_two();
void state_three();
void state_four();
void state_five();
void state_six();
void state_seven();
void state_eight();
void state_nine();
void reduce(int);
int check_handdle(char*);
int look_for(char*);
char getAtom();
void initialize(Stack*);
int isEmpty(Stack*);
void push(Stack*, char);
char pop(Stack*);
char peek(Stack*);
void clean_stack(Stack*);
void draw_stack_chr(Node*);
void draw_stack(char);
void print_string(long );
void print_readed_string();
void print_results();
int main(int argc, char* argv[]){
    // Validation to read input file
    if(argc > 1){
        if((input=fopen(argv[1],"r"))==NULL){
            printf("parser:\033[1;31m error\033[1;m no such file or directory: \033[1;36m\'%s\'\033[1;0m\n",argv[1]);
            exit(EXIT_FAILURE);
        }else{
                stack = (Stack*)malloc(sizeof(Stack));
                if (stack == NULL) {
                    printf("Error: no se pudo asignar memoria para la pila\n");
                    exit(EXIT_FAILURE);
                }
                initialize(stack);

                atom = getAtom();
                printf("\033[2J");
                print_results();
                state_cero();

                fclose(input);
        }
    }else{
        printf("parser:\033[1;31m error\033[1;m no imput file\n");
        exit(EXIT_FAILURE);
    }
}
/*
     ___  ____   __   ____  ____  ___ 
    / __)(_  _) /__\ (_  _)( ___)/ __)
    \__ \  )(  /(__)\  )(   )__) \__ \
    (___/ (__)(__)(__)(__) (____)(___/
*/
void state_cero(){
    while (flag_reduce == 0){
        
    
        if(atom == 'a'){
            state_four();
        }else if(atom == '('){
            atom = getAtom();
            print_results();
            state_three();
        }else if(atom == 'E'){
            state_two();
        }else if(atom == 'L'){
            // SPECIAL STATE
            atom = getAtom();
            print_results();
            state_one();
        }else{
            printf("\033[1;31mError:\033[1;0m state0: unespected: \033[1;32m \'a\' \'(\' \'E\' \'L\'\033[1;0m\n");
            exit(EXIT_FAILURE);
        }
    }
    flag_reduce --;
}
void state_one(){
    

    if(atom == ','){
        atom = getAtom();
        print_results();
        state_six();
    }else if(atom == EOF){
        atom = getAtom();
        print_results();
        state_five();
    }else{
        printf("\033[1;31mError:\033[1;0m state1: unespected: \033[1;32m \',\' \'EOF\' \033[1;0m\n");
        exit(EXIT_FAILURE);
    }
    flag_reduce--;
}
void state_two(){
    

    reduce(4);
    flag_reduce--;
}

void state_three(){
    while(flag_reduce == 0){
        if(atom == 'a'){
            state_four();
        }else if(atom == '('){
            atom = getAtom();
            print_results();
            state_three();
        }else if(atom == 'E'){
            state_two();
        }else if(atom== 'L'){
            atom = getAtom();
            print_results();
            state_seven();
        }else{
            printf("\033[1;31mError:\033[1;0m state3: unespected: \033[1;32m \'a\' \'(\' \'E\' \'L\'\033[1;0m\n");
            exit(EXIT_FAILURE);
        }
    }
    flag_reduce--;
}
void state_four(){
    

    reduce(2);
    flag_reduce--;
}
void state_five(){
    

    if(feof(input)){
        printf("ACEPTA\n");
    }
}
void state_six(){
    while(flag_reduce == 0){
        
    
        if(atom == 'a'){
            state_four();
        }else if(atom == '('){
            atom = getAtom();
            print_results();
            state_three();
        }else if(atom == 'E'){
            state_eight();
        }else{
            printf("\033[1;31mError\033[1;0m state6: unespected: \033[1;32m \'a\' \'(\' \'E\' \033[1;0m\n");
            exit(EXIT_FAILURE);
        }
    }
    flag_reduce--;
}
void state_seven(){
    

    if(atom == ')'){
        state_nine();
    }else if(atom == ','){
        atom = getAtom();
        print_results();
        state_six();
    }else{
        printf("\033[1;31mError\033[1;0m state7: unespected: \033[1;32m \')\' \',\' \033[1;0m\n");
        exit(EXIT_FAILURE);
    }
    flag_reduce--;
}
void state_eight(){
    

    reduce(3);
    flag_reduce--;
}
void state_nine(){
    

    reduce(1);
    flag_reduce--;
}
/*
     _   _    __    _  _  ____  ____  __    ____ 
    ( )_( )  /__\  ( \( )(  _ \(  _ \(  )  ( ___)
     ) _ (  /(__)\  )  (  )(_) ))(_) ))(__  )__) 
    (_) (_)(__)(__)(_)\_)(____/(____/(____)(____)
*/

void reduce(int reduce){
    char* handdles[]= {"(L)","a","L,E","E"};
    char no_terminal[]= {'E','E','L','L'};
    
    if(check_handdle(handdles[reduce-1])== 1){
        printf("\033[1;31mError\033[1;0m state9: \033[1;32m Reduce %d \033[1;0m\n",reduce);
    };

    atom = no_terminal[reduce-1];
    
    push(stack,atom);
    
    flag_reduce = strlen(handdles[reduce-1]);
}

int check_handdle(char* handdle){
    return (look_for((char*)handdle)==0)? 0:1;
}

int look_for(char* handdle){
    printf("\033[1;37mHANDDLE\033[1;0m-> %s\n",handdle);
    int leng_handdle = strlen(handdle);
    printf("\033[1;37mLENG\033[1;0m-> %d\n",leng_handdle);

    if(leng_handdle == 1){
        printf("look_for 1\n");
        if(*(handdle) != pop(stack)){
            printf(" Error: unespected atom: %c\n",*(handdle));
            return 1;
        }
    }else{
        int leng_handdle_memory = leng_handdle-1;
        for(int i = 0; i < leng_handdle; i++){
            printf("look_for >1\n");
            printf("HANDDLE -> %s\n",handdle);
            printf("--------------\n");
            char chr_stack = pop(stack);
            printf("STACK -> %c\n",chr_stack);
            
            if(*(handdle+(leng_handdle_memory-i)) != chr_stack){
                printf("!!!! %c\n",*(handdle+(leng_handdle_memory-i)));
                printf(" \033[1;31mError:\033[1;0m unespected atom: %c\n",*(handdle+(leng_handdle-i)));
                return 1;
            }
            printf("--------------\n");
        }
    }
    return 0;
}

/*
     ___  _____  __  __  ____  __    ____  __  __  ____  _  _  ____   __    ____  _  _ 
    / __)(  _  )(  \/  )(  _ \(  )  ( ___)(  \/  )( ___)( \( )(_  _) /__\  (  _ \( \/ )
   ( (__  )(_)(  )    (  )___/ )(__  )__)  )    (  )__)  )  (   )(  /(__)\  )   / \  / 
    \___)(_____)(_/\/\_)(__)  (____)(____)(_/\/\_)(____)(_)\_) (__)(__)(__)(_)\_) (__) 
*/
char getAtom(){
    print_string(ftell(input));
    if(getc(input) != EOF){
        fseek(input,-1,SEEK_CUR);
        atom = getc(input);
        push(stack,atom);
    }else{
        atom = EOF;
        push(stack,atom);
    }
    return atom;
}

/*
     ___  ____   __    ___  _  _ 
    / __)(_  _) /__\  / __)( )/ )
    \__ \  )(  /(__)\( (__  )  ( 
    (___/ (__)(__)(__)\___)(_)\_)

*/

void initialize(Stack* stack_ptr) {
    stack_ptr->top = NULL; // Pila vacía
}

int isEmpty(Stack* stack_ptr) {
    return (stack_ptr->top == NULL);
}

void push(Stack* stack_ptr, char chr_readed) {
    // Crear un nuevo nodo
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error: no se pudo asignar memoria\n");
        exit(EXIT_FAILURE);
    }

    newNode->chr = chr_readed;
    newNode->next = stack_ptr->top;

    stack_ptr->top = newNode;
}

char pop(Stack* stack_ptr) {
    if (isEmpty(stack_ptr)) {
        printf("Error: la pila está vacía\n");
        exit(EXIT_FAILURE);
    }

    char value = stack_ptr->top->chr;
    Node* temp = stack_ptr->top;
    stack_ptr->top = stack_ptr->top->next;
    free(temp);

    return value;
}
char peek(Stack* stack_ptr) {
    if (isEmpty(stack_ptr)) {
        printf("Error: la pila está vacía\n");
        exit(EXIT_FAILURE);
    }
    return stack_ptr->top->chr;
}

void clean_stack(Stack* stack_ptr) {
    while (!isEmpty(stack_ptr)) {
        pop(stack_ptr);
    }
}

void draw_stack(char op){
    printf(" - -  -\n");
    printf("|  %c  |\n",op);
}

void draw_stack_chr(Node* node) {
    if (node == NULL) {
        printf("La pila está vacía.\n");
        return;
    }

    while (node != NULL) {
        printf(" ******\n");
        printf("*  %c  *\n", node->chr);
        node = node->next;
    }
}
void print_string(long  offset_string){
    for(int i = 0;i < offset_string;i++){
        fseek(input,i,SEEK_SET);
        printf("%c",getc(input));
    }
    printf("\033[1;0m\n");
}

void print_readed_string(){
    fseek(input,-1,SEEK_SET);
    printf("%c",getc(input));
}

void print_results(){
    printf("\033[1;%ldH",ftell(input));
    print_readed_string();
    fflush(stdout);  // Limpia el buffer de salida
    usleep(500000); 
}