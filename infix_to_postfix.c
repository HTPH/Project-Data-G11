#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Node
{
    char data;
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

void push(Stack *s, char c)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = c;
    newNode->next = s->top;
    s->top = newNode;
}

char pop(Stack *s)
{
    if (isEmpty(s))
        return '\0';
    Node *temp = s->top;
    char c = temp->data;
    s->top = temp->next;
    free(temp);
    return c;
}

char peek(Stack *s)
{
    if (isEmpty(s))
        return '\0';
    return s->top->data;
}

int isOperator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

int priority(char c)
{
    if (c == '^')
        return 3;
    if (c == '*' || c == '/')
        return 2;
    if (c == '+' || c == '-')
        return 1;
    return 0;
}

void infixConvert(char infix[], char postfix[])
{
    Stack *stack = createStack();
    int i = 0, j = 0, step = 1;

    char display[200] = "";

    printf("\n%-6s %-8s %-20s\n", "Step", "Symbol", "Stack");
    printf("----------------------------------------\n");

    while (infix[i] != '\0')
    {
        char c = infix[i];

        if (c == ' ')
        {
            i++;
            continue;
        }

        if (isalnum(c))
        {
            postfix[j++] = c;
        }
        else if (c == '(')
        {
            push(stack, c);
        }
        else if (c == ')')
        {
            while (!isEmpty(stack) && peek(stack) != '(')
            {
                postfix[j++] = pop(stack);
            }
            pop(stack);
        }
        else if (isOperator(c))
        {
            while (!isEmpty(stack) &&
                   priority(peek(stack)) >= priority(c))
            {
                postfix[j++] = pop(stack);
            }
            push(stack, c);
        }

        int len = strlen(display);
        display[len] = c;
        display[len + 1] = '\0';

        printf("%-6d %-8c %-20s\n", step++, c, display);

        i++;
    }

    while (!isEmpty(stack))
    {
        postfix[j++] = pop(stack);

        printf("%-6d %-8s %-20s\n", step++, " ", display);
    }

    postfix[j] = '\0';
    printf("----------------------------------------\n");

    free(stack);
}

int main()
{
    char infix[100], postfix[100];
    printf("Infix: ");
    fgets(infix, sizeof(infix), stdin);
    infix[strcspn(infix, "\n")] = '\0';
    infixConvert(infix, postfix);
    printf("\nPostfix: %s\n", postfix);
    return 0;
}
