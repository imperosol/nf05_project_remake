//
// Created by thgir on 03/03/2021.
//

#ifndef NF05_PROJET_REMAKE_PATIENT_LIST_MODIFICATION_H
#define NF05_PROJET_REMAKE_PATIENT_LIST_MODIFICATION_H

#include "struct.h"
#include "patient_list_creation.h"

patientQueue* extract_queue(circuit_e argument, patientQueue* dest, patientQueue* source);

void free_queue(patientQueue **queue);

patient_t *copy_queue_in_array(patientQueue *pQueue, const int size);


#endif //NF05_PROJET_REMAKE_PATIENT_LIST_MODIFICATION_H
