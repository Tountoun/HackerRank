#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

typedef struct word word_t;
typedef struct sentence sentence_t;
typedef struct paragraph paragraph_t;
typedef struct document document_t;

/**
 * struct word - representation type of a word
 * 
 * @data: sequence of chars of the word
*/
struct word {
     char *data;
};

/**
 * struct sentence - representation type of a sentence
 * 
 * @data: an array of words of the sentence
 * @word_count: the number of words in the sentence
*/
struct sentence {
     struct word *data;
     int word_count;
};

/**
 * struct paragraph - representation type of a paragraph
 * 
 * @data: an array of sentences of the paragraph
 * @sentence_count: the number of sentences in the paragraph
*/
struct paragraph {
     struct sentence *data;
     int sentence_count;
};

/**
 * struct document - representation type of a document
 * 
 * @data: an array of paragraphs of the document
 * @paragraph_count: the number of paragraphs in the document
*/
struct document {
     struct paragraph *data;
     int paragraph_count;
};

/**
 * get_document - formats a sequence of chars in different elements
 * corresponding to the document internal structure
 *
 * @text: the sequence of chars to process
 *
 * Return: the corresponding representation of the docuemnt
 */
document_t get_document(char *text)
{
     document_t doc;
     doc.data = (paragraph_t *)malloc(MAX_PARAGRAPHS * sizeof(paragraph_t));
     doc.paragraph_count = 0;

     char *para_tok, *para_save;

     para_tok = strtok_r(text, "\n", &para_save);

     while (para_tok != NULL)
     {
          paragraph_t para;
          para.data = (sentence_t *)malloc(MAX_CHARACTERS * sizeof(sentence_t));
          para.sentence_count = 0;

          char *sen_tok, *sen_save;
          sen_tok = strtok_r(para_tok, ".", &sen_save);
          while (sen_tok != NULL)
          {
               sentence_t sen;
               sen.data = (word_t *)malloc(MAX_CHARACTERS * sizeof(word_t));
               sen.word_count = 0;
               char *word_tok, *word_save;
               word_tok = strtok_r(sen_tok, " ", &word_save);
               while (word_tok != NULL)
               {
                    word_t w;
                    w.data = word_tok;
                    sen.data[sen.word_count] = w;
                    sen.word_count++;
                    word_tok = strtok_r(NULL, " ", &word_save);
               }
               sen.data = realloc(sen.data, sen.word_count * sizeof(word_t));
               para.data[para.sentence_count] = sen;
               para.sentence_count++;
               sen_tok = strtok_r(NULL, ".", &sen_save);
          }
          para.data = realloc(para.data, para.sentence_count * sizeof(sentence_t));
          doc.data[doc.paragraph_count] = para;
          doc.paragraph_count++;
          para_tok = strtok_r(NULL, "\n", &para_save);
     }
     doc.data = realloc(doc.data, doc.paragraph_count * sizeof(paragraph_t));

     return (doc);
}

/**
 * kth_word_in_mth_sentence_of_nth_paragraph - gets the (k th) word in the (m th) sentence
 * in the (n th) paragraph of the document
 *
 * @doc: the document from which the word will be taken
 * @k: the position of the word in its sentence
 * @m: the position of the sentence that contains the word
 * @n: the position of the paragraph that containts the sentence of the word
 *
 * Return: the corresponding representation of the word
 */
word_t kth_word_in_mth_sentence_of_nth_paragraph(document_t doc, int k, int m, int n)
{
     word_t w;
     w = doc.data[n-1].data[m-1].data[k-1];

     return (w);
}

/**
 * kth_sentence_in_mth_paragraph - gets the (k th) sentence in the (m th) paragraph of a
 * document
 *
 * @doc: the document from which the sentence will be taken
 * @k: the position of the sentence in its paragraph
 * @m: the position of the paragraph that contains the sentence
 *
 * Return: the corresponding representation of the sentence
 */
sentence_t kth_sentence_in_mth_paragraph(document_t doc, int k, int m)
{
     sentence_t sen;
     sen = doc.data[m-1].data[k-1];

     return (sen);
}

/**
 * kth_paragraph - gets the (k th) paragraph in the document
 * 
 * @doc: the document from which the paragraph will be taken
 * @k: the position of the paragraph in the document
 * 
 * Return: the corresponding representation of the paragraph
 */
paragraph_t kth_paragraph(document_t doc, int k)
{
     paragraph_t para;
     para = doc.data[k-1];

     return (para);
}

/**
 * print_word - prints the data part of word_t argument
 * 
 * @w: the word to be used
 * 
 * Return: nothing
*/
void print_word(word_t w)
{
     printf("%s", w.data);
}

/**
 * print_sentence - prints the words in a sentence_t argument
 * 
 * @sen: the sentence to be used
 * 
 * Return: nothing
*/
void print_sentence(sentence_t sen)
{
     for (int i = 0; i < sen.word_count; i++)
     {
          print_word(sen.data[i]);
          if (i != sen.word_count - 1)
               printf(" ");
     }
}

/**
 * print_paragraph - prints the sentences in a paragraph_t argument
 *
 * @para: the paragraph to be used
 *
 * Return: nothing
 */
void print_paragraph(paragraph_t para)
{
     for (int i = 0; i < para.sentence_count; i++)
     {
          print_sentence(para.data[i]);
          printf(".");
     }
}

/**
 * print_document: prints the detail content of a document_t arguement
 * 
 * @doc: the document to be used
 * 
 * Return: nothing
*/
void print_document(document_t doc)
{
     for (int i = 0; i < doc.paragraph_count; i++)
     {
          print_paragraph(doc.data[i]);
          if (i != doc.paragraph_count - 1)
               printf("\n");
     }
}

/**
 * get_input_text - get a whole text with paragraphs from the user
 * 
 * Return: a pointer to the text got
*/
char *get_input_text()
{
     char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
     int paragraph_count;
     char *return_doc;

     memset(doc, 0, sizeof(doc));
     scanf("%d", &paragraph_count);
     getchar();

     for (int i = 0; i < paragraph_count; i++)
     {
          scanf("%[^\n]%*c", p[i]);
          strcat(doc, p[i]);
          if (i != paragraph_count - 1)
               strcat(doc, "\n");
     }
     return_doc = malloc((strlen(doc) + 1) * sizeof(char));
     strcpy(return_doc, doc);

     return (return_doc);
}

/**
 * main - main entry for core process
 * 
 * Return: 0
*/
int main()
{
     char *text;
     document_t doc;
     int q;

     text = get_input_text();
     doc = get_document(text);
     scanf("%d", &q);

     while (q--)
     {
          int type;
          scanf("%d", &type);

          if (type == 3)
          {
               int k, m, n;
               scanf("%d %d %d", &k, &m, &n);
               word_t w = kth_word_in_mth_sentence_of_nth_paragraph(doc, k, m, n);
               print_word(w);
          }
          else if (type == 2)
          {
               int k, m;
               scanf("%d %d", &k, &m);
               sentence_t sen = kth_sentence_in_mth_paragraph(doc, k, m);
               print_sentence(sen);
          }
          else
          {
               int k;
               scanf("%d", &k);
               paragraph_t para = kth_paragraph(doc, k);
               print_paragraph(para);
          }
          printf("\n");
     }
}