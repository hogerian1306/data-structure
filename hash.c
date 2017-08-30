typedef struct hash_element {	// ハッシュテーブルに格納される一要素
  char *key;			// キー
  char *value;			// キーに対応する値
  struct hash_element *next;	// 次の要素(シノニム)へのポインタ
} HASH_ELEMENT;

typedef struct {		        // ハッシュテーブルはこのデータ型の配列
  int count;			// このエントリを共有するシノニムの数
  HASH_ELEMENT *element;	// 格納する要素(キーと値のペア)へのポインタ
} HASH_ENTRY;

#ifndef TBL_SIZE		
 #define TBL_SIZE 6007		// TBL_SIZE(ハッシュテーブルサイズ)
#endif
#define KEY_LEN 32		// キーの最大サイズ
#define VAL_LEN 256		// 値の最大サイズ

// ハッシュテーブルの初期化（tbl[]の全要素のcountを0に、elementをNULLにする）
//	tbl[]	：ハッシュテーブル
//	tbl_size：ハッシュテーブルのサイズ
//	戻り値	：なし
void initHashTable(HASH_ENTRY tbl[], int tbl_size)
{
  int i;

  for(i=0;i<tbl_size;i++){
    (tbl+i)->count = 0;
    (tbl+i)->element = (HASH_ELEMENT *)NULL;
  }

  return;
}

// キーと値からなる要素を動的に生成する
//	key	：キー
//	value	：キーに対応する値
//	戻り値	：正常に生成できたとき     ＝ 生成した要素へのポインタ
//		：メモリ確保に失敗したとき ＝ NULL
HASH_ELEMENT *makeElement(char *key, char *value)
{
  HASH_ELEMENT *newelement;

  newelement = malloc(sizeof(HASH_ELEMENT));
  newelement->key = malloc(sizeof(char)*KEY_LEN);
  newelement->value = malloc(sizeof(char)*VAL_LEN);

  if(newelement == NULL || newelement->key == NULL || newelement->value == NULL){
    return(NULL);
  }
  strcpy(newelement->key,key);
  strcpy(newelement->value,value);
  newelement->next = (HASH_ELEMENT *)NULL;

  return(newelement);
}

// キーに対応する要素を検索する
//	tbl[]	：ハッシュテーブル
//	key	：検索するキー
//	戻り値	：キーが見つかったとき ＝ キーに対応する要素へのポインタ
//		：キーが見つからなかったとき ＝ NULL
HASH_ELEMENT *searchElement(HASH_ENTRY tbl[], char *key)
{
  HASH_ELEMENT *searchelement;
  int flg,i;
  unsigned int hashvalue;

  hashvalue = hash(key,TBL_SIZE);
  flg = 0;
  if(tbl[hashvalue].count == 0){
    return(NULL);
  }else{
    searchelement = tbl[hashvalue].element;
    while((searchelement != (HASH_ELEMENT *)NULL) && flg == 0){
      if(strcmp(searchelement->key,key) == 0){
	flg = 1;
      }else{
	searchelement = searchelement->next;
      }
    }
  }

  if(flg == 0){
    return(NULL);
  }else{
    return(searchelement);
  }
}

// キーに対応する値のみを取得する
//	tbl[]	：ハッシュテーブル
//	key	：検索するキー
//	戻り値	：キーが見つかったとき       ＝ キーに対応する値（文字列）へのポインタ
//		：キーが見つからなかったとき ＝ NULL
char *getValue(HASH_ENTRY tbl[], char *key)
{
  HASH_ELEMENT *searchelement;

  searchelement = searchElement(tbl,key);

  if(searchelement == NULL){
    return(NULL);
  }else{
    return(searchelement->value);
  }
}

// キーとそれに対応する値からなる要素をハッシュテーブルに挿入する
//	tbl[]	：ハッシュテーブル
//	key	：検索するキー
//	value	：キーに対応する値
//	戻り値	：正常に追加できたとき     ＝ 1
//		：メモリ確保に失敗したとき ＝ 0
int insertElement(HASH_ENTRY tbl[], char *key, char *value)
{
  HASH_ELEMENT *buff;
  unsigned int hashvalue;

  hashvalue = hash(key,TBL_SIZE);

  if(tbl[hashvalue].element == 0){
    tbl[hashvalue].element = makeElement(key,value);
    if(tbl[hashvalue].element == NULL){
      return(0);
    }
    tbl[hashvalue].count = 1;
  }else{
    buff = tbl[hashvalue].element;
    tbl[hashvalue].element = makeElement(key,value);
    if(tbl[hashvalue].element == NULL){
      return(0);
    }
    tbl[hashvalue].element->next = buff;
    tbl[hashvalue].count += 1;
  }
  return(1);
}

// 指定したキーがあればその値を更新し、なければ新たに要素を挿入する
//	tbl[]	：ハッシュテーブル
//	key	：検索するキー
//	value	：キーに対応する値
//	戻り値	：更新または追加できたとき ＝ 1
//		：メモリ確保に失敗したとき ＝ 0
int updateElement(HASH_ENTRY tbl[], char *key, char *value)
{
  HASH_ELEMENT *updatehash;
  int check;
  unsigned int hashvalue;

  updatehash = searchElement(tbl,key);

  if(updatehash == NULL){
    if(insertElement(tbl,key,value) == 0){
      return(0);
    }
  }else{
    strcpy(updatehash->value,value);
  }
  return(1);
}

// キーで要素を検索し、見つかった要素を削除する
//	tbl[]	：ハッシュテーブル
//	key	：検索するキー
//	戻り値	：キーが見つかり要素を削除したとき ＝ 1
//		：キーが見つからなかったとき       ＝ 0
int removeElement(HASH_ENTRY tbl[], char *key)
{

  HASH_ELEMENT *removeelement,*prev;
  int flg,check=1;
  unsigned int hashvalue;

  hashvalue = hash(key,TBL_SIZE);
  flg = 0;
  if(tbl[hashvalue].count == 0){
    return(0);
  }else{
    removeelement = tbl[hashvalue].element;
    prev = removeelement;
    while((removeelement != (HASH_ELEMENT *)NULL) && flg == 0){
      if(strcmp(removeelement->key,key) == 0){
        flg = 1;
      }else{
	prev = removeelement;
	removeelement = removeelement->next;
	check++;
      }
    }
  }

  if(flg == 1){
    prev->next = removeelement->next;
    tbl[hashvalue].count -= 1;
    free(removeelement->key);
    free(removeelement->value);
    free(removeelement);
    return(1);
  }else if(check == 1){
    removeelement = removeelement->next;
    tbl[hashvalue].count -= 1;
  }else{
    return(0);
  }
}

// ハッシュテーブルの要素をすべて削除する（メモリを解放する）
//	tbl[]	：ハッシュテーブル
//	tbl_size：ハッシュテーブルのサイズ
//	戻り値	：なし
void freeHashTable(HASH_ENTRY tbl[], int tbl_size)
{
  int i;
  HASH_ELEMENT *element,*buff;

  for(i=0;i<tbl_size;i++){
    element = (tbl+i)->element;
    while(((tbl+i)->count) != 0){
      if((tbl+i)->count > 1){
        buff = element;
	element = element->next;
      }else{
	buff = element;
      }
      free(buff);
      (tbl+i)->count -= 1;
    }
    free(tbl+i);
  }

  return;

}

// ハッシュテーブルのすべての要素をキーと値のペアで表示する
//	tbl[]	：ハッシュテーブル
//	tbl_size：ハッシュテーブルのサイズ
//	戻り値	：なし
void printHashTable(HASH_ENTRY tbl[], int tbl_size)
{
  int i,count;
  char *value,*key;
  HASH_ELEMENT *element;

  printf("Index  Key                  Value\n");
  printf("-------------------------------------------------------------------------\n");
  for(i=0;i<tbl_size;i++){
    count = tbl[i].count;
    if(count != 0){
      element = tbl[i].element;
      while(element != (HASH_ELEMENT *)NULL){
	printf("%4d:  %-20s %-20s\n",i,(element->key),(element->value));
	element = element->next;
      }
    }
  }

  return;

}

// キーからハッシュ値を求める ELFhash
//	tbl_size：ハッシュテーブルのサイズ
//	戻り値	：ハッシュ値（ハッシュテーブルのサイズを超えない非負整数）
unsigned int hash(unsigned char *key, int tbl_size)
{
  unsigned long hash_value,g;

  hash_value = 0;

  while(*key){
    hash_value = (hash_value<<4)+*key++;
    if(g = hash_value & 0xf0000000){
      hash_value ^= g>>24;
    }
    hash_value &= ~g;
  }
  return(hash_value % tbl_size);
}
