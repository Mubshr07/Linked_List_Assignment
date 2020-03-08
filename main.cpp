
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


    void delete_this_doc( document_Struct *n)
    {
        // When node to be deleted is head node
        if(head == n)
        {
            if(head->next == NULL)
            {
                //cout << "All docs are deleted"<<endl;
                head = NULL;
                return;
            }
            head->doc_id = head->next->doc_id;
            head->doc_total_pages = head->next->doc_total_pages;
            // store address of next node
            n = head->next;
            // Remove the link of next node
            head->next = head->next->next;
            // free memory
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
        // Remove node from Linked List
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
        tmp->max_capacity = max;
        tmp->current_load =0.0;
        tmp->left_capacity = max ;
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


    //int get_left_over_capacity(int printerID)
    int get_left_over_capacity(printer_struct *printer)
    {
        if(head == printer)
        {
            return head->left_capacity;
        }
        // find the previous node
        printer_struct *prev = head;
        while(prev->next != NULL && prev->next != printer)
        {
            prev = prev->next;
        }
        if(prev->next == NULL)
        {
            cout << "\nGiven node is not present in Linked List";
            return 0;
        }
        return prev->left_capacity;
    }

    int get_current_Load(int printerID)
    {
        struct printer_struct* ptr;
        ptr = head;
        while(ptr != NULL)
        {
            if(ptr->printer_id == printerID)
            {
                return ptr->current_load;
            }
            else
            {
                ptr = ptr->next;
            }
        } // end of while loop
        return -1; // error to find printer of that id
    }

    int get_max_Capacity(int printerID)
    {
        struct printer_struct* ptr;
        ptr = head;
        while(ptr != NULL)
        {
            if(ptr->printer_id == printerID)
            {
                return ptr->max_capacity;
            }
            else
            {
                ptr = ptr->next;
            }
        } // end of while loop
        return -1; // error to find printer of that id
    }


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
                ptr->left_capacity = left - docPages;
                ptr->current_load = (int)ll;
                left = left - docPages;
                cout<<" Passing Doc id : "<<docID<<" and pages: "<<docPages<<" to printer ID: "<<ptr->printer_id<<" with load : "<<ll<<" and left capacity: "<<left<<" and current docs load : " <<endl;
                //ptr->current_load = (ptr->current_load + ( (docPages / ptr->max_capacity) * 100 ));

                //cout<<"\n current left over : ("<<left<<") With load : ("<<ll<<") with max cap : "<<max<<endl;


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
                //                cout<<" congraulations you find me.";
                //cout<<endl<<" user ID " <<userID <<" Doc Counter : "<<ptr->docCounter<<" Doc id: "<<docID<<" with pages: "<<docPages <<" ,\t" ;
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
        // When node to be deleted is head node
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
            //head->docs = new document_list() {head->next->docs};
            head->docs = head->next->docs;
            // store address of next node
            n = head->next;
            // Remove the link of next node
            head->next = head->next->next;
            // free memory
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
        // Remove node from Linked List
        //cout<<" removing user (which is not head) id: "<<prev->user_id<<endl;
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
    //cout << line << endl;
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
            //cout<<" User id: "<<userIDD<<" Priority: "<<userPriority <<" total Docs: "<<userTotalDocs<<" \t\t";
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
    //cout <<endl<<endl;
}

void process_line_of_printer_File(string line)
{
    int prterIDD = 0;
    int prterCapacity = 0;
    int count = 0;
    //cout << line << endl;
    int n = 0;
    istringstream ss(line);
    do {
        string word;
        ss >> word;
        //cout <<" word indx : "<<count <<" :: " << word << endl;
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
            //cout<<" printer id: "<<prterIDD <<" with Capacity : "<< prterCapacity <<" ,\t";
            printer_obj.add_printer(prterIDD, prterCapacity);
        }
        count++;
    } while (ss);
    //cout <<endl<<endl;
}


//***************************** Printer Spooler ********************************************
void PrinterSpooler()
{
    struct user_struct *main_ptr = users_obj.get_head();
    struct user_struct *ptr;
    struct user_struct *user_with_maxPriority;
    int current_priority = 0;

    //struct printer_struct *printer_main_ptr = printer_obj.get_printer_head();
    struct printer_struct *printer_ptr = printer_obj.get_printer_head();

    cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<"++ User ID \t++ Doc ID \t++ DocPages \t++ Printer ID \t++ Printer Load \t++ Printer Capacity Left \t++"<<endl;
    cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;

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


        cout<<"\n\n User id: "<<user_with_maxPriority->user_id<<" having total docs : "<<user_with_maxPriority->docCounter<<" and Docs are : "<<endl;
        user_with_maxPriority->docs->display_doc();
        cout<<"+++++++++++++++++++++++++++++++++++++++++++++"<<endl;


        printer_ptr = printer_obj.get_printer_head();

        int lload = printer_ptr->current_load;
        int total_Page = user_with_maxPriority->docs->get_doc_head()->doc_total_pages;
        int lleft = printer_ptr->left_capacity;
        int max_capacity_ofPrinter = printer_ptr->max_capacity;

        cout<<" printer head max cap : "<<max_capacity_ofPrinter<<" with load "<<lload<<" and left cap : "<<lleft<<endl<<endl<<endl;
        while(printer_ptr !=  NULL)
        {
            if((lload < 50) && ((total_Page  < lleft) || (lleft == -1)))
            {

                document_Struct *dd = user_with_maxPriority->docs->get_doc_head();
                while (dd != NULL) {
                    cout<<" User id : "<<user_with_maxPriority->user_id<<" -> printer id "<<printer_ptr->printer_id <<" left Cap : "<< lleft <<" with load "<<lload<<endl;
                    if((lload < 50) && (total_Page < lleft))
                    {
                        int iddd = printer_ptr->printer_id;
                        int doci = dd->doc_id;
                        int docp = dd->doc_total_pages;
                        printer_obj.add_printer_Docs(iddd, doci, docp);

                        cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
                        //cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;


                        user_with_maxPriority->docs->delete_this_doc(dd);
                        dd = user_with_maxPriority->docs->get_doc_head();

                        if(dd != NULL)
                        {
                        lload = printer_ptr->current_load;
                        total_Page = dd->doc_total_pages;
                        lleft = printer_ptr->left_capacity;
                        }
                        else {
                            break;
                        }
                    }
                    else
                    {
                        cout<<"\n\n +-+-+-+-+-+-+--+-+-+-+-+-+-+-else statement and printer is changed ";
                        printer_ptr = printer_ptr->next;
                        if(printer_ptr != NULL)
                        {
                            cout<<" in If statement "<<endl;
                            lload = printer_ptr->current_load;
                            total_Page = user_with_maxPriority->docs->get_doc_head()->doc_total_pages;
                            lleft = printer_ptr->left_capacity;
                        }
                        else {
                            cout<<" in else statement "<<endl;
                            lload = 0;
                            total_Page = user_with_maxPriority->docs->get_doc_head()->doc_total_pages;
                            lleft = 1000000; //printer_ptr->left_capacity;
                        }
                    }
                } // end of while loop where doc are not null

                cout<<"\n\n\t\t\t user docs are NULL now"<<endl;
                break;
            } // end of if where lload < 50
            else {
                cout<<"------->>>>>>>>>>>>>> current printer load is greater then 50 now changing to the next printer "<<endl;
                printer_ptr = printer_ptr->next;
                if(printer_ptr != NULL)
                {
                    lload = printer_ptr->current_load;
                    total_Page = user_with_maxPriority->docs->get_doc_head()->doc_total_pages;
                    lleft = printer_ptr->left_capacity;
                }
            }

        } // end of while loop where printer is null






        /*
        while(printer_ptr != NULL)
        {
            //printer_ptr = printer_main_ptr;
            int lload = printer_ptr->current_load;
            int total_Page = user_with_maxPriority->docs->get_doc_head()->doc_total_pages;
            int lleft = printer_ptr->left_capacity;
            if((current_Printer_Load > lload) && (total_Page  < lleft))
            {
                current_Printer_Load = printer_ptr->current_load;
                left_over_capacity_ofPrinter = printer_ptr->left_capacity;
                int display_leftOver = printer_obj.get_left_over_capacity(printer_ptr);
                max_capacity_ofPrinter = printer_ptr->max_capacity;
                cout<<" -----------> printer id "<<printer_ptr->printer_id <<" left Cap : "<< left_over_capacity_ofPrinter <<" with load "<<current_Printer_Load <<endl;

                if((current_Printer_Load < 50)  && (total_Page  < left_over_capacity_ofPrinter))
                {
                    document_Struct *dd = user_with_maxPriority->docs->get_doc_head();
                    while (dd != NULL) {
                        printer_obj.add_printer_Docs(printer_ptr->printer_id, dd->doc_id, dd->doc_total_pages);
                        //cout<<" user id "<<user_with_maxPriority->user_id<<" doc id "<<dd->doc_id <<" with pages "<<dd->doc_total_pages<<" is added. ";
                        //cout<<" printer id : "<<printer_ptr->printer_id<<" with max_capacity : "<<printer_ptr->max_capacity<<" with load : "<<printer_ptr->current_load<<" and left over : "<<printer_ptr->left_capacity<<endl;

                     // cout<<"++ User ID \t++ Doc ID \t++ Printer ID \t++ Printer Load \t++ Printer Capacity Left \t++"<<endl;
                        int load = printer_ptr->current_load;
                       printf("++   U%d \t++   D%d \t++    P%d \t ++   %3.2f  \t  ++           %d     ++\n", user_with_maxPriority->user_id, dd->doc_id, printer_ptr->printer_id, load, display_leftOver );
                      cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
                      //cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;

                        user_with_maxPriority->docs->delete_this_doc(dd);
                        dd = user_with_maxPriority->docs->get_doc_head();
                    }
                }
                else if (printer_ptr->next == NULL)
                {
                    document_Struct *dd = user_with_maxPriority->docs->get_doc_head();
                    if(dd != NULL)
                    {
                        printer_obj.add_printer_Docs(printer_ptr->printer_id, dd->doc_id, dd->doc_total_pages);
                        //cout<<" user id "<<user_with_maxPriority->user_id<<" doc id "<<dd->doc_id <<" with pages "<<dd->doc_total_pages<<" is added. ";
                        //cout<<" printer id : "<<printer_ptr->printer_id<<" with max_capacity : "<<printer_ptr->max_capacity<<" with load : "<<printer_ptr->current_load<<" and left over : "<<printer_ptr->left_capacity<<endl;

                     // cout<<"++ User ID \t++ Doc ID \t++ Printer ID \t++ Printer Load \t++ Printer Capacity Left \t++"<<endl;
                        int load = printer_ptr->current_load;
                       printf("++   U%d \t++   D%d \t++    P%d \t ++   %3.2f  \t  ++           %d     ++\n", user_with_maxPriority->user_id, dd->doc_id, printer_ptr->printer_id, load, display_leftOver );
                      cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
                      //cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;

                        user_with_maxPriority->docs->delete_this_doc(dd);
                   }
                }
                //break;
            }
            printer_ptr = printer_ptr->next;

            cout<<"\n\n\n choosing next printer";
        } // end of printer while loop

        */

        //cout<<"+++++++++++++++++++++++++++++++++++++++++++++"<<endl;
        cout<<"Now deleting user of id : "<<user_with_maxPriority->user_id<<endl;
        users_obj.delete_this_user(user_with_maxPriority);
        cout<<"user deleted "<<endl;

        main_ptr = users_obj.get_head();

    } // end of parent while loop
    cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;
    cout<<"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"<<endl;

}



//***************************** Program Main Function ********************************************
int main()
{
    cout<<"************************************************************************************************"<<endl;
    cout<<"********************************* Start Linked List Program ************************************"<<endl;
    cout<<"************************************************************************************************"<<endl<<endl<<endl;
    string testline;
    string word;
    ifstream userf ( "C:\\Users\\Mubashir\\Documents\\Linked_List_Assignment\\user - Copy.txt" );
    if ( !userf.is_open() )
    {
        cout << "There was a problem opening the file. Press any key to close." << endl;
    }
    else
    {
        cout << "User File opened successfully. Now reading data: " <<endl;
        while( userf.good() )
        {
            getline ( userf, testline, '\n' );
            process_line_of_user_File(testline);
        }
        cout<<" All user data read and filled in linked-list."<<endl<<endl<<endl;
    }
    cout<<"************************************************************************************************"<<endl;
    //cout<<" Now showing user linked list "<<endl;
    //users_obj.display_users();


    cout<<endl<<endl<<endl;
    cout<<"################################################################################################"<<endl;
    cout<<"################################################################################################"<<endl;
    ifstream prters ( "C:\\Users\\Mubashir\\Documents\\Linked_List_Assignment\\printer.txt" );
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
        cout<<" All user data read and filled in linked-list."<<endl<<endl<<endl;
    }
    cout<<"################################################################################################"<<endl;
    //cout<<" Now showing Printers linked list "<<endl;
    //printer_obj.display();

    cout<<endl<<endl<<endl;
    cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
    cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
    cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%"<<endl;
    cout<<"Now Spooling "<<endl;
    PrinterSpooler();

    cout<<endl<<endl<<endl<<"************************************************************************************************"<<endl;
    cout<<"******************************************* Thank You ******************************************"<<endl;
    cout<<"************************************************************************************************"<<endl;
    return 0;
} // end of main class




