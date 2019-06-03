#include <iostream>
#include <fstream>
#include <string.h>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#include <sstream>



using namespace std;

int rec_flag_acc=0,no_acc=0;
char rec_ind_acc[5];
struct account                  //structure for main account data
{
	char acc_no[20];
	char name[20];
	char age[5];
	char gender[10];
	char branch[20];
	char tbal[20];
	char celno[20];
	char ind[5];
}acc[20];

struct account1               //structure for secondary account data
{
	char acc_no[20];
	char name[20];
	char age[5];
	char gender[10];
	char branch[20];
	char tbal[20];
	char celno[20];
	char ind[5];
}accc[20],ttmp;


struct index                           //structure for index data
{
	char acc_no[20],indacc[20];
}insacc[20],temp;

void sort_index_acc()                   //To sort usn in index file
{
	int i,j;

	for(i=0;i<no_acc-1;i++)
	for(j=0;j<no_acc-i-1;j++)
	if(strcmp(insacc[j].acc_no,insacc[j+1].acc_no)>0)
	{
		temp=insacc[j];
		insacc[j]=insacc[j+1];
		insacc[j+1]=temp;
	}
}

void sort_record_acc()           //To sort data according to usn in acc.txt file
{
	int i,j;

	for(i=0;i<no_acc-1;i++)
	for(j=0;j<no_acc-i-1;j++)
	if(strcmp(accc[j].acc_no,accc[j+1].acc_no)>0)
	{
		ttmp=accc[j];
		accc[j]=accc[j+1];
		accc[j+1]=ttmp;
	}
}

void retrive_record_acc(char *ind)      //To retrive data using given index
{
	for(int i=0;i<no_acc;i++)
	{
		if(strcmp(acc[i].ind,ind)==0)
		{
			strcpy(rec_ind_acc,ind);
			rec_flag_acc=1;
			cout<<"Record found:\n";
			cout<<"Index\tAccount No.\tName\tAge\tBranch\tGender\tTotal Balance\tPhno\n";
			cout<<acc[i].ind<<"\t"<<acc[i].acc_no<<"\t\t"<<acc[i].name<<"\t"<<acc[i].age<<"\t"<<acc[i].branch<<"\t"<<acc[i].gender<<"\t"<<acc[i].tbal<<"\t\t"<<acc[i].celno<<"\n";
            return;
		}
	}
}

int search_index_acc(char *acc_no)         //To find index using given acc_no
{
	int flag=0;
	for(int i=0;i<no_acc;i++)
	{
		if(strcmp(insacc[i].acc_no,acc_no)==0)
		{
			retrive_record_acc(insacc[i].indacc);
			flag=1;
		}
	}
	if(flag)
		return 1;
	else
		return -1;
}

int search_id_acc(char *acc_no,int j)          //To check acc_no already exist or not
{
	int flag=-1;
	for(int i=0;i<j;i++)
	{
		if(strcmp(acc[i].acc_no,acc_no)==0)
		{
			flag=i;
			break;
		}
	}
	if(flag>=0)
		return flag;
	else
		return -1;
}

void delet_acc(char *acc_no)         //To delete account detail
{
	rec_flag_acc=0;
	int fr=0;
	search_index_acc(acc_no);
	if(!rec_flag_acc)
	{
		cout<<"Deletion failed.Record not found\n";
		return;

	}
	for(int i=0;i<no_acc;i++)
	{
		if(strcmp(acc[i].ind,rec_ind_acc)==0)
		{
			fr=i;
			break;
		}
	}
	for(int i=fr;i<no_acc-1;i++)
	{
		acc[i]=acc[i+1];
		char str[3];
		sprintf(str,"%d",i);
		strcpy(acc[i].ind,str);
	}
	no_acc--;
	fstream f1,f2,f3;
	f1.open("record_acc.txt",ios::out);
	f2.open("index_acc.txt",ios::out);
	f3.open("acc.txt",ios::out);
	for(int i=0;i<no_acc;i++)
	{
		strcpy(insacc[i].acc_no,acc[i].acc_no);
		strcpy(insacc[i].indacc,acc[i].ind);
		strcpy(accc[i].acc_no,acc[i].acc_no);
		strcpy(accc[i].ind,acc[i].ind);
		strcpy(accc[i].name,acc[i].name);
		strcpy(accc[i].age,acc[i].age);
		strcpy(accc[i].branch,acc[i].branch);
		strcpy(accc[i].gender,acc[i].gender);
		strcpy(accc[i].tbal,acc[i].tbal);
		strcpy(accc[i].celno,acc[i].celno);

	}
	sort_index_acc();
	sort_record_acc();
	for(int i=0;i<no_acc;i++)
	{
	    f1<<acc[i].ind<<"|"<<acc[i].acc_no<<"|"<<acc[i].name<<"|"<<acc[i].age<<"|"<<acc[i].branch<<"|"<<acc[i].gender<<"|"<<acc[i].tbal<<"|"<<acc[i].celno<<"\n";
		f2<<insacc[i].acc_no<<"|"<<insacc[i].indacc<<"\n";
		f3<<accc[i].ind<<"|"<<accc[i].acc_no<<"|"<<accc[i].name<<"|"<<accc[i].age<<"|"<<accc[i].branch<<"|"<<accc[i].gender<<"|"<<accc[i].tbal<<"|"<<accc[i].celno<<"\n";
	}
	f1.close();
	f2.close();
	f3.close();
	cout<<"Deletion successful\n";
	
}


void depo(char *id , int m)       //To deposite into account and save same in file
{

    
    int g;
    for (int k=0;k<no_acc;k++)
    {
        if(strcmp(accc[k].acc_no,id)==0)
        {
        	cout<<"deposition successful\n";
           int i=atoi(accc[k].tbal);
           i=i+m;
          char str[20];
            sprintf(str,"%d",i);
            strcpy(accc[k].tbal,str);
            g=k;
        }
    }
    fstream f1,f2,f3;
	f1.open("acc.txt",ios::out);
	f2.open("deposite.txt",ios::app);
	f3.open("record_acc.txt",ios::out);
	time_t my_time = time(NULL);
	int f=search_id_acc(id,no_acc);
	strcpy(acc[f].tbal,accc[g].tbal);
	if(f>=0){
		cout<<"acc_no|money|date&time\n";
		cout<<id<<"|"<<m<<"|"<<ctime(&my_time)<<"total balance = "<<accc[g].tbal<<"\n";
	f2<<id<<"|"<<m<<"|"<<ctime(&my_time)<<"total balance = "<<accc[g].tbal<<"\n";
}
else{
		cout<<"acc_no not found register your acc_no\n";
		return;
	}
    for(int k = 0;k<no_acc;k++ )
    {
         f3<<acc[k].ind<<"|"<<acc[k].acc_no<<"|"<<acc[k].name<<"|"<<acc[k].age<<"|"<<acc[k].branch<<"|"<<acc[k].gender<<"|"<<acc[k].tbal<<"|"<<acc[k].celno<<"\n";
        f1<<accc[k].ind<<"|"<<accc[k].acc_no<<"|"<<accc[k].name<<"|"<<accc[k].age<<"|"<<accc[k].branch<<"|"<<accc[k].gender<<"|"<<accc[k].tbal<<"|"<<accc[k].celno<<"\n";
    }
    f1.close();
    f2.close();
    f3.close();
    
}

void withdraw(char *id , int m)     //To withdraw into account and save same in file
{
int g;
    for (int k=0;k<no_acc;k++)
    {
        if(strcmp(accc[k].acc_no,id)==0)
        {
        int i=atoi(accc[k].tbal);
           i=i-m;
           if(i<0)
           {
           	cout<<"insufficant amount\n";
           	return;
           }
           else if(i>0){
           	 cout<<"withdrawal successful\n";
            char str[20];
            sprintf(str,"%d",i);
            strcpy(accc[k].tbal,str);
            g=k;
            break;
       }

        }
    }
    fstream f1,f2,f3;
	    f1.open("acc.txt",ios::out);
		f2.open("withdraw.txt",ios::app);
		f3.open("record_acc.txt",ios::out);
	time_t my_time = time(NULL);
	int f=search_id_acc(id,no_acc);
	strcpy(acc[f].tbal,accc[g].tbal);
	if(f>=0){
		cout<<"acc_no|money|date&time\n";
		cout<<id<<"|"<<m<<"|"<<ctime(&my_time)<<"total balance = "<<accc[g].tbal<<"\n";
	f2<<id<<"|"<<m<<"|"<<ctime(&my_time)<<"total balance = "<<accc[g].tbal<<"\n";
}
else{
		cout<<"acc_no not found register your acc_no\n";
		return;
	}
    for(int k=0;k<no_acc;k++)
    {
         f3<<acc[k].ind<<"|"<<acc[k].acc_no<<"|"<<acc[k].name<<"|"<<acc[k].age<<"|"<<acc[k].branch<<"|"<<acc[k].gender<<"|"<<acc[k].tbal<<"|"<<acc[k].celno<<"\n";
        f1<<accc[k].ind<<"|"<<accc[k].acc_no<<"|"<<accc[k].name<<"|"<<accc[k].age<<"|"<<accc[k].branch<<"|"<<accc[k].gender<<"|"<<accc[k].tbal<<"|"<<accc[k].celno<<"\n";
    }
    f1.close();
    f2.close();
    f3.close();
   
}

int main()                               //main function
{
	char acc_no[20];
	char name[20];
	char age[5];
	char gender[10];
	char branch[20];
	char tbal[20];
	char celno[20];
	char ind[5];
    int amount;
    int idd=100,pass=100;
	  fstream file1;
    int i=0,j,n,money;//for processing usage
    int choice;//for getting choice
    //Level 1-Display process
    system("CLS");
 cout<<"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\";
 cout<<"\n\n\t\t\t\t\t\t\t\t\tBANK RECORD MANAGEMENT SYSTEM\n\n";
 cout<<"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\";
 cout<<"\n\n\t\t\t\t\t\t\t\t\t\t HOME PAGE \n\n";
 cout<<"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\";
   cout<<"\n\n\t\t\t\tThis is a bank record management system,used to maintain the records of accounntholders  in the Bank\n\n";
 cout<<"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\";
 getch();
fstream f;
                f.open("record_acc.txt",ios::in);          //To read existing data from the file
                for(i=0;i<100;i++){
                	f.getline(ind,5,'|');
                	if(strcmp(ind,"")==0)
                		break;
						f.getline(acc_no,20,'|');
						f.getline(name,20,'|');
						f.getline(age,5,'|');
						f.getline(branch,20,'|');
						f.getline(gender,10,'|');
						f.getline(tbal,20,'|');
						f.getline(celno,20,'\n');
                        int m=atoi(ind); 
						if(i==m)
						no_acc++;
					else
						break;
                }
                f.close();
                fstream file2,f1;
					f1.open("acc.txt",ios::out);
					file1.open("record_acc.txt",ios::in);
					file2.open("index_acc.txt",ios::out);
					for(int i=0;i<no_acc;i++)
					{
						file1.getline(acc[i].ind,5,'|');
						file1.getline(acc[i].acc_no,20,'|');
						file1.getline(acc[i].name,20,'|');
						file1.getline(acc[i].age,5,'|');
						file1.getline(acc[i].branch,20,'|');
						file1.getline(acc[i].gender,10,'|');
						file1.getline(acc[i].tbal,20,'|');
						file1.getline(acc[i].celno,20,'\n');
						strcpy(acc[i].ind,acc[i].ind);
						strcpy(insacc[i].acc_no,acc[i].acc_no);
						strcpy(insacc[i].indacc,acc[i].ind);
						strcpy(accc[i].acc_no,acc[i].acc_no);
						strcpy(accc[i].ind,acc[i].ind);
						strcpy(accc[i].name,acc[i].name);
						strcpy(accc[i].age,acc[i].age);
						strcpy(accc[i].branch,acc[i].branch);
						strcpy(accc[i].gender,acc[i].gender);
						strcpy(accc[i].tbal,acc[i].tbal);
						strcpy(accc[i].celno,acc[i].celno);
					}
					sort_index_acc();
					sort_record_acc();
					for(int i=0;i<no_acc;i++)
					{
					    f1<<accc[i].ind<<"|"<<accc[i].acc_no<<"|"<<accc[i].name<<"|"<<accc[i].age<<"|"<<accc[i].branch<<"|"<<accc[i].gender<<"|"<<accc[i].tbal<<"|"<<accc[i].celno<<"\n";
                        file2<<insacc[i].acc_no<<"|"<<insacc[i].indacc<<"\n";
					}
					f1.close();
					file1.close();
					file2.close();
while(1)//outer loop
{
	getch();
	system("CLS");
	cout<<"\n1. Admin Login\n";
	cout<<"2. User Login\n";
	cout<<"3. Exit\n";
cout<<"Enter your choice: "<<endl;
cin>>choice;
switch (choice)
{
	case 1:
	{
		
	l1: cout<<"enter admin id\n";
	cin>>idd;
	cout<<"enter password\n";
	cin>>pass;
	if(idd!=100 || pass!=100)
	{
		cout<<"worng id or password\n";
		goto l1;
	}
	do{
		cout<<"enter key to continue\n";
     		getch();
     		system("CLS");
	cout<<"\n\n1.Add New Account\n";
cout<<"2.Find account details\n";
cout<<"3.Remove account\n";
cout<<"4.Display record Branch wise\n";
cout<<"5.Display all record\n";
cout<<"6.Exit\n";
cout<<"Enter your choice: "<<endl;
cin>>choice;
switch (choice){
    case 1://Insert data
    {
    	

                cout<<"enter the no of acc:\t";
                cin>>n;
        file1.open("record_acc.txt",ios::app|ios::out);
                cout<<"enter the details\n";
                for(i = no_acc;i<no_acc+n;i++)
				{
					label: cout<<"enter "<<i+1<<" acc details:\n";
					cout<<"Account No : ";
					cin>>acc[i].acc_no;
					cout<<"Name : ";
					cin>>acc[i].name;
					cout<<"Age : ";
					cin>>acc[i].age;
					cout<<"Branch : ";
					cin>>acc[i].branch;
					cout<<"Gender : ";
					cin>>acc[i].gender;
					cout<<"Total Balance : ";
					cin>>acc[i].tbal;
					cout<<"Contact Number : ";
					cin>>acc[i].celno;
					int q = search_id_acc(acc[i].acc_no,i);
					if(q==1)
					{
						cout<<"Duplicate value\n";
						cout<<"enter again:\n";
						goto label;
					}
					file1<<i<<"|"<<acc[i].acc_no<<"|"<<acc[i].name<<"|"<<acc[i].age<<"|"<<acc[i].branch<<"|"<<acc[i].gender<<"|"<<acc[i].tbal<<"|"<<acc[i].celno<<"\n";

				}
				no_acc=no_acc+n;
                file1.close();
					fstream file1,file2,f1;
					f1.open("acc.txt",ios::out);
					file1.open("record_acc.txt",ios::in);
					file2.open("index_acc.txt",ios::out);
					for(int i=0;i<no_acc;i++)
					{
						file1.getline(ind,5,'|');
						file1.getline(acc_no,20,'|');
						file1.getline(name,20,'|');
						file1.getline(age,5,'|');
						file1.getline(branch,20,'|');
						file1.getline(gender,10,'|');
						file1.getline(tbal,20,'|');
						file1.getline(celno,20,'\n');
						strcpy(acc[i].ind,ind);
						strcpy(insacc[i].acc_no,acc_no);
						strcpy(insacc[i].indacc,ind);
						strcpy(accc[i].acc_no,acc_no);
						strcpy(accc[i].ind,ind);
						strcpy(accc[i].name,name);
						strcpy(accc[i].age,age);
						strcpy(accc[i].branch,branch);
						strcpy(accc[i].gender,gender);
						strcpy(accc[i].tbal,tbal);
						strcpy(accc[i].celno,celno);
					
					}
					sort_index_acc();
					sort_record_acc();
					for(int i=0;i<no_acc;i++)
					{
					    f1<<accc[i].ind<<"|"<<accc[i].acc_no<<"|"<<accc[i].name<<"|"<<accc[i].age<<"|"<<accc[i].branch<<"|"<<accc[i].gender<<"|"<<accc[i].tbal<<"|"<<accc[i].celno<<"\n";
                        file2<<insacc[i].acc_no<<"|"<<insacc[i].indacc<<"\n";
					}
					f1.close();
					file1.close();
					file2.close();
				}
break;
case 2://search data
{
                cout<<"Enter the Id of the acc_no whose record is to be searched:\t";
				cin>>acc_no;
				int q=search_index_acc(acc_no);
				if(q==1){
					cout<<"Search successful\n";
					cout<<"Press any key to continue\n";
                    getch();
				}
				else{
					cout<<"Search unsuccessful\n";
					cout<<"Press any key to continue\n";
                    getch();
				}

}
break;

case 3://delete data

    {
                cout<<"Enter the Id of the acc_no whose record is to be deleted:\t";
				cin>>acc_no;
				delet_acc(acc_no);
    }
    break;
case 4://display students batch-wise
    {
        char bat[20];
        cout<<"Enter the  branch you want to display details\n";
        cin>>bat;
        cout<<"Index\tAccount No.\tName\t Age\tBranch\tGender\tTotal Balance\tPhno\n";
        for(int k = 0;k<no_acc;k++)
        {
            if(strcmp(accc[k].branch,bat)==0)
            {
			cout<<k<<"\t"<<accc[k].acc_no<<"\t\t"<<accc[k].name<<"\t"<<accc[k].age<<"\t"<<accc[k].branch<<"\t"<<accc[k].gender<<"\t"<<accc[k].tbal<<"\t\t"<<accc[k].celno<<"\n";
            }
        }
    }
    break;
case 5://display all data
			{
				fstream f1;
				f1.open("acc.txt",ios::in);
				if(!f1)
				{
					cout<<"Error!!!";
					exit(0);
				}
				int i=0;
				 cout<<"Index\tAccount No.\tName\t  Age\tBranch\tGender\tTotal Balance\tPhno\n";
				while(i<no_acc)
				{
				   
			cout<<i<<"\t"<<accc[i].acc_no<<"\t\t"<<accc[i].name<<"\t  "<<accc[i].age<<"\t"<<accc[i].branch<<"\t"<<accc[i].gender<<"\t"<<accc[i].tbal<<"\t\t"<<accc[i].celno<<"\n";
				i++;
				}
				if(i==0)
					cout<<"Record is empty\n";
				f1.close();
			}
			break;
case 6: //exit
           cout<<"Have a nice day\n Exiting now\n";
           exit(0);

default :
         cout<<"Invalid input\n";
         break;
     }
 }while(choice<=6);
 }
 break;
     case 2:{
     	do{
     		cout<<"enter key to continue\n";
     		getch();
     		system("CLS");
     cout<<"\n1. Open New Account\n";
     cout<<"2. Get Account Details\n";
     cout<<"3.Deposite\n";
     cout<<"4.Withdraw\n";
     cout<<"5.Exit\n";
     cout<<"Enter your choice: "<<endl;
     cin>>choice;
switch (choice){
	case 1://Insert data
    {
    	
        file1.open("record_acc.txt",ios::app|ios::out);
					labe2: cout<<"enter acc details:\n";
					cout<<"Account No : ";
					cin>>acc[i].acc_no;
					cout<<"Name : ";
					cin>>acc[i].name;
					cout<<"Age : ";
					cin>>acc[i].age;
					cout<<"Branch : ";
					cin>>acc[i].branch;
					cout<<"Gender : ";
					cin>>acc[i].gender;
					cout<<"Total Balance : ";
					cin>>acc[i].tbal;
					cout<<"Contact Number : ";
					cin>>acc[i].celno;
					int q = search_id_acc(acc[i].acc_no,i);
					if(q==1)
					{
						cout<<"Duplicate value\n";
						cout<<"enter again:\n";
						goto labe2;
					}
					file1<<i<<"|"<<acc[i].acc_no<<"|"<<acc[i].name<<"|"<<acc[i].age<<"|"<<acc[i].branch<<"|"<<acc[i].gender<<"|"<<acc[i].tbal<<"|"<<acc[i].celno<<"\n";
				no_acc=no_acc+1;
                file1.close();
					fstream file1,file2,f1;
					f1.open("acc.txt",ios::out);
					file1.open("record_acc.txt",ios::in);
					file2.open("index_acc.txt",ios::out);
					for(int i=0;i<no_acc;i++)
					{
						file1.getline(ind,5,'|');
						file1.getline(acc_no,20,'|');
						file1.getline(name,20,'|');
						file1.getline(age,5,'|');
						file1.getline(branch,20,'|');
						file1.getline(gender,10,'|');
						file1.getline(tbal,20,'|');
						file1.getline(celno,20,'\n');
						strcpy(acc[i].ind,ind);
						strcpy(insacc[i].acc_no,acc_no);
						strcpy(insacc[i].indacc,ind);
						strcpy(accc[i].acc_no,acc_no);
						strcpy(accc[i].ind,ind);
						strcpy(accc[i].name,name);
						strcpy(accc[i].age,age);
						strcpy(accc[i].branch,branch);
						strcpy(accc[i].gender,gender);
						strcpy(accc[i].tbal,tbal);
						strcpy(accc[i].celno,celno);
					
					}
					sort_index_acc();
					sort_record_acc();
					for(int i=0;i<no_acc;i++)
					{
					    f1<<accc[i].ind<<"|"<<accc[i].acc_no<<"|"<<accc[i].name<<"|"<<accc[i].age<<"|"<<accc[i].branch<<"|"<<accc[i].gender<<"|"<<accc[i].tbal<<"|"<<accc[i].celno<<"\n";
                        file2<<insacc[i].acc_no<<"|"<<insacc[i].indacc<<"\n";
					}
					f1.close();
					file1.close();
					file2.close();
				}
break;
case 2://search data
{
                cout<<"Enter the Id of the acc_no whose record is to be searched:\t";
				cin>>acc_no;
				int q=search_index_acc(acc_no);
				if(q==1){
					cout<<"Search successful\n";
					cout<<"Press any key to continue\n";
                    getch();
				}
				else{
					cout<<"Search unsuccessful\n";
					cout<<"Press any key to continue\n";
                    getch();
				}

}
break;
case 3: //deposite money
           cout<<"deposite money to the acc_no\n";
           cout<<"enter acc_no\n";
           cin>>acc_no;
           cout<<"enter the money\n";
           cin>>money;
           depo(acc_no,money);
           break;
case 4: //withdraw money
           cout<<"withdraw money from the acc_no\n";
           cout<<"enter acc_no\n";
           cin>>acc_no;
           cout<<"enter the money\n";
           cin>>money;
           withdraw(acc_no,money);
           break;
case 5: //exit
           cout<<"Have a nice day\n Exiting now\n";
           exit(0);

default :
         cout<<"Invalid input\n";
         break;           

}
}while(choice<=5);
}
break;
case 3:
cout<<"Have a nice day\n Exiting now\n";
           exit(0);

default :
         cout<<"Invalid input\n";
         break; 
}
}
}