#include<stdio.h>
#include<math.h>


typedef struct
{
  int  burst_time;
  int priority;
  int priority_component;
  int shortness_component;
  int context_switch_component; 
  int ITS;
  int remaining_time;

}process;

void initialAssignment(process ProcessArray[],int n);




int OTS; //global variable (Original time slice)




process input(int i)
{
  process p1;
  printf("Enter the burst_time of the process %d",i+1);
  scanf("%d",&p1.burst_time);
  printf("Enter the priority of the process %d",i+1);
  scanf("%d",&p1.priority);

  return p1;
}


process display(process p1)
{
  printf("The burst time of the current process is %d",p1.burst_time);
  printf("The priority of the current process is %d\n",p1.priority);
    printf("The priority of the current process is %d\n",p1.priority_component);
      printf("The priority of the current process is %d\n",p1.shortness_component);
        printf("The priority of the current process is %d\n",p1.ITS);

}

//function to calculate its

void initialAssignment(process ProcessArray[],int n)
{
  printf("%d",ProcessArray[0].burst_time);
  //pc , get the highest priority and set pc=1 of those and rest 0
 // printf("%d\n",sizeof(processArray));
  //printf("%d",sizeof(processArray[0]));
  
 //int n=sizeof(ProcessArray)/sizeof(ProcessArray[0]);

 //remaining time equal to burst time 

 for(int i=0;i<n;i++)
 {
   ProcessArray[i].remaining_time=ProcessArray[i].burst_time;

 }




  printf("n is %d\n",n);
  int highest_priority;
  int min=0;




  for(int i=0;i<n;i++)
  {
    if(ProcessArray[i].priority < ProcessArray[min].priority)
    {
      min=i;
      printf("%d",min);
    }
    
    else
    {continue;}
      //continue;}
  }

  //here min is the minimum index priority 

  for(int i=0;i<n;i++)
  {
    if(ProcessArray[i].priority == ProcessArray[min].priority)
    {
      ProcessArray[i].priority_component=1;
    }

    else
    {
      ProcessArray[i].priority_component=0;
    }
  }
// till here we have set the pc

//now we have to set sc

ProcessArray[0].shortness_component=0;

for(int i=1;i<n;i++)
{
  if(ProcessArray[i].burst_time < ProcessArray[i-1].burst_time)
  {
    ProcessArray[i].shortness_component=1;
  }
  
  else
  {
    ProcessArray[i].shortness_component=0;
  }
}

//now we have to calculate CSC

for(int i=0;i<n;i++)
{
  ProcessArray[i].ITS=OTS+ProcessArray[i].shortness_component + ProcessArray[i].priority_component;
}




}

int  checkArray(int Array[], int n)
{

  //if all 0 return 0
 //0-executed
 //1-pending

 int check=0;
 for(int i=0;i<n;i++)
 {
   if(Array[i]==1)
   {
     check=1;
     break;
   }

   else
   {
     continue;
   }
 }

 return check; 

}







int main()
{
  int n;
  

  printf("Enter the total number of processes");
  scanf("%d",&n);
  int timeq[n][10];
  int ready[n];
  int remaining_time[n];


  for(int i=0;i<n;i++){
    ready[i]=1;
  }
  process processArray[n];


  for(int i=0;i<n;i++)
  {
    processArray[i]=input(i);
  }



  printf("Enter the value of Original time slice");
  scanf("%d",&OTS);
  
  initialAssignment(processArray,n);

  int round=0;

  while(checkArray(ready,n)==1){
    for(int i=0;i<n;i++){


      if(i==0)
      {

        if(processArray[i].shortness_component==0)
        {
          timeq[i][round]=(int)ceil((double)(processArray[i].ITS/2));

        }

        else
        {
          timeq[i][round]=processArray[i].ITS;
        }



      }

      else
      {

         if(processArray[i].shortness_component==0)
        {
          timeq[i][round]=(int)ceil((double)(timeq[i-1][round]+ timeq[i-1][round]/2));
        }

        else
        {
          timeq[i][round]=2*timeq[i-1][round];
        }
        
    }
      if(processArray[i].remaining_time>0){
      processArray[i].remaining_time=processArray[i].remaining_time- timeq[i][round];
      }

      if(processArray[i].remaining_time-timeq[i][round]<=2)
      {
        timeq[i][round]=processArray[i].remaining_time;
      }
      
    }


    round++;
  }







  //1.Calculate the ITS for all the processes
  
  for(int i=0;i<n;i++)
  {
    display(processArray[i]);
  }


}