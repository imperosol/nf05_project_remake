//
// Created by thgir on 03/03/2021.
//

#include "patient_list_modification.h"

patientQueue *extract_queue(circuit_e argument, patientQueue *dest, patientQueue *source) {
    patientQueue *new = dest;
    patientQueue *queue_tail = NULL;
    for (; source != NULL; source = source->next) {
        if (source->this->circuit == argument) {
            if (queue_tail != NULL) {
                queue_tail = queue_tail->next;
            } else {
                queue_tail = new;
            }
            new = queue_push(new, source->this, queue_tail);
        }
    }
    return new;
}

/*void free_patient(patient_t* patient) {
    for (int i = 0; i < 3 + (patient->circuit == VERY_LONG); ++i) {
        free(patient->examHour[i]);
    }
    free(patient->availabilityHour);
    free(patient->arrivalHour);
    free(patient->examDuration);
}*/

void free_queue(patientQueue **queue){
    patientQueue *current = *queue;
    patientQueue *temp = NULL;
    while (current != NULL) {
        temp = current;
        current = (current)->next;
        free(temp);
    }
    *queue = NULL;
}

patient_t **copy_queue_in_array(patientQueue *pQueue, const int size)
{
    patient_t **array = NULL;
    array = safe_malloc(size * sizeof(patient_t*));
    for (int i = 0; pQueue != NULL; ++i, pQueue = pQueue->next) {
        if (i == size) {
            fprintf(stderr, "Too many elements, the array does not contain all of them");
            break;
        }
        array[i] = pQueue->this;
    }
    return array;
}