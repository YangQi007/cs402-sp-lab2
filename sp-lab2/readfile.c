/***************************************************************************************
Copyright: 2020 cs402 sp-lab2
File name: readfile.c
Description: For this lab, you will exapand the functionality of the employee database program
             you developed in Lab #1.
             6.Remove an employee      
             7. Update an employee's information
             8. Print the M employees with the highest salaries
             9. Find all employees with matching last name
Author:YangQi
Version: v3.0
Date: 04/22/2020
History:    <author>    <time>       <version >   <desc>
             YangQi   04/18/2020       v1.0       build this mudual
             YangQi   04/19/2020       v2.0       build functions and header file
             YangQi   04/21/2020       v3.0       debug function8 and function9
**************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "readfile.h"

/*check command line*/
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("you need to enter your filename\n");
        return 0;
    }
    /*define variables and struct*/
    char *filename = argv[1], first_name[MAXNAME], last_name[MAXNAME];
    struct person employee[MAXNAME];
    int choice, employee_id, salary, key, select, M;
    /*check file*/
    int numEmployee = 0, list[MAXEMPLOYEE];
    if (open_file(filename) == -1)
    {
        printf("error: the file cannot be opened\n");
        return -1;
    }
    /*read file*/
    FILE *fp = fopen(filename, "r");
    while (!feof(fp))
    {
        fscanf(fp, "%d %s %s %d\n", &employee[numEmployee].id, &employee[numEmployee].first_name, &employee[numEmployee].last_name,
               &employee[numEmployee].salary);
        numEmployee++;
    }
    fclose(fp);
    qsort(employee, numEmployee, sizeof(struct person), IDcompare);//call qsort() method;
    for (int i = 0; i < numEmployee; i++)
    {
        list[i] = employee[i].id;
    }

    while (1)
    {
        printf("*********************************\n");
        printf("Employee DB Menu:\n");
        printf("*********************************\n");
        printf("(1) Print the Database\n");
        printf("(2) Lookup by ID\n");
        printf("(3) Lookup by Last Name\n");
        printf("(4) Add an Employee\n");
        printf("(5) Quit\n");
        printf("(6) Remove an employee\n");
        printf("(7) Update an employee's information\n");
        printf("(8) Print the M employees with the highest salaries\n");
        printf("(9) Find all employee with matching last name\n");
        printf("*********************************\n");
        printf("Enter your choice: ");
        read_int(&choice);
        /*function1:print the database*/
        if (choice == 1)
        {
            printf("----------------------------------------------\n");
            printf("First_name      Last_name     SALARY    ID\n");
            printf("----------------------------------------------\n");

            for (int i = 0; i < numEmployee; i++)
            {
                printf("%-10s %-10s %10d %10d \n", employee[i].first_name, employee[i].last_name, employee[i].salary,
                       employee[i].id);
            }
            printf("----------------------------------------------\n");
            printf("Number of employees: %d\n", numEmployee);
        }
        /*function2:look up employee by ID*/
        else if (choice == 2)
        {
            printf("enter a 6 digit employee id: ");
            read_int(&employee_id);
            key = binary_search(list, 0, numEmployee, employee_id);//call binary_search() method;
            if (key == -1)
            {
                printf("employee with id %d is Not found\n", employee_id);
            }
            else
                print_by_key(employee, key);
        }
        /*function3:lookup employee by Last name*/
        else if (choice == 3)
        {
            printf("enter employee's lastname:\n");
            read_string(last_name);
            key = search_lastname(employee, numEmployee, last_name);//call search_lastname() method;
            if (key == -1)
                printf("employee with last name %s is Not found\n", last_name);
            else
                print_by_key(employee, key);// call print_by_key() method;
        }
         /*function4:add an employee*/
        else if (choice == 4)
        {
            printf("enter employee's firstname:\n");
            read_string(first_name);
            printf("enter employee's lastname:\n");
            read_string(last_name);
            printf("enter employee's salary(between $30,000 and $150,000):\n");
            read_int(&salary);
            printf("do you want to add the following employee to the DB?\n");
            printf("%s %s, salary: %d \n", first_name, last_name, salary);
            printf("enter 1 for yes, 0 for no\n");
            read_int(&select);
            if (select == 1)
            {
                if ((salary >= 30000) && (salary <= 150000))
                {
                    int last_id = employee[numEmployee - 1].id;
                    int input_id = last_id + 1;
                    strcpy(employee[numEmployee].first_name, first_name);// string copy function;
                    strcpy(employee[numEmployee].last_name, last_name);
                    employee[numEmployee].salary = salary;
                    employee[numEmployee].id = input_id;
                    list[numEmployee] = employee[numEmployee].id;
                    numEmployee++;
                    printf("The new employee has been added!\n");
                }
                else
                {
                    printf("salary is not right,please enter another one.\n");
                }
            }
            else
            {
                printf("don't add this person to DB.\n");
            }
        }
        /*function5:quit*/
        else if (choice == 5)
        {
            printf("goodbye!\n");
            break;
        }
        /*function6:Rremove an employee*/
        else if (choice ==6){
            printf("warning! This operation is going to delete an employee!\n");
            printf("Enter a 6 digit employee id:\n");
            read_int(&employee_id);
            key = binary_search(list, 0, numEmployee, employee_id);
            if(key == -1)
            printf("Employee with id %d is not found in DB\n", employee_id);
            else{
                print_by_key(employee, key);
                printf("Are you really want to delete the employee?\n");
                printf("enter 1 for YES, 0 for NO\n");
                read_int(&select);
                if(select == 1){
                    delete_by_key(employee, numEmployee, key);
                    printf("The employee has been deleted!\n");
                    numEmployee--;
                }
                else {
                    printf("The employee has not deleted.\n");
                }
            }
        }
        /*function7: Update an employee's information*/
        else if (choice == 7){
            printf("enter a 6 digit employee id: ");
            read_int(&employee_id);
            key = binary_search(list, 0, numEmployee, employee_id);//call binary_search() method;
            if (key == -1)
            {
                printf("employee with id %d is Not found\n", employee_id);
            }
            else{
                print_by_key(employee, key);
                printf("Enter the updated employee's first name:");
                read_string(first_name);
                printf("Enter the updated employee's last name:");
                read_string(last_name);
                printf("Enter the updated employee's salary:");
                read_int(&salary);
                printf("Do you want to update the following employee to the DB?\n");
                printf("%s %s, salary: %d \n", first_name, last_name, salary);
                printf("enter 1 for yes, 0 for no\n");
                read_int(&select);
                if (select == 1){
                    update_by_key(employee, key, first_name, last_name, salary);
                    printf("Updated! The updated employee is:\n");
                    print_by_key(employee, key);
                }
                else{
                    printf("The employee has not been updated.\n");
                }

            }
       
        }
        /*function8: Print the M employees with the highest salaries*/
        else if(choice == 8){
            printf("Do you want to print M employees with highest salaries?\n");
            printf("Please enter a value of M:");
            read_int(&M);
            struct person temp[MAXNAME], highest[M];
            int temp_numEmployee = numEmployee;
            
            for(int i = 0; i< numEmployee; i++){
                strcpy(temp[i].first_name, employee[i].first_name);
                strcpy(temp[i].last_name, employee[i].last_name);
                temp[i].salary = employee[i].salary;
                temp[i].id = employee[i].id;
            }
            for(int i= 0; i<M; i++){
                int h = highest_salary_index(temp, temp_numEmployee);// call highest_salary_index()
                strcpy(highest[i].first_name, temp[h].first_name);
                strcpy(highest[i].last_name, temp[h].last_name);
                highest[i].salary = temp[h].salary;
                highest[i].id = temp[h].id;
                delete_by_key(temp, temp_numEmployee, h);
                temp_numEmployee--;
            }
            print_result(highest, M);//print M highest employees;
        }
        /*function9: Find all employees with matching last name*/
        else if(choice == 9){
            printf("Enter the employee's last name:\n");
            read_string(last_name);
            match_last_name(employee, numEmployee, last_name);//call match_last_name() method;
        }
        else{
            printf("The choice %d is not between 1 and 9, try another \n", choice);
            continue;
        }
    }
}

