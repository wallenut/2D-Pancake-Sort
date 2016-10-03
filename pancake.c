
/*  CS223 Problem set 5
        Pancake

        Allen Wang
        3/31/16

        Purpose: Understand and implement hash tables and queue in a 2 dimensional pancake sort application 

//keys: malloc strings before inserting. horizontal flip already mallocs string for you.
//search you do need to malloc to make a copy of the strings.

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Queue.h"
#include <errno.h>
#include "hash.h"

char* horizontalflip(char* original, int rows, int columns, int height, int width, bool hor)
{
	int i, j, index = 0;
	char* grid[height];
	for (i = 0; i < height; i++)
	{
		grid[i] = malloc(width* sizeof(char));
	}

	
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			grid[i][j] = original[index];
			index++;
		}

	}
	if (hor)
	{
		for (i = 0; i < rows; i++)
		{
			int left = 0, right = columns - 1;
			if ((columns % 2) == 0) //even flipping
			{
				while (left != (columns / 2))
				{
					char templeft, tempright;
					templeft = grid[i][left];
					tempright = grid[i][right];
					grid[i][left] = tempright;
					grid[i][right] = templeft;
					left++;
					right--;

				}
			}
			else if ((columns % 2) == 1)// odd number flipped
			{
				while (left != right)
				{
					char templeft, tempright;
					templeft = grid[i][left];
					tempright = grid[i][right];
					grid[i][left] = tempright;
					grid[i][right] = templeft;
					left++;
					right--;
				}
			}
		}
	}
	else if (!hor)
	{
		for (i = 0; i < columns; i++)
		{
			int top = 0, bottom = rows - 1;
			if ((rows % 2) == 0) //even flipping
			{
				while (top != (rows / 2))
				{
					char temptop, tempbottom;
					temptop = grid[top][i];
					tempbottom = grid[bottom][i];
					grid[top][i] = tempbottom;
					grid[bottom][i] = temptop;
					top++;
					bottom--;

				}
			}
			else if ((rows % 2) == 1)
			{
				while (top != bottom)
				{
					char temptop, tempbottom;
					temptop = grid[top][i];
					tempbottom = grid[bottom][i];
					grid[top][i] = tempbottom;
					grid[bottom][i] = temptop;
					top++;
					bottom--;
				}
			}
		}
	}
	int charnum = height * width;
	char* result = calloc(charnum + 1, sizeof(char));
	index = 0;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			result[index] = grid[i][j];
			index++;
		}
	}
	for (i = 0; i < height; i++)
	{
		free(grid[i]);
	}

	return result;
	
	
}

void sort(char values[], int n)
{
    // Insertion sort
    char insertitem;
    for (int i = 1; i < n; i++) //start by inserting first element as long as it is greater
    {
        insertitem = values[i];
        int k = i - 1; // Base case, insert item[1] into list i[0]
        while (k >= 0 && values[k] > insertitem )//While the value is greater than the insertion item
        {
            values[k + 1] = values[k]; //shifts the elements by 1
            k = k - 1;//moves comparison one to the left
        }
        //at this point, values[k] is either less than or equal to insert item, or 
        //reached values[-1]
        values[k + 1] = insertitem;
        
    }
    return;
}

int main( int argc, char * argv[] )
{
	int height = 0, width = 0, MAXLEN;
	if (argc != 4 && argc != 6) //either default 4 args or +2 args for height and width
	{
		fprintf(stderr, " Invalid Number of Arguments to Pancake %s\n", strerror (errno));
		return 1;
	}
	char* initial;
	char* goal;
	if (argc == 4) //no height or width specified, checks command line args
	{
		char* strtolcheck;
		height = 3;
		width = 3;
		MAXLEN = strtol(argv[1], &strtolcheck, 10);
		if ((strcmp(strtolcheck, "") != 0) || MAXLEN <= 0 )
		{
			fprintf(stderr, " Invalid Value of MAXLEN: must be non negative integer %s\n", strerror (errno));
			return 1;
		}
		int charnum = height * width;
		int initialcount = strlen(argv[2]);
		int goalcount = strlen(argv[3]);
		initial = malloc(sizeof(char) * (initialcount + 1));
		goal = malloc(sizeof(char) * (goalcount + 1));
		strcpy(initial, argv[2]);
		strcpy(goal, argv[3]);
		if (initialcount != charnum || goalcount != charnum)
		{
			fprintf(stderr, " Initial or Goal does not have height*width characters %s\n", strerror (errno));
			free(initial);
			free(goal);
			return 1;
		}
		char* initialsort = malloc(sizeof(char) * (initialcount + 1));
		char* goalsort = malloc(sizeof(char) * (goalcount + 1));
		strcpy(initialsort, argv[2]);
		strcpy(goalsort, argv[3]);
		sort(initialsort, initialcount);
		sort(goalsort, goalcount);
		for (int i = 0; i < charnum; i++)
		{
			if (initialsort[i] != goalsort[i])
			{
				fprintf(stderr, " Initial and Goal do not have the same characters %s\n", strerror (errno));
				free(initial);
				free(goal);
				free(initialsort);
				free(goalsort);
				return 1;
			}
		}
		free(initialsort);
		free(goalsort);
	}
	else if (argc == 6) // if height and width specified
	{
		char* strtolcheck;
		height = atoi(argv[1]); //strtol instead 
		width = atoi(argv[2]);
		MAXLEN = strtol(argv[3], &strtolcheck, 10);
		if ((strcmp(strtolcheck, "") != 0) || MAXLEN <= 0 )
		{
			fprintf(stderr, " Invalid Value of MAXLEN: must be non negative integer %s\n", strerror (errno));
			return 1;
		}
		height = strtol(argv[1], &strtolcheck, 10);
		if ((strcmp(strtolcheck, "") != 0) || height < 1 || height > 16)
		{
			fprintf(stderr, " Invalid Value of height: must be between 1 and 16 %s\n", strerror (errno));
			return 1;
		}
		width = strtol(argv[2], &strtolcheck, 10);
		if ((strcmp(strtolcheck, "") != 0) || width < 1 || width > 16)
		{
			fprintf(stderr, " Invalid Value of width: must be between 1 and 16 %s\n", strerror (errno));
			return 1;
		}
		int charnum = height * width;
		int initialcount = strlen(argv[4]);
		int goalcount = strlen(argv[5]);
		initial = malloc(sizeof(char) * (initialcount + 1));
		goal = malloc(sizeof(char) * (goalcount + 1));
		strcpy(initial, argv[4]);
		strcpy(goal, argv[5]);
		if (initialcount != charnum || goalcount != charnum)
		{
			fprintf(stderr, " Initial or Goal does not have height*width characters %s\n", strerror (errno));
			free(initial);
			free(goal);
			return 1;
		}
		char* initialsort = malloc(sizeof(char) * (initialcount + 1));
		char* goalsort = malloc(sizeof(char) * (goalcount + 1));
		strcpy(initialsort, argv[4]);
		strcpy(goalsort, argv[5]);
		sort(initialsort, initialcount);
		sort(goalsort, goalcount);
		for (int i = 0; i < charnum; i++)
		{
			if (initialsort[i] != goalsort[i])
			{
				fprintf(stderr, " Initial and Goal do not have the same characters %s\n", strerror (errno));
				free(initialsort);
				free(goalsort);
				free(initial);
				free(goal);
				return 1;
			}
		}
		free(initialsort);
		free(goalsort);
	}
	//This means that the command line argument conditions are all met

	//check to see if all characters are printable
	int charnum = height * width;
	for (int i = 0; i < charnum; i++)
	{
		if (!isprint(initial[i]) || !isprint(goal[i]))
		{
			fprintf(stderr, " Initial and Goal do not have printable characters %s\n", strerror (errno));
			free(initial);
			free(goal);
			return 1;
		}
	}
	if (strcmp(initial,goal) == 0)
	{
		printf("%s\n", initial);
		free(initial);
		free(goal);
		exit(10);
	}
	Queue Q;
	createQ(&Q); // create the Queue to store Conf combinations
	hashtable goaltable; //Create a hashtable that can account for bi directional search
	//hashtable initialtable;
	createTable(&goaltable);
	char* iniconfig = malloc(sizeof(char)* (charnum + 1));
	strcpy(iniconfig, initial);
	char* goalconfig = malloc(sizeof(char) * (charnum + 1));
	strcpy(goalconfig, goal);
	//converted from pseudocode
	addQ(&Q, goalconfig);
	insertTable(goaltable, goalconfig, NULL, 0, 1);
	while(!isEmptyQ(&Q))
	{
		char* removedconfig;
		removeQ(&Q, &removedconfig);
		int L;
		inTable(goaltable, removedconfig, &L);
		if (L < MAXLEN)
		{
			L += 1;
			for (int i = 1; i <= height; i++)
			{
				for (int j = 1; j <= width; j++)
				{
					int counter = 1;
					bool vert = true;
					while(counter <= 2)
					{
						char* nextconfig;
						nextconfig = horizontalflip(removedconfig, i, j, height, width, vert);//all possible horizontal flips
						// printf("\nnextconfig is %s\n", nextconfig);
						int placehold;
						bool alreadyseen;
						char* fromconfig = calloc(charnum + 1, sizeof(char));
						strcpy(fromconfig, removedconfig);
						if (strcmp(nextconfig, iniconfig) == 0) //found the initial configuration
						{
							//printf("Print the steps using this configuration to retrace all the steps from hashtable\n");
							insertTable(goaltable, nextconfig, fromconfig, L , 1);
							printTable(goaltable, nextconfig);
							free(iniconfig);
							free(initial);
							free(goal);
							destroyQ(&Q);
							exit(0);
						}
						else if (!(alreadyseen = inTable(goaltable, nextconfig, &placehold)))
						{
							insertTable(goaltable, nextconfig, fromconfig, L , 1);
							addQ(&Q, nextconfig);
						}
						else
						{
							free(nextconfig);
							free(fromconfig);
						}
						counter++;
						vert = !vert;
					}

				}
			}
			
		}
	}
	//didn't find it
	free(iniconfig);
	free(initial);
	free(goal);
	destroyQ(&Q);


	exit(0);
	// return 0;


}


