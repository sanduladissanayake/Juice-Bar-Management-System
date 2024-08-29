/*Authors: D.S.Y. Dissanayake PS/2021/009
           K.A.Y. Nimsara PS/2021/031
           O.I. Kasthuriarachchi PS/2021/063

Group 13
Purpose :Juice Bar management system */

#include <stdio.h>
#include <stdbool.h>

bool validateTime(const char *input, int *hours, int *minutes) {
    int hh, mm;
    if (sscanf(input, "%d.%d", &hh, &mm) != 2) {
        printf("Invalid time format. Please use HH:MM format.\n");
        return false;
    }

    if (hh < 8 || hh > 20 || mm < 0 || mm > 59) {
        printf("Invalid time. Hours should be between 8 and 20, and minutes between 0 and 59.\n");
        return false;
    }

    *hours = hh;
    *minutes = mm;
    return true;
}

void userdetails(char *name, char *student_no, char *email) {
    printf("Please enter your first name : ");
    scanf("%s", name);
    printf("Please enter your student number : ");
    scanf("%s", student_no);
    printf("Please enter your email : ");
    scanf("%s", email);
}

void menubar() {
    printf("\n\n*****Welcome to FRESH JUICE BAR*****\n\n");
    printf("Menu:\n");
    printf("1. Orange Juice - Rs100\n");
    printf("2. Apple Juice - Rs120\n");
    printf("3. Banana Juice - Rs80\n");
    printf("4. Papaya Juice - Rs80\n");
    printf("5. Grape Juice - Rs100\n");
    printf("6. Lemon Juice - Rs60\n");
    printf("7. Avocado Juice - Rs80\n");
    printf("8. Exit\n");
}

int getUserChoice() {
    int choice;
    while (1) {
        printf("\nEnter your choice (1-8): ");
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 8) {
            printf("Invalid choice. Please try again.\n");
            while (getchar() != '\n');
        } else {
            break;
        }
    }
    return choice;
}

void orderprocess(FILE *fp, int *token, int *count, float *total_cost, const char *juice_name, int juice_price) {
    int quantity;
    printf("Enter quantity: ");
    scanf("%d", &quantity);

    if (quantity < *count) {
        *total_cost += quantity * juice_price;
        *count -= quantity;
        fprintf(fp, "%s : %d\n", juice_name, quantity);
    } else {
        printf("Sorry, we have %d left\n", *count);
    }
}

int main() {
    int choice, hours, minutes;
    int token = 0;
    char student_no[20];
    char name[50];
    char email[50];
    char input[10];
    int count1 = 100, count2 = 100, count3 = 100, count4 = 100, count5 = 100, count6 = 100, count7 = 100;
    float total_cost = 0.0;

    FILE *fp;
    fp = fopen("./order.txt", "a");
    if (fp == NULL) {
        printf("File not found\n");
        return 1;
    }

    FILE *tokenFile;
    tokenFile = fopen("token.txt", "r");
    if (tokenFile != NULL) {
        fscanf(tokenFile, "%d", &token);
        fclose(tokenFile);
    }

    tokenFile = fopen("token.txt", "w");
    token = token + 1;

    if (tokenFile != NULL) {
        fprintf(tokenFile, "%d\n", token);
        fclose(tokenFile);
    }

    userdetails(name, student_no, email);

    menubar();

    // Order processing
    while (1) {
        choice = getUserChoice();

        if (choice == 8) {
            while (1) {
                printf("Time you want to receive the order : ");
                scanf("%s", input);
                if (validateTime(input, &hours, &minutes)) {
                    break;
                }
            }
            fprintf(fp, "receiving time %s\n", input);
            printf("\nYour total cost: Rs%.2f\n", total_cost);
            fprintf(fp, "Total : %.2f\n", total_cost);
            printf("Your token number is %d", token);
            fprintf(fp, "Token number : %d\n", token);
            fprintf(fp, "\n");
            break;
        } else if (choice < 1 || choice > 7) {
            printf("Invalid choice. Please try again.\n");
        } else {
            switch (choice) {
                case 1:
                    orderprocess(fp, &token, &count1, &total_cost, "Orange juice", 100);
                    break;
                case 2:
                    orderprocess(fp, &token, &count2, &total_cost, "Apple juice", 120);
                    break;
                case 3:
                    orderprocess(fp, &token, &count3, &total_cost, "Banana juice", 80);
                    break;
                case 4:
                    orderprocess(fp, &token, &count4, &total_cost, "Papaya juice", 80);
                    break;
                case 5:
                    orderprocess(fp, &token, &count5, &total_cost, "Grape juice", 100);
                    break;
                case 6:
                    orderprocess(fp, &token, &count6, &total_cost, "Lemon juice", 60);
                    break;
                case 7:
                    orderprocess(fp, &token, &count7, &total_cost, "Avocado juice", 80);
                    break;
                default:
                    break;
            }
        }
    }

    fclose(fp);

    printf("\nYour order will be ready at %02d.%02d \n", hours, minutes);
    printf("\n\n *****Thank you for visiting Fresh Juice Bar*****\n");

    return 0;
}
