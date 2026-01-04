#include <cs50.h>
#include <stdio.h>

int find_student(int ids[], int count, int id);
void load_students(int ids[], string names[], int attended[], int *count);
void save_students(int ids[], string names[], int attended[], int count);

int main(void)
{
    int ids[10000];
    string names[10000];
    int attended[10000];

    int count = 0;
    int total_classes = 0;

    load_students(ids, names, attended, &count);

    while (true)
    {
        printf("\n--- Attendance Tracker ---\n");
        printf("1. Add student\n");
        printf("2. Set total classes\n");
        
        printf("3. Set attendance\n");
        printf("4. Check attendance\n");
        printf("5. View all students\n");
        printf("6. Exit\n");

        int choice = get_int("Choice: ");

        if (choice == 1)
        {
            if (count == 10000)
            {
                printf("You cannot add more students.\n");
                continue;
            }

            int new_id = get_int("Student ID: ");

            if (find_student(ids, count, new_id) != -1)
            {
                printf("Student with this ID already exists.\n");
                continue;
            }

            ids[count] = new_id;
            names[count] = get_string("Name: ");
            attended[count] = 0;

            count++;
            save_students(ids, names, attended, count);

            printf("Student added.\n");
        }

        else if (choice == 2)
        {
            total_classes = get_int("Total classes: ");
            if (total_classes < 0)
            {
                printf("Invalid number.\n");
                total_classes = 0;
            }
        }

        else if (choice == 3)
        {
            if (total_classes == 0)
            {
                printf("Set total classes first.\n");
                continue;
            }

            int id = get_int("Student ID: ");
            int index = find_student(ids, count, id);

            if (index == -1)
            {
                printf("Student not found.\n");
                continue;
            }

            int a = get_int("Classes attended: ");
            if (a < 0 || a > total_classes)
            {
                printf("Invalid number.\n");


            }
            else
            {
                attended[index] = a;
                save_students(ids, names, attended, count);

                printf("Attendance updated.\n");

            }
        }

        else if (choice == 4)
        {
            if (total_classes == 0)
            {
                printf("No total classes set.\n");
                continue;
            }

            int id = get_int("Student ID: ");
            int index = find_student(ids, count, id);

            if (index == -1)
            {
                printf("Student not found.\n");
                continue;
            }

            float percent = attended[index] * 100.0 / total_classes;

            printf("\nStudent: %s\n", names[index]);
            printf("Attendance: %i / %i (%.2f%%)\n",attended[index], total_classes, percent);

            if (percent < 75.0)
            {
                printf("Low attendance warning!\n");
            }
        }

        else if (choice == 5)
        {
            if (count == 0)
            {
                printf("No students added yet.\n");
                continue;
            }

            printf("\n--- All Students ---\n");

            for (int i = 0; i < count; i++)
            {
                printf("%i. ID: %i | Name: %s | Attended: %i\n",i + 1, ids[i], names[i], attended[i]);
            }
        }

        else if (choice == 6)
        {
            printf("Goodbye!\n");
            break;
        }
        else
        {
            printf("Invalid choice.\n");
        }
    }
}

int find_student(int ids[], int count, int id)
{
    for (int i = 0; i < count; i++)
    {
        if (ids[i] == id)
        {
            return i;
        }
    }
    return -1;
}

void load_students(int ids[], string names[], int attended[], int *count)
{
    FILE *f = fopen("students.txt", "r");
    if (f == NULL)
    {
        return;
    }

    while (fscanf(f, "%i %s %i",
                  &ids[*count], names[*count], &attended[*count]) == 3)
    {
        (*count)++;
    }

    fclose(f);
}

void save_students(int ids[], string names[], int attended[], int count)
{
    FILE *f = fopen("students.txt", "w");
    if (f == NULL)
    {
        printf("Error saving file.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(f, "%i %s %i\n", ids[i], names[i], attended[i]);
    }

    fclose(f);
}
