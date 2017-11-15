#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

// if user doesnt define, this is the 
// default hash table size
const int HASH_SIZE = 100;
 
template <class ItemType>
class HashTable
{
public:
	HashTable(int hashSze = HASH_SIZE);
		/*   Function: Constructor initializes hash table 
			Precondition: None
			Postcondition: Defines private variables */
	bool IsEmpty(int key);
		/*   Function: Determines whether hash table is empty at the given key
			Precondition: Hash table has been created
			Postcondition: The function = true if the hash table is empty and the
							 function = false if hash table is not empty */
	bool  IsFull();
		/*   Function: Determines whether hash table is full
			Precondition: Hash table has been created
			Postcondition: The function = true if the hash table is full and the
							 function = false if hash table is not full */
	int Hash(ItemType newItem);
		/*   Function: Computes and returns a unique hash key for a given item
						The returned key is the given cell where the item resides
			Precondition:  Hash table has been created and is not full
			Postcondition: The hash key is returned */
	void Insert(ItemType newItem);
		/*   Function: Adds newItem to the back of the list at a given key in the hash table
						 A unique hash key is automatically generated for each newItem
			Precondition:  Hash table has been created and is not full
			Postcondition: Item is in the hash table */
	void Append(int key, ItemType newItem);
		/*   Function: Adds new item to the end of the list at a given 
						 key in the hash table
			Precondition:  Hash table has been created and is not full
			Postcondition: Item is in the hash table */
	bool Remove(ItemType deleteItem, int key = -1);
		/*   Function: Removes the first instance from the table whose value is "deleteItem"
					  Optional second parameter indicates the key where deleteItem is located
			Precondition:  Hash table has been created and is not empty
			Postcondition: The function = true if deleteItem is found and the
							 function = false if deleteItem is not found */
	void Sort(int key);
		/*   Function: Sort the items in the table at the given key
			Precondition: Hash table has been initialized
			Postcondition: The hash table is sorted */
	int TableSize();
		/*   Function: Return the size of the hash table
			Precondition: Hash table has been initialized
			Postcondition: The size of the hash table is returned */
	int TotalElems();
		/*   Function: Return the total number of elements contained in the hash table
			Precondition: Hash table has been initialized
			Postcondition: The size of the hash table is returned */
	int BucketSize(int key);
		/*   Function: Return the number of items contained in the hash table
						cell at the given key
			Precondition: Hash table has been initialized
			Postcondition: The size of the given key cell is returned */
	int Count(ItemType searchItem);
		/*   Function: Return the number of times searchItem appears in the table.
						Only works on items located in their correctly hashed cells
			Precondition: Hash table has been initialized
			Postcondition: The number of times searchItem appears in the table is returned */
	void MakeEmpty();
		/*   Function: Initializes hash table to an empty state 
			Precondition: Hash table has been created
			Postcondition: Hash table no longer exists */
	~HashTable();
		/*   Function: Removes the hash table 
			Precondition: Hash table has been declared
			Postcondition: Hash table no longer exists */
	
	//  -- ITERATOR CLASS --
	class Iterator;
		/*   Function: Class declaration to the iterator 
			Precondition: Hash table has been declared
			Postcondition: Hash Iterator has been declared */
 
	Iterator begin(int key){return(!IsEmpty(key)) ? head[key]:NULL;}
		/*   Function: Returns the beginning of the current hash cell list
			Precondition: Hash table has been declared
			Postcondition: Hash cell has been returned to the Iterator */
 
	Iterator end(int key=0){return NULL;}
		/*   Function: Returns the end of the current hash cell list
			Precondition: Hash table has been declared
			Postcondition: Hash cell has been returned to the Iterator */
	
private:
	struct node	
	{			
		ItemType currentItem;		
		node* next;	
	};
	node** head; // array of linked list declaration - front of each hash table cell
	int hashSize; // the size of the hash table (how many cells it has)
	int totElems; // holds the total number of elements in the entire table
	int* bucketSize; // holds the total number of elems in each specific hash table cell
};
 
//=========================  Implementation  ================================//
 
template<class ItemType>
HashTable<ItemType>::HashTable(int hashSze)
{
	hashSize = hashSze;
	head = new node*[hashSize];
	bucketSize = new int[hashSize];
	for(int x=0; x < hashSize; ++x)
	{
		head[x] = NULL;
		bucketSize[x] = 0;
	}
	totElems = 0;
}/* End of HashTable */
 
template<class ItemType>
bool HashTable<ItemType>::IsEmpty(int key)
{
	if(key >=0 && key < hashSize)
	{
		return head[key] == NULL;
	}
	return true;
}/* End of IsEmpty */
 
template<class ItemType>
bool HashTable<ItemType>::IsFull()
{
	try
	{
		node* location = new node;
		delete location;
		return false;
	}
	catch(std::bad_alloc&)
	{
		return true;
	}
}/* End of IsFull */
 
template<class ItemType>
int HashTable<ItemType>::Hash(ItemType newItem)
{	
	long h = 19937;
	std::stringstream convert;
 
	// convert the parameter to a string using "stringstream" which is done
	// so we can hash multiple datatypes using only one function
	convert << newItem;
	std::string temp = convert.str();
 
	for(unsigned x=0; x < temp.length(); ++x)
	{
		h = (h << 6) ^ (h >> 26) ^ temp[x];
	}
	return abs(h % hashSize);
} /* End of Hash */
 
template<class ItemType>
void HashTable<ItemType>::Insert(ItemType newItem)
{
	if(IsFull())
	{
        //std::cout<<"nINSERT ERROR - HASH TABLE FULLn";
	}
	else
	{
		int key = Hash(newItem);
		Append(key,newItem);
	}
}/* End of Insert */
 
template<class ItemType>
void HashTable<ItemType>::Append(int key, ItemType newItem)
{
	if(IsFull())
	{
        //std::cout<<"nAPPEND ERROR - HASH TABLE FULLn";
	}
	else
	{
		node* newNode = new node;  // adds new node
		newNode-> currentItem = newItem;
		newNode-> next = NULL;
	
		if(IsEmpty(key))
		{
			head[key] = newNode;
		}
		else
		{
			node* tempPtr = head[key];
			while(tempPtr-> next != NULL)
			{
				tempPtr = tempPtr-> next;
			}
			tempPtr-> next = newNode;
		}
		++bucketSize[key];
		++totElems;
	}
}/* End of Append */
 
template<class ItemType>
bool HashTable<ItemType>::Remove(ItemType deleteItem, int key) 
{
	bool isFound = false;
	node* tempPtr;
	if(key == -1)
	{
		key = Hash(deleteItem);
	}	
 
    if(IsEmpty(key))
    {
        //std::cout<<"nREMOVE ERROR - HASH TABLE EMPTYn";
    }
    else if(head[key]->currentItem == deleteItem)
    {
        tempPtr = head[key];
        head[key] = head[key]-> next;
        delete tempPtr;
        --totElems;
        --bucketSize[key];
        isFound = true;
    }
    else
    {        		
        for(tempPtr = head[key];tempPtr->next!=NULL;tempPtr=tempPtr->next)
        {
            if(tempPtr->next->currentItem == deleteItem)
            {
                node* deleteNode = tempPtr->next;
                tempPtr-> next = tempPtr-> next-> next;
                delete deleteNode;
                isFound = true;
                --totElems;
                --bucketSize[key];
                break;
            }
        }        
    }
	return isFound;
}/* End of Remove */
 
template<class ItemType>
void HashTable<ItemType>::Sort(int key)
{		
    if(IsEmpty(key))
    {
        //std::cout<<"nSORT ERROR - HASH TABLE EMPTYn";
    }
    else
    { 
        int listSize = BucketSize(key);
        bool sorted = false;
 
        do{
            sorted = true;
            int x = 0;
            for(node* tempPtr = head[key];
                tempPtr->next!=NULL && x < listSize-1;
                tempPtr=tempPtr->next,++x)
            {
                if(tempPtr-> currentItem > tempPtr->next->currentItem)
                {
                    ItemType temp = tempPtr-> currentItem;
                    tempPtr-> currentItem = tempPtr->next->currentItem;
                    tempPtr->next->currentItem = temp;
                    sorted = false;
                }
            }
            --listSize;
        }while(!sorted);
    }
}/* End of Sort */
 
template<class ItemType>
int HashTable<ItemType>::TableSize()
{
    return hashSize;
}/* End of TableSize */
 
template<class ItemType>
int HashTable<ItemType>::TotalElems()
{
    return totElems;
}/* End of TotalElems */
 
template<class ItemType>
int HashTable<ItemType>::BucketSize(int key)
{
	return(!IsEmpty(key)) ? bucketSize[key]:0;
}/* End of BucketSize */
 
template<class ItemType>
int HashTable<ItemType>::Count(ItemType searchItem) 
{
	int key = Hash(searchItem);
	int search = 0;	
 
    if(IsEmpty(key))
    {
        //std::cout<<"nCOUNT ERROR - HASH TABLE EMPTYn";
    }
    else
    {        		
        for(node* tempPtr = head[key];tempPtr!=NULL;tempPtr=tempPtr->next)
        {
            if(tempPtr->currentItem == searchItem)
            {
                ++search;
            }
        }        
    }
	return search;
}/* End of Count */
 
template<class ItemType>
void HashTable<ItemType>::MakeEmpty()
{
    totElems = 0;
    for(int x=0; x < hashSize; ++x)
    {		
        if(!IsEmpty(x))
        {
            //std::cout << "Destroying nodes ...n";
            while(!IsEmpty(x))
            {
                node* temp = head[x];
                //std::cout << temp-> currentItem <<std::endl;
                head[x] = head[x]-> next;
                delete temp;
            }			
        }
        bucketSize[x] = 0;
    }
}/* End of MakeEmpty */
 
template<class ItemType>
HashTable<ItemType>::~HashTable() 
{
	MakeEmpty();
	delete[] head;
	delete[] bucketSize;
}/* End of ~HashTable */
 
//   END OF THE HASH TABLE CLASS
// -----------------------------------------------------------
//   START OF THE HASH TABLE ITERATOR CLASS
 
template <class ItemType>
class HashTable<ItemType>::Iterator :
		public std::iterator<std::forward_iterator_tag,ItemType>,
		public HashTable<ItemType>
	{
public:
	// Iterator constructor
	Iterator(node* otherIter = NULL)
	{		
		itHead = otherIter;
	}
	~Iterator() {}
	// The assignment and relational operators are straightforward
	Iterator& operator=(const Iterator& other)
	{
		itHead = other.itHead;
		return(*this);
	}
	bool operator==(const Iterator& other)const
	{
		return itHead == other.itHead;
	}
	bool operator!=(const Iterator& other)const
	{
		return itHead != other.itHead;
	}
	bool operator<(const Iterator& other)const
	{
		return itHead < other.itHead;
	}
	bool operator>(const Iterator& other)const
	{
		return other.itHead < itHead;
	}
	bool operator<=(const Iterator& other)const
	{
		return (!(other.itHead < itHead));
	}
	bool operator>=(const Iterator& other)const
	{
		return (!(itHead < other.itHead));
	}
	// Update my state such that I refer to the next element in the
	// HashTable.
	Iterator operator+(int incr)
	{
		node* temp = itHead;
		for(int x=0; x < incr && temp!= NULL; ++x)
		{
			temp = temp->next;
		}
		return temp;
	}
	Iterator operator+=(int incr)
	{
		for(int x=0; x < incr && itHead!= NULL; ++x)
		{
			itHead = itHead->next;
		}
		return itHead;
	}
	Iterator& operator++() // pre increment
	{	
		if(itHead != NULL)
		{
			itHead = itHead->next;			
		}
		return(*this);
	}
	Iterator operator++(int) // post increment
	{
		node* temp = itHead;
		this->operator++();
		return temp;
	}
	ItemType& operator[](int incr)
	{
		// Return "junk" data 
		// to prevent the program from crashing
		if(itHead == NULL || (*this + incr) == NULL)
		{			 
			return junk;
		}
		return(*(*this + incr));
	}
	// Return a reference to the value in the node.  I do this instead
	// of returning by value so a caller can update the value in the
	// node directly.
	ItemType& operator*()
	{
		// Return "junk" data 
		// to prevent the program from crashing
		if(itHead == NULL)
		{
			return junk;
		}
		return itHead->currentItem;		
	}	
	ItemType* operator->()
	{
		return(&**this);
	}
private:
	node* itHead;
	ItemType junk;
}; 