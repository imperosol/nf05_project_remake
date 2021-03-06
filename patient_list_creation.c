//
// Created by thgir on 27/02/2021.
//

#include "patient_list_creation.h"

patientQueue *create_patient_queue(short *nbrOfPatients) {
//    printf("Number of patients : ");
//    scanf("%hd", nbrOfPatients);
    *nbrOfPatients = 500;
    patientQueue *queue = NULL;
    patientQueue *queue_tail = NULL;
    patient_t *patient = NULL;

    bool isDurationRandom = true;//get_random_generation_preference("exam duration");
    bool isArrivalHourRandom = true;//get_random_generation_preference("arrival hour");
    bool isNameRandom = true;//get_random_generation_preference("patient name");

    /* Get the time at the beginning of the program for the generation of the arrival hour of the patients */
    time_t timestamp = time(NULL);
    struct tm *currentTime = safe_malloc(sizeof(struct tm));
    gmtime_s(currentTime, &timestamp);
    /* Update starting hour by adding 1 hour because the user is in UTC+1
     * and setting the number of seconds to 0 */
    update_tm(currentTime, 0, 0, 0, 1, 0, -currentTime->tm_sec);

    for (int i = 0; i < *nbrOfPatients; ++i) {
        patient = (patient_t *) safe_malloc(sizeof(patient_t));
        input_patient_information(patient, currentTime,
                                  isDurationRandom, isArrivalHourRandom, isNameRandom);
        if (isArrivalHourRandom) {
            if (queue_tail != NULL) {
                queue_tail = queue_tail->next;
            } else {
                queue_tail = queue;
            }
            queue = queue_push(queue, patient, queue_tail);
        } else {
            queue = queue_push(queue, patient, queue);
        }
    }
    free(currentTime);

    return queue;
}

patientQueue *queue_push(struct patientQueue *queue, patient_t *newPatient, patientQueue* queue_tail) {
    if (newPatient == NULL) {
        fprintf(stderr, "No element to add has been given to the function");
        return NULL;
    }
    patientQueue *newInQueue = safe_malloc(sizeof(patientQueue));
    newInQueue->this = newPatient;
    time_t current = mktime(newPatient->arrivalHour);
    if (queue == NULL || difftime(current, mktime(queue->this->arrivalHour)) < 0) {
        /* If there is no element in the queue of if the first element of the queue has
         * a higher arrival hour than the element that is to be inserted */
        newInQueue->next = queue;
        queue = newInQueue;
    } else {
        patientQueue *temp = queue_tail;
        while (temp->next != NULL && difftime(current, mktime(temp->next->this->arrivalHour)) > 0) {
            /* While the end of the queue or an element with a higher
             * arrival hour has not been reached */
            temp = temp->next;
        }
        newInQueue->next = temp->next;
        temp->next = newInQueue;
    }
    /* The element of the returned queue are sorted by growing arrival hour */
    return queue;
}

void input_patient_information(patient_t *patient, struct tm *beginningHour,
                               bool isDurationRandom, bool isArrivalHourRandom, bool isNameRandom) {
    static int timeAfterBeginning = 0;
    // TODO free patient->availabilityHour patient->arrivalHour and patient->examDuration
    patient->availabilityHour = safe_malloc(sizeof(struct tm));
    patient->arrivalHour = safe_malloc(sizeof(struct tm));
    *patient->arrivalHour = *patient->availabilityHour = *beginningHour;
    patient->name = NULL;
    patient->surname = NULL;
    patient->circuit = circuit_taken_by_patient();
    if (!isNameRandom || !isDurationRandom || !isArrivalHourRandom) {
        clear_buffer();
        puts("\nEnter new patient :\n");
    }
    if (patient->circuit == VERY_LONG) {
        patient->examDuration = safe_malloc(sizeof(unsigned int) * 4);
        patient->examHour = safe_malloc(sizeof(struct tm*) * 4);
    } else {
        patient->examDuration = safe_malloc(sizeof(unsigned int) * 3);
        patient->examHour = safe_malloc(sizeof(struct tm*) * 3);
    }
    if (!isNameRandom) {

        printf("Patient name : ");
        input_word(&patient->name);
        printf("Patient surname : ");
        input_word(&patient->surname);
    } else {
        get_random_name_from_file("name_bank/surname.txt", &patient->surname);
        get_random_name_from_file("name_bank/name.txt", &patient->name);
    }
    if (isArrivalHourRandom) {
        timeAfterBeginning += generate_time_with_exponential_law(5);
//        update_tm(patient->arrivalHour, 0, 0, 0, 0, timeAfterBeginning, 0);
        update_tm(patient->arrivalHour, 0, 0, 0, 0, 2, 0);
    } else {
        printf("Arrival hour (format : hh mm) : ");
        scanf("%d", &patient->arrivalHour->tm_hour);
        scanf("%d", &patient->arrivalHour->tm_min);
    }
    patient->availabilityHour = patient->arrivalHour;
    if (isDurationRandom) {
        patient->examDuration[0] = generate_duration_with_box_muller_method(5, 1);
        if (patient->examDuration[0] < 1) {
            patient->examDuration[0] = 1;
        }
        patient->examDuration[1] = generate_duration_with_box_muller_method(10, 1);
        patient->examDuration[2] = generate_duration_with_box_muller_method(30, 5);
        if (patient->circuit == VERY_LONG) {
            patient->examDuration[3] = generate_duration_with_box_muller_method(30, 5);
        }
    } else {
        printf("registration duration (in minutes) : ");
        scanf("%d", &(patient->examDuration[0]));
        printf("Duration of the exam by the nurse reception organizer (in minutes) : ");
        scanf("%d", &(patient->examDuration[1]));
        if (patient->circuit == SHORT) {
            printf("Short circuit.\nDuration of the medical exam : ");
            scanf("%d", &(patient->examDuration[2]));
        } else if (patient->circuit == LONG) {
            printf("Long circuit.\nDuration of the first medical exam : ");
            scanf("%d", &(patient->examDuration[2]));
            puts("This patient does not need any further exam");
        } else if (patient->circuit == VERY_LONG) {
            printf("Long circuit.\nDuration of the first medical exam : ");
            scanf("%d", &(patient->examDuration[2]));
            puts("This patient does need one more exam");
            printf("Duration of the second medical exam : ");
            scanf("%d", &(patient->examDuration[3]));
        }
    }
    patient->examNumber = 0;  // The patient has not yet passed any exam
}

const circuit_e circuit_taken_by_patient() {
    int randomCircuit;
    /*40% chances to go in short circuit,
    60% * 20% = 12% chances to go in long circuit
    60% * 80% = 48% chances to go in very long circuit*/
    randomCircuit = rand() % 100;
    if (randomCircuit < 40) {
        return SHORT;
    } else if (randomCircuit < 52) {
        return LONG;
    } else {
        return VERY_LONG;
    }
}

void get_random_name_from_file(const char *file_to_open, char **word) {
    /* For this function, .txt files are used. Those files contains n names and n+1 lines. In the first line is
     * indicated the number of names the file contains. All the other lines contain a name.
     * This function read the first line to know the number of names in the file, generates a random number
     * between 0 and the number of line then takes the name which is in the line corresponding to this number.*/

    int nbrOfWords, wordToTake;
    char temp[40];
    FILE *file = fopen(file_to_open, "r");
    fscanf(file, "%d", &nbrOfWords);
    /* generate a random number number corresponding to the line of the word to take */
    wordToTake = rand() % nbrOfWords + 2;
    /*Go down in the file until the right line is reached*/
    for (int i = 0; i < wordToTake; ++i) {
        fgets(temp, 40, file);
    }
    fclose(file);
    /* Shift the end of the word by one character to the left to delete the character '\n' */
    temp[strlen(temp) - 1] = '\0';
    *word = safe_malloc(sizeof(char) * strlen(temp) + 1);
    strcpy(*word, temp);
}

const short generate_duration_with_box_muller_method(const short mean, const short variance) {
    float a = (float) rand() / (float) (RAND_MAX);
    float b = (float) rand() / (float) (RAND_MAX);
    float randomNbr = sqrt(-2 * log(a)) * cos(2 * M_PI * b);
    return mean + floor(variance * randomNbr);
}

const short generate_time_with_exponential_law(const short mean) {
    float t = (float) rand() / (float) (RAND_MAX);
    return ceil(-mean * log(1 - t));
}

bool get_random_generation_preference(const char *sentence) {
    char choice;
    do {
        fflush(stdin);
        printf("Do you want the %s to be randomly generated ? (y/n) : ", sentence);
        scanf("%c", &choice);
    } while (choice != 'y' && choice != 'n');
    return (choice == 'y');
}