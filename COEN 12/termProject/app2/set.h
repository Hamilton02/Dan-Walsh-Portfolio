# ifndef SET_H
# define SET_H

typedef struct set SET;
typedef struct stud STUD;

SET *createSet(int maxStud);

void destroyDataSet(SET *sp);

void *searchID(SET *sp, int iD);

void insert(SET *sp, int age, int iD);

void *deleteStud(SET *sp,  int iD);

# endif 
