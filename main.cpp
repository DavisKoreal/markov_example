#include "modules.hpp"
using namespace std;

class sequential_word{

    public:
        string word;
        int number_of_occurence;
        double probability;

    sequential_word()
    {
        number_of_occurence = 0;
    }

};


class uniqueword{

    public:
        string word;
        vector<sequential_word> unique_words_after;
        int number_of_words_after;

    uniqueword()
    {
        string word = "";
        vector<sequential_word> unique_words_after = {};
        int number_of_unique_words_after = 0;
    }

    /**
     * @brief This function takes is a string input and checks if the string is in the set 
     * of sequential words. If it is listed, it adds the occurence. Else, it adds the string
     * as a new wntry into the set of sequential words.
     * 
     * @param newword: this is the word that follows the uniquword.word in the text.
     */

    void add_unique_sequntial_word(string new_sequential_word)
    {
        //if the newword is not in the set of uniquewords_after this unique word, add it as a new unique sequential word
        //else if the word is in the set of uniqueword_after this unique word, increment its occurence

        bool already_listed = false;

                for (int i = 0; ((i < unique_words_after.size())&&(unique_words_after.size() != 0)); i++ )
                        {
                            if (unique_words_after[i].word == new_sequential_word)
                            {
                                already_listed = true;
                                unique_words_after[i].number_of_occurence += 1;
                            }
                        }
                
                if(!already_listed)
                {
                    sequential_word new_sequentiall_word_object;
                    new_sequentiall_word_object.word = new_sequential_word;
                    new_sequentiall_word_object.number_of_occurence = 1;
                    unique_words_after.push_back(new_sequentiall_word_object);
                }
    }

    /**
     * @brief This function asigns a probability to every sequntial word that follows sequentially from this
     * unique word 
     * 
     */
    void assign_probabilities()
    {
        for ( int i = 0; ((i < unique_words_after.size()) && (unique_words_after.size() != 0)); i ++)
        {
            unique_words_after[i].probability = double(unique_words_after[i].number_of_occurence)/double(unique_words_after.size());
            //cout<< "\t\tOccurences: " << unique_words_after[i].number_of_occurence << " Size of unique words: "  << unique_words_after.size() << "Probalibity: " << unique_words_after[i].probability << endl;
        }
        //cout << " all probabilities have therefore been assigned to all sequential words of this uniqueword "<< word << endl;

    }
};

int main()
{

    /**
     * @brief open the file containing the text to be worked and and return a vector of lines
     * 
     */
    fstream text_file;
    text_file.open("test.txt", fstream::in);

    vector<string> text_vector;
    while(!text_file.eof())
    {
        string line_of_text;
        getline(text_file, line_of_text);
        line_of_text += "   "; //This solves a runtime logical bug. Do not touch it.
        text_vector.push_back(line_of_text);
    }



    /**
     * @brief Split the text into its constituent set of words and set of unique words
     * 
     */

    vector<string> uniquewords;
    vector<string> words_vector;
    string word;
    bool wordhasletters = false;

    for(auto line: text_vector)
    {
        string oneline = line;

        for (auto letter: oneline)
        {
            bool isletter = (((int(letter) > 64) && (int(letter) < 91)) ||((int(letter)> 96) &&(int(letter)< 123 ))) ? true: false;  

            if(isletter)
            {
                
               word += letter;
               //cout << "This is a letter and the tentative word is " << word << "\n";
               wordhasletters = true;
            }
            else if((!isletter) &&(wordhasletters))
            {
                words_vector.push_back(word);

                /*   test if it is already in the vector
                *    if not, add to the set of unique words
                */
                bool already_listed = false;
                for(auto wordd_:uniquewords)
                {
                    if (wordd_ == word)
                    {
                        already_listed = true;
                        word = "";
                        wordhasletters = false;
                        break;
                    }
                }
                if(!already_listed)
                {
                    uniquewords.push_back(word);
                    word = "";
                    wordhasletters = false;
                }
            }
        }
    }

    /*
    for (auto word:uniquewords)
    {
        cout << word << "\n";
    }
    */

    cout << "The number of words is " << words_vector.size() << "\n";
    cout << "The number of unique words is " << uniquewords.size() << "\n";

    vector<uniqueword> Unique_words;

    /**
     * @brief for each unique word, get the set of words that follow it
     * then calculate the probabilities of each next word of following the unique word.
     * 
     */

    for(int i = 0; i < uniquewords.size(); i++)
    {
        uniqueword newunique_word;
        newunique_word.word = uniquewords[i];
        int nextword_index = i;
        nextword_index += 1;

        for(int k =0; k<words_vector.size();k++)
        {
            if(words_vector[k] == newunique_word.word)
            {
                int next = k;
                next += 1;
                newunique_word.add_unique_sequntial_word(words_vector[next]);
            }

        }

        newunique_word.assign_probabilities();  
        //cout << "Created a new word with params " << uniquewords[i] << " nextword: " << uniquewords[nextword_index] << endl;
        Unique_words.push_back(newunique_word);

    }

    for (int i = 0; i < Unique_words.size(); i++)
    {
        cout<< "Unique word is: " << Unique_words[i].word << " Size of sequential vector: " << Unique_words[i].unique_words_after.size()<< endl<<endl;
        for(int j = 0; j < Unique_words[i].unique_words_after.size(); j++)
        {
            sequential_word tword = Unique_words[i].unique_words_after[j];
            cout << "\t\tWord: " << tword.word << "   Occurences: "<<tword.number_of_occurence<<"   Probability: " << tword.probability <<endl;
        }
    }



    /**
     * @brief for each unique word and its list of words, calculate the relative frequency of each word that
     * follows the unique word, in all the instances of the unique word
     * 
     * This relative frequency is directly proportional to the probability that the subsequent word
     * follows the unique word
     * 
     */


    /**
     * @brief each unique word has a list of words that follow it, with frequencies/probabilities to each word that
     * follows it. Now for all words, we have a list of words that the next word can be, with a list os probabilities mapped
     * 
     */


    /**
     * @brief we now have our simple markov model of the entered data.
     * 
     */






    //

    return(0);
}