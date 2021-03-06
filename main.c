#include <stdio.h>
#include <stdlib.h>

#include "struct.h"
#include "patient_list_creation.h"
#include "patient_list_modification.h"
#include "exam.h"

int main() {
    srand(time(NULL));
    puts("Welcome in our hospital management program in C for NF05.\n"
         "Please write in the shell the information which you shall be asked for\n\n");
    clock_t begin = clock();
    short nbrOfPatients;
    patientQueue *queue = create_patient_queue(&nbrOfPatients);


    do_all_exam(queue, 0, 1);  // registration
    do_all_exam(queue, 1, 1);  // NRO exam

    do_branch_exam(SHORT, queue, 2, 2);
    do_branch_exam(LONG, queue, 2, 3);
    do_branch_exam(VERY_LONG, queue, 3, 2);

    /* The queue content is copied in an array for result display and deleted */
    patient_t *patient_list = copy_queue_in_array(queue, nbrOfPatients);
    free_queue(&queue);

    clock_t end = clock();
    unsigned long millis = (end -  begin) * 1000 / CLOCKS_PER_SEC;
    printf( "Finished in %ld ms\n", millis );
    puts("fini");
    while (getchar() != '\n');
    while (getchar() != '\n');
    return 0;
}
