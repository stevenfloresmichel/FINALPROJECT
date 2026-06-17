#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

const int SIZE = 1000;

//Selection sort function//
void selection_sort(int* values, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int minIndex = i;
        //finding smallest vaulue, moving to correct spot
        for (int j = i + 1; j < size; j++)
        {
            if (values[j] < values[minIndex])
                minIndex = j;
        }
        if (minIndex != i)
        {
            int temp = values[i];
            values[i] = values[minIndex];
            values[minIndex] = temp;
        }
    }
}

//Binary Search Recursive Function//
bool binary_search_recursive(int* values, int key, int start, int end)
{
    //vaule not found
    if (start > end)
        return false;
    //checking if middle is target
    int mid = start + (end - start) / 2;
    if (values[mid] == key)
        return true;
    //search left half if smaller, if not right
    if (key < values[mid])
        return binary_search_recursive(values, key, start, mid - 1);

    return binary_search_recursive(values, key, mid + 1, end);
}

//Binary Search Helper Function//
bool binary_search(int* values, int key, int size)
{
    return binary_search_recursive(values, key, 0, size - 1);
}

//Write Binary File Function//
void writeBinary(std::string filename, int* values, int length)
{
    //opening file
    std::ofstream out(filename, std::ios::binary);
    if (!out)
    {
        std::cerr << "Error opening file.\n";
        return;
    }
    //writing into array
    out.write(reinterpret_cast<char*>(&length), sizeof(length));
    out.write(reinterpret_cast<char*>(values), sizeof(int) * length);
}

//Create Binary File Function//
void createBinaryFile(std::string filename)
{
    //Array//
    int* values = new int[SIZE];
    //RNG by each run of program//
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    //writting data into file//
    for (int i = 0; i < SIZE; i++)
        values[i] = std::rand() % 1000;

    writeBinary(filename, values, SIZE);
    delete[] values;
}

//BinaryReading class//
class BinaryReader
{
private:
    int* values;
    int size;
    //loading data
    void readValues(std::string filename)
    {
        std::ifstream in(filename, std::ios::binary);

        if (!in)
        {
            std::cerr << "File error.\n";
            values = nullptr;
            size = 0;
            return;
        }
        //Reading data from file
        in.read(reinterpret_cast<char*>(&size), sizeof(size));
        values = new int[size];
        for (int i = 0; i < size; i++)
            in.read(reinterpret_cast<char*>(&values[i]), sizeof(int));
    }

public:
    BinaryReader(std::string filename)
    {
        values = nullptr;
        size = 0;
        readValues(filename);
    }
    //memory clearing//
    ~BinaryReader()
    {
        delete[] values;
    }

    int* getValues()
    {
        return values;
    }

    int getSize()
    {
        return size;
    }
};

//Analyzer Class//
class Analyzer
{
protected:
    int* values;
    int size;
    //copying array
    int* cloneValues(int* arr, int length)
    {
        int* copy = new int[length];

        for (int i = 0; i < length; i++)
            copy[i] = arr[i];

        return copy;
    }

public:
    Analyzer(int* values, int size)
    {
        this->size = size;
        this->values = cloneValues(values, size);
    }

    ~Analyzer()
    {
        delete[] values;
    }

    virtual std::string analyze() = 0;
};

//StatisticsAnalyzer Class//
class StatisticsAnalyzer : public Analyzer
{
public:
    StatisticsAnalyzer(int* values, int size)
        : Analyzer(values, size)
    {
    }

    std::string analyze() override
    {
        //sort data
        selection_sort(this->values, this->size);
        //min and max, sorted ends
        int min = values[0];
        int max = values[size - 1];
        //mean
        long long sum = 0;

        for (int i = 0; i < size; i++)
            sum += values[i];
        double mean = static_cast<double>(sum) / size;
        //median

        double median;
        if (size % 2 == 0)
            median = (values[size / 2 - 1] + values[size / 2]) / 2.0;
        else
            median = values[size / 2];
        //Mode
        int mode = values[0];
        int modeCount = 1;
        int currentCount = 1;

        for (int i = 1; i < size; i++)
        {
            if (values[i] == values[i - 1])
                currentCount++;
            else
                currentCount = 1;

            if (currentCount > modeCount)
            {
                modeCount = currentCount;
                mode = values[i];
            }
        }

        return
            "the min is " + std::to_string(min) + "\n" +
            "the max is " + std::to_string(max) + "\n" +
            "the mean value is " + std::to_string(mean) + "\n" +
            "the Median value is " + std::to_string(median) + "\n" +
            "the mode value is " + std::to_string(mode) +
            " which occured " + std::to_string(modeCount) + " times";
    }
};

//DuplicatesAnalyzer Class//
class DuplicatesAnalyzer : public Analyzer
{
public:
    DuplicatesAnalyzer(int* values, int size)
        : Analyzer(values, size) {
    }

    std::string analyze() override
    {
        //Already counted indexes
        int duplicateCount = 0;
        bool* counted = new bool[size]();
        //comparing with remaining values
        for (int i = 0; i < size; i++)
        {
            if (counted[i]) continue;

            bool found = false;

            for (int j = i + 1; j < size; j++)
            {
                if (values[i] == values[j])
                {
                    found = true;
                    counted[j] = true;
                }
            }

            if (found)
                duplicateCount++;
        }

        delete[] counted;

        return "there were " + std::to_string(duplicateCount) + " duplicate values";
    }
};

//MissingAnalyzer Class//
class MissingAnalyzer : public Analyzer
{
public:
    MissingAnalyzer(int* values, int size)
        : Analyzer(values, size) {
    }

    std::string analyze() override
    {
        //Values that exist
        bool present[1000] = { false };
        for (int i = 0; i < size; i++)
            present[values[i]] = true;

        //Non-appearing
        int missingCount = 0;
        for (int i = 0; i < 1000; i++)
            if (!present[i]) missingCount++;

        return "there were " + std::to_string(missingCount) + " missing values";
    }
};

//SearchAnalyzer Class//
class SearchAnalyzer : public Analyzer
{
public:
    SearchAnalyzer(int* values, int size)
        : Analyzer(values, size)
    {
        //Sorting
        selection_sort(this->values, this->size);
    }

    std::string analyze() override
    {
        int foundCount = 0;
        //100 random searches
        for (int i = 0; i < 100; i++)
        {
            int key = std::rand() % 1000;

            if (binary_search(values, key, size))
                foundCount++;
        }

        return "there were " + std::to_string(foundCount) +
            " of 100 random values found";
    }
};

//Main function//
int main()
{
    std::string filename = "binary.dat";

    createBinaryFile(filename);

    BinaryReader reader("binary.dat");

    int* data = reader.getValues();
    int size = reader.getSize();

    if (data == nullptr || size == 0)
    {
        std::cerr << "No data loaded.\n";
        return 1;
    }

    std::cout
        << StatisticsAnalyzer(data, size).analyze() << "\n"
        << DuplicatesAnalyzer(data, size).analyze() << "\n"
        << MissingAnalyzer(data, size).analyze() << "\n"
        << SearchAnalyzer(data, size).analyze() << "\n";

    return 0;
}