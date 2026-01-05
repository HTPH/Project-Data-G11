#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node
{
    char data[200];
    struct Node *next;
} Node;

typedef struct
{
    Node *top;
} Stack;

Stack *createStack()
{
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

int isEmpty(Stack *s)
{
    return s->top == NULL;
}

void push(Stack *s, const char *str)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->data, str);
    newNode->next = s->top;
    s->top = newNode;
}

char *pop(Stack *s)
{
    if (isEmpty(s))
        return NULL;

    Node *temp = s->top;
    char *value = strdup(temp->data);
    s->top = temp->next;
    free(temp);
    return value;
}

void printStack(Stack *s)
{
    if (isEmpty(s))
    {
        printf("-");
        return;
    }

    char arr[50][200];
    int count = 0;
    Node *temp = s->top;

    while (temp)
    {
        strcpy(arr[count++], temp->data);
        temp = temp->next;
    }

    for (int i = count - 1; i >= 0; i--)
    {
        printf("%s", arr[i]);
    }
}

int isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

void InfixConvert(char *postfix)
{
    Stack *stack = createStack();
    int step = 1;

    printf("\n%-6s %-8s %-25s\n", "Step", "Symbol", "Stack");
    printf("-------------------------------------------------\n");

    for (int i = 0; postfix[i] != '\0'; i++)
    {
        char c = postfix[i];

        if (c == ' ')
        {

            continue;
        }

        if (isalnum(c))
        {
            char s[2] = {c, '\0'};
            push(stack, s);

            printf("%-6d %-8c ", step++, c);
            printStack(stack);
            printf("\n");
        }
        else if (isOperator(c))
        {
            char *right = pop(stack);
            char *left = pop(stack);

            char expr[200];
            sprintf(expr, "(%s%c%s)", left, c, right);
            push(stack, expr);

            printf("%-6d %-8c ", step++, c);
            printStack(stack);
            printf("\n");

            free(left);
            free(right);
        }
    }

    printf("-------------------------------------------------\n");

    char *result = pop(stack);
    if (result != NULL)
    {
        printf("\nPostfix: %s\n", result);
        free(result);
    }

    free(stack);
}

int main()
{
    char postfix[200];

    printf("Postfix: ");
    fgets(postfix, sizeof(postfix), stdin);
    postfix[strcspn(postfix, "\n")] = '\0';

    InfixConvert(postfix);

    return 0;
}
