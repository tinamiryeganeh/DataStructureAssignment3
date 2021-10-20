#include <string.h>
#include <stdio.h>
#include <stdlib.h> // For built-in malloc that returns void *

#include "Dictionary.h"
#include "Enrollment.h"

// create global dictionaries
dictionary CourseDict;
dictionary StudentDict;

// -------------------------------------------
// adds *e to the CourseDict.
// Checks if *e already exists, if so print error message
// and don't update the dictionary.  Else update dictionary.
// -------------------------------------------
void addCourse(course_element *e)
{
	// check if course already exists in dictionary else print message

	// if not, insert to course dict
	if (!find(&CourseDict, e->key))
	{
		insert(&CourseDict, (element *)e);
	}
	else
	{
		printf("Doublicate key!");
	}
}

// -------------------------------------------
// deletes course whose ID/key is c_key from the CourseDict.
// This should check if the course to be deleted exists.
// If not, just print an error message: "Course does not exist."
// If the course exists, then this will also drop students who
// are currently enrolled in the course and then remove course
// from course dict
// -------------------------------------------
void delCourse(char *c_key)
{
	// check if course is in the dict - if not, print error and return
	node_t *canadate = find(&CourseDict, c_key);
	course_value *stuList;
	node_t *head;
	// node_t * temp;
	if (!canadate)
	{
		printf("Course does not exist.");
		return;
	}
	else
	{
		// get course info from the corresponding node
		// loop over the list of students enrolled in course and drop them
		// NOTE: be careful because you are looping over the same list -
		// you are removing elements from
		stuList = canadate->value;
		head = stuList->list;
		while (head != NULL)
		{
			// temp = head;
			head = head->next;
			free(head->prev);
		}
		// delete course with given key from dictionary
		delete (&CourseDict, c_key);
	}
}

// -------------------------------------------
// enrolls student into course. params are s_key and c_key
// Need to check for: existence of course, and if student
// is already enrolled in the course.  Also check if course
// is full or if student has reached max number of courses.
// If there's any error, print a message and don't enroll
// the student.  If there's no errors, update both dictionaries.
// -------------------------------------------
void enroll(char *s_key, char *c_key)
{
	// declare vars for nodes coressponding to course entry and student entry
	// in respective dictionaries
	course_element *courseEntry;
	student_element *studentEntry;

	// decalare vars for course info and student info corresponding to
	// the value fields of each node/element
	// initialize student info to NULL
	course_value *courseInfo;
	student_value *studentInfo = NULL;

	// declare course and student node corresponding to list of courses
	// in a student's node and students in a course's node
	node_t *course;
	node_t *student;

	// fetch course and student corresponding to keys from respective dicts
	// initialize vars depending on whether student/course with given key
	// is in the dictionary
	student = find(&StudentDict, s_key);
	course = find(&CourseDict, c_key);

	// if course doens't exist, print error and return
	if (!course)
	{
		printf("Course Error: Course doens't exist\n");
		return;
	}
	courseInfo = course->value;

	// if student does not exist, insert student to student dict
	if (!student)
	{
		// instantiate a 'student_element' pointer struct and set the fields
		// HINT: you can copy the s_key to the key field of student_element
		// using memcpy
		studentEntry = (student_element *)malloc(sizeof(student_element));
		memcpy(studentEntry->key, s_key, 5);
		// HINT: you will use the 'newNode' function to instantiate a struct for
		// the value field of the element. See newNode implementation in Enrollment.h
		studentEntry->value = (student_value *)newNode('s');
		// the 'value' field of student_element is itself a struct with two fields
		// initialize those fields accordingly
		studentEntry->value->num_courses = 0;
		studentEntry->value->list = (node_t *)malloc(sizeof(node_t));
		studentEntry->value->list->value = NULL;
		studentInfo = studentEntry->value;

		// insert student element in the corresponding dictionary
		// HINT: you will need to cast the student element as (element*). See Dictionary.h
		// HINT: after you insert student element into student dict, assign the value of that
		// (newly inserted node) to the student info that you initialized to NULL in the beginning
		insert(&StudentDict, (element *)studentEntry);
	}
	else
	{
		studentInfo = student->value;
	}

	// check if student is enrolled in the course. If so, print message and return
	// HINT: navigate to the (student) list of the course
	node_t *head = studentInfo->list;
	int alreadyEnrolled = 0;
	if (findList(head, s_key))
	{
		alreadyEnrolled++;
	}

	if (alreadyEnrolled == 1)
	{
		printf("Student successfully enroled\n");
		return;
	}
	if (studentInfo->num_courses >= 2)
	{
		printf("Cannot enroll in more than 2 courses.\n");
		return;
	}

	// see if course is full
	if (courseInfo->num_students >= courseInfo->capacity)
	{
		printf("Course is full!");
		return;
	}

	// if not, add student to the list (of students) in the course
	// HINT: instantiate a new node and assign it to the node corresp.
	// to student in course's list - initialize the node's fields and
	// insert it into the course's list of students enrolled in it
	// and update the course value fields
	else
	{
		node_t *newEntry = (node_t *)malloc(sizeof(node_t));
		newEntry->value = studentInfo;
		insertList(&courseInfo->list, newEntry);
		courseInfo->num_students++;
	}

	// otherwise, add node to the list of student's enrolled courses
	// HINT: again, instantiate a node (this will be the node of a course
	// in a student's list) and intialize the fields of that node
	node_t *newCourseNode = (node_t *)malloc(sizeof(node_t));
	insertList(&(studentInfo->list), newCourseNode);
	newCourseNode->value = courseInfo;
	studentInfo->num_courses++;
}

// -------------------------------------------
// drops a student from course. params are s_key and c_key
// Need to check for: existence of course, and if student
// is enrolled in the course.  If any error is encountered,
// print an error message.
// If there are no errors, update both dictionaries.
// -------------------------------------------
void drop(char *s_key, char *c_key)
{
	// fetch nodes corresponding to student and course from
	// respective dicts having the given keys
	node_t *student = find(&StudentDict, s_key);
	node_t *course = find(&CourseDict, c_key);
	course_element *courseEntry = ((course_element*)course->value);
	student_element *studentEntry = ((student_element*)student->value);
	// if found no such student or course, print message and return
	if (student == NULL || course == NULL)
	{
		return;
	}

		// see if student is enrolled in the course
		// if(studentNode is/(enrolled) in courseList)

		node_t *headCourseList = courseEntry->value->list;
		node_t *headStudentList = studentEntry->value->list;
		// int alreadyEnrolled = 0;
		if (findList(course, c_key))
		{
		// delete course from student list
			deleteList(&headStudentList, student);

		// delete student from course list
			deleteList(&headCourseList, course);

		// update counter fields
		courseEntry->value->num_students--;
		studentEntry->value->num_courses--;
		}
}

// -------------------------------------------
// prints the StudentDict.
// -------------------------------------------
void printStudents()
{
	printf("Students:\n");
	print(&StudentDict);
}

// -------------------------------------------
// prints the CourseDict.
// -------------------------------------------
void printCourses()
{
	printf("Courses:\n");
	print(&CourseDict);
}

// -------------------------------------------
// Don't edit the code below.  This is the driver code to test
// your implementation.
// -------------------------------------------
int main()
{
	char line[100];
	char *command;
	int done = 0;

	course_element *ce;
	student_element *se;

	char *course_key;
	char *student_key;

	// initialize dictionaries
	create(&CourseDict, 20);
	create(&StudentDict, 20);

	// process input
	while (!done)
	{
		// read an entire line as a string
		fgets(line, 100, stdin);

		// pulls command code, assume comma or tab separated
		command = strtok(line, " \t\n\r");
		// printf(" command = %s %d\n", command, strlen(command));
		if (strcmp(command, "ex") == 0)
		{
			printf("Exited Program\n");
			done = 1;
		}
		else if (strcmp(command, "ac") == 0) // add a new course
		{
			// printf("ac\n");

			// Parse and package rest of line into a course_element
			ce = (course_element *)malloc(sizeof(course_element));
			course_key = strtok(NULL, " ");
			printf("Adding course: %s\n", course_key);
			memcpy((*ce).key, course_key, 5);
			ce->value = (void *)newNode('c');
			ce->value->capacity = atoi(strtok(NULL, " "));
			ce->value->num_students = 0;
			ce->value->list = NULL;
			addCourse(ce);
		}
		else if (strcmp(command, "dc") == 0) // delete a course
		{
			course_key = strtok(NULL, " ");
			delCourse(course_key);
			printf("Delete Course Complete\n");
		}
		else if (strcmp(command, "en") == 0) // enroll a student
		{
			// printf("en\n");

			// Parse and package rest of line into a course_element
			student_key = strtok(NULL, " ");
			course_key = strtok(NULL, " ");
			printf("Enrolling student: %s into course: %s\n", student_key, course_key);
			enroll(student_key, course_key);
		}
		else if (strcmp(command, "dr") == 0) // drop a student
		{
			student_key = strtok(NULL, " ");
			course_key = strtok(NULL, " ");
			printf("Dropping student: %s from course: %s\n", student_key, course_key);
			drop(student_key, course_key);
		}
		else if (strcmp(command, "ps") == 0) // print students
			printStudents();
		else if (strcmp(command, "pc") == 0) // print courses
			printCourses();
		else
			printf("Unrecognized command: %2s\n", command);
	}

	return 0;
}