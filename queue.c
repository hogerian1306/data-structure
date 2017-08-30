#define Head (q->head)
#define Tail (q->tail)
#define Storage (q->storage)

typedef struct{
  int storage[QUEUE_SIZE];
  int head;
  int tail;
}QUEUE;

//[機能]キューを初期化し、空の状態にする
//[引数]q:初期化するキュー(ポインタ)
void initQueue(QUEUE *q){
  Head = 0;
  Tail = 0;
  return;
}

//[機能]キューにデータを格納する
//[引数]*q:データの格納対象となるキュー(ポインタ)
//      data:格納するデータ
//[返り値]正常終了:1 ,キューが満杯(オーバーフロー):0
int enQueue(QUEUE *q,int data)
{
  if((Tail+1)%(QUEUE_SIZE)==Head){
    return(0);
  }else{
    Storage[Tail] = data;
    Tail = (Tail+1)%(QUEUE_SIZE);
    return(1);
  }
}

//[機能]キューからデータを取り出す
//[引数]*q:データの取り出し対象となるキュー(ポインタ)
//      *data:取り出したデータの格納先(ポインタ)
//[返り値]正常終了:1 ,キューが空(アンダーフロー):0
int deQueue(QUEUE *q,int *data)
{
  if(Head == Tail){
    return(0);
  }else{
    *data = Storage[Head];
    Head = (Head+1)%(QUEUE_SIZE);
    return(1);
  }
}
