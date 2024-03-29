#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DATE_SIZE 11
#define DATA_COUNT 3192
#define NUM_YEARS 265 // 2015 - 1750

// Accont's for header and skips over it
int counter = -1;

// Date
char dt[DATA_COUNT][DATE_SIZE];

// Land Average Temperature
double lat[DATA_COUNT];

// Land Average Temperature Uncertainty
double latu[DATA_COUNT];

// Land Max Temperature
double lmt[DATA_COUNT];

// Land Max Temperature Uncertainty
double lmtu[DATA_COUNT];

// Land Min Temperature
double lmit[DATA_COUNT];

// Land Min Temperature Uncertainty
double lmitu[DATA_COUNT];

// Land and Ocean Average Temperature
double loat[DATA_COUNT];

// Land and Ocean Average Temperature Uncertainty
double loatu[DATA_COUNT];

// Land Average Temperature Yearly Averages
double latYearlyAverage[NUM_YEARS];

// Land Max Temperature Yearly Averages
double lmtYearlyAverage[NUM_YEARS];

// Land Min Temperature Yearly Averages
double lmitYearlyAverage[NUM_YEARS];

// Land and Ocean Average Temperature Yearly Averages
double loatYearlyAverage[NUM_YEARS];

// Array of pointers to the yearly averages
// 0 is LAT
// 1 is LMT
// 2 is LMIT
// 3 is LOAT
double *yearlyAverages[] = {
    latYearlyAverage,
    lmtYearlyAverage,
    lmitYearlyAverage,
    loatYearlyAverage};

// Array of pointers to the data arrays
// 0 is LAT
// 1 is LMT
// 2 is LMIT
// 3 is LOAT
double *data[] = {
    lat,
    lmt,
    lmit,
    loat};

// Global array of file names
char fileNames[10][50] = {
    "Question-6.dat",
    "Question-7-1800.dat",
    "Question-7-1900.dat",
    "Question-8-lat.dat",
    "Question-8-lmt.dat",
    "Question-8-lmit.dat",
    "Question-9-firstCentury.dat",
    "Question-9-secondCentury.dat",
    "Question-9-thirdCentury.dat",
    "Question-9-fourthCentury.dat"};
void setValuesFromFile()
{
    FILE *file;
    file = fopen("GlobalTemperatures.csv", "r");
    if (file == NULL)
    {
        printf("Error: File not found\n");
        exit(1);
    }
    // Line shouldn't be more than 1024 characters? (Idk maybe lol)
    char line[1024];
    while (fgets(line, 1024, file))
    {
        // Skip header
        if (counter == -1)
        {
            counter++;
            continue;
        }
        // Split the line into tokens using comma as the delimiter
        char *token = strtok(line, ",");
        int index = 0;

        // Iterate through each token and assign values to the corresponding arrays
        while (token != NULL)
        {
            switch (index)
            {
            case 0:
                // Copy the date string to the date array
                strncpy(dt[counter], token, DATE_SIZE);
                dt[counter][DATE_SIZE - 1] = '\0'; // Null terminate the string
                break;
            case 1:
                // Convert the string to a double and assign it to lat array
                lat[counter] = atof(token);
                break;
            case 2:
                // Convert the string to a double and assign it to latu array
                latu[counter] = atof(token);
                break;
            case 3:
                // Convert the string to a double and assign it to lmt array
                lmt[counter] = atof(token);
                break;
            case 4:
                // Convert the string to a double and assign it to lmtu array
                lmtu[counter] = atof(token);
                break;
            case 5:
                // Convert the string to a double and assign it to lmit array
                lmit[counter] = atof(token);
                break;
            case 6:
                // Convert the string to a double and assign it to lmitu array
                lmitu[counter] = atof(token);
                break;
            case 7:
                // Convert the string to a double and assign it to loat array
                loat[counter] = atof(token);
                break;
            case 8:
                // Convert the string to a double and assign it to loatu array
                loatu[counter] = atof(token);
                break;
            default:
                break;
            }
            // Doesn't immediately set value to null, instead checks first string and moves onto next token
            // until there are no other tokens to view
            token = strtok(NULL, ",");
            index++;
        }

        // Increment the counter after processing each line
        counter++;
    }
    fclose(file);
    printf("Data count: %d\n", counter);
}

/**
 * This function uses fscanf to sort the values
 * Probably need to format the date using ints and storing the values overall is gonna be a huge hassle
 * but I can try getting this to work sometime later
 */
void setValuesFromFile2()
{
    FILE *file;
    file = fopen("GlobalTemperatures.csv", "r");
    if (file == NULL)
    {
        perror("Failed to open file");
        return;
    }

    while (fscanf(file, "%s,%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf", dt[counter], &lat[counter], &latu[counter], &lmt[counter], &lmtu[counter], &lmit[counter], &lmitu[counter], &loat[counter], &loatu[counter]) != EOF)
    {
        // Skip header
        if (counter == -1)
        {
            counter++;
            continue;
        }
        dt[counter][DATE_SIZE - 1] = '\0'; // Null terminate the string
        counter++;
    }
    fclose(file);
}
/**
 * Function to print the arrays
 * TESTING PURPOSES COMMENT OUT ON PRODUCTION
 */
void printArrays()
{
    for (int i = 0; i < counter; i++)
    {
        printf("Date: %s\n", dt[i]);
        printf("Land Average Temperature: %f\n", lat[i]);
        printf("Land Average Temperature Uncertainty: %f\n", latu[i]);
        printf("Land Max Temperature: %f\n", lmt[i]);
        printf("Land Max Temperature Uncertainty: %f\n", lmtu[i]);
        printf("Land Min Temperature: %f\n", lmit[i]);
        printf("Land Min Temperature Uncertainty: %f\n", lmitu[i]);
        printf("Land and Ocean Average Temperature: %f\n", loat[i]);
        printf("Land and Ocean Average Temperature Uncertainty: %f\n", loatu[i]);
    }
}

/**
 * Retrieves the position of an array based on a given date string.
 *
 * @param date The date string in the format "YYYY-MM-DD".`
 * @return The position in the array.
 */
int getArrPosition(char *date)
{
    int year, month, day;
    if (sscanf(date, "%d-%d-%d", &year, &month, &day) != 3)
    {
        printf("Error: Invalid date format\n");
        exit(1);
    }
    return (year - 1750) * 12 + month - 1;
}

int getYearlyArrPosition(int year)
{
    return year - 1750;
}

/**
 * Calculates the yearly averages of the latitudes.
 * The function iterates over each year and calculates the average latitude for that year.
 * The average latitude is calculated by summing up the latitudes for each month in the year and dividing by 12.
 * The calculated yearly averages are stored in the `yearlyAverages` array.
 */
void calcYearlyAverages(double *values, double *yearlyAverages)
{
    // FILE* debugFile = fopen("debug.txt", "a");
    double sum = 0;
    for (int i = 0; i <= NUM_YEARS; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            sum += values[i * 12 + j];
        }
        yearlyAverages[i] = sum / 12;
        // fprintf(debugFile, "Year: %d, Average: %f\n", i + 1750, yearlyAverages[i]);
        sum = 0;
    }
    // fclose(debugFile);
}
/**
 * Computes the yearly average for different variables.
 * Calls the `calcYearlyAverages` function for each variable.
 */
void computeYearlyAverage()
{
    calcYearlyAverages(lat, latYearlyAverage);
    calcYearlyAverages(lmt, lmtYearlyAverage);
    calcYearlyAverages(lmit, lmitYearlyAverage);
    calcYearlyAverages(loat, loatYearlyAverage);
}

/**
 * Writes data to a file in GNUPlot format.
 *
 * @param xvalues An array of integers representing the x-values.
 * @param yvalues An array of doubles representing the y-values.
 * @param xName The name of the x-axis.
 * @param yName The name of the y-axis.
 * @param size The size of the arrays.
 * @param fileName The name of the file to write the data to.
 * @param isAppended A flag indicating whether to append to an existing file (1) or create a new file (0).
 */
void writeGNUPlot(int *xvalues, double *yvalues, char *xName, char *yName, int size, char *fileName, int isAppended)
{
    FILE *file;
    // printf("Testing xValues 0 %d\n", xvalues[0]);
    // printf("Testing yValues 0 %lf\n", yvalues[0]);
    // printf("Testing xValues 1 %d\n", xvalues[1]);
    // printf("Testing yValues 1 %lf\n", yvalues[1]);
    switch (isAppended)
    {
    case 0:
        file = fopen(fileName, "w");
        break;
    case 1:
        file = fopen(fileName, "a");
        break;
    default:
        perror("Invalid file mode");
        return;
    }
    fprintf(file, "# %s vs %s\n", xName, yName);
    if (file == NULL)
    {
        perror("Failed to open file");
        return;
    }
    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%d %lf\n", xvalues[i], yvalues[i]);
    }
    fclose(file);
    printf("File written: %s\n", fileName);
}

/**
 * Writes data points to a file in GNUPlot format.
 *
 * This function takes arrays of x and y values, along with their corresponding names,
 * and writes them to a file in GNUPlot format. The data points are written from the
 * startIndex to the endIndex (exclusive) in the arrays.
 *
 * @param xvalues    An array of integers representing the x values.
 * @param yvalues    An array of doubles representing the y values.
 * @param xName      The name of the x values.
 * @param yName      The name of the y values.
 * @param size       The size of the arrays.
 * @param fileName   The name of the file to write the data to.
 * @param startIndex The index to start writing from in the arrays.
 * @param endIndex   The index to stop writing at in the arrays (exclusive).
 */
void writeGNUPlotIndex(int *xvalues, double *yvalues, char *xName, char *yName, int size, char*fileName, int startIndex, int endIndex) {
    FILE *file;
    file = fopen(fileName, "w");
    if (file == NULL)
    {
        perror("Failed to open file");
        return;
    }
    fprintf(file, "# %s vs %s\n", xName, yName);
    for (int i = startIndex; i < endIndex; i++)
    {
        fprintf(file, "%d %lf\n", xvalues[i], yvalues[i]);
    }
    fclose(file);
    printf("File written: %s\n", fileName);
}


/**
 * Based on the land average temperature column, calculate the yearly averages for each year
 * between 1760 and 2015 (the average of the twelve months of each year).
 * One average per year. Ignore the years 1750-1759.
 */
void q1()
{
    // 10 is the year 1760
    for (int i = 10; i <= NUM_YEARS; i++)
    {
        printf("Year: %d, Average: %f\n", i + 1750, latYearlyAverage[i]);
    }
}
/**
 * Based on the land average temperature column, calculate the average land
 * temperature for the different centuries: 18th century (1760-1799), 19th century
 * (1800-1899), 20th century (1900-1999) and 21st century (2000-2015). One
 * average per century.ss
 *
 */
void q2()
{
    double avg_temp_18th, avg_temp_19th, avg_temp_20th, avg_temp_21th;

    // 18th century (1760-1799)
    for (int i = getArrPosition("1760-01-01"); i < getArrPosition("1799-12-01"); i++)
    {
        avg_temp_18th += lat[i];
    }
    // Print the average land temperature for the 18th century
    printf("18th century average land temperature: %f\n", avg_temp_18th / 480);

    // 19th century (1800-1899)
    for (int i = getArrPosition("1800-01-01"); i < getArrPosition("1899-12-01"); i++)
    {
        avg_temp_19th += lat[i];
    }
    // Print the average land temperature for the 19th century
    printf("18th century average land temperature: %f\n", avg_temp_19th / 1200);

    // 20th century (1900-1999)
    for (int i = getArrPosition("1900-01-01"); i < getArrPosition("1999-12-01"); i++)
    {
        avg_temp_20th += lat[i];
    }
    // Print the average land temperature for the 20th century
    printf("18th century average land temperature: %f\n", avg_temp_20th / 1200);

    // 21st century (2000-2015)
    for (int i = getArrPosition("2000-01-01"); i < getArrPosition("2015-12-01"); i++)
    {
        avg_temp_21th += lat[i];
    }
    // Print the average land temperature for the 21th century
    printf("18th century average land temperature: %f\n", avg_temp_21th / 191);
}

/**
 * Based on the land average temperature column, calculate the monthly averages
 * for each month for all years combined between 1900 and 2015. A total of twelve
 * averages. One average per month.
 */
void q3()
{
    // Declaring the variables sum and month
    double sum;

    // This loop will go through the 12 months of the year (January, Febuary, ......)
    for (int i = 0; i < 12; i++)
    {
        sum = 0;

        // This loops through the years between 1900 and 2015
        for (int j = getArrPosition("1900-01-01") + i; j < getArrPosition("2015-12-01"); j += 12)
        {

            sum += lat[i];
        }

        // This prints out the month average over the years of 1900 2015
        printf("This is the average from 1900 to 2015 for the month ");

        switch (i)
        {
        case 0:
            printf("January ");
            break;
        case 1:
            printf("February ");
            break;
        case 2:
            printf("March ");
            break;
        case 3:
            printf("April ");
            break;
        case 4:
            printf("May ");
            break;
        case 5:
            printf("June ");
            break;
        case 6:
            printf("July ");
            break;
        case 7:
            printf("August ");
            break;
        }

        printf("%lf\n", (sum / 116));
    }
}
/**
 * Based on the land average temperature column, what was the
 * hottest month recorded and what was the coldest month
 * recorded (month and year in each case). In case of a tie, mention
 * only one (doesn't matter which one).
 */
void q4()
{
    int hottestMonthPos = 0;
    int coldestMonthPos = 0;

    // Use max and min double values to ensure the first
    // value is always greater or less than the current value
    double hottestMonth = __DBL_MIN__;
    double coldestMonth = __DBL_MAX__;
    for (int i = 0; i < DATA_COUNT; i++)
    {
        // Check if the current month's temperature is greater than the current hottest month
        if (lmt[i] > hottestMonth)
        {
            hottestMonth = lmt[i];
            hottestMonthPos = i;
        }
        // Check if the current month's temperature is less than the current coldest month
        if (lmit[i] < coldestMonth)
        {
            coldestMonth = lmit[i];
            coldestMonthPos = i;
        }
    }

    printf("Hottest month: %s, Temperature: %f\n", dt[hottestMonthPos], hottestMonth);
    printf("Coldest month: %s, Temperature: %f\n", dt[coldestMonthPos], coldestMonth);
}

/**
 * Based on your answer in question 1, what year was the hottest and what year was the coldest?
 */
void q5()
{
    int hottestYearPos = 0;
    int coldestYearPos = 0;

    // Use max and min double values to ensure the first
    // value is always greater or less than the current value
    double hottestYear = __DBL_MIN__;
    double coldestYear = __DBL_MAX__;
    for (int i = 10; i <= NUM_YEARS; i++)
    {
        if (latYearlyAverage[i] > hottestYear)
        {
            hottestYear = latYearlyAverage[i];
            hottestYearPos = i;
        }
        if (latYearlyAverage[i] < coldestYear)
        {
            coldestYear = latYearlyAverage[i];
            coldestYearPos = i;
        }
    }

    printf("Hottest year: %d, Temperature: %f\n", hottestYearPos + 1750, hottestYear);
    printf("Coldest year: %d, Temperature: %f\n", coldestYearPos + 1750, coldestYear);
}
/**
 * Based on your answer in question 1, generate a GNUPlot data file and use GNUPlot to 
 * make a graph (line plot) of the yearly temperatures for the years 1760 to 2015. 
 * Label the axes clearly and add a title and legend to your graph.
 */
void q6()
{
    int xvalues[NUM_YEARS];
    for (int i = 10; i <= NUM_YEARS; i++)
    {
        xvalues[i - 10] = i + 1750;
    }
    // Subtract 10 to avoid the last 10 years after 2015
    writeGNUPlot(xvalues, latYearlyAverage, "Years 1760 - 2015", "Temperatures", NUM_YEARS - 9, "Question-6.dat", 0);
}

/**
 * Generate a GNUPlot data file and use GNUPlot to make a graph (line plots) of the average land temperatures for the 19th and 20th centuries. 
 * Put both lines on the same figure. Ensure that you have the same x-axis scale (for example 1852 and 1952 would both have an x-value of 52).  
 * Have your two line plots with different colours. Label the axes clearly and add a title and legend to your graph. 
*/
void q7()
{
    int xvalues[101];
    double yvalues[101];
    double yvalues2[101];
    for (int i = 0; i <= 100; i++)
    {
        xvalues[i] = i;
        yvalues[i] = latYearlyAverage[getYearlyArrPosition(1800 + i)];
        yvalues2[i] = latYearlyAverage[getYearlyArrPosition(1900 + i)];
    }
    writeGNUPlot(xvalues, yvalues, "1800-1900", "Temps", 101, "Question-7-1800.dat", 0);
    writeGNUPlot(xvalues, yvalues2, "1900-2000", "Temps", 101, "Question-7-1900.dat", 0);
}

/**
 * Using the columns LandAverageTemperature, LandMaxTemperature and LandMinTemperature, generate a GNUPlot data file and use GNUPlot to make 
 * line plots that show all three temperatures on the same figure. Use the years for the x-axis (use only the years between 1850 and 2015) 
 * and the yearly averages for the y-axis. Use three different colours (or different line styles) for the three lines. 
 * Make sure that the line plotting LandAverageTemperature stands out from the other two (ex: make that line thicker). 
 * Make sure your graph has a title, axes labels and a legend that explicitly tells which line is which.

*/
void q8()
{
    int numYears = 2015 - 1850 + 1;
    int xvalues[numYears];
    double adjustedLatYearlyAverage[numYears];
    double adjustedLmtYearlyAverage[numYears];
    double adjustedLmitYearlyAverage[numYears];
    for (int i = 1850; i <= 2015; i++)
    {
        xvalues[i - 1850] = i;
        adjustedLatYearlyAverage[i - 1850] = latYearlyAverage[getYearlyArrPosition(i)];
        adjustedLmtYearlyAverage[i - 1850] = lmtYearlyAverage[getYearlyArrPosition(i)];
        adjustedLmitYearlyAverage[i - 1850] = lmitYearlyAverage[getYearlyArrPosition(i)];
        // printf("Year: %d, Adjusted Lat: %f, Adjusted Lmt: %f, Adjusted Lmit: %f\n", i,
        //     adjustedLatYearlyAverage[i - 1850],
        //     adjustedLmtYearlyAverage[i - 1850],
        //     adjustedLmitYearlyAverage[i - 1850]);
    }
    writeGNUPlot(xvalues, adjustedLatYearlyAverage, "Years 1850 - 2015", "Avg Temperatures", numYears, "Question-8-lat.dat", 0);
    writeGNUPlot(xvalues, adjustedLmtYearlyAverage, "Years 1850 - 2015", "Max Temperatures", numYears, "Question-8-lmt.dat", 0);
    writeGNUPlot(xvalues, adjustedLmitYearlyAverage, "Years 1850 - 2015", "Min Temperatures", numYears, "Question-8-lmit.dat", 0);
}

/**
 * Using the columns LandAverageTemperature, LandMaxTemperature and LandMinTemperature, generate a GNUPlot data file and use GNUPlot to make four bar 
 * plots (box or histogram plos) that show the average, low and high temperatures for each of the four centuries. 
 * Put all 4 century plots on the same figure displayed as subplots (multiplots). 
 * Each plot will show the boxes with different colours (one colour per century). 
 * Have a title to your figure and have the name of the century on each subplot. Have a legend on each subplot.
*/
void q9()
{
}


/**
 * @brief Cleans up files using the global array of file names.
 * 
 * This function iterates over the global array of file names and removes each file using the `remove()` function.
 * The array size is assumed to be 10.
 */
void cleanup()
{
    // Remove files using the global array of file names
    for (int i = 0; i < 10; i++)
    {
        remove(fileNames[i]);
    }
}

int main(void)
{
    cleanup();
    // remove("debug.txt");
    // Some updates here and there lololollolol
    // Call function to get data count
    setValuesFromFile();
    // Calculate the yearly averages
    computeYearlyAverage();
    q1();
    q2();
    q3();
    q4();
    q5();
    q6();
    q7();
    q8();
    q9();
    // int arrPos = getYearlyArrPosition(1850);
    // printf("LAT 1850: %f, LMT 1850: %f, LMIT 1850: %f\n", latYearlyAverage[arrPos], lmtYearlyAverage[arrPos], lmitYearlyAverage[arrPos]);
    return 0;
}