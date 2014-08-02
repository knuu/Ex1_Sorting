#include <stdio.h>

#define MAX_LINE 512
#define MAX_DATA 50
#define MIN_DATA 1
#define MAX_NUMBER 9999
#define MIN_NUMBER 1
#define MAX_OUTPUT 10

int input(int num[]);
void output(int num[], int size);
int partition(int num[], int left, int right);
void quicksort(int num[], int n);
void quicksort1(int num[], int left, int right);
void swap (int *x, int *y);

int main(void)
{
  int num[MAX_LINE], size;
  size = input(num);
  printf("入力された数列\n");
  output(num, size);
  quicksort(num, size);
  printf("ソート後の数列\n");
  output(num, size);
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

void quicksort(int num[], int n) /*mainで入力をバブルソートと同じ形式にする*/
{
  quicksort1(num,0,n - 1);
}

void quicksort1(int num[], int left, int right) /*クイックソート本体*/
{
  int pivot;
  
  if (left >= right) /*要素数が１個の時はソートを終了*/
    {
      return;
    }

  /*列を２つに分割*/
  pivot = partition(num,left,right);

  /*分割の右と左で再帰的にクイックソートをする*/
  quicksort1(num, left, pivot - 1);
  quicksort1(num, pivot + 1, right);
}

int partition(int num[], int left, int right) {
  int i, j, pivot,mid;
  i = left;
  j = right - 1;

  /*3つの数を取り、その中央値を基準にとる*/
  mid = (left + right) / 2;
  if ((num[left] < num[mid] && num[mid] < num[right]) || (num[right] < num[mid] && num[mid] < num[left])) 
    {
      swap(&num[mid],&num[right]);
    }
  if ((num[right] < num[left] && num[left] < num[mid]) || (num[mid] < num[left] && num[left] < num[right]))
    {
      swap(&num[left],&num[right]);
    }      
  pivot = num[right];

  /*分割を行う部分*/
  for ( ; ;i++,j--) {

    /*iを右に移動*/
    while (num[i] < pivot) { 
      i++;
    }
    
    /*jを左に移動*/
    while (i < j && num[j] > pivot) {
      j--;
    }

    /*iとjがぶつかれば終了*/
    if (i >= j) {
      break;
    }

    /*iとjを交換*/
    swap(&num[i],&num[j]);
  }

  /*基準とiを交換*/
  swap(&num[i],&num[right]);
  return i;
}

void swap (int *x, int *y) /*要素を交換する関数*/
{
  int temp = *x;
  *x = *y;
  *y = temp;
}
