// Path: main.c

// The records of the students list are stored in a file named “students.dat”.
// Write the program that has the interface as follows:
// Please choose:
// 1. Insert students records to the database.
// 2. Read all students information from database
// 3. Print/show information of all students
// 4. Ranking of students based on the average.
// 5. Calculate the Average mark of all students of a given class name.
// 0. Exit

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <math.h>

struct students{
  char name[30];
  char class[10];
  float average;
};


// Menu
void menu(){
    printf("+-----------------------------------------------------------------------+\n");
    printf("|                             Please choose:                            |\n");
    printf("| (1) Insert students records to the database.                          |\n");
    printf("| (2) Read all students information from database                       |\n");
    printf("| (3) Print/show information of all students                            |\n");
    printf("| (4) Ranking of students based on the average.                         |\n");
    printf("| (5) Calculate the Average mark of all students of a given class name. |\n");
    printf("| (0) Exit                                                              |\n");
    printf("+-----------------------------------------------------------------------+\n");
}

int get_number_of_students_db(FILE *fp){
    // Print number of students in file
    fseek(fp, 0, SEEK_END);
    int number_of_students = ftell(fp)/sizeof(struct students);

    printf("Number of students in database: %d\n", number_of_students);
    // fclose(fp);

    return number_of_students;
}

// Insert students records to the database.
void insert(){
  FILE *fp;
  struct students st;
  fp = fopen("students.dat", "ab");
  if(fp == NULL){
    printf("Error in opening file\n");
    exit(1);
  }
  printf("Enter name: ");
  scanf("%s", st.name);
  printf("Enter class: ");
  scanf("%s", st.class);
  printf("Enter average: ");
  scanf("%f", &st.average);
  fwrite(&st, sizeof(st), 1, fp);
  fclose(fp);
  printf("Insert completed!\n");
}

// Read all students information from database

void read(){
    FILE *fp;
    fp = fopen("students.dat", "rb");

    int number_of_students = get_number_of_students_db(fp);
}

// Print/show information of all students
void print(){
    FILE *fp;
    fp = fopen("students.dat", "rb");

    if(fp == NULL){
        printf("Error in opening file, or no students in database\n");
        exit(1);
    }

    int number_of_students = get_number_of_students_db(fp);

    struct students_db {
        char name[30];
        char class[10];
        float average;
    } students_db[number_of_students];

    // Print name of all students
    fseek(fp, 0, SEEK_SET);
    for(int i = 0; i < number_of_students; i++){
        fread(&students_db[i], sizeof(struct students_db), 1, fp);
        printf("+----------------------------------+\n");
        printf("Student %d: %s\n", i + 1, students_db[i].name);
        printf("Class: %s\n", students_db[i].class);
        printf("Average: %.2f\n", students_db[i].average);
    }
    printf("+----------------------------------+\n");
  fclose(fp);
}

// Ranking of students based on the average.

void ranking(){
    FILE *fp;
    fp = fopen("students.dat", "rb");
    int number_of_students = get_number_of_students_db(fp);

    struct students_db {
        char name[30];
        char class[10];
        float average;
    } students_db[number_of_students];

    if(fp == NULL){
        printf("Error in opening file\n");
        exit(1);
    }
    
    // Read all students
    fseek(fp, 0, SEEK_SET);
    for(int i = 0; i < number_of_students; i++){
        fread(&students_db[i], sizeof(struct students_db), 1, fp);
    }

    for(int i = 0; i < number_of_students; i++){
        for(int j = i + 1; j < number_of_students; j++){
            if(students_db[i].average < students_db[j].average){
                struct students_db temp = students_db[i];
                students_db[i] = students_db[j];
                students_db[j] = temp;
            }
        }
    }
    
    // Print ranking
    printf("Ranking top students:\n");
    for(int i = 0; i < number_of_students; i++){
        printf("%d. %s, score: %.2f\n", i + 1, students_db[i].name, students_db[i].average);
    }

    fclose(fp);

}

// Calculate the Average mark of all students of a given class name.

void average(){
    printf("Enter class name to calculate avg score: ");
    char given_class_name[10];
    int num_student_in_given_class_name = 0;
    scanf("%s", given_class_name);

    FILE *fp;
    fp = fopen("students.dat", "rb");
    int number_of_students = get_number_of_students_db(fp);
    float total_score = 0;

    struct students_db {
        char name[30];
        char class[10];
        float average;
    } students_db[number_of_students];

    // Read all students
    fseek(fp, 0, SEEK_SET);
    for(int i = 0; i < number_of_students; i++){
        fread(&students_db[i], sizeof(struct students_db), 1, fp);
    }

    for (int i = 0; i < number_of_students; i++){
        if(strcmp(students_db[i].class, given_class_name) == 0){
            total_score += students_db[i].average;
            num_student_in_given_class_name++;
        }
    }

    float avg_class_score = total_score / num_student_in_given_class_name;

    printf("+----------------------------------+\n");
    printf("| Average score of class %s: %.2f|\n", given_class_name, avg_class_score);
    printf("+----------------------------------+\n\n");

    // Print ranking
    printf("Calculated based on:\n");
    for(int i = 0; i < number_of_students; i++){
        printf("%d. %s, score: %.2f\n", i + 1, students_db[i].name, students_db[i].average);
    }

    fclose(fp);
}

// Main function
int main(){
  int choice;
  int a[10] = {1, 2, 3, 4, 5, 6, 7, 8};
  // print Length of a
    printf("Length of a: %lu\n", sizeof(a)/sizeof(a[0]));
  do{
    menu();
    printf("Enter your choice: ");
    scanf("%d", &choice);
    switch(choice){
      case 1:
        insert();
        break;
      case 2:
        read();
        break;
      case 3:
        print();
        break;
      case 4:
        ranking();
        break;
      case 5:
        average();
        break;
      case 0:
        printf("Exit\n");
        break;
      default:
        printf("Invalid choice\n");
    }
  }while(choice != 0);
  return 0;
}

// Teen svien ko dc co dau space