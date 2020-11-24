#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include <assert.h>
#include<time.h>

//color code definition
#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"


//convert string to uppercase
void stringToUpper(char name[100])
{
	int i;
	
	for (i = 0; name[i]!='\0'; i++)
	{
      	if(name[i]>='a' && name[i]<='z')
		{
         	name[i] = name[i]-32;
      	}
   	}
}

//generate Quiz Questions
int generateQuizTest()
{
	int num=10;
	int arr[num];
	int i,j;
	int temp;
	int count=0;
	
	srand(time(0));
	
	//generate random number and store unique umber in array
	for(i=0;i<num;i++)
	{
		temp=rand()%30;
		
		for(j=0;j<i;j++)
		{
			if(temp==arr[j])
			{
				break;
			}
		}
		
		if(i==j)
		{
			arr[i]=temp;
		}
		else
		{
			i--;
		}
	}
	
	//for generating random question
	for(i=0;i<num;i++)
	{
		system("cls");
		char ch;
		int lineNumber=(arr[i])*4;

		static const char filenameQ[] = "question.txt";
		FILE *ques_file = fopen(filenameQ, "r");
		int countQues = 0;
	
		if ( ques_file != NULL )
		{
    		char line[1000];
    		
    		while (fgets(line, sizeof line, ques_file) != NULL)
    		{
        		if (countQues == lineNumber)
        		{
        			printf(WHT "\n\t\t\tQuestion No. %d\n\n" WHT,i+1);
        			printf(YEL);
	            	puts(line);
	            	fgets(line, sizeof line, ques_file);
	            	puts(line);
	            	fgets(line, sizeof line, ques_file);
	            	puts(line);
	            	break;
        		}
        		else
        		{
           			countQues++;
        		}
    		}
    	
    		fclose(ques_file);
		}
		else
		{
    		printf("File does not exist. Please create a Question File!");
    		return 0;
		}
		
		option:
		printf(" Your option : ");
		scanf(" %c",&ch);
		ch=toupper(ch);
		
		if(ch!='A' && ch!='B' && ch!='C' && ch!='D')
		{
			printf(" Enter valid Option!\n");
			goto option;
		}
		
		static const char filenameA[] = "answer.txt";
		FILE *ans_file = fopen(filenameA, "r");
		int countAns = 0;
		int lineAnswer=(arr[i])*3;
		
		if ( ans_file != NULL )
		{
    		char answer[1000];
    		
    		while (fgets(answer, sizeof answer, ans_file) != NULL)
    		{
        		if (countAns == lineAnswer)
        		{
	            	char out=answer[1];
	            	
	            	if(ch==out)
	            	{
	            		printf(GRN "\nYour Answer is Correct!" GRN);
	            		printf(YEL);
	            		count=count+4;
	            		Beep(650, 100);
					}
					else
					{
						printf(RED "\nWrong Answer!\n" RED);
						printf(YEL);
						printf("Correct Answer : %c)",out);
						fgets(answer, sizeof answer, ans_file);
						puts(answer);
						count=count-1;
						Beep(1000, 100);
					}
					
					break;
					
        		}
        		else
        		{
           			countAns++;
        		}
    		}
    	
    		fclose(ans_file);
		}
		else
		{
    		printf("File does not exist. Please create a Answer File!");
    		return 0;
		}
		
		getch();
		
	}
	
	return count;
	
}

//to display highest score
void showHighest()
{
	system("cls");
	char name[100];
	int scr;
	FILE *f;
	f=fopen("score.txt","r");
	
	if(f==NULL)
	{
		printf("\n\n\t\t*************************************************************");
		printf("\n\n\t\t\t\tNo one has Participated Yet!");
		printf("\n\n\t\t*************************************************************");
		fclose(f);
		getch();
		return;
	}
	
	fscanf(f,"%s%d",&name,&scr);
	
	printf("\n\n\t\t*************************************************************");
	printf("\n\n\t\t %s has secured the Highest Marks : %d",name,scr);
	printf("\n\n\t\t*************************************************************");
	fclose(f);
	getch();
}

//to reset the program
void resetScore()
{
	system("cls");
    
   	if (remove("score.txt")==0 && remove("record.txt")==0) 
	{
		printf("\n\n\t\t*******************************************************************");
		printf("\n\n\t\t\t\t Reset Succesfull! Press any key to enter Home Page.");
		printf("\n\n\t\t*******************************************************************"); 
	}
   	else
    {
    	printf("\n\n\t\t*******************************************************************");
		printf("\n\n\t\t\t\tNo score available Currently.");
		printf("\n\n\t\t*******************************************************************");
	}
	
}

//for Quiz Game Rules
void help()
{
	system("cls");
	printf(CYN);
    printf("\n\n                              HELP");
    printf("\n -------------------------------------------------------------------------------------");
    printf("\n ......................... C program Quiz Game........................................");
    printf("\n >> Your game starts with the CHALLANGE ROUND. In this round you will be asked");
    printf("\n    total 10 questions each right answer will award score of 10 points.");
    printf("\n    By this way you can gain points depending upon number of correct answers!!!!!.....");
    printf("\n >> You will be given 4 options and you have to press A, B ,C or D for the");
    printf("\n    right option");
    printf("\n >> You will be asked questions continuously if you keep giving the right answers.");
    printf("\n >> There is Negative marking for wrong answers, 1 marks will be deducted for each wrong answer.");

	printf("\n\n ****************************BEST OF LUCK***********************************");
	printf(YEL);

}

//to save record of every participant
void saveRecord(int score, char plnm[100])
{
	system("cls");
	
	//store time in a variable
	time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char s[64];
    assert(strftime(s, sizeof(s), "%c", tm));
    
	FILE *f;
	f=fopen("record.txt","a+");
	fprintf(f,"%s\n%d\n%s\n\n",plnm,score,s);
	fclose(f);
}

//to update highest score if new topper comes
void editHighest(int score, char plnm[100])
{
	system("cls");
	int sc=0;
	char nm[100];
	FILE *f;
	f=fopen("score.txt","r");
	fscanf(f,"%s%d",&nm,&sc);
	
	if (score>=sc)
	{ 
		sc=score;
	    fclose(f);
	    f=fopen("score.txt","w");
	    fprintf(f,"%s\n%d",plnm,sc);
	    fclose(f);
	}
}

//to search record by name
void searchRecord()
{
	system("cls");
    FILE *f;
	f=fopen("record.txt","r");
	
	if(f==NULL)
	{
		printf("\n\n\t\t*************************************************************");
		printf("\n\n\t\t\t\tNo one has Participated Yet!");
		printf("\n\n\t\t*************************************************************");
		fclose(f);
		getch();
		return;
	}
	else
	{
		char searchName[100];
		int i;
    	printf("\n\n\n\n\n\n\n\n\n\n\t\t\tEnter Name that is to be Searched: " MAG);
    	scanf(" %s",&searchName);
    	printf(YEL);
    	
    	//convert string to uppercase
    	stringToUpper(searchName);
    	
    	char record[100];
    		
    	while (fgets(record, sizeof record, f) != NULL)
    	{
        	char matchName[100];
        	int score;
        	char time[100];
        	system("cls");
        	int flag=1;
        	strcpy(matchName, record);
        	
        	//convert string to uppercase
    		stringToUpper(matchName);
   			
   			//matching two string for equality
   			for(i=0;searchName[i]!='\0';i++)
   			{
   				if(matchName[i]!=searchName[i])
   				{
   					flag=0;
   					break;
				}
			}
   			
   			if(flag==1)
   			{
   				printf("\n\n\t\tDetails of Required Student is : ");
   				puts(record);
   				fgets(record, sizeof record, f);
   				printf("\t\tScore : ");
   				puts(record);
   				fgets(record, sizeof record, f);
   				printf("\t\tTime [mm/dd/yy] [hh:mm:ss] : ");
   				puts(record);
   				break;
   				
			}
			
			fgets(record, sizeof record, f);
			fgets(record, sizeof record, f);
			fgets(record, sizeof record, f);
			
    	}
    	
    		fclose(f);
	}
	
	
}


//main starts here
int main()
{
    int score,i;
    char choice;
    char playername[100];
     
    mainhome:
    system("cls");
    
    printf("\n");
    printf(RED "\t\t\t\t  QUIZ GAME\n" RED);
    printf(YEL "\t\t______________________________________________" YEL);
    printf("\n\n\t\t\t   WELCOME to the Quiz Show");
    printf("\n\t\t______________________________________________");
    printf("\n\t\t______________________________________________");
    printf("\n\n\t\t > Press S to start the game");
    printf("\n\t\t > Press V to view the Highest score  ");
    printf("\n\t\t > Press R to Reset score");
    printf("\n\t\t > Press F to Search Record");
    printf("\n\t\t > press H for Help            ");
    printf("\n\t\t > press Q to Quit             ");
    printf("\n\t\t______________________________________________\n");
    printf(CYN "\t\t\t\t Created by Yogesh and Saurabh             " CYN);
    choice=toupper(getch());
     
    if (choice=='V')
	{
		Beep(550, 100);
		showHighest();
		goto mainhome;
	}
    else if (choice=='H')
	{
		help();
		Beep(550, 100);
		getch();
		goto mainhome;
	}
	else if (choice=='R')
	{
		resetScore();
		Beep(550, 100);
		getch();
		goto mainhome;
	}
	else if (choice=='F')
	{
		Beep(550, 100);
		searchRecord();
		Beep(550, 100);
		getch();
		goto mainhome;
	}
	else if (choice=='Q')
	{
		Beep(550, 100);
		exit(1);
	}
    else if(choice=='S')
    {
    	Beep(750, 200);
    	system("cls");

    	printf("\n\n\n\n\n\n\n\n\n\n\t\t\tResister your name: " MAG);
    	scanf(" %s",&playername);
    	printf(YEL);

    	system("cls");
    	printf(CYN);
    	printf("\n ------------------  Welcome %s to General Knowledge Quiz Game --------------------------",playername);
    	Beep(550, 100);
    	printf("\n\n Here are some tips you might wanna know before playing:");
    	printf("\n -------------------------------------------------------------------------");
    	printf("\n >> Your game starts with CHALLANGE ROUND. In this round you will be asked a");
    	printf("\n    total of 10 questions. Each right answer will award score of 10 points.");
    	printf("\n    By this way you can gain points depending upon number of correct answers!!!!!..........");
    	printf("\n >> You will be given 4 options and you have to press A, B ,C or D for the");
    	printf("\n    right option.");
    	printf("\n >> You will be asked questions continuously, till right answers are given");
    	printf("\n >> No negative marking for wrong answers!");
    	printf("\n\n\t\t!!!!!!!!!!!!! ALL THE BEST !!!!!!!!!!!!!");
    	printf(YEL);
    	printf("\n\n\n Press Y  to Start the Game!\n");
    	printf("\n Press any other key to return to the main menu!");
    
    	if (toupper(getch())=='Y')
		{
			Beep(550, 100);
			goto test;
    	}
		else
		{
			Beep(750, 100);
    		goto mainhome;
    		system("cls");
    	}
	
    	test:
    	system("cls");
		
		game:
    	score=generateQuizTest();
	
    	system("cls");
	
		if(score>0)
		{
	   		printf("\n\n\t\t**************** CONGRATULATION *****************");
	    	printf("\n\t\t\t        You scored %d points.",score);
			goto go;
		}
		else if(score<0)
		{
	 		printf("\n\n\t******** SORRY YOU SCORED NEGATIVE MARKS! PREPARE HARD. ********");
	    	printf("\n\t\t\t Thanks for your Participation.");
			goto go;
		}
		else
		{
	 		printf("\n\n\t******** SORRY YOU SCORED ZERO! BETTER LUCK NEXT TIME. ********");
	    	printf("\n\t\t\t Thanks for your Participation.");
			goto go;
		}

		go:
		puts("\n\n\t\t\t Press any key if you want to go main menu");
		Beep(750, 100);
		getch();
		
		saveRecord(score,playername);
		editHighest(score,playername);
		goto mainhome;
	}
	
	return 0;
	
}

