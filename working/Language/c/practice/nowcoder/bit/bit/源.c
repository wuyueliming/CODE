
//#include<stdlib.h>
//#include<stdio.h>                                          ¸´ÔÓÁ´±íµÄ¸´ÖÆ
//
//struct Node* copyRandomList(struct Node* head) {
//    struct Node* cur = head;
//    while (cur) {
//        struct Node* copy = (struct Node*)malloc(sizeof(struct Node));
//        copy->val = cur->val;
//        copy->next = cur->next;
//        cur->next = copy;
//        cur = copy->next;
//    }
//
//    cur = head;
//    while (cur) {
//        struct Node* copy = cur->next;
//        if (cur->random == NULL) {
//            copy->random = NULL;
//        }
//        else {
//            copy->random = cur->random->next;
//        }
//        cur = copy->next;
//    }
//
//    struct Node* HEAD = (struct Node*)malloc(sizeof(struct Node));
//    struct Node* TAIL = HEAD; TAIL->next = NULL;
//    cur = head;
//    while (cur) {
//        struct Node* copy = cur->next;
//        struct Node* next = copy->next;
//
//        TAIL->next = cur->next;
//        TAIL = TAIL->next;
//
//        cur->next = next;
//        cur = cur->next;
//    }
//
//
//    return HEAD->next;
//}



#include<math.h>
#include<stdio.h>

int main() {

	printf("%f\n", cos(3.1415926/20));
	printf("%f", cos(3.1415926 / 20)/ sin(3.1415926 / 20));




	return 0;
}



















































































