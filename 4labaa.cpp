#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};


struct Node* CreateTree(struct Node* root, struct Node* r, int data)
{
    if (r == NULL)
    {
        r = (struct Node*)malloc(sizeof(struct Node));
        if (r == NULL)
        {
            printf("Ошибка выделения памяти\n");
            exit(1);
        }
        r->left = NULL;
        r->right = NULL;
        r->data = data;
        if (root == NULL) return r;
        if (data > root->data)
            root->left = r;
        else
            root->right = r;
        return r;
    }

    if (data > r->data)
        CreateTree(r, r->left, data);
    else
        CreateTree(r, r->right, data);
    return root;
}

void print_tree(struct Node* r, int l)
{
    if (r == NULL) return;
    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++)
        printf("    ");
    printf("%d ур %d\n", r->data, l);
    print_tree(r->left, l + 1);
}

int FindAll(struct Node* r, int value, int level)
{
    if (r == NULL) return 0;
    int count = 0;
    if (r->data == value)
    {
        printf("Значение %d найдено на уровне %d\n", value, level);
        count++;
    }
    count += FindAll(r->left, value, level + 1);
    count += FindAll(r->right, value, level + 1);
    return count;
}

int CountValue(struct Node* r, int value, int level)
{
    if (r == NULL) return 0;
    int count = 0;
    if (r->data == value)
    {
        printf("Значение %d уровень %d\n", value, level);
        count++;
    }
    count += CountValue(r->left, value, level + 1);
    count += CountValue(r->right, value, level + 1);
    return count;
}

void FreeTree(struct Node* r)
{
    if (r == NULL) return;
    FreeTree(r->left);
    FreeTree(r->right);
    free(r);
}

void WaitEnter()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    printf("\nНажмите Enter для возврата в меню");
    getchar();
}

int main()
{
    setlocale(LC_ALL, "");
    struct Node* root = NULL;
    int choice, D;

    while (1)
    {
        system("cls");

        printf("1 - Построить дерево\n");
        printf("2 - Вывести дерево \n");
        printf("3 - Найти значение \n");
        printf("4 - Подсчитать вхождения значения \n");
        printf("0 - Выход\n");
        printf("Введите число: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Некорректный ввод\n");
            WaitEnter();
            continue;
        }

        switch (choice)
        {
        case 1:
            printf("-1 - окончание построения дерева\n");
            while (1)
            {
                printf("Введите число: ");
                if (scanf("%d", &D) != 1)
                {
                    while (getchar() != '\n');
                    continue;
                }
                if (D == -1) break;
                root = CreateTree(root, root, D);
            }
            printf("Построение дерева окончено\n");
            break;

        case 2:
            if (root == NULL) printf("Дерево пусто\n");
            else print_tree(root, 0);
            break;

        case 3:
        {
            int v;
            printf("Введите значение для поиска: ");
            if (scanf("%d", &v) != 1) { while (getchar() != '\n'); break; }
            if (root == NULL)
            {
                printf("Дерево пусто\n");
                break;
            }
            int found = FindAll(root, v, 0);
            if (found == 0)
                printf("Значение %d не найдено\n", v);

            break;
        }

        case 4:
        {
            int v;
            printf("Введите значение для подсчёта: ");
            if (scanf("%d", &v) != 1) { while (getchar() != '\n'); break; }
            if (root == NULL)
            {
                printf("Дерево пусто\n");
                break;
            }
            int c = CountValue(root, v, 0);
            if (c == 0)
                printf("Значение %d не встречается\n", v);
            else
                printf("Значение %d встречается %d раз(а)\n", v, c);
            break;
        }

        case 0:
            FreeTree(root);
            return 0;

        default:
            printf("Нет такого пункта меню\n");
        }

        WaitEnter();
    }
}