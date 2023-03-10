/* Comisaru Gabriel-Cornel - 311CB */
#include "Functii.h"

// functie de creeare director
TDir *createDir(TDir *parent, char *nume)
{
    TDir *dir = calloc(1, sizeof(TDir));
    dir->name = calloc(1, strlen(nume));
    dir->name = nume;
    dir->parent = parent;
    dir->head_directories = NULL;
    dir->head_files = NULL;
    dir->dr = dir->st = NULL;
    return dir;
}

//functie de creeare fisier
TFile *createFile(TDir *parent, char *nume)
{
    TFile *file = calloc(1, sizeof(TFile));
    file->name = calloc(1, strlen(nume));
    file->name = nume;
    file->parent = parent;
    file->dr = NULL;
    file->st = NULL;
    return file;
}

int touch(TDir *parent, char *nume_fiser)
{
    // salvez head-urile de fisier si director din arborii binari
    TFile *headf = (TFile *)parent->head_files;
    TDir *headdir = (TDir *)parent->head_directories;
    // verificam daca exista un director cu numele fisierului
    if (headdir != NULL && existaDir(headdir, nume_fiser) == 0)
            return 0;
    // cazul in care directorul nu are niciun fisier
    if (headf == NULL)
    {
        // verificam daca exista un director cu numele fisierului
        parent->head_files = createFile(parent, nume_fiser); // creeam fisierul
        return 0;
    }
    TFile *auxfile, *save;
    auxfile = headf;
    // verificam daca exista un fisierul deja exista
    while (auxfile)
    {
        save = auxfile;
        if (strcmp(nume_fiser, auxfile->name) == 0)
        {
            printf("File %s already exists!\n", nume_fiser);
            return 0;
        }
        if (strcmp(nume_fiser, auxfile->name) < 0)
            auxfile = auxfile->st;
        else
            auxfile = auxfile->dr;
    }
    // in caz contrar adaugam noul fisier in arborele de fisiere
    // in save, reprezentand fisierul de dinaintea celui pe 
    // care il vom adauga in ordine lexicografica
    // comparam save-ul cu numele de fisier pentru a
    // afla daca adaugam fisierul in stanga sau in dreapta
    // save-ului
    if (strcmp(nume_fiser, save->name) < 0)
        save->st = createFile(parent, nume_fiser);
    else if (strcmp(nume_fiser, save->name) > 0)
        save->dr = createFile(parent, nume_fiser);
    return 1;
}

//functie ce verifica daca directorul exista in arborele de directoare
int existaDir (TDir* dir, char* nume) {
    while (dir)
    {
        if (strcmp(nume, dir->name) == 0)
        {
            printf("Directory %s already exists!\n", nume);
            return 0;
        }
        if (strcmp(nume, dir->name) < 0)
            dir = dir->st;
        else
            dir = dir->dr;
    }
    return 1;
}

int mkdir(TDir *parent, char *nume_dir)
{
    TFile *headf = (TFile *)parent->head_files;
    TDir *headdir = (TDir *)parent->head_directories;
    while (headf)
        {
            //verificam daca exista un fisier cu numele directorului
            if (strcmp(nume_dir, headf->name) == 0)
            {
                printf("File %s already exists!\n", nume_dir);
                return 0;
            }
            if (strcmp(nume_dir, headf->name) < 0)
                headf = headf->st;
            else
                headf = headf->dr;
        }
    // verificam daca head-ul de directoare este gol, caz in care
    // vom adauga directorul
    if (headdir == NULL)
    {
        parent->head_directories = createDir(parent, nume_dir);
        return 0;
    }
    TDir *auxdir, *save;
    auxdir = headdir;
    // verificam daca exista deja directorul
    while (auxdir)
    {
        save = auxdir;
        if (strcmp(nume_dir, auxdir->name) == 0)
        {
            printf("Directory %s already exists!\n", nume_dir);
            return 0;
        }
        if (strcmp(nume_dir, auxdir->name) < 0)
            auxdir = auxdir->st;
        else
            auxdir = auxdir->dr;
    }
    // comparam save-ul cu numele de director pentru a
    // afla daca adaugam director in stanga sau in dreapta
    // save-ului
    if (strcmp(nume_dir, save->name) < 0)
        save->st = createDir(parent, nume_dir);
    else if (strcmp(nume_dir, save->name) > 0)
        save->dr = createDir(parent, nume_dir);
    return 1;
}

void ls(TDir *parent)
{
    TFile *headf = (TFile *)parent->head_files;
    TDir *headdir = (TDir *)parent->head_directories;
    printDir(headdir); // afisam arborele de directoare
    printFiles(headf); // afisam arborele de fisiere
    printf("\n");
}

void printFiles(TFile *file)
{
    if (file == NULL)
        return;
    // se apeleaza recursiv functie de printFiles pt fiecare st si dr
    printFiles(file->st);
    printf("%s ", file->name);
    printFiles(file->dr);
}

void printDir(TDir *dir)
{
    if (dir == NULL)
        return;
        // se apeleaza recursiv functia de printDir pt fiecare st si dr
    printDir(dir->st);
    printf("%s ", dir->name);
    printDir(dir->dr);
}

void rm(TDir *parent, char *nume_fisier)
{
    TFile *file = (TFile *)parent->head_files;
    TFile *prevfile = (TFile *)parent->head_files;
    int ok = 0;
    while (file)
    {
        // caz in care fisierul este gasit
        if (strcmp(file->name, nume_fisier) == 0)
        {
            ok = 1; // verific daca fisierul exista in arbore
            break;
        }
        prevfile = file; // salvez fisierul anterior fisierului pe care-l stergem
        if (strcmp(nume_fisier, file->name) < 0)
            file = file->st;
        else
            file = file->dr;
    }
    // caz in care fisierul nu a fost gasit
    if (ok == 0)
        printf("File %s doesn't exist!\n", nume_fisier);
    else
    {
        // cazul in care fisierul pe care dorim sa-l stergem este cel din head_file
        if (strcmp(prevfile->name, file->name) == 0)
        {
            // salvam arborele din nodul drept al head-ului
            TFile *aux = parent->head_files->dr;
            fflush(stdout);
            // verificam daca nodul drept este NULL, daca da atribuim head-ului urm fisier din st
            if (parent->head_files->dr == NULL)
            {
                parent->head_files = parent->head_files->st;
            }
            else if (parent->head_files->st != NULL)
            {
                // salvam fisierul din dreapta urmatorului fisier al lui head_file
                TFile *naux = parent->head_files->st->dr;
                TFile *anotheraux;
                // inlocuim nodul head_files cu nodul stang
                parent->head_files = parent->head_files->st;
                // atribuim noului head nod-ul din dreapta cu cel precedent din dreapta head-ului
                parent->head_files->dr = aux;
                anotheraux = parent->head_files->dr;
                // gasim cel mai mic element pentru a adauga in stanga acestuia fisierul anterior salvat in naux
                while (anotheraux->st)
                    anotheraux = anotheraux->st;
                anotheraux->st = naux;
            }
            else if (parent->head_files->st == NULL)
            {
                parent->head_files = parent->head_files->dr;
            }
        }
        // verific ca fisierul sa nu fie ultimul din arbore
        else if (prevfile->dr != NULL || prevfile->st != NULL)
        {
            // daca fisierul caruia ii dam rm este mai mare lexicografic decat fisierul anterior
            if (strcmp(file->name, prevfile->name) > 0)
            {
                TFile *aux;
                if (file->dr == NULL)
                    prevfile->dr = file->st;
                else if (file->st == NULL)
                    prevfile->dr = file->dr;
                else
                {
                    prevfile->dr = file->dr;
                    aux = file->dr->st;
                    while (aux->st)
                        aux = aux->st;
                    aux->st = file->st;
                }
            }
            // daca fisierul caruia ii dam rm este mai mic lexicografic decat fisierul anterior
            else if (strcmp(file->name, prevfile->name) < 0)
            {
                TFile *aux;
                if (file->dr == NULL)
                    prevfile->st = file->st;
                else if (file->st == NULL)
                    prevfile->st = file->dr;
                else
                {
                    prevfile->st = file->dr;
                    aux = file->dr->st;
                    while (aux->st)
                        aux = aux->st;
                    aux->st = file->st;
                }
            }
        }
        free(file->name);
        free(file);
    }
}

void rmdir(TDir *parent, char *nume_dir)
{
    TDir *dir = (TDir *)parent->head_directories;
    TDir *prevdir = (TDir *)parent->head_directories;
    int ok = 0;
    while (dir)
    {
        if (strcmp(dir->name, nume_dir) == 0)
        {
            ok = 1; // verific daca fisierul exista in arbore
            break;
        }
        prevdir = dir; // salvez fisierul anterior fisierului pe care-l stergem
        if (strcmp(nume_dir, dir->name) < 0)
            dir = dir->st;
        else
            dir = dir->dr;
    }
    if (ok == 0)
        printf("Directory %s doesn't exist!\n", nume_dir);
    else
    {
        // cazul in care fisierul pe care dorim sa-l stergem este cel din head_file
        if (strcmp(prevdir->name, dir->name) == 0)
        {
            // salvam arborele din nodul drept al head-ului
            TDir *aux = parent->head_directories->dr;
            fflush(stdout);
            // verificam daca nodul drept este NULL, daca da atribuim head-ului urm fisier din st
            if (parent->head_directories->dr == NULL)
            {
                parent->head_directories = parent->head_directories->st;
            }
            else if (parent->head_directories->st == NULL)
            {
                parent->head_directories = parent->head_directories->dr;
            }
            else
            {
                // salvam fisierul din dreapta urmatorului fisier al lui head_file
                TDir *naux = parent->head_directories->st->dr;
                TDir *anotheraux;
                // inlocuim nodul head_files cu nodul stang
                parent->head_directories = parent->head_directories->st;
                // atribuim noului head nod-ul din dreapta cu cel precedent din dreapta head-ului
                parent->head_directories->dr = aux;
                anotheraux = parent->head_directories->st;
                // gasim cel mai mic element pentru a adauga in stanga acestuia fisierul anterior salvat in naux
                while (anotheraux->st)
                    anotheraux = anotheraux->st;
                anotheraux->st = naux;
            }
        }
        // verific ca fisierul sa nu fie ultimul din arbore
        else if (prevdir->dr != NULL || prevdir->st != NULL)
        {
            // daca fisierul caruia ii dam rm este mai mare lexicografic decat fisierul anterior
            if (strcmp(dir->name, prevdir->name) > 0)
            {
                TDir *aux;
                if (dir->dr == NULL && dir->st == NULL)
                {
                    dir = dir;
                    prevdir->dr = NULL;
                }
                else if (dir->dr == NULL)
                {
                    prevdir->dr = dir->st;
                }
                else if (dir->st == NULL)
                {
                    prevdir->dr = dir->dr;
                }
                else
                {
                    prevdir->dr = dir->dr;
                    aux = dir->dr->st;
                    while (aux->st)
                    {
                        aux = aux->st;
                    }
                    aux->st = dir->st;
                }
                // daca fisierul caruia ii dam rm este mai mic lexicografic decat fisierul anterior
            }
            // un mare if in care nu mai tin minte exact ce am facut doar stiu ca am luat mai multe cazuri
            // pentru a evita seg fault-ul pe care il primeam cand nod-urile erau NULL
            else if (strcmp(dir->name, prevdir->name) < 0)
            {
                TDir *aux;
                if (dir->dr == NULL && dir->st == NULL)
                {
                    dir = dir;
                    prevdir->st = NULL;
                }
                else if (dir->dr == NULL)
                {
                    prevdir->st = dir->st;
                }
                else if (dir->st == NULL)
                {
                    prevdir->st = dir->dr;
                }
                else
                {
                    prevdir->st = dir->dr;
                    if (dir->dr->st != NULL)
                    {
                        aux = dir->dr->st;
                    }
                    else
                    {
                        aux = dir->dr;
                    }
                    if (aux != NULL)
                    {
                        while (aux->st)
                            aux = aux->st;
                        aux->st = dir->st;
                    }
                    else
                    {
                        aux = dir->st;
                    }
                }
            }
        }
        else if (prevdir->dr == NULL || prevdir->st == NULL)
        {
            prevdir = dir;
        }
        free(dir->name);
        free(dir);
    }
}

void cd(TDir **parent, char *nume_dir)
{
    TDir *dir = (*parent)->head_directories;
    TDir *save;
    int ok = 0;
    int ok2 = 0;
    // verific daca comanda este cd .. pentru a trece
    // in directorul parinte al directorului curent
    if (strcmp(nume_dir, "..") == 0)
    {
        *parent = (*parent)->parent;
        ok2 = 1;
    }
    else
        while (dir)
        {
            save = dir; // salvez fisierul anterior fisierului pe care-l stergem
            if (strcmp(dir->name, nume_dir) == 0)
            {
                ok = 1; // verific daca fisierul exista in arbore
                break;
            }
            if (strcmp(nume_dir, dir->name) < 0)
                dir = dir->st;
            else
                dir = dir->dr;
        }
    if (ok == 0 && ok2 == 0)
        printf("Directory not found!\n");
    else if (ok2 == 0)
    {
        *parent = save;
    }
}

void pwd(TDir *parent)
{
    int i = 0;
    char *array = calloc(1, sizeof(char));
    int j = 0, k = 0;
    // strcat(array, "/");
    for (i = 0; parent != NULL; i++)
    {
        char *array2 = calloc(100, sizeof(char));
        array2 = parent->name;
        j = 0;
        k = 0;
        char *save = calloc(100, sizeof(char));
        // salvez literele numelui in ordine inversa
        // pentru a putea afisa toata calea
        for (j = strlen(array2) - 1; j >= 0; j--)
        {
            save[k] = array2[j];
            k++;
        }
        // concatenez fiecare nume de parinte in string-ul array
        strcat(array, save);
        // adaug "/" ce va aparea cand afisam calea folosind pwd
        strcat(array, "/");
        parent = parent->parent;
    }
    // printf("SIZE:%d\n", strlen(array));
    for (i = strlen(array) - 1; i >= 0; i--)
    {
        printf("%c", array[i]);
    }
    printf("\n");
}

void find(TDir *root)
{
    char *tip = calloc(2, sizeof(char));
    scanf("%s", tip);
    // verific daca cautam fisier
    if (strcmp(tip, "-f") == 0)
    {
        TDir *aux, *save;
        TFile *naux;
        char *nume_file = calloc(100, sizeof(char));
        scanf("%s", nume_file); // citesc fisierul pe care doresc sa l gasesc
        int spy = 0;
        aux = root;
        while (aux)
        {
            naux = aux->head_files; // atribuim arborele de fisiere
            spy = 0; // variabila in care salvez 1 daca fisierul a fost gasit
            findFile(aux, naux, nume_file, &spy, &save); // apelam functie de gasire a fisierului in directorul curent
            if (spy == 1) // verific daca fisierul a fost gasit
            {
                printf("File %s found!\n", nume_file);
                pwd(save); // afisez calea catre directorul parinte al fisierului
                break;
            }
            aux = aux->head_directories; // intram intr-un arbore de directoare nou
        }
        if (spy == 0)
        {
            printf("File %s not found!\n", nume_file);
        }
    }
    // verific daca cautam un director
    else if (strcmp(tip, "-d") == 0)
    {
        TDir *aux, *save;
        char *nume_dir = calloc(100, sizeof(char));
        scanf("%s", nume_dir); // citesc directorul pe care doresc sa-l gasesc
        int spy = 0; // variabila in care salvez 1 daca directorul a fost gasit
        aux = root->head_directories;
        while (aux)
        {
            spy = 0;
            findDir(aux, nume_dir, &spy, &save); // apelam functia de gasire a directorului din directorul curent
            if (spy == 1) // verific daca directorul a fost gasit
            {
                printf("Directory %s found!\n", nume_dir);
                pwd(save); // afisez calea catre director
                break;
            }
            aux = aux->head_directories;
        }
        if (spy == 0)
            printf("Directory %s not found!\n", nume_dir);
    }
}

void findDir(TDir *aux, char *nume_dir, int *spy, TDir **save)
{
    // verificam daca arborele de directoare este NULL si in caz contrar
    // apelam din nou functia de findDir dar cu arborele de directoare
    // din head-ul directorului cu care intru pentru a cauta succesiv
    // in fiecare arbore de directoare
    if (aux->head_directories != NULL)
        findDir(aux->head_directories, nume_dir, spy, save);
    if (strcmp(aux->name, nume_dir) == 0) // verific daca am gasit directorul
    {
        *spy = 1;
        *save = aux;
    }
    if (aux->st != NULL) // daca ramura stanga nu este nula apelam recursiv functia
    {
        findDir(aux->st, nume_dir, spy, save);
    }
    if (aux->dr != NULL) // daca ramura dreapta nu este nula apelam recursiv functia
    {
        findDir(aux->dr, nume_dir, spy, save);
    }
}

void findFile(TDir *aux, TFile *file, char *nume_file, int *spy, TDir **save)
{
    // printf("[%s]:[%s]\n", aux->name, file->name);
    //  if (aux->head_directories != NULL)
    //      findFile(aux->head_directories, file, nume_file, spy, save);
    if (file != NULL) // verificam daca fisierul este null
    {
        if (*spy != 1)
        {
            if (strcmp(file->name, nume_file) == 0) // caz in care fisierul este gasit
            {
                *spy = 1;
                *save = aux;
            }
        }
        if (file->st != NULL) // apelam functia cu ramura stanga si dreapta
            findFile(aux, file->st, nume_file, spy, save);
        if (file->dr != NULL)
            findFile(aux, file->dr, nume_file, spy, save);
        if (aux->st != NULL) // apelam functia si cu urmatoarele arborele de directoare
        {
            file = aux->st->head_files;
            findFile(aux->st, file, nume_file, spy, save);
        }
        if (aux->dr != NULL)
        {
            file = aux->dr->head_files;
            findFile(aux->dr, file, nume_file, spy, save);
        }
        if (aux->head_directories != NULL) {
            //file = aux->head_directories->head_files;
            findFile(aux->head_directories, file, nume_file, spy, save);
        }
    }
}