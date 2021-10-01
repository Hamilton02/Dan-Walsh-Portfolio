# ifndef SET_H
# define SET_H

typedef struct set SET;
typedef struct list LIST;
typedef struct stud STUD;

SET *createDataSet(int maxStud);

void destroyDataSet(SET *sp);

void **searchAge(SET *sp, int age);

void insertStud(SET *sp, int age, int iD);

void *deleteStud(SET *sp, int age, int iD);

int maxAgeGap(SET *sp);

# endif 
