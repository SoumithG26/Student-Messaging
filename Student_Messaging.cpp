#include <iostream>  // Including input-output stream header file
#include <string>
#include <ctime>
#include <fstream>
#include<cstdlib>
#include<sstream>
using namespace std; // Using standard namespace

// -----------------------------------------------------------------------------------------------

// File Names
#define STUDENT_FILE "student_data.txt"
#define MESSAGE_FILE "Messages.txt"
#define MARKS_FILE "Marks.txt"

// CLASS:STUDENT_DATA

bool isUpdating = false;
string updateRoll = "";

class Student_Data {                                                                                        //Student Data Class
private:
    string rollNo, firstName, middleName, lastName, college, branch, section, mail;
public:
    Student_Data* next;
    Student_Data* prev;
    Student_Data(){
    	rollNo="";
    	firstName="";
    	middleName="";
    	lastName="";
    	college="";
    	branch="";
    	section="";
    	mail="";
    	next=NULL;
    	prev=NULL;
	}
	static Student_Data* enterdata();
	void readFile(Student_Data*&,Student_Data*&);
	void swap(Student_Data*, Student_Data*);
	void display_sdata();
    void display_node(Student_Data* temp);
    void sort_students(Student_Data*);
    static void search_sdata(Student_Data* , string );
    static void writeToFile(Student_Data* );
    static void overWriteFile(Student_Data*& );
    static void update_student(Student_Data*& , Student_Data*& , string );
    static void displayAll() {              
        ifstream file(STUDENT_FILE);
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
    static bool exists(const string& rollNo) {
        ifstream file(STUDENT_FILE);
        string line, rno;
        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, rno, ',');
            if (isUpdating && rno == updateRoll) {
                continue;                       // to skip the current roll number
            }
            else if (rno == rollNo) return true;
        }
        return false;
    }
};
void Student_Data::search_sdata(Student_Data* start, string rollno)
    {
    	Student_Data* current = start;
    	while(current!=NULL)
    	{
    		if(current->rollNo == rollno)
    		{
    			current->display_node(current);
    			return;
			}
			current=current->next;
		}
	}
void Student_Data::writeToFile(Student_Data* newdata) {        //APPENDS to file
        ofstream file(STUDENT_FILE, std::ios::app);
	    if (file.is_open()) {
	        file << newdata->rollNo;
	        file << "," << newdata->firstName;
	        file << "," << newdata->middleName;
	        file << "," << newdata->lastName;
	        file << "," << newdata->college;
	        file << "," << newdata->branch;
	        file << "," << newdata->section;
	        file << "," << newdata->mail<<endl;
	        file.close();
	    } else {
	        cout << "\t\t\t\t\t\t\t\t\t\t"<<"Unable to open Student Data file";
	    }
	    ofstream f(MARKS_FILE, std::ios::app);
	    if (f.is_open()){
	    	f << newdata->rollNo;
	    	f << "," << "-1"<<endl;
	    	f.close();
		}
		else{
			cout << "\t\t\t\t\t\t\t\t\t\t"<<"Unable to open Marks file";
		}
        f.close();
    }
void Student_Data::overWriteFile(Student_Data*& start) {        //reWrites to file
        ofstream file(STUDENT_FILE, std::ios::out);
        Student_Data* currentNode = start;
        if(file.is_open()){
            while(currentNode != NULL){
                file << currentNode->rollNo;
                file << "," << currentNode->firstName;
                file << "," << currentNode->middleName;
                file << "," << currentNode->lastName;
                file << "," << currentNode->college;
                file << "," << currentNode->branch;
                file << "," << currentNode->section;
                file << "," << currentNode->mail<<endl;
                currentNode = currentNode->next;
            }
        }
        else{
            cout << "\t\t\t\t\t\t\t\t\t\t"<<"Unable to open Student Data file";
        }
    }
void Student_Data::update_student(Student_Data*& start, Student_Data*& newdata, string rollno)
    {                                                   
        Student_Data* current = start;
        while(current != NULL)
        {
            if(current->rollNo == newdata->rollNo)
            {
                Student_Data* prevNode = current->prev;
                Student_Data* nextNode = current->next;

                if (prevNode!= NULL) {            
                    prevNode->next = newdata;
                } else {                    //  when updating node is the first node
                    start = newdata;    
                }

                if (nextNode!= NULL) {            
                    nextNode->prev = newdata;
                }

                newdata->prev = prevNode;
                newdata->next = nextNode;

                delete current;
                break;
            }
            current = current->next;
        }
    }
Student_Data* Student_Data::enterdata()
{
	Student_Data* newdata=new Student_Data();
    if(!isUpdating){
        cout << "\t\t\t\t\t\t\t\t\t\t"<<"Enter Roll No: "; cin >> newdata->rollNo;
    }
    else{
        newdata->rollNo = updateRoll; // if updating, use the roll number from the global variable
    }
    if (Student_Data::exists(newdata->rollNo)) {
        cout << "\n\t\t\t\t\t\t\t\t\t\tRoll No. already exists in student data.\n";
        return NULL;
    }
    cout << "\t\t\t\t\t\t\t\t\t\t"<<"Enter First Name: "; cin >> newdata->firstName;
    cout << "\t\t\t\t\t\t\t\t\t\t"<<"Enter Middle Name: "; cin >> newdata->middleName;
    cout << "\t\t\t\t\t\t\t\t\t\t"<<"Enter Last Name: "; cin >> newdata->lastName;
    cout << "\t\t\t\t\t\t\t\t\t\t"<<"Enter College: "; cin >> newdata->college;
    cout << "\t\t\t\t\t\t\t\t\t\t"<<"Enter Branch: "; cin >> newdata->branch;
    cout << "\t\t\t\t\t\t\t\t\t\t"<<"Enter Section: "; cin >> newdata->section;
    cout << "\t\t\t\t\t\t\t\t\t\t"<<"Enter Mail ID: "; cin >> newdata->mail;
    newdata->next=NULL;
    newdata->prev=NULL;
    return newdata;
}
void Student_Data::display_sdata()      //to display nodes of dbLl
{
	Student_Data *temp,*last;
    temp=this;
    while(temp!=NULL)
    {
        cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Roll No.: "<<temp->rollNo<<"\n";
		cout<<"\t\t\t\t\t\t\t\t\t\t"<<"First Name: "<<temp->firstName<<"\n";
		cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Middle Name: "<<temp->middleName<<"\n";
		cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Last Name: "<<temp->lastName<<"\n";
		cout<<"\t\t\t\t\t\t\t\t\t\t"<<"College: "<<temp->college<<"\n";
		cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Branch: "<<temp->branch<<"\n";
		cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Section: "<<temp->section<<"\n";
		cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Mail: "<<temp->mail<<"\n";
		cout<<"\t\t\t\t\t\t\t\t\t\t"<<"--------------------------------------\n";
        last=temp;
        temp=temp->next;
    }
}
void Student_Data::display_node(Student_Data* temp){
    cout<<"\t\t\t\t\t\t\t\t\t\t"<<"-------------------------------"<<endl;
    cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Student Roll Number: "<<temp->rollNo<<endl;
    cout<<"\t\t\t\t\t\t\t\t\t\t"<<"First Name: "<<temp->firstName<<endl;
    cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Middle Name: "<<temp->middleName<<endl;
    cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Last Name: "<<temp->lastName<<endl;
    cout<<"\t\t\t\t\t\t\t\t\t\t"<<"College: "<<temp->college<<endl;
    cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Branch: "<<temp->branch<<endl;
    cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Section: "<<temp->section<<endl;
    cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Mail: "<<temp->mail<<endl;
    cout<<"\t\t\t\t\t\t\t\t\t\t"<<"-------------------------------"<<endl;
}   
void Student_Data::readFile(Student_Data*& start,Student_Data*& end)
{
	fstream file(STUDENT_FILE, ios::in);
    if(!file){
        cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Unable to Open Student data File"<<endl;
    }else{
        string input;
        bool dataPresent = false;
        while (getline(file, input)) {
            dataPresent = true;
            Student_Data* newdata = new Student_Data();
            if (!start) {
                start = newdata;
                newdata->prev = NULL;
                newdata->next = NULL;
                end = newdata;
            } else {
                end->next = newdata;
                newdata->prev = end;
                end = newdata;
                newdata->next = NULL;
            }
            stringstream ss(input);     // converting string to stringstream to split using getline
            string temp;

                        // reading and assigning values from file
            getline(ss, newdata->rollNo, ',');
            getline(ss, newdata->firstName, ',');
            getline(ss, newdata->middleName, ','); 
            getline(ss, newdata->lastName, ',');  
            getline(ss, newdata->college, ',');  
            getline(ss, newdata->branch, ',');
            getline(ss, newdata->section, ',');
            getline(ss, newdata->mail, ',');
        }
        if(!dataPresent){
            cout<<"\t\t\t\t\t\t\t\t\t\t"<<"File is Empty... Add Student details first"<<endl;
        }
    }
	
    file.close();
}
void Student_Data::swap(Student_Data* a,Student_Data* b)
{
	std::string temp;
	temp=a->rollNo;
	a->rollNo = b->rollNo;
	b->rollNo = temp;
	
	temp=a->firstName;
	a->firstName = b->firstName;
	b->firstName = temp;
	
	temp=a->middleName;
	a->middleName = b->middleName;
	b->middleName = temp;
	
	temp=a->lastName;
	a->lastName = b->lastName;
	b->lastName = temp;
	
	temp=a->college;
	a->college = b->college;
	b->college = temp;
	
	temp=a->branch;
	a->branch = b->branch;
	b->branch = temp;
	
	temp=a->section;
	a->section = b->section;
	b->section = temp;
	
	temp=a->mail;
	a->mail = b->mail;
	b->mail = temp;
}
void Student_Data::sort_students(Student_Data* start)
{
	Student_Data* current = start;
    while(current != NULL)
    {
    	Student_Data* nextNode = current->next;
    	while(nextNode !=NULL)
    	{
    		if(current->rollNo > nextNode->rollNo)
    		{
    			swap(current, nextNode);
			}
			nextNode = nextNode->next;
		}
		current = current->next;
	}
}


class Message{
    private:
        string start_date;
        string start_time;
        string from;
        string to;
        string message;
        string end_date;
        string end_time;
        
    public:
    	Message *next;
        Message *prev;
        static Message* newMessage();
        void Display_nodes();
    	void readFile(Message*& ,Message*& );
        void Sort(Message* );
        void display(Message* );
        void filterByTime(Message* );
        void filterByRollno(Message* );
        void swap(Message*, Message*);
        int compareDateTime(string, string, string, string);
        void delmsg(Message*, string);
        Message()
        {
        	start_date="";
		    start_time="";
		    from="";
		    to="";
		    message="";
		    end_date="";
		    end_time="";
		    next=NULL;
		    prev=NULL;
		}
        static void displayAll() {
            ifstream file(MESSAGE_FILE);
            string line;
            while (getline(file, line)) {
                cout << line << endl;
            }
        }
};
Message* Message::newMessage()
{
    string senderRollNo;
    string receiverRollNo;
    Message* newMessage = new Message();
   
    //input roll nos
    cout << "\t\t\t\t\t\t\t\t\t\t"<<"Enter Sender Roll No: "; cin >> senderRollNo;
    //(REQUIRED)checking in student data
        if (!Student_Data::exists(senderRollNo)) {
            cout << "\t\t\t\t\t\t\t\t\t\t"<<"Sender not found in student data.\n";
            return 0;
        }
        cout << "\t\t\t\t\t\t\t\t\t\t"<<"Enter Receiver Roll No: "; cin >> receiverRollNo;
        if(!Student_Data::exists(receiverRollNo)){
        	cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Receiver not found in student data.\n";
        	return 0;
		}

        if(senderRollNo == receiverRollNo){
            cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Can't Send Messages To yourself"<<endl;
            return 0;
        }

    newMessage->from=senderRollNo;
    newMessage->to=receiverRollNo;

    //start time and date
    time_t start_time_raw = time(0);
    tm* start_time_info=localtime(&start_time_raw);
   
    char start_date_str[12];
    strftime(start_date_str,sizeof(start_date_str),"%d-%m-%Y",start_time_info);
    newMessage->start_date = start_date_str;
   
    char start_time_str[12];
    strftime(start_time_str,sizeof(start_time_str),"%H:%M:%S",start_time_info);
    newMessage->start_time = start_time_str;
    cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Start Date: "<<newMessage->start_date<<endl;
    cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Start time: "<<newMessage->start_time<<endl;
   
    //message
    cout << "\t\t\t\t\t\t\t\t\t\t"<<"Enter message: ";
    cin.ignore(); // Ignore newline character
    getline(cin, newMessage->message);
   
    //end time and date
    time_t end_time_raw = time(0);
    tm* end_time_info = localtime(&end_time_raw);
   
    char end_date_str[12];
    strftime(end_date_str,sizeof(end_date_str),"%d-%m-%Y",end_time_info);
    newMessage->end_date = end_date_str;
   
    char end_time_str[12];
    strftime(end_time_str,sizeof(end_time_str),"%H:%M:%S",end_time_info);
    newMessage->end_time=end_time_str;
   
    cout << "\t\t\t\t\t\t\t\t\t\t"<<"Message: " << newMessage->message << endl;
    cout<<"\t\t\t\t\t\t\t\t\t\t"<<"End Date: "<<newMessage->end_date<<endl;
    cout<<"\t\t\t\t\t\t\t\t\t\t"<<"End time: "<<newMessage->end_time<<endl;

    
    //----------------------------------writing to the file
    ofstream file(MESSAGE_FILE,std::ios::app);
    if (file.is_open()) {
        file << newMessage->start_date;
        file << "," << newMessage->start_time;
        file << "," << newMessage->from;
        file << "," << newMessage->to;
        file << "," << newMessage->message;
        file << "," << newMessage->end_date;
        file << "," << newMessage->end_time << endl;
        file.close();
    } else {
        cout << "\t\t\t\t\t\t\t\t\t\t"<<"Unable to open Messages file";
    }
    //----------------------------------
    newMessage->next=NULL;
    newMessage->prev=NULL;
    return newMessage;
}
void Message::Display_nodes()
{
    //to display nodes of dbLl
    Message *temp,*last;
    temp=this; bool found;
    cout<<"\n\t\t\t\t\t\t\t\t\t\tTraversal in Forward direction:\n";
    while(temp!=NULL)
    {
    	found=true;
        cout<<"\t\t\t\t\t\t\t\t\t\t"<<temp->from<<"\n\t\t\t\t\t\t\t\t\t\t"<<temp->to<<"\n\t\t\t\t\t\t\t\t\t\t"<<temp->start_date<<"\n\t\t\t\t\t\t\t\t\t\t"<<temp->start_time<<"\n\t\t\t\t\t\t\t\t\t\t"<<temp->message<<"\n\t\t\t\t\t\t\t\t\t\t"<<temp->end_date<<"\n\t\t\t\t\t\t\t\t\t\t"<<temp->end_time<<"\n\n";
        last=temp;
        temp=temp->next;
    }
    if(!found)
    {
    	cout<<"\t\t\t\t\t\t\t\t\t\t"<<"No message stored..\n";
	}
}
void Message::readFile(Message*& head,Message*& last)
{
	fstream file(MESSAGE_FILE, ios::in);
	string input;
    //Message* currentNode;   //used in the while loop
    while (getline(file, input)) {
        Message* newNode = new Message();
            if (!head) {
                head = newNode;
                newNode->prev = NULL;
                newNode->next = NULL;
                last = newNode;
            } else {
                last->next = newNode;
                newNode->prev = last;
                last = newNode;
                newNode->next = NULL;
            }
            stringstream ss(input);     // converting string to stringstream to split using getline
            string temp;

                        // reading and assigning values from file
            getline(ss, newNode->start_date, ',');
            getline(ss, newNode->start_time, ','); 
            getline(ss, newNode->from, ',');
            getline(ss, newNode->to, ',');
            getline(ss, newNode->message, ','); 
            getline(ss, newNode->end_date, ','); 
            getline(ss, newNode->end_time, ',');  
                        
        }
        file.close();
}
void Message::swap(Message* a,Message* b)
{
	std::string temp;
	temp=a->from;
	a->from = b->from;
	b->from = temp;
	
	temp=a->to;
	a->to = b->to;
	b->to = temp;
	
	temp=a->start_time;
	a->start_time = b->start_time;
	b->start_time = temp;
	
	temp=a->start_date;
	a->start_date = b->start_date;
	b->start_date = temp;
	
	temp=a->message;
	a->message = b->message;
	b->message = temp;
	
	temp=a->end_time;
	a->end_time = b->end_time;
	b->end_time = temp;
	
	temp=a->end_date;
	a->end_date = b->end_date;
	b->end_date = temp;
}
void Message::Sort(Message* head)
{
    Message* current = head;
    while(current != NULL)
    {
    	Message* nextNode = current->next;
    	while(nextNode !=NULL)
    	{
    		if(current->from > nextNode->from || (current->from == nextNode->from && current->to > nextNode->to))
    		{
    			swap(current, nextNode);
			}
			nextNode = nextNode->next;
		}
		current = current->next;
	}
}
void Message::filterByTime(Message* head)
{
	string sdate;
	string stime;
    string edate;
    string etime;
    int choose;
	cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Enter the initial date: (dd-mm-yyyy)";cin>>sdate;
	cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Enter the end date: (dd-mm-yyyy)";cin>>edate;
	cout<<"\t\t\t\t\t\t\t\t\t\t"<<"1. Display all the messages\n";
	cout<<"\t\t\t\t\t\t\t\t\t\t"<<"2. Display messages in a time range\n";
    cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Enter your choice: ";
	cin>>choose;
	if (choose==1)
	{
		Message* temp=head;
		int count=0;
		while(temp != NULL)
		{
			if(temp->end_date==edate && temp->start_date==sdate)
			{
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Start Date: "<<temp->start_date<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Start Time: "<<temp->start_time<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"From: "<<temp->from<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"To: "<<temp->to<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Message: "<<temp->message<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"End Date: "<<temp->end_date<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"End Time: "<<temp->end_time<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"-----------------------------------------\n";
				count++;
			}
			temp=temp->next;
		}
		if(count==0){
			cout<<"\t\t\t\t\t\t\t\t\t\t"<<"No messages found"<<endl;
		}
		else cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Total messages are "<<count<<endl;
	}
	else if (choose==2){
	    cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Enter the initial time: (hh:mm:ss): ";
        cin.ignore();  // flush newline from previous input
        getline(cin, stime);

        cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Enter the end time: (hh:mm:ss): ";
        getline(cin, etime);

	    Message* temp = head;
	    bool found = false;
	    while(temp != NULL)
	    {
	    	if (compareDateTime(temp->start_date, temp->start_time, sdate, stime) >= 0 &&
                compareDateTime(temp->end_date, temp->end_time, edate, etime) <= 0)
	    	{
	            found = true;
	    		cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Start Date: "<<temp->start_date<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Start Time: "<<temp->start_time<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"From: "<<temp->from<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"To: "<<temp->to<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Message: "<<temp->message<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"End Date: "<<temp->end_date<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"End Time: "<<temp->end_time<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"-----------------------------------------\n";
			}
			temp=temp->next;
		}
	    if(!found)
	    {
	        cout<<"\t\t\t\t\t\t\t\t\t\t"<<"No messages found"<<endl;
	    }
	}
}
int Message::compareDateTime(string date1, string time1, string date2, string time2)
{
	int d1, m1, y1, h1, min1, s1;
	int d2, m2, y2, h2, min2, s2;
	sscanf(date1.c_str(), "%d-%d-%d", &d1, &m1, &y1);
	sscanf(time1.c_str(), "%d:%d:%d", &h1, &min1, &s1);
	
	sscanf(date2.c_str(), "%d-%d-%d", &d2, &m2, &y2);
	sscanf(time2.c_str(), "%d:%d:%d", &h2, &min2, &s2);
	
	if (y1>y2) return 1; //messaged year is greater than entered year we can print msg
	else if (y1 < y2) return -1;
	else{
		if (m1 > m2) return 1;
		else if (m1 < m2) return -1;
		else{
			if (d1 > d2) return 1;
			else if (d1 < d2) return -1;
			else{
				if (h1 > h2) return 1;
				else if (h1 < h2) return -1;
				else{
					if (min1 > min2) return 1;
					else if (min1 < min2) return -1;
					else{
						if (s1 > s2) return 1;
						else if (s1 < s2) return -1;
						else return 0;
					}
				}
			}
		}
	}
}
void Message::delmsg(Message* head, string msg)
{
	bool found = false;
	Message* temp = head;
	while (temp!=NULL)
	{
		Message* nextTemp = temp->next;
		if(temp->message==msg)
		{
			found=true;
			if(temp==head)
			{
				head = temp->next;
				if(head != NULL)
				{
					head->prev=NULL;
				}
			}else if (temp->next==NULL)
			{
				temp->prev->next = NULL;
			}else{
				temp->prev->next=temp->next;
				temp->next->prev=temp->prev;
			}
			
			delete temp;
			temp=nextTemp;
			continue;
			//code to delete from file
            //----------------------------------writing to the file
            ofstream file(MESSAGE_FILE,std::ios::app);
            Message* newMessage = head;
            while(newMessage != NULL){
                if (file.is_open()) {
                    file << newMessage->start_date;
                    file << "," << newMessage->start_time;
                    file << "," << newMessage->from;
                    file << "," << newMessage->to;
                    file << "," << newMessage->message;
                    file << "," << newMessage->end_date;
                    file << "," << newMessage->end_time << endl;
                    file.close();
                } else {
                    cout << "\t\t\t\t\t\t\t\t\t\t"<<"Unable to open Messages file";
                }
                newMessage = newMessage->next;
            }
            //----------------------------------
		}
		temp=nextTemp;
	}
	if (!found) {
		cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Message not found."<<endl;
	}
}
void Message::filterByRollno(Message* head)
{
	int choose; int count=0;
	Message* temp=head;
	cout<<"\t\t\t\t\t\t\t\t\t\t"<<"1. Display messages sent by\n";
	cout<<"\t\t\t\t\t\t\t\t\t\t"<<"2. Display messages recieved by\n";
    cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Enter Your Choice: ";
	cin>>choose;
	if (choose==1)
	{
		string sender;
		cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Enter sender's Roll no : "; 
        cin>>sender;
		Message* temp = head;
		while(temp!=NULL)
		{
			if (temp->from==sender)
			{
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Start Date: "<<temp->start_date<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Start Time: "<<temp->start_time<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"From: "<<temp->from<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"To: "<<temp->to<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Message: "<<temp->message<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"End Date: "<<temp->end_date<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"End Time: "<<temp->end_time<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"-----------------------------------------\n";
				count++;
			}
			temp=temp->next;
		}
		if(count==0)
		{
			cout<<"\t\t\t\t\t\t\t\t\t\t"<<"No messages sent by "<<sender<<endl;
		}
		else cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Total message(s) sent by "<<sender<<" are "<<count<<endl;
	}
	else if (choose==2)
	{
		string receiver; int count = 0;
		cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Enter receiver's Roll no: "; 
        cin>>receiver;
		Message* temp = head;
		while(temp!=NULL)
		{
			if (temp->to==receiver)
			{
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Start Date: "<<temp->start_date<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Start Time: "<<temp->start_time<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"From: "<<temp->from<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"To: "<<temp->to<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Message: "<<temp->message<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"End Date: "<<temp->end_date<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"End Time: "<<temp->end_time<<endl;
				cout<<"\t\t\t\t\t\t\t\t\t\t"<<"-----------------------------------------\n";
				count++;
			}
			temp=temp->next;
		}
		if(count==0)
		{
			cout<<"\t\t\t\t\t\t\t\t\t\t"<<"No messages received by "<<receiver<<endl;
		}
		else cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Total message(s) received by "<<receiver<<" are "<<count<<endl;
	}
}
void Message::display(Message* head)
{
	Message* temp=head;
	while(temp!=NULL)
	{
		cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Start Date: "<<temp->start_date<<endl;
		cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Start Time: "<<temp->start_time<<endl;
		cout<<"\t\t\t\t\t\t\t\t\t\t"<<"From: "<<temp->from<<endl;
		cout<<"\t\t\t\t\t\t\t\t\t\t"<<"To: "<<temp->to<<endl;
		cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Message: "<<temp->message<<endl;
		cout<<"\t\t\t\t\t\t\t\t\t\t"<<"End Date: "<<temp->end_date<<endl;
		cout<<"\t\t\t\t\t\t\t\t\t\t"<<"End Time: "<<temp->end_time<<endl;
		cout<<"\t\t\t\t\t\t\t\t\t\t"<<"-----------------------------------------\n";
		temp=temp->next;
	}
}
class InterviewList {
private:
    string rollNo;
    int marks;
    InterviewList* next;
    InterviewList* front;
    InterviewList* rear;
public:

    InterviewList() {
        rollNo = "";
        marks = -1;
        next = NULL;
        front = rear = NULL;
    }
    void enqueue(string,int);
    void freeQueue();
    bool readFromFile();
    void displayQueue();
    void sortQueue();
    void saveToFile();
    void searchMarksByRollNo(string);
    void updateMarks(string);
};
void InterviewList::enqueue(string rollNo, int marks) {
    InterviewList* newNode = new InterviewList();
    newNode->rollNo = rollNo;
    newNode->marks = marks;
    newNode->next = NULL;

    if (rear == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

void InterviewList::freeQueue() {
    InterviewList* temp = front;
    while (temp != NULL) {
        InterviewList* nextNode = temp->next;
        delete temp;
        temp = nextNode;
    }
    front = rear = NULL;
}

bool InterviewList::readFromFile() {
    freeQueue();

    ifstream file(MARKS_FILE);
    if (!file) {
        cout << "\t\t\t\t\t\t\t\t\t\t"<<"Unable to open marks file.\n";
        return false;
    }

    bool dataPresent = false;
    string line;
    while (getline(file, line)) {
        dataPresent = true;
        if (line.empty()) continue;

        stringstream ss(line);
        string rollNo, marksStr;
        getline(ss, rollNo, ',');
        getline(ss, marksStr);

        int marks = atoi(marksStr.c_str());
        enqueue(rollNo, marks);
    }

    if(!dataPresent){
        cout<<"\t\t\t\t\t\t\t\t\t\t"<<"No Student Roll Numbers Found... Add Student Details"<<endl;
        return dataPresent;
    }
    file.close();
    return dataPresent;
}
void InterviewList::sortQueue() {
    InterviewList* i = front;
    while (i != NULL) {
        InterviewList* j = i->next;
        while (j != NULL) {
            if (i->marks < j->marks) {
                swap(i->rollNo, j->rollNo);
                swap(i->marks, j->marks);
            }
            j = j->next;
        }
        i = i->next;
    }
}

void InterviewList::displayQueue() {
    if (front == NULL) {
        cout << "\t\t\t\t\t\t\t\t\t\t"<<"File is empty!\n";
        return;
    }
    sortQueue();
    InterviewList* temp = front;
    while (temp != NULL) {
        if(temp->marks!=-1){
            cout <<"\t\t\t\t\t\t\t\t\t\t"<<"Roll No: "<< temp->rollNo << " " <<"\tMarks: "<< temp->marks << endl;
        }
        temp = temp->next;
    }
}


void InterviewList::saveToFile() {
    ofstream file(MARKS_FILE);
    InterviewList* temp = front;
    while (temp != NULL) {
        file << temp->rollNo << "," << temp->marks << endl;
        temp = temp->next;
    }
    file.close();
    cout << "\t\t\t\t\t\t\t\t\t\t"<<"File saved successfully.\n";
}

void InterviewList::searchMarksByRollNo(string roll) {
    readFromFile();
    InterviewList* temp = front;
    bool found = false;

    while (temp != NULL) {
        if (temp->rollNo == roll) {
            found = true;
            if (temp->marks == -1)
                cout <<"\t\t\t\t\t\t\t\t\t\t"<< temp->rollNo << " Exists But Marks Are Not Entered" << endl;
            else
                cout <<"\t\t\t\t\t\t\t\t\t\t"<< temp->rollNo << " Got " << temp->marks << " Marks\n";
            break;
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "\t\t\t\t\t\t\t\t\t\t"<<"Student Exists But Roll number not found in Marks File.\n";
    }
}

void InterviewList::updateMarks(string roll) {
    readFromFile();
    InterviewList* temp = front;

    while (temp != NULL) {
        if (temp->rollNo == roll) {
            if(temp->marks!= -1){
                int newMarks;
                cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Current Marks: "<<temp->marks<<endl;
                cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Enter New Marks To be Updated: ";
                cin>>newMarks;
                temp->marks = newMarks;
                saveToFile();
                cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Successfully Updated Marks of "<<temp->rollNo<<endl;
            }else{
                cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Marks of "<<temp->rollNo<<" not Entered....Cannot Update"<<endl;
            }
            break;
        }
        temp = temp->next;
    }
}

class MeritList {
private:
    string rollNo;
    int marks;
public:
    MeritList* next;

    // Static pointer to the top of the stack (like head)
    static MeritList* top;

    // Constructor
    MeritList(string r = "", int m = -1) {
        rollNo = r;
        marks = m;
        next = NULL;
    }

    // Core static functions
    static void push(string rollNo, int marks);
    static void display();
    static void displayReverse(MeritList* node);
    static void clear();
    static bool readFromFile();
    static MeritList* getTop();
    static void search();
    static void overwriteToFile();
    static void updateMarks(const string& roll, int newMarks);
    static void writeStackReversed(MeritList* , ofstream& );
    static void Enter();
    static void update();
};

// Initialize static member
MeritList* MeritList::top = NULL;

// Push keeping list sorted by marks descending
void MeritList::push(string rollNo, int marks) {
    MeritList* newNode = new MeritList(rollNo, marks);
    if (!top || marks > top->marks) {
        newNode->next = top;
        top = newNode;
    } else {
        MeritList* current = top;
        while (current->next && current->next->marks >= marks) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void MeritList::Enter(){
	MeritList* current = MeritList::getTop();
	ifstream marksFile(MARKS_FILE);
    if (!marksFile) {
        cout << "\t\t\t\t\t\t\t\t\t\t"<<"Unable to open marks.txt\n";
        return;
    }
    ifstream file(MARKS_FILE);
    if(file.peek()==std::istream::traits_type::eof())
    {
    	cout<<"\t\t\t\t\t\t\t\t\t\t"<<"File is empty.Enter student data first...\n";
    	return;
	}
	bool anyUpdated = false;
	while (current) {
	    if (current->marks == -1) {
	        cout <<"\t\t\t\t\t\t\t\t\t\t"<< "Roll No: " << current->rollNo <<"\n\t\t\t\t\t\t\t\t\t\t"<< "Enter marks (press Enter for -1): ";
	        string input;
	        getline(cin, input);
	        if (!input.empty()) {
	            stringstream ss(input);
	            int tempMarks;
	            if (ss >> tempMarks) {
	                current->marks = tempMarks;
	                anyUpdated = true;
	            } else {
	                cout <<"\t\t\t\t\t\t\t\t\t\t"<< "Invalid input, marks kept as -1.\n";
	            }
	        }
	    }
	    current = current->next;
	}
	if (anyUpdated) {
	    MeritList::overwriteToFile();
	    cout << "\t\t\t\t\t\t\t\t\t\t"<<"Marks updated.\n";
	} else {
	    cout << "\t\t\t\t\t\t\t\t\t\t"<<"All marks were already entered.\n";
	}
}

// Display list from lowest to highest marks using recursion
void MeritList::displayReverse(MeritList* node) {
    if (!node) return;
    displayReverse(node->next);
    cout << "\t\t\t\t\t\t\t\t\t\t"<<"Roll no: " << node->rollNo << ", Marks: " << node->marks << endl;
}

void MeritList::display() {
    if (!top) {
        cout << "\t\t\t\t\t\t\t\t\t\t"<<"Merit list is empty.\n";
        return;
    }
    cout << "\n\t\t\t\t\t\t\t\t\t\tMerit List (Lowest to Highest):\n";
    displayReverse(top);
    cout << endl;
}

// Clear the linked list
void MeritList::clear() {
    while (top) {
        MeritList* temp = top;
        top = top->next;
        delete temp;
    }
}

// Read from file and build list

bool MeritList::readFromFile() {
    clear();
    ifstream file(MARKS_FILE);
    if (!file) {
        cout << "\t\t\t\t\t\t\t\t\t\t"<<"Marks file not found. Starting fresh.\n";
        return false;
    }

    bool dataPresent = false;
    string line;
    while (getline(file, line)) {
    	dataPresent = true;
        if (line.empty()) continue;
        stringstream ss(line);
        string roll, marksStr;
        getline(ss, roll, ',');
        getline(ss, marksStr);
        int marks = -1;
        if (!marksStr.empty()) {
            stringstream ms(marksStr);
            ms >> marks;
        }
        push(roll, marks);
    }
    if(!dataPresent){
        cout<<"\t\t\t\t\t\t\t\t\t\t"<<"No Student Roll Numbers Found... Add Student Details"<<endl;
        return dataPresent;
    }
    file.close();
    return dataPresent;
}
void MeritList::update(){
	int newmarks;
    string roll;
    bool found;
    MeritList meritList;

    cout << "\t\t\t\t\t\t\t\t\t\t"<<"You Have Selected to Update Student Marks" << endl;

    bool dataPresent = meritList.readFromFile();
    if (dataPresent) {
        cout << "\t\t\t\t\t\t\t\t\t\t"<<"Enter Student Roll Number: ";
        cin >> roll;

        found = Student_Data::exists(roll);

        if (found) {
            MeritList* current = MeritList::getTop();
            bool rollFound = false;

            while (current != NULL) {
                if (current->rollNo == roll) {
                    rollFound = true;

                    if (current->marks == -1) {
                        cout << "\t\t\t\t\t\t\t\t\t\t"<<"Marks have not been entered yet. Cannot update.\n";
                    } else {
                        cout << "\t\t\t\t\t\t\t\t\t\t"<<"Current marks: " << current->marks << endl;
                        cout << "\t\t\t\t\t\t\t\t\t\t"<<"Enter new marks to update: ";
                        cin >> newmarks;
                        MeritList::updateMarks(roll, newmarks);
                    }
                    break;
                }
                current = current->next;
            }  
        } else {
            cout << "\t\t\t\t\t\t\t\t\t\t"<<"Student Details Not Found in Student_Data.\n";
        }
    }

}

// Return top pointer
MeritList* MeritList::getTop() {
    return top;
}

// Search for a roll no and display marks info
void MeritList::search() {
    if (!top) {
        cout << "\t\t\t\t\t\t\t\t\t\t"<<"Merit list is empty.\n";
        return;
    }
    string roll;
    cout << "\t\t\t\t\t\t\t\t\t\t"<<"Enter roll no to search marks: ";
    getline(cin, roll);

    MeritList* current = top;
    bool found = false;
    while (current) {
        if (current->rollNo == roll) {
            found = true;
            if (current->marks == -1) {
                cout << "\t\t\t\t\t\t\t\t\t\t"<<roll << " exists but marks are NOT entered.\n";
            } else {
                cout <<"\t\t\t\t\t\t\t\t\t\t"<<roll << " got " << current->marks << " marks.\n";
            }
            break;
        }
        current = current->next;
    }
    if (!found) {
        cout <<"\t\t\t\t\t\t\t\t\t\t"<< "Roll no " << roll << " not found in merit list.\n";
    }
}

// Write list reversed to file (lowest first)
void MeritList::writeStackReversed(MeritList* node, ofstream& out) {
    if (!node) return;
    writeStackReversed(node->next, out);
    out << node->rollNo << "," << node->marks << "\n";
}

// Overwrite file with current merit list
void MeritList::overwriteToFile() {
    ofstream file(MARKS_FILE);
    if (!file) {
        cout << "\t\t\t\t\t\t\t\t\t\t"<<"Error opening file for writing.\n";
        return;
    }
    writeStackReversed(top, file);
    file.close();
    cout << "\t\t\t\t\t\t\t\t\t\t"<<"Marks file updated.\n";
}

// Update marks by roll number only if current marks != -1
void MeritList::updateMarks(const string& roll, int newMarks) {
    MeritList* current = top;
    bool found = false;
    bool updated = false;

    MeritList* newList = NULL;

    // We rebuild the list with updated marks
    while (current) {
        if (current->rollNo == roll) {
            found = true;
            if (current->marks == -1) {
                cout << "\t\t\t\t\t\t\t\t\t\t"<<"Cannot update marks: current marks are -1 (not entered).\n";
                // Add the node unchanged
                MeritList* node = new MeritList(current->rollNo, current->marks);
                node->next = newList;
                newList = node;
            } else {
                // Add with updated marks
                MeritList* node = new MeritList(current->rollNo, newMarks);
                node->next = newList;
                newList = node;
                updated = true;
            }
        } else {
            MeritList* node = new MeritList(current->rollNo, current->marks);
            node->next = newList;
            newList = node;
        }
        current = current->next;
    }

    if (!found) {
        cout << "\t\t\t\t\t\t\t\t\t\t"<<"Roll no " << roll << " not found in merit list.\n";
        // free newList
        while (newList) {
            MeritList* temp = newList;
            newList = newList->next;
            delete temp;
        }
        return;
    }

    // Reverse newList back to proper order
    MeritList* reversed = NULL;
    while (newList) {
        MeritList* temp = newList;
        newList = newList->next;
        temp->next = reversed;
        reversed = temp;
    }

    clear();
    top = reversed;

    if (updated) {
        cout << "\t\t\t\t\t\t\t\t\t\t"<<"Marks updated successfully.\n";
        overwriteToFile();
    }
}

int main()
{
    Message* head; Message* last; head=last=NULL;
    Student_Data* start; Student_Data* end; start=end=NULL;
    int choice, task;
    do
    {
        cout <<"\033[1;32m\n\t\t\t\t\t\t\t\t\t====== MAIN MENU ======\n";
        cout << "\t\t\t\t\t\t\t\t\t"<<"1. Student Data\n";
        cout << "\t\t\t\t\t\t\t\t\t"<<"2. Messages\n";
        cout << "\t\t\t\t\t\t\t\t\t"<<"3. Merit list\n";
        cout << "\t\t\t\t\t\t\t\t\t"<<"4. Interview list\n";
        cout << "\t\t\t\t\t\t\t\t\t"<<"5. Clear Console\n";
        cout << "\t\t\t\t\t\t\t\t\t"<<"0. EXIT\033[0m\n";
        
        cout << "\t\t\t\t\t\t\t\t\t"<<"Enter choice: \033[1;36m";
        cin >> choice;
        cout<<"\033[0m";
        
        
        if ( choice == 1 )
        {
        	int choice;
        	cout << "\033[1;34m\t\t\t\t\t\t\t\t\t\t\t--- Student Data ---\n";
            cout << "\t\t\t\t\t\t\t\t\t\t"<<"1. Enter student data.\n";
            cout << "\t\t\t\t\t\t\t\t\t\t"<<"2. Display student data.\n";
            cout << "\t\t\t\t\t\t\t\t\t\t"<<"3. Search student data.\n";
            cout << "\t\t\t\t\t\t\t\t\t\t"<<"4. Sort student data.\n";
            cout << "\t\t\t\t\t\t\t\t\t\t"<<"5. Update student data.\033[0m\n";
            cout << "\t\t\t\t\t\t\t\t\t\t"<<"\033[1;32m6. Go Back\033[0m\n";
            cout << "\t\t\t\t\t\t\t\t\t\t"<<"Enter your choice: \033[1;36m";
            cin >> task;
            cout<<"\033[0m";
            switch(task)
            {
            	case 1:
            		{
            			cout<<"\t\t\t\t\t\t\t\t\t\t"<<"You have selected to enter student data.\n";
            			Student_Data* newdata=Student_Data::enterdata();          //calling function to create new message
                        if (newdata == NULL) {
                            cout << "\t\t\t\t\t\t\t\t\t\t"<<"Returning to menu...\n";
                            break;
                        }
		                if (!start) {
		                    start = newdata;
		                    end = newdata;
		                } else {
		                    end->next = newdata;
		                    newdata->prev = end;
		                    end = newdata;
		                }
		                Student_Data::writeToFile(newdata);
		                cout<<"\t\t\t\t\t\t\t\t\t\t"<<"\nStudent data stored..\n";
		                start->display_sdata();
		                break;
					}
				case 2:
					{
                        cout <<"\t\t\t\t\t\t\t\t\t\t"<< "You have selected to display student data.\n";
						Student_Data* start = NULL;
	                    Student_Data* end = NULL;
                        start->Student_Data::readFile(start,end);
                        start->Student_Data::display_sdata();
						break;
					}
				case 3:
					{
                        string rollNo;
                        cout <<"\t\t\t\t\t\t\t\t\t\t"<< "You have selected to search student data.\n";
                        ifstream file(STUDENT_FILE);
                        if(!file){
                            cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Unable to open Student Data File"<<endl;
                            break;
                        }else{
                            cout <<"\t\t\t\t\t\t\t\t\t\t"<< "Enter Student Roll Number: ";
                            cin >> rollNo;
                            if (!Student_Data::exists(rollNo)) {
                                cout <<"\t\t\t\t\t\t\t\t\t\t"<< "Roll No. does not exist.\n";
                                cout <<"\t\t\t\t\t\t\t\t\t\t"<< "Do you want to add it? (1 for Yes, 0 for No): ";
                                int addChoice;
                                cin >> addChoice;
                                if (addChoice == 1) {
                                    Student_Data* newdata=Student_Data::enterdata();          //calling function to create new message
                                    start->Student_Data::writeToFile(start);
                                    cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Student data stored..\n";
                                    start->display_sdata();
                                } else {
                                    cout << "\tReturning to menu...\n";
                                }
                                break;
                            } else {
                                start->readFile(start,end);
                                Student_Data::search_sdata(start,rollNo);
                            }
                        }
						break;
					}
				case 4:
					{
						cout << "\t\t\t\t\t\t\t\t\t\t"<<"You have selected to sort the student data.\n";
	                    Student_Data* start = NULL;
	                    Student_Data* end = NULL;
	                    Student_Data* temp = new Student_Data();
	                    start->readFile(start,end);
	                    start->Student_Data::sort_students(start);
	                    cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Sorted Students based on the roll no order:\n";
	                    start->Student_Data::display_sdata();
	                    break;
					}
                case 5:
                    {
                        cout << "\t\t\t\t\t\t\t\t\t\t"<<"You have selected to update student data.\n";
                        Student_Data* start = NULL;
                        Student_Data* end = NULL;
                        start->Student_Data::readFile(start,end);
                        string rollno;
                        start->display_sdata();
                        cout <<"\t\t\t\t\t\t\t\t\t\t"<< "=========================================\n\n";
                        cout << "\t\t\t\t\t\t\t\t\t\t"<<"Enter the roll no. to be updated: ";
                        cin>>rollno;
                        if (Student_Data::exists(rollno)) {
                            cout << "\t\t\t\t\t\t\t\t\t\t"<<"Roll No. exists. Enter new details:\n";
                            isUpdating = true;
                            updateRoll = rollno;
                            Student_Data* newdata=Student_Data::enterdata();          //calling function to create new message
                            isUpdating = false;
                            updateRoll = "";
                            if(newdata == NULL) {
                                cout << "\t\t\t\t\t\t\t\t\t\t"<<"Returning to menu...\n";
                                break;
                            }
                            Student_Data::update_student(start,newdata,rollno);
                            Student_Data::overWriteFile(start);
                            cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Student data updated..\n";
                            start->display_sdata();
                        } else {
                            cout << "\t\t\t\t\t\t\t\t\t\t"<<"Roll No. does not exist.\n";
                            cout << "\t\t\t\t\t\t\t\t\t\t"<<"Do you want to add it? (1 for Yes, 0 for No): ";
                            int addChoice;
                            cin >> addChoice;
                            if (addChoice == 1) {
                                Student_Data* newdata=Student_Data::enterdata();          //calling function to create new message
                                start->Student_Data::writeToFile(start);
                                cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Student data stored..\n";
                                start->display_sdata();
                            } else {
                                cout << "\t\t\t\t\t\t\t\t\t\t"<<"Returning to menu...\n";
                            }
                        }
                        break;
                    }
                case 6:
                    continue;
			}
		}
        else if (choice == 2)
        {
            bool dataPresent;
            int choice,i;
            cout << "\033[1;33m\n\t\t\t\t\t\t\t\t\t\t--- Messages ---\n";
            cout <<"\t\t\t\t\t\t\t\t\t\t"<< "1. Send the messages.\n";
            cout <<"\t\t\t\t\t\t\t\t\t\t"<< "2. Sort & Display messages based on sender and receiver names.\n";
            cout <<"\t\t\t\t\t\t\t\t\t\t"<< "3. Display messages based on time.\n";
            cout <<"\t\t\t\t\t\t\t\t\t\t"<< "4. Display messages based on roll no.\033[0m\n";
            cout <<"\t\t\t\t\t\t\t\t\t\t"<< "\033[1;32m5. Go Back\033[0m\n";
            cout <<"\t\t\t\t\t\t\t\t\t\t"<< "Enter your choice: \033[1;36m";
            cin >> task;
            cout<<"\033[0m";
            switch (task)
            {
            case 1: // Send the messages.
                {
                cout << "\t\t\t\t\t\t\t\t\t\t"<<"You have selected to send the messages.\n";
                
                Message* newMessage=Message::newMessage();          //calling function to create new message
                if(newMessage == 0){
                    break;
                }
                if (!head) {
                    head = newMessage;
                    last = newMessage;
                } else {
                    last->next = newMessage;
                    newMessage->prev = last;
                    last = newMessage;
                }
                head->Display_nodes(); //to display nodes in forward direction
                break;
                }
            case 2: // Sort & Display messages based on sender and receiver Roll Nos.
                {
                    cout <<"\t\t\t\t\t\t\t\t\t\t"<< "You have selected to sort and display messages.\n";
                    fstream file(MESSAGE_FILE,ios::in);
                    if(!file){
                        cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Unable to open Messages File"<<endl;
                    }else{
                        Message* head = NULL;
                        Message* last = NULL;
                        Message* temp = new Message();          
                        head->Message::readFile(head,last);
                        head->Message::Sort(head);
                        cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Sorted Messages based on the roll no order:\n";
                        head->Message::display(head);
                        break;
                    }
                    break;
                }
            case 3: // Display messages based on time.
            {
			
                cout << "\t\t\t\t\t\t\t\t\t\t"<<"You have selected to display messages based on time.\n";
                fstream file(MESSAGE_FILE,ios::in);
                if(!file){
                    cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Unable to open Messages File"<<endl;
                    break;
                }else{
                    Message* head = NULL;
                    Message* last = NULL;
                    Message* temp = new Message();
                    head->Message::readFile(head, last);
                    head->Message::filterByTime(head);
                    break;
                }
        	}
        	case 4: // Display messages based on rollno.
            {
            	cout << "\t\t\t\t\t\t\t\t\t\t"<<"You have selected to display messages based on roll no.\n";
                fstream file(MESSAGE_FILE,ios::in);
                if(!file){
                    cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Unable to open Messages File"<<endl;
                    break;
                }else{
                    Message* head = NULL;
                    Message* last = NULL;
                    Message* temp = new Message();
                    head->Message::readFile(head, last);
                    head->Message::filterByRollno(head);
                    break;
                }
			}
            case 5: // Go Back
               continue;
            };
        }
        else if (choice == 3)
        {
        	int choice;
            bool dataPresent = false;
    		MeritList::readFromFile();
            cout << "\033[1;35m\n\t\t\t\t\t\t\t\t\t\t--- Merit List ---\n";
	        cout << "\t\t\t\t\t\t\t\t\t\t"<<"1. Enter Marks\n";
	        cout << "\t\t\t\t\t\t\t\t\t\t"<<"2. Display Merit List\n";
	        cout << "\t\t\t\t\t\t\t\t\t\t"<<"3. Search Student Marks\n";
	        cout << "\t\t\t\t\t\t\t\t\t\t"<<"4. Update Marks by Roll No\033[0m\n";
	        cout << "\t\t\t\t\t\t\t\t\t\t"<<"\033[1;32m5. Go back\033[0m\n";
	        cout << "\t\t\t\t\t\t\t\t\t\t"<<"Enter your choice: \033[1;36m";
	        cin >> choice;
            cout<<"\033[0m";
	        cin.ignore(); // clear newline after number input
	        switch (choice) {
	        	case 1:
	        		{
	        			MeritList::Enter();
			        }
                    break;
	            case 2:
	                MeritList::display();
	                break;
	
	            case 3:
	                MeritList::search();
	                break;
	
	            case 4: 
	            {
	            	 MeritList::update();
				}
	            case 5:
	               continue;
	            default:
	                cout << "\t\t\t\t\t\t\t\t\t\t"<<"Invalid choice, try again.\n";
	        }
        }
        else if (choice == 4)
        {
        	bool found;
            bool dataPresent;
		    InterviewList i;
		    string roll;
		    int choice;
	        cout<<"\033[38;2;255;165;0m\n\t\t\t\t\t\t\t\t\t\t--- Interview List ---\n";
	        cout<<"\t\t\t\t\t\t\t\t\t\t"<<"1. Display Interview List\n";
	        cout<<"\t\t\t\t\t\t\t\t\t\t"<<"2. Sort and Save to File\n";
	        cout<<"\t\t\t\t\t\t\t\t\t\t"<<"3.Search Student Marks\n";
	        cout<<"\t\t\t\t\t\t\t\t\t\t"<<"4.Update Student Marks\033[0m\n";
	        cout<<"\t\t\t\t\t\t\t\t\t\t"<<"\033[1;32m5. Go Back\033[0m\n";
	        cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Enter your choice: \033[1;36m";
	        cin >> choice;
            cout<<"\033[0m";
	
	        switch (choice) {
	            case 1:
	                cout<<"\t\t\t\t\t\t\t\t\t\t"<<"You have Selected to Display interview List\n\n";
	                dataPresent = i.readFromFile(); 
                    if(dataPresent){
                        i.displayQueue();
                    }       
	                break;
	
	            case 2:
	                cout<<"\t\t\t\t\t\t\t\t\t\t"<<"You have Selected to Sort and Save to File\n";
	                dataPresent= i.readFromFile();
                    if(dataPresent){
                        i.sortQueue();       
	                    i.saveToFile();      
                    }    
	                
	                break;
	
	            case 3:
	                cout<<"\t\t\t\t\t\t\t\t\t\t"<<"You Have Selected to Search for Student Marks\n";
                    dataPresent= i.readFromFile();
                    if(dataPresent){
                        cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Enter the Roll Number of Student: ";
                        cin>>roll;
                        found = Student_Data::exists(roll);
                        if(found){
                            i.searchMarksByRollNo(roll);
                        }else{
                            cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Student Details Are Not There"<<endl;
                        }      
                    }
	                break;
	            case 4:
	                int newmarks;
	                cout<<"\t\t\t\t\t\t\t\t\t\t"<<"You Have Selected to Update Student Marks"<<endl;
                    dataPresent= i.readFromFile();
                    if(dataPresent){
                        cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Enter Student Roll Number: ";
                        cin>>roll;
                        found = Student_Data::exists(roll);
                        if(found){
                            cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Student Exists.."<<endl;
                            i.updateMarks(roll);
                        }else{
                            cout<<"\t\t\t\t\t\t\t\t\t\t"<<"Student Details Not there"<<endl;
                        }      
                    }
	                break;
                case 5:
                    continue;
	            default:
	                cout << "\t\t\t\t\t\t\t\t\t\t"<<"Invalid choice.\n";
	        }
        }
        else if(choice == 5){
            system("cls");
        }
        else if (choice == 0)
        {
            cout << "\t\t\t\t\t\t\t\t\t\t"<<"Exiting...\n";
        }
        else
        {
            cout << "\t\t\t\t\t\t\t\t\t\t"<<"Invalid choice, please try again.\n";
        }
    } while (choice != 0);
    return 0;
    }

