/* Comisaru Gabriel-Cornel - 311CB */
#include "Functii.h"

int main() {
    TDir* root = malloc(sizeof(struct _Dir));
    root->name = calloc(1, strlen("root") + 1);
    root->name = "root";
    root->head_directories = NULL; 
    root->head_files = NULL; 
    root->parent = NULL;
    root->st = root->dr = NULL;
    char* comanda = calloc(100, sizeof(char));
    TDir* CurrDir = calloc(10, sizeof(TDir));
    CurrDir = root  ;
    while(scanf("%s", comanda) == 1) {
        if (strcmp(comanda, "touch") == 0) {
            char* nume_fisier = calloc(50, sizeof(char));
            scanf("%s", nume_fisier);
            touch(CurrDir, nume_fisier);
        }
        if (strcmp(comanda, "mkdir") == 0) {
            char* nume_dir = calloc(50, sizeof(char));
            scanf("%s", nume_dir);
            mkdir(CurrDir, nume_dir);
        }
        if (strcmp(comanda, "ls") == 0) {
            ls(CurrDir);
        }
        if (strcmp(comanda, "rm") == 0) {
            char* nume_fisier = calloc(50, sizeof(char));
            scanf("%s", nume_fisier);
            rm(CurrDir, nume_fisier);
        }
        if (strcmp(comanda, "rmdir") == 0) {
            char* nume_dir = calloc(50, sizeof(char));
            scanf("%s", nume_dir);
            rmdir(CurrDir, nume_dir);
        }
        if (strcmp(comanda, "cd") == 0) {
            char* nume_dir = calloc(50, sizeof(char));
            scanf("%s", nume_dir);
            cd(&CurrDir, nume_dir);
        }
        if (strcmp(comanda, "pwd") == 0)
            pwd(CurrDir);
        if (strcmp(comanda, "find") == 0)
            find(root);
    }
}