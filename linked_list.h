#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SUCCESS 1
#define FAIL 0

typedef void(*print_type) (void *);
typedef size_t(*get_size_type) (char, void *);

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

size_t get_size(char type, void *data) {
	size_t size;
	switch (type)
	{
	case 'i': return sizeof(int);
	case 'c': return sizeof(char);
	case 'f': return sizeof(float);
	case 's': size = strlen((char *)data) + 1;
		return size;
	default: return 0;
		break;
	}
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

int insert_node(void *data, char type, get_size_type get_size, list **head) {

	int bytes = get_size(type, data);
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

	print_type cur = NULL;

	switch (type)
	{
	case 'i': cur = &print_int;
		break;
	case 's': cur = &print_string;
		break;
	case 'c': cur = &print_char;
		break;
	case 'f': cur = &print_float;
		break;
	default: cur = NULL;
		break;
	}

	new_node->type = cur;
	(*head)->head = new_node;
	(*head)->size++;

	return SUCCESS;
}

int insert_char(char data, list ** head) {
	return insert_node((char *)&data, 'c', &get_size, head);
}
int insert_int(int data, list ** head) {
	return insert_node((int *)&data, 'i', &get_size, head);
}
int insert_float(float data, list ** head) {
	return insert_node((float *)&data, 'f', &get_size, head);
}
int insert_string(char * data, list ** head) {
	return insert_node((char *)data, 's', &get_size, head);
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
