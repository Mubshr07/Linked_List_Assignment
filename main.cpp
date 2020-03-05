
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <bits/stdc++.h>


using namespace std;

//***************************** Document Struct & Class ********************************************
struct document_Struct
{
    int doc_id;
    int doc_total_pages;
    document_Struct *next;
}; // end of struct for document

class document_list
{
private:
    document_Struct *head, *tail;
public:
    document_list()
    {
        head = NULL;
        tail = NULL;
    } // end of constructor

    void add_doc(int id, int pages)
    {
        document_Struct *tmp = new document_Struct;
        tmp->doc_id = id;
        tmp->doc_total_pages = pages;
        tmp->next = NULL;

        if(head == NULL)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail = tail->next;
        }
    } // end of add_node function

    document_Struct * get_doc_with_ID (int id)
    {
        struct document_Struct* ptr;
      ptr = head;
      while (ptr != NULL) {
         if(ptr->doc_id = id)
         {
             return ptr;
         }
         else
         {
            ptr = ptr->next;
         }
      } // End of while loop
      return NULL;
    } // end of get_doc_with_ID method


    void display_doc() {
      struct document_Struct* ptr;
      ptr = head;
      while (ptr != NULL) {
         cout<<" doc ID : "<< ptr->doc_id <<" with pages : "<<ptr->doc_total_pages <<endl;
         ptr = ptr->next;
      } // End of while loop
   } // end of display function

} docs_obj; // end of class document_list Class





//***************************** Printer Struct & Class ********************************************
struct printer_struct
{
    int printer_id ;
    int current_load ;
    int max_capacity ;
    int left_capacity ;
    document_list *docs;
    printer_struct *next;
};

class printer_list
{
private:
    printer_struct *head,*tail;
public:
    printer_list()
    {
        head = NULL;
        tail = NULL;
    } // end of constructor

    void add_node(int id, int max)
    {
        printer_struct *tmp = new printer_struct;
        tmp->printer_id = id;
        tmp->max_capacity = max;
        tmp->docs = NULL;
        tmp->next = NULL;

        if(head == NULL)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail = tail->next;
        }
    } // end of add_node function

    int add_printer_Docs(int printerID, int docID)
    {
        struct printer_struct* ptr;
        //struct document_Struct *doc_ptr;
        ptr = head;
        while(ptr != NULL)
        {
            if(ptr->printer_id == printerID)
            {
                struct document_Struct * docPtr;
                document_list doclist;
                docPtr = doclist.get_doc_with_ID(docID);

                ptr->docs->add_doc( docPtr->doc_id, docPtr->doc_total_pages);

                return 1;
            }
            else
            {
                ptr = ptr->next;
            }
        } // end of while loop
        return -1; // error to find that user id
    } // end of add_user_Docs

    void display() {
      struct printer_struct* ptr;
      ptr = head;
      cout<<" Now Printing Printers list"<<endl;
      while (ptr != NULL) {
         cout<< ptr->printer_id <<" with max capacity: "<< ptr->max_capacity <<endl;
         ptr = ptr->next;
      } // End of while loop
   } // end of display function
};



//***************************** Printer Struct & Class ********************************************
struct user_struct
{
    int user_id ;
    int priority ;
    int numberOfDocs;
    int docCounter;
    document_list *docs;

    user_struct *next;
};

class user_list
{
private:
    user_struct *head,*tail;
public:
    user_list()
    {
        head = NULL;
        tail = NULL;
    } // end of constructor

    void add_user(int id, int priority, int docsNo)
    {
        user_struct *tmp = new user_struct;
        tmp->user_id = id;
        tmp->priority = priority;
        tmp->numberOfDocs = docsNo;
        tmp->docCounter = 0;
        tmp->docs = new document_list();

        tmp->next = NULL;

        if(head == NULL)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail = tail->next;
        }
    } // end of add_node function

    void  add_user_Docs(int userID, int docID, int docPages)
    {
        struct user_struct* ptr;
        ptr = head;
        while(ptr != NULL)
        {
            if(ptr->user_id == userID)
            {
//                cout<<" congraulations you find me.";
                cout<<endl<<" user ID " <<userID <<" Doc Counter : "<<ptr->docCounter<<" Doc id: "<<docID<<" with pages: "<<docPages <<" ,\t" ;
                ptr->docs->add_doc(docID, docPages);
                ptr->docCounter++;
                //return 1;
                break;
            }
            else
            {
                ptr = ptr->next;
            }
        } // end of while loop
        //return -1; // error to find that user id
    } // end of add_user_Docs

    void display_users() {
      struct user_struct* ptr;
      ptr = head;
      cout<<"Now Printing Users list"<<endl;
      while (ptr != NULL) {
         cout<<"User id "<< ptr->user_id <<" with priority "<< ptr->priority <<" and total Doc: "<< ptr->numberOfDocs << " with docs : "<<endl;
            if(ptr->docs != NULL)
            {
                ptr->docs->display_doc();
            }
         cout<<endl<<endl;
         ptr = ptr->next;
      } // End of while loop
   } // end of display function

} users_obj;




void process_line_of_user_File(string line)
{
    int userIDD = 0;
    int userPriority = 0;
    int userTotalDocs = 0;
    int docIDD = 0;
    int docPagess = 0;

    int count = 0;

    cout << line << endl;
    int n = 0;

    istringstream ss(line);

    do {
        string word;
        ss >> word;

        // Print the read word
        //cout <<" word indx : "<<count <<" :: " << word << endl;

        n = word.length();
        char char_array[n + 1];
        strcpy(char_array, word.c_str());

        if((count == 0) && (char_array[0] == 'u' || char_array[0] == 'U') && (word != ""))  // User ID
        {
            string id_is = "";
            for(int ii =1; ii<n; ii++) { id_is += char_array[ii]; }
            istringstream ss_id(id_is);
            ss_id >> userIDD ;
        }
        else if(count == 1  && (word != ""))  // user Priority
        {
            istringstream sstream(word);
            sstream >> userPriority ;
        }
        else if(count == 2 && (word != "")) // user total documents
        {
            istringstream sstream(word);
            sstream >> userTotalDocs ;

            cout<<" User id: "<<userIDD<<" Priority: "<<userPriority <<" total Docs: "<<userTotalDocs<<" \t\t";
            users_obj.add_user(userIDD, userPriority, userTotalDocs);

        }

         else if(count > 2 && (word != "")) // docs
        {
            if((char_array[0] == 'd' || char_array[0] == 'D'))
            {
                string str = "";
                for(int ii =1; ii<n; ii++) { str += char_array[ii]; }
                istringstream ss_s(str);
                ss_s >> docIDD ;
            }
            else
            {
                istringstream sstream(word);
                sstream >> docPagess ;
//                cout<<" Doc id: "<<docIDD<<" with pages: "<<docPagess <<" ,\t";
                users_obj.add_user_Docs(userIDD, docIDD, docPagess);
            }
        }


        count++;

    } while (ss);




    cout <<endl<<endl;
}




//***************************** Program Main Function ********************************************
int main()
{

    cout<<"************************************************************************************************"<<endl;
    cout<<"********************************* Start Linked List Program ************************************"<<endl;
    cout<<"************************************************************************************************"<<endl<<endl<<endl;

    string testline;
    string word;

    ifstream Test ( "C:\\Users\\Mubashir\\Documents\\Linked_List_Assignment\\user - Copy.txt" );

    if ( !Test.is_open() )
    {
        cout << "There was a problem opening the file. Press any key to close." << endl;
    }
    else
    {
        cout << "File opened successfully. Now reading data: " << endl<<endl;
        while( Test.good() )
        {
            getline ( Test, testline, '\n' );
            process_line_of_user_File(testline);
        }
    }

    cout<<"************************************************************************************************"<<endl;
    cout<<"************************************************************************************************"<<endl;
    cout<<" Now showing user linked list "<<endl;
    users_obj.display_users();


    cout<<"************************************************************************************************"<<endl;
    cout<<"************************************************************************************************"<<endl;
    cout<<" Now showing Docs linked list "<<endl;
    //docs_obj.display_doc();



    cout<<endl<<endl<<endl<<"************************************************************************************************"<<endl;
    cout<<"******************************************* Thank You ******************************************"<<endl;
    cout<<"************************************************************************************************"<<endl;
    return 0;
} // end of main class




