/* ----------------------------------------------------------------------------
 * Copyright &copy;     2015 Ben Blazak <bblazak@fullerton.edu>
 *                      2015 Alex Liao  <ycl@csu.fullerton.edu>
 * Released under the [MIT License] (http://opensource.org/licenses/MIT)
 * ------------------------------------------------------------------------- */

/**
 * A program to read unsigned integers from a text file and separate them into
 * two files, one for primes, another for composites.
 */

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>

using std::cout;
using std::endl;
using std::fill_n;
using std::string;
using std::ifstream;
using std::ofstream;

const string input_file = "/Users/Ayl/Downloads/gitFiles/assignment-02/input.txt",
output_p   = "/Users/Ayl/Downloads/gitFiles/assignment-02/Outputs/primes.txt",
output_c   = "/Users/Ayl/Downloads/gitFiles/assignment-02/Outputs/composites.txt";

ifstream readFile (input_file);
ofstream write_prim (output_p);
ofstream write_comp (output_c);

int find_max (const string & = input_file);

void sieve (const int, bool []);

int write_p (const int,
             bool [],
             const string & = input_file,
             const string & = output_p);

int write_c (const int,
             bool [],
             const string & = input_file,
             const string & = output_c);

int main()
{
    int max = find_max();
    
    if (max == -1)
    {
        cout << "Error finding max! \n";
        return 1; // error msg
    }
    else
    {
        cout << "Max is > " << max << endl;
    }
    
    bool * test_data = new bool[max];
    
    sieve(max, test_data);
    
    write_p(max, test_data);
    
    write_c(max, test_data);
    
    return 0;
}

int find_max (const string &input)
{
    int current_num, max = 0;
    
    if (readFile.fail())
    {
        return -1; // error reading file
    }
    else
    {
        while (readFile >> current_num)
        {
            if (current_num > max)
            {
                max = current_num;
            }
        }
    }
    
    //readFile.close();
    
    return max;
}

void sieve (const int test_size, bool test_data[])
{
    fill_n(test_data, test_size, true);     //  fill entire array to `true`
    
    test_data[0] = false;   //  set indices [0], [1] as `false`
    test_data[1] = false;
    
    //  iterate through the indeces in the array test_data,
    //  if an index is marked as `true`, mark all multiples of the index as `false`
    
    for (int p = 2; p < test_size; p++)
    {
        if (test_data[p])   //  if the index is true, execute. . . for loop
        {
            for (int m_of_p = 2; m_of_p < test_size; m_of_p++)
            {
                int multiple = p * m_of_p;
                if (multiple > test_size)
                {
                    break;  //  if multiple of the true index is greater than max
                }
                else
                {
                    test_data[multiple] = false;
                }
            }
        }
    }
}

int write_p (const int    test_size,
             bool         test_data[],
             const string &input,
             const string &output)
{
    readFile.clear();
    readFile.seekg(std::ios_base::beg);
    
    int current_num;
    
    if (readFile.fail() || write_prim.fail())
    {
        cout << "Error in read/ write primes\n";
        return -1;  //  File read/ write error
    }
    else
    {
        while (readFile >> current_num)
        {
            if (test_data[current_num] == true)
            {
                write_prim << current_num << endl;
            }
        }
    }
    
    //readFile.close();
    write_prim.close();
    
    return 0;   //  function execute success
}

int write_c (const int    test_size,
             bool         test_data[],
             const string &input,
             const string &output)
{
    readFile.clear();
    readFile.seekg(std::ios_base::beg);
    
    int current_num;
    
    if (readFile.fail() || write_comp.fail())
    {
        cout << "Error in read/ write composites \n";
        return -1;  //  File read/ write error
    }
    else
    {
        while (readFile >> current_num)
        {
            if (test_data[current_num] == false)
            {
                if (current_num == 0 || current_num == 1)
                {
                    continue;
                }
                
                write_comp << current_num << endl;
            }
        }
    }
    
    readFile.close();
    write_comp.close();
    
    return 0;   //  Function execute success
}


