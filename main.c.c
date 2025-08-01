#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Property{
    char Location[50];
    char City[50];
    double Price;
    int Rooms;
    int Bathrooms;
    int CarParks;
    char Type[50];
    char Furnish[50];
};

char gFieldName[50];
const int max_row = 3940;
const char *filename = "file.csv";

void readCSV(const char *filename, struct Property *properties, int maxProperties) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    char line[3940];

    for (int i = 0; i <= maxProperties; i++) {
        if (fgets(line, sizeof(line), file) == NULL) {
            break;
        }

        if (i == 0) {
            continue;
            ;
        }
        
        sscanf(line, "%49[^,],%49[^,],%lf,%d,%d,%d,%49[^,],%49[^\n]",
               properties[i - 1].Location, properties[i - 1].City,
               &properties[i - 1].Price, &properties[i - 1].Rooms,
               &properties[i - 1].Bathrooms, &properties[i - 1].CarParks,
               properties[i - 1].Type, properties[i - 1].Furnish);
    }

    fclose(file);
}

void print_csv(struct Property *properties, int total_row) {
    printf("%-30s %-15s %-15s %-10s %-10s %-10s %-10s %-10s\n",
           "Location", "City", "Price", "Rooms", "Bathrooms", "CarParks", "Type", "Furnish");

    for (int i = 0; i < total_row; i++) {
        printf("%-30s %-15s %-15.2lf %-10d %-10d %-10d %-10s %-1s\n",
               properties[i].Location, properties[i].City,
               properties[i].Price, properties[i].Rooms,
               properties[i].Bathrooms, properties[i].CarParks,
               properties[i].Type, properties[i].Furnish);
    }
}

void display_data() {
    struct Property properties[max_row];
    readCSV(filename, properties, max_row);

    print_csv(properties, max_row);
}

void search_data() {
    struct Property properties[max_row];
    readCSV(filename, properties, max_row);

    char column[50], keyword[50];
    printf("Enter Column you want to search: ");
    scanf("%s", column);
    printf("Enter keyword: ");
    scanf("%s", keyword);

    int columnIndex = -1;
    if (strcmp(column, "Location") == 0) {
        columnIndex = 0;
    } else if (strcmp(column, "City") == 0) {
        columnIndex = 1;
    } else if (strcmp(column, "Price") == 0) {
        columnIndex = 2;
    } else if (strcmp(column, "Rooms") == 0) {
        columnIndex = 3;
    } else if (strcmp(column, "Bathrooms") == 0) {
        columnIndex = 4;
    } else if (strcmp(column, "CarParks") == 0) {
        columnIndex = 5;
    } else if (strcmp(column, "Type") == 0) {
        columnIndex = 6;
    } else if (strcmp(column, "Furnish") == 0) {
        columnIndex = 7;
    } else {
        fprintf(stderr, "Error: Unrecognized column name\n");
        return;
    }

    int count = 0;
    for (size_t i = 0; i < max_row; i++) {
        if ((columnIndex == 0 && strstr(properties[i].Location, keyword) != NULL) ||
            (columnIndex == 1 && strstr(properties[i].City, keyword) != NULL) ||
            (columnIndex == 2 && properties[i].Price == atof(keyword)) ||
            (columnIndex == 3 && properties[i].Rooms == atoi(keyword)) ||
            (columnIndex == 4 && properties[i].Bathrooms == atoi(keyword)) ||
            (columnIndex == 5 && properties[i].CarParks == atoi(keyword)) ||
            (columnIndex == 6 && strstr(properties[i].Type, keyword) != NULL) ||
            (columnIndex == 7 && strstr(properties[i].Furnish, keyword) != NULL)) {
            count++;
        }
    }

    struct Property search_properties[count];
    int result_index = 0;
    for (size_t i = 0; i < max_row; i++) {
        if ((columnIndex == 0 && strstr(properties[i].Location, keyword) != NULL) ||
            (columnIndex == 1 && strstr(properties[i].City, keyword) != NULL) ||
            (columnIndex == 2 && properties[i].Price == atof(keyword)) ||
            (columnIndex == 3 && properties[i].Rooms == atoi(keyword)) ||
            (columnIndex == 4 && properties[i].Bathrooms == atoi(keyword)) ||
            (columnIndex == 5 && properties[i].CarParks == atoi(keyword)) ||
            (columnIndex == 6 && strstr(properties[i].Type, keyword) != NULL) ||
            (columnIndex == 7 && strstr(properties[i].Furnish, keyword) != NULL)) {
            search_properties[result_index] = properties[i];
            result_index++;
        }
    }

    print_csv(search_properties, count);
}

int compareFieldsAsc(const void *a, const void *b) {
    const struct Property *propertyA = (const struct Property *)a;
    const struct Property *propertyB = (const struct Property *)b;

    if (strcmp(gFieldName, "Location") == 0)
        return strcmp(propertyA->Location, propertyB->Location);
    else if (strcmp(gFieldName, "City") == 0)
        return strcmp(propertyA->City, propertyB->City);
    else if (strcmp(gFieldName, "Price") == 0)
        return (propertyA->Price < propertyB->Price) ? -1 : (propertyA->Price > propertyB->Price);
    else if (strcmp(gFieldName, "Rooms") == 0)
        return (propertyA->Rooms < propertyB->Rooms) ? -1 : (propertyA->Rooms > propertyB->Rooms);
    else if (strcmp(gFieldName, "Bathrooms") == 0)
        return (propertyA->Bathrooms < propertyB->Bathrooms) ? -1 : (propertyA->Bathrooms > propertyB->Bathrooms);
    else if (strcmp(gFieldName, "CarParks") == 0)
        return (propertyA->CarParks < propertyB->CarParks) ? -1 : (propertyA->CarParks > propertyB->CarParks);
    else if (strcmp(gFieldName, "Type") == 0)
        return strcmp(propertyA->Type, propertyB->Type);
    else if (strcmp(gFieldName, "Furnish") == 0)
        return strcmp(propertyA->Furnish, propertyB->Furnish);
    else {
        printf("Invalid field name.\n");
        exit(1);
    }
}

int compareFieldsDesc(const void *a, const void *b) {
    const struct Property *propertyA = (const struct Property *)a;
    const struct Property *propertyB = (const struct Property *)b;

    if (strcmp(gFieldName, "Location") == 0)
        return -strcmp(propertyA->Location, propertyB->Location);
    else if (strcmp(gFieldName, "City") == 0)
        return -strcmp(propertyA->City, propertyB->City);
    else if (strcmp(gFieldName, "Price") == 0)
        return (propertyA->Price > propertyB->Price) ? -1 : (propertyA->Price < propertyB->Price);
    else if (strcmp(gFieldName, "Rooms") == 0)
        return (propertyA->Rooms > propertyB->Rooms) ? -1 : (propertyA->Rooms < propertyB->Rooms);
    else if (strcmp(gFieldName, "Bathrooms") == 0)
        return (propertyA->Bathrooms > propertyB->Bathrooms) ? -1 : (propertyA->Bathrooms < propertyB->Bathrooms);
    else if (strcmp(gFieldName, "CarParks") == 0)
        return (propertyA->CarParks > propertyB->CarParks) ? -1 : (propertyA->CarParks < propertyB->CarParks);
    else if (strcmp(gFieldName, "Type") == 0)
        return -strcmp(propertyA->Type, propertyB->Type);
    else if (strcmp(gFieldName, "Furnish") == 0)
        return -strcmp(propertyA->Furnish, propertyB->Furnish);
    else {
        printf("Invalid field name.\n");
        exit(1);
    }
}

void sort_data() {

    struct Property properties[max_row];
    readCSV(filename, properties, max_row);

    char order[50];
    printf("Enter Column you want to sort: ");
    scanf("%s", gFieldName);
    printf("Enter order (asc or desc): ");
    scanf("%s", order);

    if (strcmp(order, "asc") == 0) {
        qsort(properties, max_row, sizeof(struct Property), (int (*)(const void *, const void *))compareFieldsAsc);
    } else if (strcmp(order, "desc") == 0) {
        qsort(properties, max_row, sizeof(struct Property), (int (*)(const void *, const void *))compareFieldsDesc);
    } else {
        printf("wrong order only allow asc or desc\n");
        exit(1);
    }

    print_csv(properties, max_row);
}

void export_to_csv() {

    char new_filename[50];
    printf("Enter filename: ");
    scanf("%s", new_filename);

    FILE *file = fopen(strcat(new_filename, ".csv"), "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    struct Property properties[max_row];
    readCSV(filename, properties, max_row);

    fprintf(file, "Location 1,Location 2,Price,Rooms,Bathrooms,CarParks,Type,Furnish\n");

    for (int i = 0; i < max_row; i++) {
        fprintf(file, "%s,%s,%.2lf,%d,%d,%d,%s,%s\n",
                properties[i].Location,
                properties[i].City,
                properties[i].Price,
                properties[i].Rooms,
                properties[i].Bathrooms,
                properties[i].CarParks,
                properties[i].Type,
                properties[i].Furnish);
    }

    fclose(file);
}

int main() {
    int choice;
    printf("What do you want to do?\n");
    printf("1. Display data\n");
    printf("2. Search Data\n");
    printf("3. Sort Data\n");
    printf("4. Export Data\n");
    printf("5. Exit\n");
    printf("Your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        display_data();
        break;
    case 2:
        search_data();
        break;
    case 3:
        sort_data();
        break;
    case 4:
        export_to_csv();
        break;
    case 5:
        exit(1);
        break;
    default:
        printf("Wrong choice");
        break;
    }

    return 0;
}
