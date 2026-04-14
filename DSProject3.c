#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100

int nextID = 1;

typedef struct Patient {
    int  id;
    char name[N];
    int  age;
    char gender;
    char disease[N];
    char condition;
} Patient;

typedef struct node {
    Patient     data;
    struct node *prev;
    struct node *next;
} node;

typedef struct {
    node *head;
    node *tail;
    int   size;
} LL;

void initList(LL *l) {
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
}

void printPatient(Patient *p) {
    char cond[20];
    if      (p->condition == 'C') strcpy(cond, "Critical");
    else if (p->condition == 'U') strcpy(cond, "Under Observation");
    else                          strcpy(cond, "Stable");

    printf("  Patient ID : %d\n",  p->id);
    printf("  Name       : %s\n",  p->name);
    printf("  Age        : %d\n",  p->age);
    printf("  Gender     : %c\n",  p->gender);
    printf("  Disease    : %s\n",  p->disease);
    printf("  Condition  : %s\n",  cond);
}

void addPatient(LL *l) {
    node *newrec = (node *)malloc(sizeof(node));
    newrec->data.id = nextID++;
    printf("\nPatient ID: %d\n", newrec->data.id);

    printf("Enter Name: ");
    scanf("%s", newrec->data.name);

    printf("Enter Age: ");
    scanf("%d", &newrec->data.age);

    printf("Enter Gender (M/F): ");
    scanf(" %c", &newrec->data.gender);
    newrec->data.gender = toupper(newrec->data.gender);

    printf("Enter Disease: ");
    scanf("%s", newrec->data.disease);

    printf("Enter Condition        \n");
    printf("  C - Critical         \n");
    printf("  U - Under Observation\n");
    printf("  S - Stable           \n");
    printf("Choice                 : ");
    scanf(" %c", &newrec->data.condition);
    newrec->data.condition = toupper(newrec->data.condition);

    newrec->next = NULL;
    newrec->prev = NULL;

    if (l->head == NULL) {
        l->head = newrec;
        l->tail = newrec;
    } else {
        newrec->prev  = l->tail;
        l->tail->next = newrec;
        l->tail       = newrec;
    }

    l->size++;
    printf("\nPatient %d added successfully!\n", newrec->data.id);
}

void deletePatient(LL *l) {
    if (l->head == NULL) {
        printf("\nNo patients in the record!\n");
        return;
    }

    int searchID;
    printf("\nEnter Patient ID to delete: ");
    scanf("%d", &searchID);

    node *p = l->head;
    while (p != NULL) {
        if (p->data.id == searchID) {
            if (p->prev != NULL)
                p->prev->next = p->next;
            else
                l->head = p->next;

            if (p->next != NULL)
                p->next->prev = p->prev;
            else
                l->tail = p->prev;

            printf("\nPatient %d (%s) deleted successfully!\n",
                   p->data.id, p->data.name);
            free(p);
            l->size--;
            return;
        }
        p = p->next;
    }
    printf("\nPatient ID %d not found!\n", searchID);
}

void displayPatients(LL *l) {
    if (l->head == NULL) {
        printf("\nNo patients in the record!\n");
        return;
    }

    printf("\n-------- PATIENT WAITING LIST (%d) ---------\n", l->size);
    node *p  = l->head;
    int   count = 1;
    while (p != NULL) {
        printf("\n  [%d]\n", count++);
        printPatient(&p->data);
        p = p->next;
    }
    printf("\n-------------------------------------------\n");
}

void searchPatient(LL *l) {
    if (l->head == NULL) {
        printf("\nNo patients in the record!\n");
        return;
    }

    int ch;
    printf("\nSearch by:\n");
    printf("  1. Patient ID\n");
    printf("  2. Patient Name\n");
    printf("  3. Gender\n");
    printf("  4. Condition\n");
    printf("Enter choice: ");
    scanf("%d", &ch);

    if (ch == 1) {
        int searchID;
        printf("Enter Patient ID: ");
        scanf("%d", &searchID);

        node *p = l->head;
        while (p != NULL) {
            if (p->data.id == searchID) {
                printf("\nPatient Found:\n");
                printPatient(&p->data);
                return;
            }
            p = p->next;
        }
        printf("\nPatient ID %d not found!\n", searchID);

    } else if (ch == 2) {
        char searchName[N];
        printf("Enter Patient Name: ");
        scanf("%s", searchName);

        int   found = 0;
        node *p  = l->head;
        while (p != NULL) {
            if (strcmp(p->data.name, searchName) == 0) {
                if (!found) printf("\nPatient(s) Found:\n");
                printf("\n");
                printPatient(&p->data);
                found = 1;
            }
            p = p->next;
        }
        if (!found)
            printf("\nNo patient named '%s' found!\n", searchName);

    } else if (ch == 3) {
        char g;
        printf("Enter Gender (M/F): ");
        scanf(" %c", &g);
        g = toupper(g);

        int   found = 0;
        node *p  = l->head;
        while (p != NULL) {
            if (p->data.gender == g) {
                if (!found) printf("\nPatient(s) Found:\n");
                printf("\n");
                printPatient(&p->data);
                found = 1;
            }
            p = p->next;
        }
        if (!found)
            printf("\nNo patients with gender '%c' found!\n", g);

    } else if (ch == 4) {
        char c;
        printf("Enter Condition (C/U/S): ");
        scanf(" %c", &c);
        c = toupper(c);

        int   found = 0;
        node *p  = l->head;
        while (p != NULL) {
            if (p->data.condition == c) {
                if (!found) printf("\nPatient(s) Found:\n");
                printf("\n");
                printPatient(&p->data);
                found = 1;
            }
            p = p->next;
        }
        if (!found)
            printf("\nNo patients with that condition found!\n");

    } else {
        printf("\nInvalid search option!\n");
    }
}

void updatePatient(LL *l) {
    if (l->head == NULL) {
        printf("\nNo patients in the record!\n");
        return;
    }

    int searchID;
    printf("\nEnter Patient ID to update: ");
    scanf("%d", &searchID);

    node *p = l->head;
    while (p != NULL) {
        if (p->data.id == searchID) {
            printf("\nCurrent Details:\n");
            printPatient(&p->data);

            int f;
            printf("\nUpdate:\n");
            printf("  1. Name\n");
            printf("  2. Age\n");
            printf("  3. Gender\n");
            printf("  4. Disease\n");
            printf("  5. Condition\n");
            printf("  6. All Fields\n");
            printf("Enter choice: ");
            scanf("%d", &f);

            switch (f) {
                case 1:
                    printf("New Name      : ");
                    scanf("%s", p->data.name);
                    break;
                case 2:
                    printf("New Age       : ");
                    scanf("%d", &p->data.age);
                    break;
                case 3:
                    printf("New Gender (M/F): ");
                    scanf(" %c", &p->data.gender);
                    p->data.gender = toupper(p->data.gender);
                    break;
                case 4:
                    printf("New Disease   : ");
                    scanf("%s", p->data.disease);
                    break;
                case 5:
                    printf("New Condition (C/U/S): ");
                    scanf(" %c", &p->data.condition);
                    p->data.condition = toupper(p->data.condition);
                    break;
                case 6:
                    printf("New Name      : ");
                    scanf("%s", p->data.name);
                    printf("New Age       : ");
                    scanf("%d", &p->data.age);
                    printf("New Gender (M/F): ");
                    scanf(" %c", &p->data.gender);
                    p->data.gender = toupper(p->data.gender);
                    printf("New Disease   : ");
                    scanf("%s", p->data.disease);
                    printf("New Condition (C/U/S): ");
                    scanf(" %c", &p->data.condition);
                    p->data.condition = toupper(p->data.condition);
                    break;
                default:
                    printf("\nInvalid choice!\n");
                    return;
            }

            printf("\nPatient %d updated successfully!\n", p->data.id);
            printf("\nUpdated Details:\n");
            printPatient(&p->data);
            return;
        }
        p = p->next;
    }
    printf("\nPatient ID %d not found!\n", searchID);
}

int main() {
    LL  l;
    int ch;
    initList(&l);

    while (1) {
        printf("\n====== HOSPITAL PATIENT RECORD ======\n");
        printf("  1. Add Patient\n");
        printf("  2. Delete Patient\n");
        printf("  3. Display All Patients\n");
        printf("  4. Search Patient\n");
        printf("  5. Update Patient\n");
        printf("  6. Exit\n");
        printf("=====================================\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: addPatient(&l);      break;
            case 2: deletePatient(&l);   break;
            case 3: displayPatients(&l); break;
            case 4: searchPatient(&l);   break;
            case 5: updatePatient(&l);   break;
            case 6:
                printf("\nExiting... !\n\n");
                exit(0);
            default:
                printf("\nInvalid choice! Try again.\n");
        }
    }
    return 0;
}