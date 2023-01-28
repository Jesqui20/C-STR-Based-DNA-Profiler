/*



*/



#include <iostream>
#include "ourvector.h"
#include <fstream>
#include <string>
using namespace std;



struct Person
{
    string name;
    ourvector<int> STR_Counts;  // average GPA
    bool STR_Match = false;
};

struct STR
{
    ourvector<char> STR_seq;
}; // ourvector <STR> STR_Sequences; (Will hold each STR)

struct DNA
{
    ourvector<char> DNA_seq;
};




// Function prototypes:

void display(ourvector<STR>& STR_Seqs, ourvector<Person>& people, DNA& DNA_Entry, ourvector<int>& Processed_STR_Counts, bool& isProcessed);

void search(ourvector<int>& Processed_STR_Counts,ourvector<Person>& people, bool dbLoaded, bool dnaLoaded, bool isProcessed);

void STRcount_match(ourvector<int>& Processed_STR_Counts, Person& potentialMatch);

int load_db(string filename, ourvector<STR>& STR_seqs, ourvector<Person>& people, bool& isProcessed, bool& dbLoaded);

int load_dna(string filename, DNA& DNA_Entry, bool& isProcessed, bool& dnaLoaded);

void storeSTRs(string STR_Line, ourvector<STR>& STR_seqs);

void storePeople(string People_Line, ourvector<Person>& people);

void process(ourvector<int>& Processed_STR_Counts, ourvector<STR>& STR_seqs, DNA& DNA_Process, bool& isProcessed, bool dbLoaded, bool dnaLoaded);

int countMatches(ourvector<char>& DNA_To_Process, ourvector<char>& STR_To_Process);

bool confirmMatch(int i, ourvector<char> DNA_To_Process, ourvector<char> STR_To_Process);

/*
void loadData(string filename, ourvector<Student> &students);

void load_dna(string filename, ourvector<DNA>& DNA);

void load_db(string filename, ourvector<Pereeson>& persons);

void parseLine(string line, Student &newStudent);
void loadData(string filename, ourvector<Student> &students);
void print(ourvector<Student> &students);
int searchData(string name, ourvector<Student> &students);


string getName(string &line);
double getGPA(string &line);
int searchData(string name, ourvector<Student> &students);
*/


int main()
{
    ourvector<Person> people;

    ourvector<STR> STR_Sequences;

    ourvector<int> Processed_STR_Counts; //Reset at beginning of process()

    DNA DNA_Entry;


    bool isProcessed = false, dbLoaded = false, dnaLoaded = false;

    // This vector is to store structures composed of STR sequences. 



    // pop people on after reading the DNA for the last person,
    // or this is the first person being added.


    //cout << endl << "  Welcome to the DNA Profiler NucleoSearch" << endl << endl;
    cout << "Welcome to the DNA Profiling Application." << endl;

    string filename;

    //cout << "  Supported Commands:" << endl << "    '#': Quit" << endl << "    'load' filename: Load database from file" << endl << "    'display': Display database information" << endl;
    //cout << endl;
    cout << "Enter command or # to exit: ";

    //cout << "  Please enter a .txt file containing a DNA sequence" << endl << endl;
    //cout << "  The DNA Sequence Will Be Searched Among a DNA Database for a Match. " << endl << endl;

    //cin >> filename;

    // Here: Enter the template for opening the file, or have the file reading done in another function...


    //cout << "  Enter command: ";
    string command;
    cin >> command;
    //cout << endl;

    while (command != "#") {
        // "load filename"
        // load in the data and store in a useful way
        if (command == "load_db") {
            cin >> filename;

            cout << "Loading database..." << endl;

            load_db(filename, STR_Sequences, people, isProcessed, dbLoaded);

            //display(STR_Sequences, people, DNA_Entry);



            /*
            loadData(filename, students);
            */

            // "lookup First Last"
            // allow user to look up average GPA of a particulary student.
        }
        else if (command == "load_dna")
        {
            cin >> filename;

            cout << "Loading DNA..." << endl;

            load_dna(filename, DNA_Entry,isProcessed, dnaLoaded);
        }
        else if (command == "display")
        {
            display(STR_Sequences,people,DNA_Entry,Processed_STR_Counts, isProcessed);

        }
        else if (command == "process")
        {
            //ourvector<int>& Processed_STR_Counts, ourvector<STR>& STR_seqs, DNA& DNA_Process

            // Check if Database is loaded, and DNA is loaded first.
            process(Processed_STR_Counts, STR_Sequences, DNA_Entry, isProcessed, dbLoaded, dnaLoaded);
        }
        else if (command == "search")
        {

            search(Processed_STR_Counts,people, dbLoaded, dnaLoaded, isProcessed);

        }
        else if (command == "lookup") {
            string name;
            cin.ignore();
            getline(cin, name, '\n');

            cout << "Lookup command with" << name << endl;

            /*

            int ind = searchData(name, students);

            */

            //cout << name << " found.  GPA: " <<
            //students[ind].gpa << endl;

        }
        cout << "Enter command or # to exit: ";
        cin >> command;
    }



    return 0;
}



void display(ourvector<STR>& STR_Seqs, ourvector<Person>& people, DNA& DNA_Entry, ourvector<int>& Processed_STR_Counts, bool& isProcessed)
{

    /*
    
        Database loaded:
        Alice 2 8 3
        Bob 4 1 5
        Charlie 3 2 5

        No DNA loaded.

        No DNA has been processed.
    
    
    
    
    
    */

    // Output the stored STRs from STR_Sequences

    if (STR_Seqs.size() == 0)
    {
        cout << "No database loaded." << endl;
    }
    else
    {
        cout << "Database loaded: " << endl;
        /*
        for (auto STR : STR_Seqs)
        {
            for (int i = 0; i < STR.STR_seq.size(); ++i)
            {
                cout << STR.STR_seq[i];
            }
            cout << " ";
        }
        cout << endl;
        */

        // Output the stored People from people


        // NO DATABASE LOADED!!!!!! ******
        //cout << "People Stored In Database: " << endl;
        for (auto Person : people)
        {
            cout << Person.name << " ";
            //cout << Person.STR_Counts.size() << endl;
            for (int i = 0; i < Person.STR_Counts.size(); ++i)
            {
                if (i == Person.STR_Counts.size() - 1)
                {
                    cout << Person.STR_Counts[i];
                }
                else
                {
                    cout << Person.STR_Counts[i] << " ";
                }

            }
            cout << endl;
        }
        cout << endl;
    }

    // Output the stored DNA sequence
    if (DNA_Entry.DNA_seq.size() == 0)
    {
        cout << "No DNA loaded." << endl << endl;
        
    }
    else
    {
        cout << "DNA loaded: " << endl;
        for (int i = 0; i < DNA_Entry.DNA_seq.size(); ++i)
        {
            cout << DNA_Entry.DNA_seq[i];
        }
        cout << endl << endl;
    }
    // Output the DNA being processed

    if (isProcessed)
    {
        cout << "DNA processed, STR counts: " << endl;

        for (int i = 0; i < STR_Seqs.size(); ++i)
        {
            for (int y = 0; y < STR_Seqs[i].STR_seq.size(); ++y)
            {
                cout << STR_Seqs[i].STR_seq[y];
            }
            cout << ": " << Processed_STR_Counts[i] << endl;
        }
    }
    else
    {
        cout << "No DNA has been processed." << endl;
    }

}

void search(ourvector<int>& Processed_STR_Counts,ourvector<Person>& people, bool dbLoaded, bool dnaLoaded, bool isProcessed)
{
    if (dbLoaded && dnaLoaded && isProcessed)
    {
        cout << "Searching database..." << endl;

        for (int i = 0; i < people.size(); ++i)
        {
            STRcount_match(Processed_STR_Counts, people[i]);
        }

        for (int i = 0; i < people.size(); ++i)
        {
            if (people[i].STR_Match)
            {
                cout << "Found in database! DNA matches: " << people[i].name << endl;
                return;
            }
        }
        cout << "Not found in database." << endl;
    }
    else if (!dbLoaded)
    {
        cout << "No database loaded." << endl;
    }
    else if (!dnaLoaded)
    {
        cout << "No DNA loaded." << endl;
    }
    else if (!isProcessed)
    {
        cout << "No DNA processed." << endl;
    }



    return;
}

void STRcount_match(ourvector<int>& Processed_STR_Counts, Person& potentialMatch)
{
    for (int i = 0; i < potentialMatch.STR_Counts.size(); ++i)
    {
        if (potentialMatch.STR_Counts[i] == Processed_STR_Counts[i])
        {

        }
        else
        {
            return;
        }
    }

    potentialMatch.STR_Match = true;
}

int load_db(string filename, ourvector<STR>& STR_seqs, ourvector<Person>& people, bool& isProcessed, bool& dbLoaded)
{
    ifstream infile(filename);
    string STR_Line, Person_Line;

    if (!infile.is_open())
    {
        cout << "Error: unable to open '"<< filename << "'" << endl;
        //Error: unable to open 'invalid_db_file.txt
        return 1;
    }

    getline(infile, STR_Line, '\n');

    if (!infile.fail())
    {
        storeSTRs(STR_Line, STR_seqs);
    }

    getline(infile, Person_Line, '\n');

    while (!infile.eof())
    {
        if (!infile.fail())
        {
            storePeople(Person_Line, people);
        }

        getline(infile, Person_Line, '\n');

    }
    dbLoaded = true;
    isProcessed = false;
    infile.close();
    return 0;
}

void storeSTRs(string STR_Line, ourvector<STR>& STR_seqs)
{

    for (std::size_t i = 5; i < STR_Line.size(); ++i)
    {
        STR newSTR;

        while (STR_Line[i] != ',' && i < STR_Line.size())
        {
            newSTR.STR_seq.push_back(STR_Line[i]);
            ++i;
        }

        STR_seqs.push_back(newSTR);
    }
}


void storePeople(string People_Line, ourvector<Person>& people)
{
    // Build each Person structure, then append to the vector of people composing the database
    string newName, newInt;
    ourvector<int> STR_Counts;
    Person newPerson;
    int i = 0;
    int y = 0; // Tracks the integer length of the STR count

    while (People_Line[i] != ',')
    {
        newName += People_Line[i];
        ++i;
    }
    newPerson.name = newName;

    for (i; i < People_Line.size(); ++i)
    {
        newInt = "";
        while (People_Line[i] != ',' && i < People_Line.size())
        {
            newInt += People_Line[i];
            i++;

        }
        if (newInt != "")
        {
            int newSTR_Count = stoi(newInt);

            newPerson.STR_Counts.push_back(newSTR_Count);
        }
        
        
        
    }
    people.push_back(newPerson);
}

int load_dna(string filename, DNA& DNA_Entry, bool& isProcessed, bool& dnaLoaded)
{
    ifstream infile2(filename);
    string DNA_Lines;


    if (!infile2.is_open())
    {
        cout << "Error: unable to open '" << filename << "'" << endl;
        //Error: unable to open 'invalid_dna_file.txt
        return 1;
    }

    //getline(infile, STR_Line, '\n');
    infile2 >> DNA_Lines;

    if (!infile2.fail())
    {
        isProcessed = false;

        for (int i = 0; i < DNA_Lines.size(); ++i)
        {
            DNA_Entry.DNA_seq.push_back(DNA_Lines[i]);
        }
    }
    dnaLoaded = true;
    return 0;
}

void process(ourvector<int>& Processed_STR_Counts, ourvector<STR>& STR_seqs, DNA& DNA_Process, bool& isProcessed, bool dbLoaded, bool dnaLoaded)
{
    int STR_Matches = 0;

    if (dbLoaded && dnaLoaded)
    {
        cout << "Processing DNA..." << endl;

        isProcessed = true;

        for (int z = 0; z < STR_seqs.size(); ++z)
        {
            STR_Matches = countMatches(DNA_Process.DNA_seq, STR_seqs[z].STR_seq);

            Processed_STR_Counts.push_back(STR_Matches);
        }
    }
    else if (!dbLoaded)
    {
        cout << "No database loaded." << endl;
    }
    else if (!dnaLoaded)
    {
        cout << "No DNA loaded." << endl;
    }

}

int countMatches(ourvector<char>& DNA_To_Process, ourvector<char>& STR_To_Process)
{
    bool match = false;
    int matches = 0, most_matches = 0;
    ourvector<int> Matches_Count;

    for (int i = 0; i < DNA_To_Process.size() && ((i + STR_To_Process.size()) < DNA_To_Process.size()); ++i)
    {
        match = false;
        matches = 0;

        if (DNA_To_Process[i] == STR_To_Process[0])
        {
            match = confirmMatch(i, DNA_To_Process, STR_To_Process);
        }
        
        while (match && ((i + STR_To_Process.size()) < DNA_To_Process.size()))
        {
            i += STR_To_Process.size();
            matches += 1;

            match = confirmMatch(i, DNA_To_Process, STR_To_Process);
        }
        Matches_Count.push_back(matches);
    }

    /*
    if (Matches_Count.size() == 0) {

        return 0;
    }
    */

    most_matches = Matches_Count[0];

    for (int y = 0; y < Matches_Count.size(); ++y)
    {
        if (most_matches < Matches_Count[y])
        {
            most_matches = Matches_Count[y];
        }
    }

    return most_matches;
}

bool confirmMatch(int i, ourvector<char> DNA_To_Process, ourvector<char> STR_To_Process)
{
    for (int x = 0; x < STR_To_Process.size(); ++x)
    {
        if (STR_To_Process[x] == DNA_To_Process[i])
        {
            ++i;
        }
        else
        {
            return false;
        }
    }

    return true;
}

/*
int main()
{

    string filename, value;

    ourvector<string> DNA_Strands;

     // TODO:  Write your code here.  You should have LOTS of function decomposition.

    cout << "TEST" << endl;

    cout << "Input file name" << endl;

    cin >> filename;

    cout << "File Name Was: " << filename << endl;

    ifstream infile(filename);

    while (!infile.eof())
    {

    getline(infile,value,'\n');

        if (!infile.fail())
        {

            DNA_Strands.push_back(value);

            cout << "Success: " << value << endl;


        }
    }

    for (auto &e : DNA_Strands)
    {
        cout << e << endl;
    }


    return 0;
}

*/
