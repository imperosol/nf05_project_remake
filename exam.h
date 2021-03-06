//
// Created by thgir on 02/03/2021.
//

#ifndef NF05_PROJET_REMAKE_EXAM_H
#define NF05_PROJET_REMAKE_EXAM_H

#include "struct.h"
#include "standard_functions.h"
#include "patient_list_modification.h"

void do_branch_exam(circuit_e branch, patientQueue *pQueue, const short examNbr, const short nbrOfRooms);
int do_all_exam(patientQueue* pQueue, const short examNbr, const short nbrOfRooms);
int do_one_exam(patient_t * patient, examRoom * room, const short examNbr);


#endif //NF05_PROJET_REMAKE_EXAM_H
