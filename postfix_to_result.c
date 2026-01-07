#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct Stack
{
    Node *top;
} Stack;

Stack *createStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

int isEmpty(Stack *stack)
{
    return stack->top == NULL;
}

void push(Stack *stack, int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = stack->top;
    stack->top = newNode;
}

int pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        return 0;
    }
    Node *temp = stack->top;
    int data = temp->data;
    stack->top = stack->top->next;
    free(temp);
    return data;
}

int peek(Stack *stack)
{
    if (isEmpty(stack))
    {
        return 0;
    }
    return stack->top->data;
}

void printStackAll(Stack *stack, int markedValue)
{
    if (isEmpty(stack))
    {
        printf("-");
        return;
    }

    Node *temp = stack->top;
    int isFirst = 1;

    int values[100];
    int count = 0;

    while (temp != NULL)
    {
        values[count++] = temp->data;
        temp = temp->next;
    }

    for (int i = count - 1; i >= 0; i--)
    {
        if (!isFirst)
        {
            printf(", ");
        }

        if (values[i] == markedValue && i == 0)
        {
            printf("(%d)", values[i]);
        }
        else
        {
            printf("%d", values[i]);
        }
        isFirst = 0;
    }
}

void printStack(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("-");
        return;
    }

    Node *temp = stack->top;
    int isFirst = 1;

    int values[100];
    int count = 0;

    while (temp != NULL)
    {
        values[count++] = temp->data;
        temp = temp->next;
    }

    for (int i = count - 1; i >= 0; i--)
    {
        if (!isFirst)
        {
            printf(", ");
        }
        printf("%d", values[i]);
        isFirst = 0;
    }
}

int isOperator(char ch)
{
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^');
}

int cal(int operand1, int operand2, char operator)
{
    switch (operator)
    {
    case '+':
        return operand1 + operand2;
    case '-':
        return operand1 - operand2;
    case '*':
        return operand1 * operand2;
    case '/':
        return operand1 / operand2;
    case '^':
        return pow(operand1, operand2);
    default:
        return 0;
    }
}

int PostfixConvert(char *postfix)
{
    Stack *stack = createStack();
    int i = 0;
    int step = 1;
    printf("\n");
    printf("%-10s %-15s %-30s\n", "Step", "Symbol", "Stack");
    printf("-------------------------------------------------------\n");

    while (postfix[i] != '\0')
    {
        char current = postfix[i];

        if (current == ' ')
        {
            i++;
            continue;
        }

        if (isdigit(current))
        {
            int num = 0;

            while (postfix[i] != '\0' && isdigit(postfix[i]))
            {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }

            push(stack, num);

            printf("%-10d %-15d ", step, num);
            printStack(stack);
            printf("\n");

            step++;
            continue;
        }
        else if (isOperator(current))
        {
            int operand2 = pop(stack);
            int operand1 = pop(stack);

            int result = cal(operand1, operand2, current);

            push(stack, result);

            printf("%-10d %-15c ", step, current);
            printStackAll(stack, result);
            printf("\n");

            step++;
        }

        i++;
    }

    printf("-------------------------------------------------------\n");

    int result = pop(stack);

    while (!isEmpty(stack))
    {
        pop(stack);
    }
    free(stack);

    return result;
}

int main()
{
    char postfix[100];

    printf("Postfix:");

    fgets(postfix, sizeof(postfix), stdin);

    postfix[strcspn(postfix, "\n")] = '\0';

    int result = PostfixConvert(postfix);

    printf("Result: %d\n", result);

    return 0;
}