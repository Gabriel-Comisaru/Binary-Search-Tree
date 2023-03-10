/* Comisaru Gabriel-Cornel - 311CB */
#ifndef FUNCTII_H_INCLUDED
#define FUNCTII_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Dir {
    char* name;
    struct _Dir* parent;
    struct _File* head_files;
    struct _Dir* head_directories;
    struct _Dir* st;
    struct _Dir* dr;
} TDir;

typedef struct _File {
    char* name;
    struct _Dir* parent;
    struct _File* st;
    struct _File* dr;
} TFile;

TDir* createDir(TDir* parent, char* nume);
TFile* createFile(TDir* parent, char* nume);
int touch(TDir* parent, char* nume_fiser);
int mkdir(TDir* parent, char* nume_dir);
void ls(TDir* parent);
void printFiles(TFile* file);
void printDir(TDir* dir);
void rm(TDir* parent, char* nume_fisier);
void rmdir(TDir* parent, char* nume_dir);
void cd(TDir** parent, char* nume_dir);
void pwd(TDir* parent);
void find(TDir* root);
void findDir(TDir* aux, char* nume_dir, int* spy, TDir** save);
void findFile(TDir* aux, TFile* file, char* nume_file, int* spy, TDir** save);
int existaDir (TDir* dir, char* nume);
#endif