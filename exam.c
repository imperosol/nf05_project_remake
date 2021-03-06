//
// Created by thgir on 02/03/2021.
//

#include "exam.h"


void do_branch_exam(circuit_e branch, patientQueue *pQueue, const short examNbr, const short nbrOfRooms) {
    patientQueue *circuit_queue = extract_queue(branch, NULL, pQueue);
    if (branch == LONG) {
        circuit_queue = extract_queue(VERY_LONG, circuit_queue, pQueue);
    }
    do_all_exam(circuit_queue, examNbr, nbrOfRooms); // Exam for short circuit
    free_queue(&circuit_queue);
}

int get_next_free_room(examRoom *roomArray, const short arraySize) {
    int i = 0;
    for (int j = 1; j < arraySize; ++j) {
        if (difftime(mktime(roomArray[i].endOfExam), mktime(roomArray[j].endOfExam)) < 0){
            i = j;
        }
    }
    return i;
}

int do_all_exam(patientQueue *pQueue, const short examNbr, const short nbrOfRooms) {
    int i;
    examRoom *examRoom = safe_malloc(nbrOfRooms * sizeof(examRoom));
    for (i = 0; i < nbrOfRooms; ++i) {
        examRoom[i].endOfExam = safe_malloc(sizeof(struct tm));
        *examRoom[i].endOfExam = *pQueue->this->availabilityHour;
    }
    while (pQueue != NULL) {
        i = get_next_free_room(examRoom, nbrOfRooms);
        do_one_exam(pQueue->this, &examRoom[i], examNbr);
        pQueue = pQueue->next;
    }
    for (i = 0; i < nbrOfRooms; ++i) {
        free(examRoom[i].endOfExam);
    }
    free(examRoom);
    return 0;
}

int do_one_exam(patient_t * patient, examRoom* room, const short examNbr)
{
//    TODO free patient->examHour[examNbr]
    patient->examHour[examNbr] = safe_malloc(sizeof(struct tm));
    time_t difference = difftime(mktime(patient->availabilityHour), mktime(room->endOfExam));
    if (difference < 0) {
        /* If the patient arrives before the room is free and has to wait */
        *patient->examHour[examNbr] = *room->endOfExam;
        *patient->availabilityHour = *patient->examHour[examNbr];
    } else {
        /* If the room is free when the patient arrives */
        *patient->examHour[examNbr] = *patient->availabilityHour;
    }
    update_tm(patient->availabilityHour, 0, 0, 0, 0,
              patient->examDuration[examNbr], 0);
    mktime(patient->availabilityHour);
    *room->endOfExam = *patient->availabilityHour;
    return 0;
}