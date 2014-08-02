#include <stdio.h>

#define MAX_LINE 512
#define MAX_DATA 50
#define MIN_DATA 1
#define MAX_NUMBER 9999
#define MIN_NUMBER 1
#define MAX_OUTPUT 10

int input(int num[]);
void bubblesort(int num[],int size);
void output(int num[],int size);

int main(void)
{
  int num[MAX_LINE],quant;
  quant = input(num);
  printf("入力された数列\n");
  output(num,quant);
  bubblesort(num,quant);
  printf("ソート後の数列\n");
  output(num,quant);
  return 0;
}

int input(int num[]) /* 入力用の関数 */
{
  int count = 0, input_num; /* 配列数をカウント */
  char array[MAX_LINE]; /* 入力した数字 */

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
    } else {
      num[count] = input_num;
      printf("%d\n",input_num);
      count++;
      if (count - 1 == MAX_DATA) {
	printf("入力した数字が%d個に達したので、入力を終了します。\n", MAX_DATA);
      }
    }
  }
  return count;
}

void bubblesort(int num[], int size) /* バブルソート本体 */
{
  int temp;
  int i,j;
  for (i = size; i > 1; i--) {
    for (j = 0; j < i - 1; j++) {
      if (num[j] > num[j + 1]) { /* XnとXn+1の交換 */
    temp = num[j];
    num[j] = num[j + 1];
    num[j + 1] = temp;
      }
    }
  }
}

void output(int num[],int size) /* 出力用の関数 */
{
  int i;
  for (i = 0; i < size; i++) {
    if ((i+1) % MAX_OUTPUT == 0) { /* 10個ずつで改行 */
      printf("%4d\n", num[i]);
    } else {
      printf("%4d\t", num[i]);
    }
  }
  printf("\n");
}
