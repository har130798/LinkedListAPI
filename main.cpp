#include "linked_list.h"

int main() {
	char s[20] = "temporary";
	int i = 35;
	float f = 65.04;
	char c = 'c';
	void * v = NULL;

	list * head = create_list();

	insert_int(i, &head);
	insert_char(c, &head);
	insert_float(f, &head);
	insert_string(s, &head);
	insert_int(++i, &head);
	insert_char(++c, &head);
	strcpy_s(s, 5, "doom");
	insert_string(s, &head);
	display(&head);

	system("pause");
	return 0;
}