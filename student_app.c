#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STUDENT_FILE "students.txt"
#define CREDENTIAL_FILE "credentials.txt"

struct Student {
    int roll;
    char name[50];
    float marks;
};

/* current user info */
char currentUser[50];
char currentRole[20];

/* function prototypes */
int loginSystem();
void registerUser();
void mainMenuRouter();

void adminMenu();
void staffMenu();
void userMenu();
void guestMenu();

void addStudent();
void viewStudents();
void searchByRoll();
void searchByName();
void updateStudent();
void deleteStudent();

/* -------------------- MAIN -------------------- */
int main() {
    printf("=====================================\n");
    printf("     STUDENT MANAGEMENT SYSTEM\n");
    printf("=====================================\n");

    while (1) {
        int choice;
        printf("\n1. Login\n2. Register\n3. Continue as Guest\n4. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (choice == 1) {
            if (loginSystem()) {
                mainMenuRouter();
            } else {
                printf("Login failed.\n");
            }
        } else if (choice == 2) {
            registerUser();
        } else if (choice == 3) {
            strcpy(currentRole, "GUEST");
            strcpy(currentUser, "guest");
            guestMenu();
        } else if (choice == 4) {
            printf("Exiting program. Goodbye!\n");
            break;
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}

/* -------------------- LOGIN -------------------- */
int loginSystem() {
    char username[50];
    char password[50];
    char fileUser[50], filePass[50], fileRole[50];
    int attempts = 3;

    printf("\n===== LOGIN =====\n");
    printf("Username: ");
    if (scanf("%49s", username) != 1) return 0;

    while (attempts > 0) {
        printf("Password (%d attempts left): ", attempts);
        if (scanf("%49s", password) != 1) return 0;

        FILE *fp = fopen(CREDENTIAL_FILE, "r");
        if (!fp) {
            printf("Error: %s not found! You can register a user.\n", CREDENTIAL_FILE);
            return 0;
        }

        while (fscanf(fp, "%49s %49s %49s", fileUser, filePass, fileRole) == 3) {
            if (strcmp(username, fileUser) == 0 && strcmp(password, filePass) == 0) {
                strcpy(currentUser, fileUser);
                strcpy(currentRole, fileRole);
                fclose(fp);
                printf("\nLogin successful! Welcome %s (Role: %s)\n", currentUser, currentRole);
                return 1;
            }
        }

        fclose(fp);
        attempts--;
        printf("Incorrect password!\n");
    }

    printf("Too many attempts. Login failed.\n");
    return 0;
}

/* -------------------- REGISTER -------------------- */
void registerUser() {
    char username[50], password[50], role[50];
    char fu[50], fpw[50], fr[50];

    printf("\n===== REGISTER NEW USER =====\n");
    printf("Enter username: ");
    if (scanf("%49s", username) != 1) return;
    printf("Enter password: ");
    if (scanf("%49s", password) != 1) return;
    printf("Enter role (ADMIN/STAFF/USER/GUEST): ");
    if (scanf("%49s", role) != 1) return;

    FILE *fp = fopen(CREDENTIAL_FILE, "r");
    if (fp) {
        while (fscanf(fp, "%49s %49s %49s", fu, fpw, fr) == 3) {
            if (strcmp(fu, username) == 0) {
                printf("Username already exists. Registration cancelled.\n");
                fclose(fp);
                return;
            }
        }
        fclose(fp);
    }

    fp = fopen(CREDENTIAL_FILE, "a");
    if (!fp) {
        printf("Unable to open %s for writing.\n", CREDENTIAL_FILE);
        return;
    }
    fprintf(fp, "%s %s %s\n", username, password, role);
    fclose(fp);
    printf("User registered successfully. You may now login.\n");
}

/* -------------------- ROUTER -------------------- */
void mainMenuRouter() {
    if (strcmp(currentRole, "ADMIN") == 0 || strcmp(currentRole, "admin") == 0)
        adminMenu();
    else if (strcmp(currentRole, "STAFF") == 0 || strcmp(currentRole, "staff") == 0)
        staffMenu();
    else if (strcmp(currentRole, "USER") == 0 || strcmp(currentRole, "user") == 0)
        userMenu();
    else
        guestMenu();
}

/* -------------------- ADMIN MENU -------------------- */
void adminMenu() {
    int ch;
    while (1) {
        printf("\n========== ADMIN MENU (%s) ==========\n", currentUser);
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student by Roll\n");
        printf("4. Search Student by Name\n");
        printf("5. Update Student\n");
        printf("6. Delete Student\n");
        printf("7. Logout\n");
        printf("Enter choice: ");
        if (scanf("%d", &ch) != 1) { while (getchar() != '\n'); continue; }

        switch (ch) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchByRoll(); break;
            case 4: searchByName(); break;
            case 5: updateStudent(); break;
            case 6: deleteStudent(); break;
            case 7: return;
            default: printf("Invalid choice!\n");
        }
    }
}

/* -------------------- STAFF MENU -------------------- */
void staffMenu() {
    int ch;
    while (1) {
        printf("\n========== STAFF MENU (%s) ==========\n", currentUser);
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student by Roll\n");
        printf("4. Search Student by Name\n");
        printf("5. Logout\n");
        printf("Enter choice: ");
        if (scanf("%d", &ch) != 1) { while (getchar() != '\n'); continue; }

        switch (ch) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchByRoll(); break;
            case 4: searchByName(); break;
            case 5: return;
            default: printf("Invalid choice!\n");
        }
    }
}

/* -------------------- USER MENU -------------------- */
void userMenu() {
    int ch;
    while (1) {
        printf("\n=========== USER MENU (%s) ===========\n", currentUser);
        printf("1. View Students\n");
        printf("2. Search Student by Roll\n");
        printf("3. Search Student by Name\n");
        printf("4. Logout\n");
        printf("Enter choice: ");
        if (scanf("%d", &ch) != 1) { while (getchar() != '\n'); continue; }

        switch (ch) {
            case 1: viewStudents(); break;
            case 2: searchByRoll(); break;
            case 3: searchByName(); break;
            case 4: return;
            default: printf("Invalid choice!\n");
        }
    }
}

/* -------------------- GUEST MENU -------------------- */
void guestMenu() {
    int ch;
    while (1) {
        printf("\n=========== GUEST MENU ===========\n");
        printf("1. View Students\n");
        printf("2. Search Student by Roll\n");
        printf("3. Search Student by Name\n");
        printf("4. Back to Main\n");
        printf("Enter choice: ");
        if (scanf("%d", &ch) != 1) { while (getchar() != '\n'); continue; }

        switch (ch) {
            case 1: viewStudents(); break;
            case 2: searchByRoll(); break;
            case 3: searchByName(); break;
            case 4: return;
            default: printf("Invalid choice!\n");
        }
    }
}

/* -------------------- ADD STUDENT -------------------- */
void addStudent() {
    struct Student st;
    FILE *fp = fopen(STUDENT_FILE, "a+");
    if (!fp) {
        printf("Error opening %s for writing.\n", STUDENT_FILE);
        return;
    }

    /* Add heading only if file is empty */
    fseek(fp, 0, SEEK_END);
    if (ftell(fp) == 0) {
        fprintf(fp, "ROLL NAME MARKS\n");
    }

    printf("\nEnter Roll: ");
    if (scanf("%d", &st.roll) != 1) { while (getchar() != '\n'); fclose(fp); return; }

    printf("Enter Name (no spaces): ");
    if (scanf("%49s", st.name) != 1) { fclose(fp); return; }

    printf("Enter Marks: ");
    if (scanf("%f", &st.marks) != 1) { while (getchar() != '\n'); fclose(fp); return; }

    fprintf(fp, "%d %s %.2f\n", st.roll, st.name, st.marks);
    fclose(fp);

    printf("Student added successfully!\n");
}

/* -------------------- VIEW STUDENTS -------------------- */
void viewStudents() {
    struct Student st;
    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) {
        printf("No student records found.\n");
        return;
    }

    char header[100];
    fgets(header, sizeof(header), fp); // Skip heading

    printf("\nROLL\tNAME\tMARKS\n");
    printf("---------------------------\n");

    while (fscanf(fp, "%d %49s %f", &st.roll, st.name, &st.marks) == 3) {
        printf("%d\t%s\t%.2f\n", st.roll, st.name, st.marks);
    }
    fclose(fp);
}

/* -------------------- SEARCH BY ROLL -------------------- */
void searchByRoll() {
    struct Student st;
    int roll, found = 0;

    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) {
        printf("No student records found.\n");
        return;
    }

    char header[100];
    fgets(header, sizeof(header), fp); // Skip heading

    printf("Enter Roll to search: ");
    if (scanf("%d", &roll) != 1) { while (getchar() != '\n'); fclose(fp); return; }

    while (fscanf(fp, "%d %49s %f", &st.roll, st.name, &st.marks) == 3) {
        if (st.roll == roll) {
            printf("\nRecord Found:\nRoll: %d\nName: %s\nMarks: %.2f\n",
                   st.roll, st.name, st.marks);
            found = 1;
            break;
        }
    }

    if (!found) printf("Record not found.\n");
    fclose(fp);
}

/* -------------------- SEARCH BY NAME -------------------- */
void searchByName() {
    struct Student st;
    char search[50], lowerSearch[50], lowerName[50];
    int i, found = 0;

    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) {
        printf("No student records found.\n");
        return;
    }

    char header[100];
    fgets(header, sizeof(header), fp); // Skip heading

    printf("Enter Name to search: ");
    if (scanf("%49s", search) != 1) { fclose(fp); return; }

    for (i = 0; search[i]; i++)
        lowerSearch[i] = tolower(search[i]);
    lowerSearch[i] = '\0';

    while (fscanf(fp, "%d %49s %f", &st.roll, st.name, &st.marks) == 3) {
        for (i = 0; st.name[i]; i++)
            lowerName[i] = tolower(st.name[i]);
        lowerName[i] = '\0';

        if (strcmp(lowerSearch, lowerName) == 0) {
            printf("\nRecord Found:\nRoll: %d\nName: %s\nMarks: %.2f\n",
                   st.roll, st.name, st.marks);
            found = 1;
            break;
        }
    }

    if (!found) printf("Name not found.\n");
    fclose(fp);
}

/* -------------------- UPDATE STUDENT -------------------- */
void updateStudent() {
    struct Student list[1000];
    int count = 0, found = 0;
    int roll,i;

    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) {
        printf("No student records found.\n");
        return;
    }

    char header[100];
    fgets(header, sizeof(header), fp); // Skip heading

    while (fscanf(fp, "%d %49s %f", &list[count].roll, list[count].name, &list[count].marks) == 3) {
        count++;
    }
    fclose(fp);

    printf("Enter Roll to update: ");
    if (scanf("%d", &roll) != 1) { while (getchar()!='\n'); return; }

    for (i = 0; i < count; i++) {
        if (list[i].roll == roll) {
            found = 1;
            printf("Existing: Roll:%d Name:%s Marks:%.2f\n",
                   list[i].roll, list[i].name, list[i].marks);

            printf("Enter new Name (no spaces): ");
            scanf("%49s", list[i].name);
            printf("Enter new Marks: ");
            scanf("%f", &list[i].marks);
            break;
        }
    }

    if (!found) {
        printf("Record not found.\n");
        return;
    }

    fp = fopen(STUDENT_FILE, "w");
    if (!fp) {
        printf("Error writing to file.\n");
        return;
    }

    fprintf(fp, "ROLL NAME MARKS\n");

    for (i = 0; i < count; i++) {
        fprintf(fp, "%d %s %.2f\n", list[i].roll, list[i].name, list[i].marks);
    }
    fclose(fp);

    printf("Record updated successfully.\n");
}

/* -------------------- DELETE STUDENT -------------------- */
void deleteStudent() {
    struct Student list[1000];
    int count = 0, found = 0;
    int roll,i,j;

    FILE *fp = fopen(STUDENT_FILE, "r");
    if (!fp) {
        printf("No student records found.\n");
        return;
    }

    char header[100];
    fgets(header, sizeof(header), fp); // Skip heading

    while (fscanf(fp, "%d %49s %f", &list[count].roll, list[count].name, &list[count].marks) == 3) {
        count++;
    }
    fclose(fp);

    printf("Enter Roll to delete: ");
    if (scanf("%d", &roll) != 1) { while (getchar()!='\n'); return; }

    for (i = 0; i < count; i++) {
        if (list[i].roll == roll) {
            found = 1;
            for (j = i; j < count - 1; j++) {
                list[j] = list[j + 1];
            }
            count--;
            break;
        }
    }

    if (!found) {
        printf("Record not found.\n");
        return;
    }

    fp = fopen(STUDENT_FILE, "w");
    if (!fp) {
        printf("Error writing to file.\n");
        return;
    }

    fprintf(fp, "ROLL NAME MARKS\n");

    for (i = 0; i < count; i++) {
        fprintf(fp, "%d %s %.2f\n", list[i].roll, list[i].name, list[i].marks);
    }
    fclose(fp);

    printf("Record deleted successfully.\n");
}
