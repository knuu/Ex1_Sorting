#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 512
#define MAX_DATA 50
#define MIN_DATA 1
#define MAX_NUMBER 9999
#define MIN_NUMBER 1
#define MAX_OUTPUT 10

struct listelem {
  int                 data;
  struct listelem     *next;
};

int input(struct listelem *l);
void output(struct listelem *l, int size);
struct listelem *insertsort(struct listelem *l, int size);
struct listelem *insert(struct listelem *top, int n);
void free_list(struct listelem *top);

int main(void)
{
  int size;
  struct listelem *l = (struct listelem *) malloc(sizeof(struct listelem));
  
  /* 入力 */
  size = input(l);
  printf("入力された数列\n");
  output(l, size);
  /* 挿入ソート */
  l = insertsort(l, size);
  /* 出力 */
  printf("ソート後の数列\n");
  output(l, size);
  
  free_list(l);
  return 0;
}

int input(struct listelem *l) /* 入力用の関数 */
{
  int count = 0; /* 配列数をカウント */
  int input_num; /* 入力された数字 */
  char array[MAX_LINE]; /* 入力した数字 */
  struct listelem *search = l;
	
  printf("ソートしたいデータを%dから%dの自然数(半角)で入力して下さい\n", MIN_NUMBER, MAX_NUMBER);
  printf("入力が自然数でない場合は、小数部分は切り捨てられます。\n");
  printf("文字や範囲外の整数、全角数字などは記録されないので注意してください。\n");
  printf("データは%d個までにしてください。\n", MAX_DATA);
  printf("データ入力を終わりたい時は、/を入力してください。\n");
	
  while (count < MAX_DATA) {
    printf("%d 個目の数字\n", count + 1);
    fgets(array, sizeof(array), stdin);
    if (*array == '/') {
      /* "/"が入力されたら、データ入力を終了 */
      printf("入力を%d個で終了します。\n", count + 1);
      count++;
      break;
    }
		
    input_num = MIN_NUMBER - 1;
    sscanf(array, "%d", &input_num);
    if (input_num < MIN_NUMBER || MAX_NUMBER < input_num) {
      printf("数字が範囲外、または、文字等が入力されたため、ソートデータには記録されませんでした。\n");
    } else if (count == 0) {
      search->data = input_num;
      count++;
    } else {
      search->next = (struct listelem *) malloc(sizeof(struct listelem));
      search = search->next;
      search->data = input_num;
      printf("%d\n",input_num);
      count++;
      if (count - 1 == MAX_DATA) {
	printf("入力した数字が%d個に達したので、入力を終了します。\n", MAX_DATA);
      }
    }
  }
  return count;
}

void output(struct listelem *l, int size) /* 出力用の関数 */
{
  int i;
  struct listelem *search = l;
  for (i = 0; i < size; i++) {
    if ((i+1) % MAX_OUTPUT == 0) { /* 10個ずつで改行 */
      printf("%4d\n", search->data);
    } else {
      printf("%4d\t", search->data);
    }
    search = search->next;
  }
  printf("\n");
}

struct listelem *insertsort(struct listelem *l, int size) {
  int i;
  struct listelem *search = l, *temp;
  struct listelem *sorted = (struct listelem *) malloc(sizeof(struct listelem));
  sorted->data = search->data;
  search = search->next;
  for (i = 0; i < size - 1; i++) {
    sorted = insert(sorted, search->data);
    temp = search;
    search = search->next;
    free(temp);
  }
  return sorted;
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

void free_list(struct listelem *l) {
  struct listelem *temp;
  while (l != NULL) {
    temp = l;
    l = l->next;
    free(temp);
  }
}
