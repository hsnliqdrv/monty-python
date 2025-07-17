#include <stdio.h>
#include <stdlib.h>
#define MAX_CMD_SIZE 256
typedef struct stack_s
{
        int n;
        struct stack_s *prev;
        struct stack_s *next;
} stack_t;

char *_strdup(char *src)
{
	char *dest;
	int l = 0, i;

	while (src[l])
		l++;
	dest = malloc(l + 1);
	for (i = 0; i < l; i++)
		dest[i] = src[i];
	dest[l] = '\0';
	return (dest);
}

char **split(char *s, int *count)
{
	char **res, *s2 = _strdup(s);
	int i = 0, c = 0, a = 0;

	while (s[i])
	{
		if (s[i] == ' ')
			c++;
		i++;
	}
	c++;
	res = malloc(sizeof(char *) * c);
	*count = c;
	c = 0;
	i = 0;
	while (s2[i])
	{
		if (s2[i] == ' ')
		{
			s2[i] = '\0';
			res[a] = _strdup(s2 + c);
			a++;
			c = i + 1;
		}
		i++;
	}
	res[a] = _strdup(s2 + c);
	free(s2);
	return (res);
}

stack_t *get(stack_t *ptr, int index)
{
	int i = 0;
	stack_t *p = ptr;
	while (p)
	{
		if (i == index)
		{
			return (p);
		}
		i++;
		p = p->next;
	}
	return (NULL);
}
stack_t *get_last(stack_t *ptr)
{
	stack_t *p = ptr;
	if (!p)
		return (p);
	while (p->next)
		p = p->next;
	return (p);
}

int equals(char *s1, char *s2)
{
	int i = 0;

	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	if (s1[i] != s2[i])
		return (0);
	return (1);
}

int push(stack_t **ptr, int elem)
{
	stack_t *p = malloc(sizeof(stack_t));
	p->n = elem;
	p->next = *ptr;
	p->prev = NULL;
	*ptr = p;
	return (0);
}
int pall(stack_t **ptr)
{
	stack_t *p = *ptr;

	if (!p)
		return (0);
	while (p)
	{
		printf("%d ", p->n);
		p = p->next;
	}
	printf("\n");
	return (0);
}
int pint(stack_t **ptr, int index)
{
	stack_t *p = get(*ptr, index);
	if (!p)
		return (1);
	printf("%d\n", p->n);
	return (0);
}
int pop(stack_t **ptr)
{
	stack_t *p = *ptr;
	if (!p)
		return (1);
	*ptr = p->next;
	free(p);
	return (0);
}
int swap(stack_t **ptr, int i1, int i2)
{
	stack_t *p1 = get(*ptr, i1);
	stack_t *p2 = get(*ptr, i2);
	if (!p1 || !p2)
		return (1);
	int t = p1->n;
	p1->n = p2->n;
	p2->n = t;
	return (0);
}
int add(stack_t **ptr, int elem)
{
	stack_t *p = get_last(*ptr);
	stack_t *p2 = malloc(sizeof(stack_t));
	p2->n = elem;
	p2->prev = p;
	if (!p)
		*ptr = p2;
	else
		p->next = p2;
	p2->next = NULL;
	return (0);
}

int process(stack_t** ptr, char *cmd)
{
	int c, i, res;
	char **arr = split(cmd, &c);

	if (equals(arr[0], "PUSH"))
	{
		if (c != 2)
		{
			printf("PUSH: wrong usage\n");
			res = 1;
		}
		else
			res = push(ptr, atoi(arr[1]));
	}
	else if (equals(arr[0], "PALL"))
	{
                if (c != 1)
		{
                        printf("PALL: wrong usage\n");
			res = 1;
		}
		else
                	res = pall(ptr);
	}
	else if (equals(arr[0], "PINT"))
	{
                if (c != 2)
		{
                        printf("PINT: wrong usage\n");
			res = 1;
		}
		else
                	res = pint(ptr, atoi(arr[1]));
	}
	else if (equals(arr[0], "POP"))
	{
                if (c != 1)
		{
                        printf("POP: wrong usage\n");
			res = 1;
		}
		else
                	res = pop(ptr);
	}
	else if (equals(arr[0], "SWAP"))
	{
                if (c != 3)
		{
                        printf("SWAP: wrong usage\n");
			res = 1;
		}
		else
                	res = swap(ptr, atoi(arr[1]), atoi(arr[2]));
	}
	else if (equals(arr[0], "ADD"))
	{
                if (c != 2)
		{
                        printf("ADD: wrong usage\n");
			res = 1;
		}
		else
			res = add(ptr, atoi(arr[1]));
	}
	else
	{
		printf("\"%s\" is not a command\n", arr[0]);
		res = 1;
	}
	for (i = 0; i < c; i++)
		free(arr[i]);
	free(arr);
	return (res);
}

int main(int argc, char **argv)
{
	int i;
	int line = 0;
	FILE *fptr;
	char cmd[MAX_CMD_SIZE];
	stack_t* ptr;

	if (argc < 2)
	{
		puts("no file given");
		return (-1);
	}
	fptr = fopen(argv[1], "r");
	if (!fptr)
	{
		puts("could not open file");
		return (-1);
	}
	ptr = malloc(sizeof(stack_t));
	while (fgets(cmd, MAX_CMD_SIZE, fptr))
	{
		for (i = 0; i < 256; i++)
		{
			if (cmd[i] == '\n')
			{
				cmd[i] = '\0';
				break;
			}
		}
		if (process(&ptr, cmd) != 0)
		{
			printf("error in line %d in file %s\n", line + 1, argv[1]);
			return (1);
		}
		line++;
	}
	free(ptr);
	return (0);
}
