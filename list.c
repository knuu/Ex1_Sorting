#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 512
#define MAX_NUMBER 9999
#define MIN_NUMBER 1
#define QUANTITY 10

struct listelem {
  int                 data;
  struct listelem     *next;
};

void input(struct listelem *top);
void print_list(struct listelem *top);
struct listelem *insert(struct listelem *top, int n);
struct listelem *delete(struct listelem *top, int n);
struct listelem *insert_list(struct listelem *l);
struct listelem *delete_list(struct listelem *l);
void free_list(struct listelem *l);

int main(void) {
  
  struct listelem *l = (struct listelem *) malloc(sizeof(struct listelem));
  
  input(l);
  
  printf("入力された数のリスト\n");
  print_list(l);
  
  printf("挿入を開始します\n");
  l = insert_list(l);

  printf("続いて、要素の削除を行います\n");
  l = delete_list(l);
  
  free_list(l);
  return 0;
}

void input(struct listelem *top) {
  
  int count; /* 入力した数字の数をカウント */
  int input_num; /* 入力された数字 */
  char array[MAX_LINE];
  struct listelem *search = top;
  
  printf("自然数を%dから%dの自然数で%d個入力して下さい\n", MIN_NUMBER, MAX_NUMBER, QUANTITY);
  printf("入力が自然数でない場合は、小数部分は切り捨てられます。\n");
  printf("文字や範囲外の整数は記録されないので注意してください。\n");
  for (count = 0; count < QUANTITY; count++) {
    printf("%d 個目の数字\n", count + 1);
    input_num = MIN_NUMBER - 1;
    fgets(array, sizeof(array), stdin);
    sscanf(array, "%d", &input_num);
    if (input_num < MIN_NUMBER || MAX_NUMBER < input_num) {
      printf("数字が範囲外、または、文字等が入力されたため、リストには記録されませんでした。\n");
      count--;
    } else if (count == 0) {
      search->data = input_num;
    } else {
      search->next = (struct listelem *) malloc(sizeof(struct listelem));
      search = search->next;
      search->data = input_num;
    }
  }
}

void print_list(struct listelem *top) {
  struct listelem *search = top;
  while (search != NULL) {
    printf("%d ", search->data);
    search = search->next;
  }
  printf("\n");
}

struct listelem *insert_list(struct listelem *l) {
  int i,n;
  char array[MAX_LINE];
  struct listelem *top = l;
  printf("挿入したい自然数を%dから%dの自然数で入力して下さい\n", MIN_NUMBER, MAX_NUMBER);
  printf("入力が自然数でない場合は、小数部分は切り捨てられます\n");
  printf("文字や範囲外の整数は挿入されないので注意してください\n");
  for (i = 0; i < QUANTITY; i++) {
    n = MIN_NUMBER - 1;
    printf("%d 個目の入力\n", i + 1);  
    fgets(array, sizeof(array), stdin);
    sscanf(array, "%d", &n);  
    if (n < MIN_NUMBER || MAX_NUMBER < n) {
      printf("数字が範囲外、または、文字等が入力されたため、挿入されませんでした。\n");
      i--;
    } else {
      top = insert(n, top);
      print_list(top);
    }
  }
  return top;
}

struct listelem *delete_list(struct listelem *l) {
  int i,n;
  char array[MAX_LINE];
  struct listelem *top = l;
  printf("削除したい自然数を%dから%dの自然数で入力して下さい\n", MIN_NUMBER, MAX_NUMBER);
  printf("入力が自然数でない場合は、小数部分は切り捨てられます\n");
  i = 0;
  while (i < QUANTITY) {
    n = MIN_NUMBER - 1;
    printf("%d 個目の入力\n", i + 1);  
    fgets(array, sizeof(array), stdin);
    sscanf(array, "%d", &n);  
    if (n < MIN_NUMBER || MAX_NUMBER < n) {
      printf("数字が範囲外、または、文字等は削除の対象にはなりません\n");
    } else {
      top = delete(n, top);
      print_list(top);
      i++;
    }
  }
  return top;
}

struct listelem *insert(struct listelem *top, int n) {
  struct listelem *prev = NULL, *search = top;
  while (search != NULL && n > search->data) {
    prev = search;
    search = search->next;
  } 
  
  struct listelem *insert_l = (struct listelem *) malloc(sizeof(struct listelem));
  insert_l->data = n;
  insert_l->next = search;
  if (prev == NULL) {
    /* 先頭の場合、先頭が変わる */
    return insert_l;
  } else {
    /* 先頭以外の場合、付け替える */
    prev->next = insert_l;
    return top;
  }
}

struct listelem *delete(struct listelem *top, int n) {
  struct listelem *prev = NULL,*search = top, *temp;
  while (search != NULL) {
    while (search != NULL && search->data != n) {
      prev = search;
      search = search->next;
    }
    if (search == NULL) break;
    if (prev == NULL) {
      temp = search;
      search = search->next;
      top = search;
      free(temp);
    } else {
      temp = search;
      search = search->next;
      prev->next = search;
      free(temp);
    }
  }
  return top;
}

void free_list(struct listelem *l) {
  struct listelem *temp;
  while (l != NULL) {
    temp = l;
    l = l->next;
    free(temp);
  }
}
