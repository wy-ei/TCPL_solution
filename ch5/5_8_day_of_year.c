/*
 * 5-8. There is no error checking in day_of_year or month_day . Remedy this defect.
 *
 * wy-ei 2015.2.9
*/

#include <stdio.h>
#include <stdlib.h>

static char daytab[][12]={
	{31,28,31,30,31,30,31,31,30,31,30,31},
	{31,29,31,30,31,30,31,31,30,31,30,31}
};

int day_of_year(int year,int month,int day);
void month_day(int year,int days,int *month,int *day);

int main(){
	int year = 2015,month = 10,day = 1;

	int days = day_of_year(year,month,day);
	
	if(days==-1){
		printf("error:wrong input.\n");
	}else{
		printf("%d-%d-%d is the %dth day in %d\n",year,month,day,days,year);
	}

	days+=1;

	month_day(year,days,&month,&day);
	
	printf("The %dth day in %d is %d-%d\n",days,year,month,day);
	
	return EXIT_SUCCESS;
}

int day_of_year(int year,int month,int day){
	if(month>12||month<1){
		return -1;
	}	
	int leap = (year%4==0&&year%100!=0)||year%400==0;
	if(day>daytab[leap][month-1]||day<1){
		return -1;
	}

	int i;
	for(i=0;i<month-1;i++){
		day+=daytab[leap][i];
	}
	return day;
}

void month_day(int year,int days,int *month,int *day){
	int leap = (year%4==0&&year%100!=0)||year%400==0;
		
	int nday = leap==0?365:366;

	if(days>nday){
		printf("error:There is only %d days in This year .\n",nday);
		*month=-1;
		*day=-1;
	}else if(days<0){
		printf("error:wrong input.\n");
	}else{
		int i;
		for(i=0;days>daytab[leap][i];i++){
			days-=daytab[leap][i];
		}	
		*month=i+1;
		*day=days;
	}
}
