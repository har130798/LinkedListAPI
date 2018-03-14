#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SUCCESS 1
#define FAIL 0

typedef void(*print_type) (void *);
typedef size_t(*get_size) (void *);

typedef struct node {
	void *data;
	struct node * next;
	print_type type;
}node;

typedef struct list {
	struct node * head;
	int size;
}list;

const int size_list = sizeof(list);
const int size_node = sizeof(node);
const int int_size = sizeof(int);

void print_int(void * a) {
	printf("%d ", *(int *)a);
}

void print_string(void * a) {
	printf("%s ", (char *)a);
}

void print_char(void * a) {
	printf("%c ", *(char *)a);
}

void print_float(void * a) {
	printf("%0.2f ", *(float *)a);
}

size_t get_int_size(void *data) {
	return sizeof(int);
}

size_t get_float_size(void *data) {
	return sizeof(float);
}

size_t get_char_size(void *data) {
	return sizeof(char);
}

size_t get_string_size(void *data) {
	size_t size = strlen((char *)data) + 1;
	return size;
}

list * create_list() {
	list * new_list = (list *)malloc(size_list);

	if (new_list == NULL) return NULL;

	new_list->head = NULL;
	new_list->size = 0;

	return new_list;
}

node * create_node(size_t bytes) {
	node * new_node = (node *)malloc(size_node);

	if (new_node == NULL) return NULL;

	new_node->data = (void *)malloc(bytes);
	new_node->next = NULL;
	new_node->type = NULL;

	return new_node;
}

int insert_node(void *data, get_size get_size, print_type type, list **head) {

	int bytes = get_size(data);
	if (*head == NULL) return FAIL;
	if (bytes == 0) return FAIL;
	if (data == NULL) return FAIL;

	node * temp = (*head)->head;
	node * new_node = create_node(bytes);

	if (new_node == NULL) return FAIL;

	new_node->next = temp;

	if (memcpy(new_node->data, data, bytes) == NULL) {
		return FAIL;
	}

	new_node->type = type;
	(*head)->head = new_node;
	(*head)->size++;

	return SUCCESS;
}

int insert_char(char data, list ** head) {
	return insert_node((char *)&data, &get_char_size, &print_char, head);
}
int insert_int(int data, list ** head) {
	return insert_node((int *)&data, &get_int_size, &print_int, head);
}
int insert_float(float data, list ** head) {
	return insert_node((float *)&data, &get_float_size, &print_float, head);
}
int insert_string(char * data, list ** head) {
	return insert_node((char *)data, &get_string_size, &print_string, head);
}
void display(list ** head) {
	node * temp = (*head)->head;

	while (temp != NULL)
	{
		temp->type(temp->data);
		temp = temp->next;
	}
	printf("\n");
}
