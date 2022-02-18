#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Word {
    string word;
    int countInText;
    int pages[100];
};


int main()
{
    const int numIgnoreWords = 14;
    string ignoreWords[numIgnoreWords] = { "in", "for", "on", "the", "for", "across", "below",
                        "into", "upon", "without", "to", "at", "of", "by" };

    ifstream fIn("text.txt"); 
    string text;
    int page = 1;
    int line = 1;
    const int allLine = 45;
    int count, ignoreCounter, startCapacity;
    ignoreCounter = 0;
    startCapacity = 0;
    int numAllIndexing = 20000;
    Word* indexing = new Word[numAllIndexing];

    int textLenght = 0;

    string* splitedString = new string[numAllIndexing];

    int alreadyThere, now, sizeTemp;
    string str, temp = "";
start:
    if (fIn.peek() != EOF)
    {
        count = 0;
        alreadyThere = 0;
        now = 0;
        if (line == allLine)
        {
            line = 1;
            ++page;
        }
        textLenght = 0;

        getline(fIn, text);
        ++line;

    textLenght:
        if (text[textLenght] != '\0') {
            ++textLenght;
            goto textLenght;
        }
    split:
        if (count <= textLenght)
        {
            if (text[count] >= 'A' && text[count] <= 'Z' || text[count] >= 'a' && text[count] <= 'z'
                || ((text[count] == '-' || text[count] == '\'') && count != textLenght)) {
                str += text[count];
            }

            else {
                splitedString[alreadyThere] = str;
                str = "";
                ++alreadyThere;
            }
            ++count;
            goto split;
        }
    getWord:
        count = 0;
        sizeTemp = 0;
        if (now < alreadyThere)
        {
            temp = splitedString[now];
        tempSize:
            if (temp[sizeTemp] != '\0')
            {
                ++sizeTemp;
                goto tempSize;
            }
            if (!sizeTemp)
            {
                ++now;
                goto getWord;
            }
        toLower:
            if (count <= sizeTemp)
            {
                if (temp[count] >= 'A' && temp[count] <= 'Z')
                {
                    temp[count] = temp[count] + 32;
                }
                ++count;
                goto toLower;
            }
        ignoreWord:
            if (ignoreCounter < numIgnoreWords)
            {
                if (temp == ignoreWords[ignoreCounter])
                {
                    goto start;
                }
                ++ignoreCounter;
                goto ignoreWord;
            }
            ignoreCounter = 0;
            count = 0;
        presenceCheck:
            if (count < startCapacity)
            {
                if (indexing[count].word == temp)
                {
                    if (indexing[count].countInText != 101)
                    {
                        indexing[count].pages[indexing[count].countInText] = page;
                        ++indexing[count].countInText;
                    }
                    ++now;
                    goto getWord;
                }
                ++count;
                goto presenceCheck;
            }
            else
            {
                indexing[startCapacity].pages[0] = page;
                indexing[startCapacity].countInText = 1;
                indexing[startCapacity].word = temp;
                ++startCapacity;
                ++now;
                goto getWord;
            }
        }
        goto start;
    }
    int i=0, j=0;

sorting:
    if (i < startCapacity-1)
    {
        j = 0;
    sortingBubble:
        if (j<startCapacity-i-1)
        {
            if (indexing[j].word > indexing[j + 1].word)
            {
                Word center;
                center = indexing[j + 1];
                indexing[j + 1] = indexing[j];
                indexing[j] = center;
            }
            ++j;
            goto sortingBubble;
        }
        ++i;
        goto sorting;
    }
    count=0, i=0, j=0;
printResult:
    if (count < startCapacity) {
        if (indexing[count].countInText != 101)
        {
            cout << indexing[count].word << " - ";
        printPage:
            if (i < indexing[count].countInText)
            {
                if (j != indexing[count].pages[i])
                {
                    cout << indexing[count].pages[i] << ", ";
                    j = indexing[count].pages[i];
                }
                ++i;
                goto printPage;
            }
            cout << endl;
        }
        ++count;
        goto printResult;
    }
    return 0;
}