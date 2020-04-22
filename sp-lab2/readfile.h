#define MAXNAME 64
#define MAXEMPLOYEE 1024

struct person {
    char first_name[MAXNAME], last_name[MAXNAME];
    int id, salary;
}employee;

int open_file(char *filename){
    if(fopen(filename, "r") == NULL)
    return -1;
    return 0;
}

int read_int(int *address){
    if(scanf("%d", address) == 0)
    return -1;
    return 0;
}

int read_float(float *address){
    if(scanf("%f", address) == 0)
    return -1;
    return 0;
}

int read_string(char *address){
    if(scanf("%s", address) == 0)
    return -1;
    return 0;
}

void close_file(FILE *filename){
    fclose(filename);
}
/*soring by id in a struct*/
int IDcompare(const void *a, const void *b)
{
        struct person *c = (struct person*) a;
        struct person *d = (struct person*) b;
        return c->id - d->id;
}
/*binary search function using recursion method*/
int binary_search(const int array[], int l, int r,int value){
    if (r >= l){
        int mid = l + (r - l)/2;
        if (array[mid] == value)
            return mid;
        if (array[mid] > value)
            return binary_search(array, l, mid-1, value );
        else
            return binary_search(array, mid+1, r, value);
    }
    return -1;
}

/*print employee by key*/
void print_by_key(struct person employee[MAXEMPLOYEE], int key){
     printf("---------------------------------------------------\n");
     printf("First_name     Last_name      SALARY     ID\n");
     printf("%-10s %-10s %10d %10d \n", employee[key].first_name, employee[key].last_name, employee[key].salary, employee[key].id);
     printf("---------------------------------------------------\n");
}
/*search last name function*/
int search_lastname(struct person employee[MAXNAME],int numEmployee, char last_name[]){
    for (int i= 0; i< numEmployee; i++){
        if(strcasecmp(employee[i].last_name, last_name) ==0){    //call strcasecmp function;
            return i;
        }
    }
    return -1;
}
/*matching last name function*/
void match_last_name(struct person employee[MAXNAME], int numEmployee, char last_name[]){
    int key1 = search_lastname(employee, numEmployee, last_name);
    if(key1 == -1){
        printf("Employee with last name %s is not found in DB\n",last_name);
    }
    else{
        printf("---------------------------------------------------\n");
        printf("First_name     Last_name      SALARY     ID\n");
        for(int i = 0; i<numEmployee; i++)
            if(strcasecmp(employee[i].last_name, last_name) == 0)
        printf("%-10s %-10s %10d %10d \n", employee[i].first_name, employee[i].last_name, employee[i].salary, employee[i].id);
        printf("---------------------------------------------------\n");
    }
}
/*delete an employee by key*/
void delete_by_key(struct person *pointer, int numEmployee, int key){
    struct person employee[MAXNAME];
    for(int i = 0; i< numEmployee; i++){
        strcpy(employee[i].first_name, pointer->first_name);
        strcpy(employee[i].last_name, pointer->last_name);
        employee[i].salary = pointer->salary;
        employee[i].id = pointer->id;
        pointer++;
    }
    for(int i =0; i<numEmployee; i++)
    pointer--;

    for(int k =0; k< numEmployee-1; k++){
        if(k >= key){
            int nextindex = k+1;
            strcpy(pointer->first_name, employee[nextindex].first_name);
            strcpy(pointer->last_name, employee[nextindex].last_name);
            pointer->salary = employee[nextindex].salary;
            pointer->id = employee[nextindex].id;        
        }
        pointer++;
    }
    for(int i =0; i<numEmployee-1; i++)
    pointer--;
}
/*update an employee by key*/
void update_by_key(struct person *pointer, int key, char first_name[], char last_name[], int salary){
    for (int k = 0; k< key; k++)
        pointer++;
        strcpy(pointer->first_name, first_name);
        strcpy(pointer->last_name, last_name);
        pointer->salary = salary;
     for (int k = 0; k< key; k++)
     pointer--;
}
/*find highest salary index*/
int highest_salary_index(struct person employee[MAXNAME], int numEmployee){
    int largest = 0;
    for(int i=1; i<numEmployee;i++)
        if(employee[i].salary > employee[largest].salary)
            largest = i;
            return largest;
}
/*print employees with highest salary*/
void print_result(struct person employee[MAXNAME],int numEmployee){
    printf("---------------------------------------------------\n");
    printf("First_name     Last_name      SALARY     ID\n");
    for(int i =0; i<numEmployee;i++)
        printf("%-10s %-10s %10d %10d \n", employee[i].first_name, employee[i].last_name, employee[i].salary, employee[i].id);
    printf("---------------------------------------------------\n");
}