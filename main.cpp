#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;


#define userFile_Name "C:\\Users\\Mubashir\\Documents\\Linked_List_Assignment\\user.txt"
#define printerFile_Name "C:\\Users\\Mubashir\\Documents\\Linked_List_Assignment\\printer.txt"
#define OutFile_Name "C:\\Users\\Mubashir\\Documents\\Linked_List_Assignment\\output.txt"
















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

    void delete_this_doc( document_Struct *n)
    {
        if(head == n)
        {
            if(head->next == NULL)
            {
                head = NULL;
                return;
            }
            head->doc_id = head->next->doc_id;
            head->doc_total_pages = head->next->doc_total_pages;
            n = head->next;
            head->next = head->next->next;
            free(n);
            return;
        }
        // find the previous node
        document_Struct *prev = head;
        while(prev->next != NULL && prev->next != n)
        {
            prev = prev->next;
        }
        if(prev->next == NULL)
        {
            cout << "\nGiven node is not present in Linked List";
            return;
        }
        prev->next = prev->next->next;
        free(n);
        return;
    }

    document_Struct * get_doc_head ()
    {
        struct document_Struct* ptr;
        ptr = head;
        if(ptr != NULL)
        {
            return ptr;
        }
        return NULL;
    } // end of get_doc_with_ID method

    void display_doc() {
        struct document_Struct* ptr;
        ptr = head;
        while (ptr != NULL) {
            cout<<"\t\t\t doc ID : "<< ptr->doc_id <<" with pages : "<<ptr->doc_total_pages <<endl;
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
    bool inifinity;
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

    void add_printer(int id, int max)
    {
        printer_struct *tmp = new printer_struct;
        tmp->printer_id = id;
        if(max == -1)
        {
            tmp->max_capacity = 1000000000;
            tmp->left_capacity = 1000000000 ;
            tmp->inifinity = true;
        }
        else
        {
            tmp->max_capacity = max;
            tmp->left_capacity = max ;
            tmp->inifinity = false;
        }
        tmp->current_load =0.0;
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

    int add_printer_Docs(int printerID, int docID, int docPages)
    {
        struct printer_struct* ptr;
        ptr = head;
        while(ptr != NULL)
        {
            if(ptr->printer_id == printerID)
            {
                ptr->docs->add_doc( docID, docPages);
                int max = ptr->max_capacity;
                float ll = ptr->current_load;
                int left = ptr->left_capacity;
                ll = (ll + ( (docPages *100 ) / max ));
                left = left - docPages;
                if(!(ptr->inifinity))
                {
                    ptr->left_capacity = left;
                    ptr->current_load = (int)ll;
                }
                ofstream output;
                output.open (OutFile_Name, ios::app );
                if ( !output.is_open() )
                {
                    cout << "There was a problem opening the file. Press any key to close." << endl;
                }
                else
                {
                    output << "D"<<docID<<", P"<<printerID <<endl;
                    output.close();
                }
                return 1;
            }
            else
            {
                ptr = ptr->next;
            }
        } // end of while loop
        return -1; // error to find that user id
    } // end of add_user_Docs

    struct printer_struct * get_printer_head()
    {
        return head;
    }

    void display() {
        struct printer_struct* ptr;
        ptr = head;
        while (ptr != NULL) {
            cout<<" Printer ID : " << ptr->printer_id <<" with max capacity: "<< ptr->max_capacity <<endl;
            ptr = ptr->next;
        } // End of while loop
    } // end of display function
}printer_obj;

//***************************** USER Struct & Class ********************************************
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

    user_struct * get_head()
    {
        return head;
    }

    void  add_user_Docs(int userID, int docID, int docPages)
    {
        struct user_struct* ptr;
        ptr = head;
        while(ptr != NULL)
        {
            if(ptr->user_id == userID)
            {
                ptr->docs->add_doc(docID, docPages);
                ptr->docCounter++;
                break;
            }
            else
            {
                ptr = ptr->next;
            }
        } // end of while loop
    } // end of add_user_Docs

    void delete_this_user( user_struct *n)
    {
        if(head == n)
        {
            if(head->next == NULL)
            {
                cout << "All Users are deleted"<<endl;
                head = NULL;
                return;
            }
            head->user_id = head->next->user_id;
            head->priority = head->next->priority;
            head->numberOfDocs = head->next->numberOfDocs;
            head->docCounter = head->next->docCounter;
            head->docs = head->next->docs;
            n = head->next;
            head->next = head->next->next;
            free(n);
            return;
        }
        // find the previous node
        user_struct *prev = head;
        while(prev->next != NULL && prev->next != n)
        {
            prev = prev->next;
        }
        if(prev->next == NULL)
        {
            cout << "\nGiven node is not present in Linked List";
            return;
        }
        prev->next = prev->next->next;
        free(n);
        return;
    }

    void display_users() {
        struct user_struct* ptr;
        ptr = head;
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

//***************************** File Lines handlers Methods ********************************************
void process_line_of_user_File(string line)
{
    int userIDD = 0;
    int userPriority = 0;
    int userTotalDocs = 0;
    int docIDD = 0;
    int docPagess = 0;
    int count = 0;
    int n = 0;
    istringstream ss(line);
    do {
        string word;
        ss >> word;
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
                users_obj.add_user_Docs(userIDD, docIDD, docPagess);
            }
        }
        count++;
    } while (ss);
}

void process_line_of_printer_File(string line)
{
    int prterIDD = 0;
    int prterCapacity = 0;
    int count = 0;
    int n = 0;
    istringstream ss(line);
    do {
        string word;
        ss >> word;
        n = word.length();
        char char_array[n + 1];
        strcpy(char_array, word.c_str());
        if((count == 0) && (char_array[0] == 'p' || char_array[0] == 'P') && (word != ""))  // Printer ID
        {
            string id_is = "";
            for(int ii =1; ii<n; ii++) { id_is += char_array[ii]; }
            istringstream ss_id(id_is);
            ss_id >> prterIDD ;
        }
        else if(count == 1  && (word != ""))  // user Priority
        {
            istringstream sstream(word);
            sstream >> prterCapacity ;
            printer_obj.add_printer(prterIDD, prterCapacity);
        }
        count++;
    } while (ss);
}

//***************************** Printer Spooler ********************************************
void PrinterSpooler()
{
    struct user_struct *main_ptr = users_obj.get_head();
    struct user_struct *ptr;
    struct user_struct *user_with_maxPriority;
    int current_priority = 0;
    struct printer_struct *printer_ptr = printer_obj.get_printer_head();
    while (main_ptr != NULL) {
        ptr = main_ptr;
        current_priority = 0;
        while (ptr != NULL)  // only to find out the user in linked-list having largest priority number
        {
            if(current_priority < ptr->priority)
            {
                current_priority = ptr->priority;
                user_with_maxPriority = ptr;
            }
            ptr = ptr->next;
        } // end of child while loop
        user_with_maxPriority->docs->display_doc();
        printer_ptr = printer_obj.get_printer_head();
        int lload = printer_ptr->current_load;
        int total_Page = user_with_maxPriority->docs->get_doc_head()->doc_total_pages;
        int lleft = printer_ptr->left_capacity;
        int max_capacity_ofPrinter = printer_ptr->max_capacity;
        while(printer_ptr !=  NULL)
        {
            if((lload < 50) && ((total_Page  < lleft) || (lleft == -1)))
            {
                document_Struct *dd = user_with_maxPriority->docs->get_doc_head();
                while (dd != NULL) {
                    if((lload < 50) && (total_Page < lleft))
                    {
                        ofstream output;
                        output.open (OutFile_Name, ios::app );
                        if ( !output.is_open() )
                        {
                            cout << "There was a problem opening the file. Press any key to close." << endl;
                        }
                        else
                        {
                            output << "U"<<user_with_maxPriority->user_id<<", ";
                            output.close();
                        }
                        int iddd = printer_ptr->printer_id;
                        int doci = dd->doc_id;
                        int docp = dd->doc_total_pages;
                        printer_obj.add_printer_Docs(iddd, doci, docp);
                        user_with_maxPriority->docs->delete_this_doc(dd);
                        dd = user_with_maxPriority->docs->get_doc_head();
                        if(dd != NULL)
                        {
                            printer_ptr = printer_obj.get_printer_head();
                            lload = printer_ptr->current_load;
                            total_Page = dd->doc_total_pages;
                            lleft = printer_ptr->left_capacity;
                            max_capacity_ofPrinter = printer_ptr->max_capacity;
                        }
                        else {
                            break;
                        }
                    }
                    else
                    {
                        printer_ptr = printer_ptr->next;
                        if(printer_ptr != NULL)
                        {
                            lload = printer_ptr->current_load;
                            total_Page = user_with_maxPriority->docs->get_doc_head()->doc_total_pages;
                            lleft = printer_ptr->left_capacity;
                        }
                        else {
                            lload = 0;
                            total_Page = user_with_maxPriority->docs->get_doc_head()->doc_total_pages;
                            lleft = 1000000; //printer_ptr->left_capacity;
                        }
                    }
                } // end of while loop where doc are not null
                break;
            } // end of if where lload < 50
            else {
                printer_ptr = printer_ptr->next;
                if(printer_ptr != NULL)
                {
                    lload = printer_ptr->current_load;
                    total_Page = user_with_maxPriority->docs->get_doc_head()->doc_total_pages;
                    lleft = printer_ptr->left_capacity;
                }
            }
        } // end of while loop where printer is null
        users_obj.delete_this_user(user_with_maxPriority);
        main_ptr = users_obj.get_head();
    } // end of parent while loop
}


//***************************** Program Main Function ********************************************
int main()
{
    cout<<"************************************************************************************************"<<endl;
    cout<<"********************************* Start Linked List Program ************************************"<<endl;
    cout<<"************************************************************************************************"<<endl;
    string testline;
    string word;
    ifstream userf ( userFile_Name );
    if ( !userf.is_open() )
    {
        cout << "There was a problem opening the User file. Press any key to close." << endl;
    }
    else
    {
        cout << "User File opened successfully. Now reading data: " <<endl;
        while( userf.good() )
        {
            getline ( userf, testline, '\n' );
            process_line_of_user_File(testline);
        }
        cout<<" All user data read and filled in linked-list."<<endl;
    }
    cout<<"************************************************************************************************"<<endl;
    cout<<endl<<endl<<endl;
    cout<<"################################################################################################"<<endl;
    cout<<"################################################################################################"<<endl;
    ifstream prters ( printerFile_Name );
    if ( !prters.is_open() )
    {
        cout << "There was a problem opening the file printers.txt. Press any key to close." << endl;
    }
    else
    {
        cout << " Printer File opened successfully. Now reading data: "<<endl;
        while( prters.good() )
        {
            getline ( prters, testline, '\n' );
            process_line_of_printer_File(testline);
        }
        cout<<" All Printer data read and filled in linked-list."<<endl;
    }
    cout<<"################################################################################################"<<endl;
    cout<<endl<<endl<<endl;
    cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
    ofstream output;
    output.open (OutFile_Name , ios::out );
    if ( !output.is_open() )
    {
        cout << "There was a problem opening the output file . " << endl;
    }
    else
    {
        cout << " Output File opened successfully. "<<endl;
    }
    output.close();
    cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl<<endl;
    cout<<"Now Spooling "<<endl;
    PrinterSpooler();
    cout<<endl<<endl<<" Output file generated .";
    cout<<endl<<endl<<endl<<"************************************************************************************************"<<endl;
    cout<<"******************************************* Thank You ******************************************"<<endl;
    cout<<"************************************************************************************************"<<endl;
    return 0;
} // end of main class
