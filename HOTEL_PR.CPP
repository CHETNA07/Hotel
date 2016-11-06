#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<string.h>
#include<stdio.h>
#include<process.h>

class hotel
{
   int room_no;
   char room_type[10];
   char name[20];
   char address[50];
   char phone_no[10];

   public:
   void  main_menu();
   void add();
   void display();
   void rooms();
   void edit();
   int check(int);
   void modify(int);
   void delete_rec(int);
};

void hotel::main_menu()
{
 int choice;


// while(choice=='1'||choice=='2'||choice=='3'||choice=='4')
 {
  clrscr();
  cout<<"\t\t\t\tMAIN MENU\n";
  cout<<"\t\t\t..................\n";
  cout<<"1. Book a room\n";
  cout<<"2. Customer Record\n";
  cout<<"3. Rooms Allotted\n";
  cout<<"4. Edit Record\n";
  cout<<"5. Exit\n";
  cout<<"\n\n\t\tEnter your choice : ";
  cin>>choice;

  switch(choice)
  {
   case 1:add();
	  break;
   case 2:display();
	  break;
   case 3:rooms();
	  break;
   case 4:edit();
	  break;
  }
 }
}

void hotel::add()
{
 clrscr();
 int r,flag;
 char ans;
 ofstream fout("Record.dat",ios::out);
 cout<<"Enter room type : ";
 gets(room_type);
 cout<<"\n\n\tRoom No. :";
 cin>>r;
 flag=check(r);

 if(flag)
  cout<<"\nRoom is already booked !!!\n";
 else
  {
   cout<<"\nEnter Customer Details";
   cout<<"\n------------------------------";
   room_no=r;
   cout<<"Name :";
   gets(name);
   cout<<"Address : ";
   gets(address);
   cout<<"Phone no. :";
   gets(phone_no);
   fout.write((char*)this,sizeof(hotel));
   cout<<"\nRoom has been booked !!";
  }

  cout<<"\nPress 'y' key to continue or 'n' to exit !";
  cin>>ans;
  if(ans=='y')
  {
   main_menu();
  }
  else if(ans=='n')
  {
   exit(0);
  }
  getch();
  fout.close();

}

void hotel::display()
{
 clrscr();
 int r,flag;
 char ans;
 ifstream fin("Record.dat",ios::in);
 cout<<"\nEnter the room no : ";
 cin>>r;

 while(!fin.eof())
 {
  fin.read((char*)this,sizeof(hotel));
  if(r==room_no)
  {
   cout<<"\nThe customer details are as follows : \n\n";
   cout<<"Name : ";
   puts(name);
   cout<<"\nAddress : ";
   puts(address);
   cout<<"\nContact Details : ";
   puts(phone_no);
   flag=1;
   break;
  }
  if(flag==0)
  {
   cout<<"\nDetails of the customer not found.\n";
  }

  cout<<"\nPress 'y' key to continue or 'n' to exit !";
  cin>>ans;
  if(ans=='y')
  {
   main_menu();
  }
  else if(ans=='n')
  {
   exit(0);
  }
  getch();
  fin.close();
 }
}

void hotel::rooms()
{
 clrscr();
 char ans;
 ifstream fin("Record.dat",ios::in);
 cout<<"\n\t\t List of Rooms allotted";
 cout<<"\n\t\t----------------------------";
 cout<<"\n\nRoom No. \t Address \t\t\t Phone No. \n";

 while(!fin.eof())
 {
  fin.read((char*)this,sizeof(hotel));
  cout<<"\n\n"<<room_no<<"\t\t"<<name;
  cout<<"\t\t"<<address<<"\t\t"<<phone_no;
 }

 cout<<"\nPress 'y' key to continue or 'n' to exit !";
  cin>>ans;
  if(ans=='y')
  {
   main_menu();
  }
  else if(ans=='n')
  {
   exit(0);
  }
 getch();
 fin.close();
}

void hotel::edit()
{
 clrscr();
 char ans;
 int choice, r;

 cout<<"\n EDIT MENU";
 cout<<"\n---------------";
 cout<<"\n\n1. Modify Customer Record";
 cout<<"\n\n2. Delete Customer Record";

 cout<<"\nEnter your choice : ";
 cin>>choice;
 clrscr();
 cout<<"\nEnter room no :";
 cin>>r;

 switch(choice)
 {
  case 1:modify(r);
	 break;
  case 2:delete_rec(r);
	 break;
  default:cout<<"\n Wrong Choice...!!";
 }

 cout<<"\nPress 'y' key to continue or 'n' to exit !";
  cin>>ans;
  if(ans=='y')
  {
   main_menu();
  }
  else if(ans=='n')
  {
   exit(0);
  }
 getch();
}

int hotel::check(int r)
{
 int flag=0;
 ifstream fin("Record.dat",ios::in);
 while(!fin.eof())
 {
  fin.read((char*)this,sizeof(hotel));
  if(room_no==r)
  {
   flag=1;
   break;
  }
 }
 fin.close();
 return(flag);
}

void hotel::modify(int r)
{
 long pos,flag=0;
 fstream file("Record.dat",ios::in|ios::out|ios::binary);

 while(!file.eof())
 {
  pos=file.tellg();
  file.read((char*)this,sizeof(hotel));
  if(room_no==r)
  {
   cout<<"\nEnter New Details";
   cout<<"\n------------------------";
   cout<<"\nName : ";
   gets(name);
   cout<<"Address : ";
   gets(address);
   cout<<"Phone No. : ";
   gets(phone_no);

   file.seekg(pos);
   file.write((char*)this,sizeof(hotel));
   cout<<"\nRecord has been modified..";
   flag=1;
   break;
  }
 }

 if(flag==0)
 {
  cout<<"\n Room No. not found or vacant";
 }
 file.close();
}

void hotel::delete_rec(int r)
{
 int flag=0;
 char ch;
 ifstream fin("Record.dat",ios::in);
 ofstream fout("temp.dat",ios::out);
 while(!fin.eof())
 {
  fin.read((char*)this,sizeof(hotel));
  if(room_no==r)
  {
   cout<<"\n Name : "<<name;
   cout<<"\n Address : "<<address;
   cout<<"\n\n Do youwant to delete this record(y/n)";
   cin>>ch;
   if(ch=='n')
   {
    fout.write((char*)this,sizeof(hotel));
   }
   flag=1;
  }

  else
  {
   fout.write((char*)this,sizeof(hotel));
  }
 }
 fin.close();
 fout.close();
 if(flag==0)
 {
  cout<<"\nRoom not found or vacant..";
 }
 else
 {
  remove("Record.dat");
  rename("temp.dat","Record.dat");
 }
}

void main()
{
 hotel h;

 clrscr();
 cout<<"\n\t\t\t************************************";
 cout<<"\n\t\t\t* HOTEL MANAGEMEBT SYSTEM *";
 cout<<"\n\t\t\t************************************";

 h.main_menu();
 getch();
}