#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

// Struct
struct TreeNode {
    char *name;
    int size;
    struct TreeNode* left;
    struct TreeNode* right;
};


// functions for correct inputs
int correct_int_input(){

    int num;

    char *input1 = malloc(128);
    while (1) {
        
        fgets(input1, 128, stdin);
        int valid = 1;
        for (int i = 0; input1[i] != '\0'; i++) {
            if (!isdigit(input1[i]) && !isspace(input1[i])) {
            valid = 0;
            break;
            }
        }   

        if (!valid) {
            printf("Error: Enter only numbers\n> ");
            fflush(stdin);
            continue;
        }
        if (sscanf(input1, "%d", &num) != 1) {
            printf("Errorr: Enter only numbers\n> ");
            fflush(stdin);
            continue;
        }
        free(input1);
        return num;
    }
}

char* correct_str_input(){
    char *text = malloc(256);
    fgets(text, 256, stdin);

    while (strlen(text) > 254) {
        printf("Error: the text is longer than 256 characters! Try again.\n\n");
        printf("Enter a text(256 character max): ");
        fflush(stdin);
        fgets(text, 256, stdin);

    }
    text[strlen(text)-1] = 0;
    return text;
}
//end functions for correct inputs

// works with tree
struct TreeNode* create_node(const char* name, int size) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->name = strdup(name);
    newNode->size = size;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// work with file
void add_f(struct TreeNode **root, struct TreeNode *node){
    if (*root == NULL) {
        *root = node;
        return;
    }

    if ((*root)->left == NULL){
        (*root)->left = node;
        return;
    }

    if ((*root)->right == NULL){
        (*root)->right = node;
        return;
    }

    printf("\nFile system doesn't support more than 2 subojects\n");

}

void print_file_system(struct TreeNode *root, int depth){
    if (root == NULL){
        return;
    }

    for (int i = 0; i<depth; ++i)
    {
        printf("| ");
    }
    printf("# %s [%d bytes]\n", root->name, root->size);
    print_file_system(root->left, depth + 1);
    print_file_system(root->right, depth + 1);

}
#define print_file_system(root) print_file_system(root, 0)
// work with file

//work with Tree
struct TreeNode* find_node(struct TreeNode *root, char *name)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (strcmp(root->name, name) == 0)
    {
        return root;
    }

    struct TreeNode *temp = find_node(root->left, name);
    if (temp)
    {
        return temp;
    }

    temp = find_node(root->right, name);
    if (temp)
    {
        return temp;
    }

    return NULL;
}


void free_subobjects(struct TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }

    free_subobjects(root->left);
    free_subobjects(root->right);

    printf("%s deleted \n", root->name);
    free(root->name);
    free(root);
}   


void delete_object(struct TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }

    printf("Enter name of superobject\n> ");
    struct TreeNode *snode = find_node(root, correct_str_input());

    if (!snode){
        printf("Given object does not exist");
        return;
    }

    printf("Enter name of object: ");

    char *nameNode = correct_str_input();
    
    if (snode->left == NULL){
        printf("\nIncorrectly entered object\n");
        return;
    }

    if (strcmp(snode->left->name, nameNode) == 0){
        free_subobjects(snode->left);
        snode->left = NULL;
        return;
    }

    if (snode->right == NULL){
        printf("Incorrectly entered object");
        return;
    }

    if (strcmp(snode->right->name, nameNode) == 0){
        free_subobjects(snode->right);
        snode->right = NULL;
        return;
    }

    printf("Given object doesn't exist");
}


void input_new_node(struct TreeNode *root)
{
    printf("Enter name of superobject\n> ");
    struct TreeNode *node = find_node(root, correct_str_input());

    if (!node){
        printf("Given object doesn't exist");
        return;
    }
    

    printf("Enter name of object\n> ");
    char *name = correct_str_input();

    struct TreeNode *checkName = find_node(node, name);
    if (checkName){
        printf("\nGiven object already exists\n");
        free(name);
        return;
    }
    printf("Enter size of object (bytes)\n>  ");
    int size = correct_int_input();
    add_f(&node, create_node(name, size));
    free(name);
}

void rotate_to_left(struct TreeNode **node)
{
    if (node == NULL)
    {
        return;
    }

    struct TreeNode *previousNode = *node;
    if (previousNode != NULL && previousNode->right != NULL)
    {
        struct TreeNode *nextRight = previousNode->right;
        struct TreeNode *q = nextRight->left;   // q it's next next left
        nextRight->left = previousNode;
        previousNode->right = q;
        *node = nextRight;
    }
}

void rotate_to_right(struct TreeNode **node)
{
    if (node != NULL)
    {
        struct TreeNode *previousNode = *node;
        if (previousNode != NULL && previousNode->left != NULL)
        {
            struct TreeNode *nextLeft = previousNode->left;
            struct TreeNode *p = nextLeft->right;   //p it's next next right
            nextLeft->right = previousNode;
            previousNode->left = p;
            *node = nextLeft;
        }
    }
}


struct TreeNode *to_line(struct TreeNode *root)
{
    if (root == NULL)
        return NULL;

    while (root->left != NULL)
    {
        rotate_to_right(&root);
    }
    
    struct TreeNode *current = root->right;
    struct TreeNode *previous = root;
    while (current != NULL)
    {
        while (current->left != NULL)
        {
            rotate_to_right(&current);
            previous->right = current;
        }
        previous = current;
        current = current->right;
    }
    return root;
}


void compress(struct TreeNode **root, int times)
{
    struct TreeNode *head = NULL, *prev = NULL;
    struct TreeNode *node = *root;
    for (int i = 0; i < times; i++)
    {
        rotate_to_left(&node);
        if (prev != NULL)
            prev->right = node;
        else
            head = node;
        prev = node;
        node = node->right;
        if (node == NULL)
            break;
    }
    *root = head;
}

int calculate_nodes(struct TreeNode *root){
    if (root == NULL)
    {
        return 0;
    }

    return 1 + calculate_nodes(root->left) + calculate_nodes(root->right);
}


void DSW_Balance(struct TreeNode **root)
{

    *root = to_line(*root);
    int amountNodes = calculate_nodes(*root);

    int level = (int)floor(log2f((float)amountNodes));
    int bottom = amountNodes - ((1 << level) - 1);

    compress(root, bottom);

    for (int i = ((1 << level) - 1) / 2; i > 0; i /= 2)
    {
        compress(root, i);
    }

}

void save_tree(struct TreeNode *root, FILE *file);
struct TreeNode* load_tree(FILE *file);
void free_tree(struct TreeNode *root);

void save_tree(struct TreeNode *root, FILE *file) {
    if (root == NULL)
        return;

    fprintf(file, "%s %d\n", root->name, root->size);
    save_tree(root->left, file);
    save_tree(root->right, file);
}

struct TreeNode* load_tree(FILE *file) {
    char name[256];
    int size;
    if (fscanf(file, "%s %d", name, &size) != 2)
        return NULL;

    struct TreeNode *node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->name = strdup(name);
    node->size = size;
    node->left = load_tree(file);
    node->right = load_tree(file);

    return node;
}

void free_tree(struct TreeNode *root) {
    if (root == NULL)
        return;
    
    free_tree(root->left);
    free_tree(root->right);
    free(root->name);
    free(root);
}


int main() {
    struct TreeNode* root = NULL;

    FILE *file = fopen("filesystem.txt", "r+");

    if (file)
    {
        root = load_tree(file);
        fclose(file);
        file = fopen("filesystem.txt", "wa+");
    }
    else
    {
        root = create_node("ROOT", 0);
        file = fopen("filesystem.txt", "w+");
    }

    while (1)
    {
        printf("\n----FILE SYSTEM MENU-----\n\n");
        printf("\nOptions:\n1 - Create\n2 - Delete\n3 - Print file system\n4 - DSW-Balance\n0 - Exit\n> ");
        int inp = correct_int_input();


        switch (inp) {
            case 1:
                input_new_node(root);
                break;
            case 2:
                delete_object(root);
                break;
            case 3:
                printf("\n\n-----Your File System-----\n\n");
                print_file_system(root);
                break;
            case 4:
                printf("\nYour file system has been sorted\n");
                DSW_Balance(&root);
                break;
            
            case 0:
                puts("Exit...");
                fseek(file, 0, SEEK_SET);
                save_tree(root, file);
                fclose(file);
                free_tree(root);
                return 0;
            default:
                puts("Unknown command");
                break;  
        }   
    }

    return 0;
}