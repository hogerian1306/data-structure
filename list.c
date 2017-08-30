typedef struct cell{
  int data;
  struct cell *next;
}LIST;

LIST *initList(void)
{
  return(((LIST *)NULL));
}

//[機能]与えられたリストが空リストかどうか判定
//[引数]*head:リストの先頭へのポインタ
//[返り値]headが空リスト:1,headが空リストではない:0
int isEmptyList(LIST *head)
{
  if(head == ((LIST *)NULL)){
    return(1);
  }else{
    return(0);
  }
}

//[機能]新しいセルをリストの先頭へ挿入する
//[引数]**head:リストへの先頭アドレスを格納している変数へのポインタのポインタ
//　　　　data:リストの先頭へ挿入するセルの整数値データ
//[返り値]追加に成功:1,失敗した:0(元のリストは不変)
int insertHead(LIST **head,int data)
{
  LIST *newcell;
  
  newcell = ((LIST *)malloc(sizeof(LIST)));
  if(newcell == NULL){
    return(0);
  }else{
    newcell->data = data;
    newcell->next = *head;
    *head = newcell;
    return(1);
  }
}

//[機能]リストの先頭セルを削除する
//[引数]**head:リストの先頭アドレスを格納している変数へのポインタのポインタ
//[返り値]正常削除:1,空リストから削除:0
int removeHead(LIST **head)
{
  LIST *buff;

  if(isEmptyList(*head)){
    return(0);
  }else{
    buff = *head;
    *head = (*head)->next;
    free(buff);
    return(1);
  }
}

//[機能]リストに格納されているデータを先頭から順に表示する
//[引数]*head:リストの先頭セルへのポインタ(リストの先頭アドレス)
void printList(LIST *head)
{
  LIST *buff;
  
  for(buff=head;isEmptyList(buff)==0;buff=buff->next){
    if(isEmptyList(buff->next)){
      printf("%d",buff->data);
    }else{
      printf("%d -> ",buff->data);
    }
  }
  return;
}
