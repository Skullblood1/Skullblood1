/*
 * Employee Salary Management System
 *
 * Accepts an employee's name, address, salary and ID from the user.
 * The name is validated with fnEmployeeNameValid() before the remaining
 * details are accepted.
 */

#include <stdio.h>
#include <string.h>

/* Return codes for name validation */
#define NAME_VALID          0
#define NAME_INVALID_CHAR   1
#define NAME_EMPTY          2

#define MAX_NAME_LEN        50
#define MAX_ADDRESS_LEN     100

struct Employee {
    int   iEmployeeId;
    char  acName[MAX_NAME_LEN];
    char  acAddress[MAX_ADDRESS_LEN];
    float fSalary;
};

int fnEmployeeNameValid(const char acName[]);
void fnReadLine(char acBuffer[], int iSize);
void fnDisplayEmployee(const struct Employee *psEmp);

int main(void)
{
    struct Employee sEmp;
    int iStatus;

    printf("===== Employee Salary Management System =====\n\n");

    /* a) Accept the full name and validate it before anything else */
    do {
        printf("Enter employee's full name: ");
        fnReadLine(sEmp.acName, MAX_NAME_LEN);

        iStatus = fnEmployeeNameValid(sEmp.acName);

        if (iStatus == NAME_VALID) {
            printf("Valid name\n\n");
        } else {
            printf("Invalid name");
            if (iStatus == NAME_EMPTY)
                printf(" (name cannot be empty)");
            else
                printf(" (only letters and spaces are allowed)");
            printf(". Please try again.\n\n");
        }
    } while (iStatus != NAME_VALID);

    /* Name is valid, now accept the remaining details */
    printf("Enter employee ID: ");
    while (scanf("%d", &sEmp.iEmployeeId) != 1 || sEmp.iEmployeeId <= 0) {
        while (getchar() != '\n')
            ;
        printf("Invalid ID. Enter a positive number: ");
    }
    while (getchar() != '\n')
        ;

    printf("Enter employee address: ");
    fnReadLine(sEmp.acAddress, MAX_ADDRESS_LEN);

    printf("Enter employee salary: ");
    while (scanf("%f", &sEmp.fSalary) != 1 || sEmp.fSalary < 0) {
        while (getchar() != '\n')
            ;
        printf("Invalid salary. Enter a non-negative amount: ");
    }

    fnDisplayEmployee(&sEmp);

    return 0;
}

/*
 * Checks each character of the name. Allowed characters are
 * 'a'-'z', 'A'-'Z' and a blank space.
 * Returns NAME_VALID on success, otherwise an error code.
 */
int fnEmployeeNameValid(const char acName[])
{
    int iIndex;
    int iHasLetter = 0;

    for (iIndex = 0; acName[iIndex] != '\0'; iIndex++) {
        char cCh = acName[iIndex];

        if ((cCh >= 'a' && cCh <= 'z') || (cCh >= 'A' && cCh <= 'Z')) {
            iHasLetter = 1;
        } else if (cCh != ' ') {
            return NAME_INVALID_CHAR;
        }
    }

    if (!iHasLetter)
        return NAME_EMPTY;

    return NAME_VALID;
}

/* Reads a line from stdin and strips the trailing newline */
void fnReadLine(char acBuffer[], int iSize)
{
    if (fgets(acBuffer, iSize, stdin) == NULL) {
        acBuffer[0] = '\0';
        return;
    }

    size_t uLen = strlen(acBuffer);
    if (uLen > 0 && acBuffer[uLen - 1] == '\n') {
        acBuffer[uLen - 1] = '\0';
    } else {
        /* Input was longer than the buffer; discard the rest of the line */
        int iCh;
        while ((iCh = getchar()) != '\n' && iCh != EOF)
            ;
    }
}

void fnDisplayEmployee(const struct Employee *psEmp)
{
    printf("\n========== Employee Details ==========\n");
    printf("Employee ID : %d\n", psEmp->iEmployeeId);
    printf("Name        : %s\n", psEmp->acName);
    printf("Address     : %s\n", psEmp->acAddress);
    printf("Salary      : %.2f\n", psEmp->fSalary);
    printf("======================================\n");
}
