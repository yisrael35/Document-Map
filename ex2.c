
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

typedef struct document document;
typedef struct paragraph paragraph;
typedef struct sentence sentence;
typedef struct word word;

// void print_document(struct document );
void print_word( word );
/*yisrael bar 27-31/11/19 */

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;//denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data  ;
    int sentence_count;//denotes number of sentences in a paragraph
};

struct document {
    struct paragraph* data;
    int paragraph_count;//denotes number of paragraphs in a document
};

struct document get_document(char* text) {
int char_length=0,i=0,word_amount=0,paragraph_amount=0,sentence_amount=0;
//count how many chars are there in text
while (text[i]!='\0'){
    char_length++;
    i++;
}
//check quanintiy of each of the following : words, sentence , paragraph
i=0;
while (i<=char_length)
{
    //count the words
    if (text[i]==' '||text[i]=='.')
    {
        if(text[i-1]=='.'){}
        else 
        word_amount++;
    }
    //count the paragraph
    if (text[i]=='\n'||text[i]=='\0')
    {
        paragraph_amount++;
    }//count the sentence
    if (text[i]=='.')
    {
        sentence_amount++;
    }
    i++;
}

// printf("%d %d %d %d \n",char_length,word_amount, sentence_amount,paragraph_amount  );
//createing the arrays of each of the following : words, sentence , paragraph
paragraph *par=(paragraph*)malloc(paragraph_amount*sizeof(paragraph));
if(par==NULL)exit(1);
sentence *sen=(sentence*)malloc(sentence_amount*sizeof(sentence));
if(sen==NULL)exit(1);
word *wor=(word*)malloc(word_amount*sizeof(word));
if(wor==NULL)exit(1);

//fill the array of words
int j=0,word_count=0,char_count=0,word_per_sen=0 ,k=0;
for ( i = 0; text[i]!='\0'; i++)
{
if (text[i]==' ' || text[i]=='.')
    {
        if(text[i-1]=='.'){}
        else {
      while(text[j]==' ' || text[j]=='\n'|| text[j]=='.'||text[j]=='\r') 
     j++;
     //build a single word
   char* w0=(char*)malloc((i-j)*sizeof(char));//take2
    for (char_count=0; j<i; j++,char_count++)
    {
     if(   text[j]=='\n' )j++;
    w0[char_count]=text[j];//take2
    }
      word ww={w0};//take2
      wor[word_count]= ww;//take2
      word_count++;
      word_per_sen++;
    //update the word count in a sentence
        if(text[i]=='.'){
        sen[k].word_count=word_per_sen;
        // printf("word_per_sen: %d ",sen[k].word_count);
        k++;
        word_per_sen=0;
        }
        }
    } 

 
}

//fill the sentence array
// j=0,k=0;
// int sentence_count=0,sen_per_par=0,counter=0,temp=0;
// for ( i = 0; text[i]!='\0'; i++)
// {
//         if (text[i]==' ' || text[i]=='.' ){
//              if(text[i-1]=='.'){
//             }else
//              counter++;
//         }
//         if(text[i]=='.'){
//        word* w1=(word*)malloc((counter)*sizeof(word));//take2
//        temp=counter;
//         counter+=j;
//         for ( int h=0; j < counter; j++,h++)
//         {
//                 w1[h]=wor[j];//take2
//         }
//         sentence s1={w1,temp};//take2
//         sen[sentence_count]=s1;//take2
//         counter=0;
//         sentence_count++;
//         sen_per_par++;
//         }  
//         if (text[i]=='\n'||text[i]=='\0')
//           {
//         par[k].sentence_count=sen_per_par;
//         sen_per_par=0;
//         k++;
//              }
// }
///////////////xxxxxxxxxxxxx/////
//fill the sentence array
 j=0,k=0;
    for (i=0; i<sentence_amount;i++){
        //build a single sentence
    word *w1=(word*)malloc((sen[i].word_count)*sizeof(word));//take2
    for(int h=0;h< sen[i].word_count; h++,j++){
    w1[h]=wor[j];//take2
    }
    sentence s1={w1,sen[i].word_count};//take2
    sen[i]=s1;
    }
  int  counter=0;
    for(i=0; text[i]!='\0'; i++){
            if ( text[i]=='.' ){
             counter++;
        } 
             if (text[i]=='\n'||text[i]=='\0')
          {
           par[k].sentence_count=counter;
        //    printf("par[k].sentence_count= %d ",par[k].sentence_count= );
           counter=0;
           k++;
             }
           }
    par[k].sentence_count=counter;
///////////////xxxxxxxxxxxxx/////

// sentence ** w2=(sentence*)malloc(paragraph_amount*sizeof(sentence));//take1
//fill the paragraph
// j=0,counter=0;
// int paragraph_count=0;
// for ( i = 0; text[i]!='\0'; i++)
// {
//     if(text[i]=='.') counter++;
//     if(text[i]=='\n'||text[i]=='\0'){
//     //  w2[paragraph_count]=(sentence*)malloc((i-j)*sizeof(sentence));//take1
//     sentence *se=(sentence*)malloc((counter)*sizeof(sentence));//take2
//     counter+=j;
//     for (int h=0 ; j < counter; j++){
//     //  w2[paragraph_count][h]=sen[j];//take1
//     se[h]=sen[j];//take2
//     }
//     // sen[paragraph_count].data=w2[paragraph_count];//take1
//     paragraph p1={se,counter};//take2
//     par[paragraph_count]=p1;
//     paragraph_count++;
//     counter=0;
//     }
// }
/////////////
//fill the paragraph
j=0;
    for (i=0; i<paragraph_amount;i++){
        //build a single paragraph
    sentence *se=(sentence*)malloc((par[i].sentence_count)*sizeof(sentence));//take2
    // printf(" sentence_count %d\n",par[i].sentence_count);
    for(int h=0;h< par[i].sentence_count; h++,j++){
    se[h]=sen[j];//take2
    }
    paragraph p1={se,par[i].sentence_count};//take2
    // printf("paragraph_amount %d", paragraph_amount);

    par[i]=p1;
    }
    //////////////////////

document doc={par,paragraph_amount};
////print check//
// printf("check\n");
//     for(i=0; i<doc.paragraph_count; i++){
//         for(j=0; j< doc.data[i].sentence_count; j++){
//             for(k=0; k< doc.data[i].data[j].word_count;k++){
//                 print_word(doc.data[i].data[j].data[k]);
//                 if(k!=doc.data[i].data[j].word_count-1)
//                 printf(" ");
//             }printf(".");
//         }printf("\n");
//     }
    
// printf("check end \n");
////print//

return doc;
}
struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) {
    return Doc.data[n-1].data[m-1].data[k-1];
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) { 
    return Doc.data[m-1].data[k-1];
}

struct paragraph kth_paragraph(struct document Doc, int k) {
    return Doc.data[k-1];
}

void print_word(struct word w) {
    printf("%s", w.data);
}


void print_sentence(struct sentence sen) {
    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if(i!=sen.word_count-1){
            printf(" ");
        }
        
    }
}

void print_paragraph(struct paragraph para) {
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
            printf(". ");
    }
}

void print_document(struct document doc) {
    for(int i = 0; i < doc.paragraph_count-1; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
}

char* get_input_text() {    
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    scanf("%*c");
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]c", p[i]); 
        scanf("%*c");
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}
int main() 
{
    char* text = get_input_text();
    struct document Doc = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else{
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }   
    //doing free to all the arrays
        for(int i=0; i<Doc.paragraph_count; i++){
          for(int j=0; j< Doc.data[i].sentence_count; j++){
            for(int k=0; k< Doc.data[i].data[j].word_count;k++){
               free(Doc.data[i].data[j].data[k].data);
            }
        }
    }
        for(int i=0; i<Doc.paragraph_count; i++){
          for(int j=0; j< Doc.data[i].sentence_count; j++){
               free(Doc.data[i].data[j].data);
        }
    }    
        free(Doc.data);
}     


