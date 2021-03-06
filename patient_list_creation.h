//
// Created by thgir on 27/02/2021.
//

#ifndef NF05_PROJET_REMAKE_PATIENT_LIST_CREATION_H
#define NF05_PROJET_REMAKE_PATIENT_LIST_CREATION_H


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "struct.h"

patientQueue* create_patient_queue(short* nbrOfPatients);
patientQueue* queue_push(struct patientQueue* queue, patient_t* newPatient, patientQueue* queue_tail);
const circuit_e circuit_taken_by_patient();
int input_word(char ** word);
void input_patient_information(patient_t* patient, struct tm * beginningHour,
                               bool isDurationRandom, bool isArrivalHourRandom, bool isNameRandom);
const short generate_time_with_exponential_law(const short mean);
const short generate_duration_with_box_muller_method(const short mean, const short variance);
void get_random_name_from_file(const char* file_to_open, char** word);
bool get_random_generation_preference(const char* sentence);



#endif //NF05_PROJET_REMAKE_PATIENT_LIST_CREATION_H
