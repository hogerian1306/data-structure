#define STACK_SIZE 100         //スタック大きさを設定
#define SP (s->sp)             //スタックポインタの参照をSPとする

typedef struct{
    int strage[STACK_SIZE];    //stackのデータ格納領域
    int sp;                    //次に格納するデータ位置(初期値は0)
}STACK;

//[機能]指定されたスタックを初期化する
//[引数]*s:初期化するスタック(ポインタ)  
void initStack(STACK *s)
{
    SP = 0;
    return;
}

//[機能]指定されたスタックにデータを格納する
//[引数]*s:格納対象となるスタック(ポインタ)
//      data:格納するデータ
//[返り値]正常終了:1 ,スタックオーバーフロー:0
int push(STACK *s,int data)
{
    if(SP < STACK_SIZE){
        s -> strage[SP] = data;
        SP++;
        return(1);
    }else{
        return(0);
    }
}

//[機能]指定されたスタックからデータを取り出す
//[引数]*s:取り出し対象となるスタック(ポインタ)
//      data:取り出したデータの格納先(ポインタ)
//[戻り値]正常終了:1 ,スタックアンダーフロー:0
int pop(STACK*s,int *data)
{
 
  if(SP>0){
    SP--;
    *data = s->strage[SP];
    s -> strage[SP] = NULL;
    return(1);
  }else{
    return(0);
  }
}
