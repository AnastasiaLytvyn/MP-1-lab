#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    const int numIgnoreWords = 14;
    string ignoreWords[numIgnoreWords] = { "in", "for", "on", "the", "for", "across", "below",
                        "into", "upon", "without", "to", "at", "of", "by" };

    int ignoreCounter = 0;

    ifstream fIn("text.txt");
    int numDisplayWord = 25;

    // first - words 
    // second - count
    int numAllWord = 1000;
    string* words = new string[numAllWord];
    int* counter = new int[numAllWord];
    counter[0] = 0;
    int startCapacity = 0;
    int count = 0;


    string text;
    int start, wordLenght=0;
    int temp;
    string str;

start:
    if (fIn >> text)
    {
        start = 0;
        wordLenght = 0;

    wordLenght:
        if (text[wordLenght] != '\0' || text[wordLenght] >= 'A' && text[wordLenght] <= 'Z'
            || text[wordLenght] >= 'a' && text[wordLenght] <= 'z'
            || text[wordLenght] == '-' || text[wordLenght] == '\'')
        {
            ++wordLenght;
            goto wordLenght;
        }
        if (wordLenght == 1 && !(text[wordLenght] >= 'A' && text[wordLenght] <= 'Z'
            || text[wordLenght] >= 'a' && text[wordLenght] <= 'z'))
        {
            goto start;
        }

    toLower:
        if (start <= wordLenght)
        {
            if (text[start] >= 'A' && text[start] <= 'Z')
            {
                text[start] = text[start] + 32;
            }
            ++start;
            goto toLower;
        }


    ignoreWord:
        if (ignoreCounter < numIgnoreWords)
        {
            if (text == ignoreWords[ignoreCounter])
            {
                goto start;
            }
            ++ignoreCounter;
            goto ignoreWord;
        }
        ignoreCounter = 0;

    presenceCheck:
        if (count < startCapacity)
        {
            if (words[count] == text)
            {
                counter[count] += 1;
                goto start;
            }
            ++count;
            goto presenceCheck;
        }
        else
        {
            words[startCapacity] = text;
            counter[startCapacity] = 1;
            ++startCapacity;
        }
        count = 0;
        goto start;
    }


    int i, j;
    i = 1;
    sorting:
    if (i < startCapacity)
    {
        str = words[i];
        temp = counter[i];
        j = i - 1;
    sortingInserts:
        if (j >= 0 && counter[j] < temp)
        {
            words[j + 1] = words[j];
            counter[j + 1] = counter[j];
            --j;
            goto sortingInserts;
        }
        words[j + 1] = str;
        counter[j + 1] = temp;
        ++i;
        goto sorting;
    }
    if (startCapacity < numDisplayWord)
    {
        numDisplayWord = startCapacity;
    }
    printResult:
    if (count < numDisplayWord)
    {
        cout << words[count] << " - " << counter[count] << endl;
        ++count;
        goto printResult;
    }
    return 0;
}