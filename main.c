#include <stdbool.h>;
#include <stdio.h>;



typedef enum{
    PSH,
    ADD,
    POP,
    SET,
    DVD,
    MLT,
    SUB,
    MOV,
    MIR,
    MOR,
    HLT
} InstructionSet;

typedef enum{
    A, B, C, D, E, F, QT_REGISTRES // Le dernier element vaut forcément le nombre de vrai registres
} Registres;


int pi = 0;
int ps = -1; // on l'init à -1 pour eviter d'accéder à un nombre aléatoire
int stack[256];
int registres[QT_REGISTRES];
bool running = true;


const int program[]={
    PSH, 2,
    PSH, 4,
    DVD,
    MIR, A,
    MOR, A,
    POP,
    HLT
};


int fetch(){
    return program[pi];
}

void eval(int instr){
    switch(instr){
        case HLT:{ // Fun Fact quand on ouvre des brackets dans un switch ca donne au cas un scope, dcp on peut déclarer des variables à l'intérieur
            running = false;
            printf("end\n");
            break;
        }
        case PSH:{
            ps++;
            int pushed = program[++pi];
            stack[ps] = pushed; // Le ++pi. Lorsque l'on détécte PSH on sait que la prochaine étape à faire c'est lire la valeure à ++pi  ex: PSH 5  psh --> pi  5 --> ++pi
            printf("pushed %d\n",pushed);
            break;
        }
        case POP:{
            // on enregistre la valeure avant de décrémenter
            int val_pop = stack[ps--];
            printf("popped %d\n",val_pop);
            break;
        }
        case ADD:{
            int a = stack[ps--];

            int b = stack[ps--];

            int resultat = a+b;
            ps++;
            stack[ps]=resultat;
            printf("added %d and %d \n",a,b);
            break;
        }
        case DVD:{
            int a = stack[ps--];

            int b = stack[ps--];

            int resultat = a/b;
            ps++;
            stack[ps]=resultat;
            printf("divided %d by %d \n",a,b);
            break;
        }
        case MLT:{
            int a = stack[ps--];

            int b = stack[ps--];

            int resultat = a*b;
            ps++;
            stack[ps]=resultat;
            printf("multiplied %d by %d \n",a,b);
            break;
        }
        case SUB:{
            int a = stack[ps--];

            int b = stack[ps--];

            int resultat = a-b;
            ps++;
            stack[ps]=resultat;
            printf("substracted %d from %d \n",b,a);
            break;
        }
        case MOV: {
            registres[program[pi + 2]] = registres[program[pi + 1]];
            pi = pi + 2;
            break;
        }
        case SET: {
            registres[program[pi + 1]] = registres[pi + 2];
            pi = pi + 2;
            break;
        }
        case MIR: {
            registres[program[pi + 1]] = stack[ps--]; // ps-- afin de mettre la valeur dans le registre et oublier la valuer sur ps
            pi = pi + 1;
            break;
        }
        case MOR: {
            stack[++ps] = registres[program[pi + 1]] ; 
            ps++;
            break;
        }
    }
}




int main(){
    while(running){
        eval(fetch());
        pi++;
    }
}

