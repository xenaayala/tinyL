#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InstrUtils.h"
#include "Utils.h"

//Function that does the optimization 
Instruction* opti(Instruction * head);
Instruction* optim(Instruction *head);


// Global Variable used as BOOL to check if anything was changed
int changed=0;

Instruction* opti(Instruction *	head){

        Instruction *first, *second, *third;
        Instruction *ptr = head;
	do {
		first = ptr;
		second = ptr->next;
		third = second->next;
		if (first->opcode == LOADI && second->opcode == LOADI) {
			switch (third->opcode) {
				case SUB:
                                        if (first->field1 == third->field2 && second->field1 == third->field3) {
                                                ptr->field1 = third->field1;
                                                ptr->field2 = first->field2 - second->field2;
                                                ptr->next = third->next;
                                                third->next->prev = ptr;
                                                changed=1;
						free(second);
                                                free(third);
                                        }
					break;
				case ADD:
					if ((first->field1 == third->field2 && second->field1 == third->field3) || (first->field1 == third->field3 && second->field1 == third->field2)) {
						ptr->field1 = third->field1;
						ptr->field2 = first->field2 + second->field2;
						ptr->next = third->next;
						third->next->prev = ptr;
						changed=1;
						free(second);
						free(third);
					}		
					break;
				case MUL:
					if ((first->field1 == third->field2 && second->field1 == third->field3) || (first->field1 == third->field3 && second->field1 == third->field2)) {
						ptr->field1 = third->field1;
						ptr->field2 = first->field2 * second->field2;
						ptr->next = third->next;
						third->next->prev = ptr;
						changed=1;
						free(second);
						free(third);
					}		
					break;		
				default:
					break;
			}
		}
		ptr = ptr->next;
	} while (ptr != NULL && ptr->next != NULL && ptr->next->next != NULL);

	return head;

}

Instruction* optim(Instruction *head){
	changed=0;

	Instruction *ptr=head;
	head=opti(ptr);
	 
	while (changed==1){
		changed=0;
		head=opti(ptr);
	}
	return head; 
}

int main()
{
	Instruction *head;

	head = ReadInstructionList(stdin);
	if (!head) {
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}
	Instruction* ptr=head;
	/* YOUR CODE GOES HERE */


	//Optimize the first time
	head=optim(ptr);
	
	
	
	//printf("second time\n");
	//head=opti(ptr);

//	if(head){
		PrintInstructionList(stdout, head);
		DestroyInstructionList(head);
//	}
	return EXIT_SUCCESS;
}

 
