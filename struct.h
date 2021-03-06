//
// Created by thgir on 27/02/2021.
//

#ifndef NF05_PROJET_REMAKE_STRUCT_H
#define NF05_PROJET_REMAKE_STRUCT_H

#include <time.h>
#include <stdbool.h>
#include "standard_functions.h"


typedef enum
{
    SHORT,LONG,VERY_LONG
} circuit_e;


typedef struct {
    char* name;
    char* surname;
    struct tm* arrivalHour;
    struct tm* availabilityHour;
    struct tm** examHour;
    unsigned int * examDuration;
    circuit_e circuit;
    unsigned short examNumber;
} patient_t;

//patient_t patient_default = {NULL, NULL, NULL, NULL, NULL};

typedef struct patientQueue patientQueue;
struct patientQueue {
    patient_t * this;
    struct patientQueue * next;
};

typedef struct
{
    struct tm* endOfExam;
}examRoom;

#endif //NF05_PROJET_REMAKE_STRUCT_H
