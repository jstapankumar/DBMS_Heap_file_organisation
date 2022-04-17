#include <bits/stdc++.h>
using namespace std;

int p_size;

class blank_page           ////////////////////////////////class for creating a blank page 
{

public:
  int size;
  int num_records;
  int free_p;
  int empty_spc;
  int page_id;
  vector<int> data;
  blank_page *next;
  blank_page *prev;

  blank_page(int s)        ///////////////////////////////constructor for the blank page and initialization of various properties of the blank page
  {
    page_id = 0;
    size = s;
    num_records = 0;
    free_p = 0;
    empty_spc = s - 16;
    next = NULL;
    prev = NULL;
  }
};

blank_page *head = NULL;

///////////////////////function to insert a value

void insert_d(int r_size, int value)
{
  if (head == NULL)
  { ///////////when there is no page  in the file or file is empty
    blank_page *newPage1 = new blank_page(p_size);
    head = newPage1;
    newPage1->data.push_back(value);
    newPage1->empty_spc -= (r_size + 4);
    newPage1->free_p += r_size;
    newPage1->num_records += 1;
    return;
  }

  blank_page *temp = head; /////////////when there are pages in file as well as space is availabe to store the record
  while (temp != NULL)     ////////////////loop to check whether empty space is available or not by traversing through each page
  {
    if (temp->empty_spc >= r_size + 4)     /////////////////////////if thre is sufficient empty space to insert a record we simply need to insert the record and update the value of various things
    {
      temp->data.push_back(value);
      temp->empty_spc -= (r_size + 4);
      temp->free_p += r_size;
      temp->num_records += 1;
      return;
    }
    temp = temp->next;
  }
  blank_page *last = head;
  blank_page *newPage2 = new blank_page(p_size); //////////////when there doesn't exist a page that can accomodate the record then we have to create a new page
  while (last->next != NULL)
  {
    last = last->next;
  }
  last->next = newPage2;
  newPage2->prev = last;
  newPage2->data.push_back(value); ////////////////////////////pushing the value to be inserted into the data vector
  newPage2->empty_spc -= (r_size + 4);    /////////////////////////////////////reducing the size of empty space
  newPage2->free_p += r_size;      ///////////////////////////changing the adress of free space pointer
  newPage2->num_records += 1;      ///////////////////////////increasing the value of number of records by 1 after successfull insertion
  newPage2->page_id = last->page_id + 1;  ////////////////////////////////incresing the value of page_id as we have created a new page
}

//////////////////////////////function to search a value

int search(int value)
{

  blank_page *temp = head;
  bool flag = true;
  while (temp != NULL) //////////////////loop to traverse through the entire file by going_through each page
  {
    for (int i = 0; i < (temp->data).size(); i++) //////////////////loop to traverse through the entire page by going_through each record
    {

      if ((temp->data)[i] == value)
      {

        cout << temp->page_id << " " << i << "\n"; ////////////when we got the value we required we need to cout the page_id and the index at which we got the record
        return 0;
      }
    }
    temp = temp->next;
    if (temp == NULL) //////////////////when we can't find the value we need to cout -1 for page_id and -1 for record
    {
      flag = false;
    }
  }
  if (flag == false)
  {
    cout << "-1 -1"
         << "\n";
    return 0;
  }
}

/////////////////////////////////function to dispaly the status of heap file

void print_status()
{
  int num_pages = 0;
  blank_page *temp1 = head;
  while (temp1 != NULL) ///////////////////////////loop for counting the number of pages in a file
  {
    num_pages += 1;
    temp1 = temp1->next;
  }
  int n = num_pages;
  cout << n << " ";
  blank_page *temp2 = head;
  while (temp2 != NULL)///////////////////////////loop for getting and printing number of records in each file
  {
    cout << temp2->num_records << " ";
    temp2 = temp2->next;
  }
  cout << "\n";
}

/////////////////////////////////////////// main function

int main()
{
  cin >> p_size;
  int operation;
  int x;
  int y;
  int v;
  while (7)
  {
    cin >> operation;
    switch (operation)
    {
    case 1: ///////////////////////case1 is for inserting a record
    {
      cin >> x >> y;
      insert_d(x, y);
    }
    break;
    case 2: ////////////////////////case2 is for printing the status of the heap file
    {
      print_status();
    }
    break;
    case 3: ///////////////////////case3 is for searching the value v in heap file
    {
      cin >> v;
      search(v);
    }
    break;
    case 4: //////////////////////case4 is for quitting
    {
      return 0;
    }
    }
  }
}
