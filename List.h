#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
class List{
public: string settings;
private: int w_number = 1;
public: void restart_number(){
	w_number = 1;
}
public: int count_settings(){
	return settings.length();
}
public: void settings_out(){
	cout<<settings<<endl;
}

public : int hash(char* unit){											// Hashes by the first letter 
	char b = unit[0];
	
	if(strchr(settings.c_str(), b)){
			return  strchr(settings.c_str(), b) - settings.c_str();
			
		} 
	else{
		return settings.length();
	} 
} 	


private: char types[3][7] = {"Junior", "Middle", "Senior"};		//used to save the level of professionalism in int

public: typedef struct list{								//a standart node
	char name[15];
	char surname[20];
	string cv;										// Text about the worker
	int type; 										// the professionalism level {1, 2, 3}  = {Junior, Middle, Senior}
	
	struct list * next; 							// Alphabet order

	
} list;
public: 
typedef struct list_minor{                          //the node for the surnames with the pointer to the next letter
	char name[15];
	char surname[20];
	string cv;										// Text about the worker
	int type;                                       // the professionalism level {1, 2, 3}  = {Junior, Middle, Senior}
	
	list * next;                       		// Alphabet order
	struct list_minor * next_L;                     // Shortcut forward through the Alphabet
	
} list_minor;



public: typedef struct found_el{
	vector<list*>  list_el;
	vector<list_minor*> minor_el;
}found_el;




private : list_minor * add_node(list_minor  *first, char *name, char *surname, string cv, int type = 1){		//Adds an element into the list 
	
	list_minor * n = first;
	list_minor * prev = n;
	while(n->next_L){														//walks through the Leter shortcut 
		if(surname[0]<n->next_L->surname[0]) break;
		prev = n;
		n = n->next_L;
	}
	if((strcmp(n->surname, surname) == 0) && strcmp(n->name, name)==0){			//checks whether such elem already existed in the minor_node
		cout<<"Worker "<< surname<< " was already registred. Would you like to update his CV? y/n"<<endl;
		char ch;
		cin>>ch;
		if(ch=='y'){
			n->cv =cv;
			n->type = type;
			cout<<n->surname<<"`s CV was updated"<<endl;
			return first;
		}
		else return first;
	
	}
	else if(list * elem = list_search_unit(n->next, name, surname)){				//checks whether such elem already existed in the regular node
		cout<<"Worker "<< surname<< " was already registred. Would you like to update his CV? y/n";
		char ch;
		cin>>ch;
		if(ch=='y'){
			elem->cv =cv;
			elem->type = type;
			cout<<elem->surname<<"`s CV was updated"<<endl;
			return first;
		}
		else return first;
	}
	
	if(surname[0]!=n->surname[0] && !n->next_L && strcmp(n->surname, surname)<0){	//checks if it is in the end of the letter list and creates new minor node at the right place
		prev = n;
		n = n->next_L;
		n = create_node(name, surname, cv, type);
		prev->next_L = n;
		return first;
	}
	if(surname[0]==n->surname[0]){																			//cheks if The letter was already registered
	if(strcmp(n->surname, surname)>0 || (strcmp(n->surname, surname) == 0) && strcmp(n->name, name)>0 ){ 	//checks if the lem has to be inserted before the first of the list
		
		list_minor *new_el = new list_minor;
		strcpy(new_el->name, name);
		strcpy(new_el->surname,surname);
		new_el->type = type;
		new_el->cv = cv;
		new_el->next_L = n->next_L;
		prev->next_L = new_el;
		if(first == n)
			first = new_el;
		list*temp = new list;
		strcpy(temp->name, n->name);
		strcpy(temp->surname,n->surname);
		temp->next = n->next;
		temp->type = n->type;
		temp->cv = n->cv;
		new_el->next = temp;
		free(n);
		return first;
	}
	list * nextel;
	list *new_el = new list;
	strcpy(new_el->name, name);
	strcpy(new_el->surname,surname);
	new_el->next = NULL;
	new_el->type = type;
	new_el->cv = cv;
	list *n = first->next;
	if((n == NULL) || (strcmp(n->surname, new_el->surname)>0)){ //puts at the second place
		new_el->next = n;
		first->next = new_el;
		return first;
	}
	if(strcmp(n->surname, new_el->surname)== 0){		//puts relatively to the name? because the surnames are equal
			if(strcmp(n->name, new_el->name)>0){
				new_el->next = n->next;
				n->next = new_el;
				return first;
			}
		}
	do{													//loops searching for the right place to insert
		if(n->next)nextel = n->next;
		else nextel= NULL;
	
		if((nextel == NULL) ||(strcmp(nextel->surname, new_el->surname)>0)){
			new_el->next = nextel;
			n->next = new_el;
			return first;
			
		}
		if(strcmp(nextel->surname, new_el->surname)== 0){
			if(strcmp(nextel->name, new_el->name)>0){
				new_el->next = nextel->next;
				n->next = new_el;
				return first;
			}
		}
		n = n->next;
		}while(n );
	cerr<<"Wrong Insert in the DATABASE"<<endl;
	exit(-1);
	}
	else{
	if(strcmp(n->surname, surname)>0 || (strcmp(n->surname, surname) == 0) && strcmp(n->name, name)>0 ){  
		list_minor *new_el = new list_minor;
		strcpy(new_el->name, name);
		strcpy(new_el->surname,surname);
		new_el->type = type;
		new_el->cv = cv;
		new_el->next_L = n;
		new_el->next = NULL;
		if(prev!=n)prev->next_L = new_el;
		if(first = n)
			first = new_el;
		return first;
	}
	list * nextel;
	list_minor *new_el = new list_minor;
	strcpy(new_el->name, name);
	strcpy(new_el->surname,surname);
	new_el->next = NULL;
	new_el->type = type;
	new_el->cv = cv;
	new_el->next_L = n->next_L;
	prev->next_L = new_el;
	n->next_L = new_el;
	do{
		nextel = n->next;
	
		if((nextel == NULL) ||(strcmp(nextel->surname, new_el->surname)>0)){
			new_el->next = nextel;
			n->next = NULL;
			return first;
			
		}
		else if(strcmp(nextel->surname, new_el->surname)== 0){
			if(strcmp(nextel->name, new_el->name)>0){
				new_el->next = nextel->next;
				n->next = NULL;
				return first;
			}
	
		}
		list *n = n->next;
		}while(n );
	cerr<<"Wrong Insert in the DATABASE"<<endl;
	exit(-1);
	}

	
}

private: list_minor * create_node(char name[15], char surname[20], string cv, int type = 1){
	
    list_minor *new_el = new list_minor;
    strcpy(new_el->name, name);

    strcpy(new_el->surname, surname);
    new_el->cv = cv;
	new_el->next = NULL;
	new_el->next_L = NULL;
	new_el->type = type;
    return new_el;
}


public: void display(list_minor * first){ 		//displays data about the worker in the list
	list_minor *n = first;

	while(n){
		list * elem = n->next;
		cout<<"Leter is "<<n->surname[0]<<endl;
		cout<<"Worker "<<w_number++<<":"<<endl;
		cout<<"\t"<<n->name<<" "<<n->surname<<". Professionalism level is "<<types[n->type- 1]<<endl;
		cout<<"CV:\n\t"<<n->cv<<endl;
		while(elem){
			cout<<"Worker "<<w_number++<<":"<<endl;
			cout<<"\t"<<elem->name<<" "<<elem->surname<<". Professionalism level is "<<types[elem->type - 1] <<endl;
			cout<<"CV:\n\t"<<elem->cv<<endl;
			elem=elem->next;
		}
		
		n=n->next_L;
	}
	
};
private: void export_by_letter(list_minor * first, string filename){		//secondary programm to help the export function
	list_minor *n = first;
	ofstream fw(filename, ios_base::app);
	string line;

	if(!fw.is_open()){
		cerr<<"Erron in file open"<<endl;
		return;
	}
	while(n){
		list * elem = n->next;
		string s(types[n->type- 1]);
		string name(n->name), surname(n->surname);
		line = name + ' ' + surname + ' '+ s;
		fw<<line<<endl;
		fw<<n->cv<<endl;
		while(elem){
			string s(types[elem->type- 1]);
			string name(elem->name), surname(elem->surname);
			line = name + ' ' + surname + ' '+ s;
			fw<<line<<endl;
			fw<<elem->cv<<endl;
			elem=elem->next;
		}
		
		n=n->next_L;
	}
	fw.close();
	
};



public: void display_one(list * n){								// displays data from a standart node
	if(n){
		cout<<n->name<<" "<<n->surname<<". Professionalism level is "<<types[n->type- 1]<<endl;
		cout<<"CV:\n\t"<<n->cv<<endl;
	}
	else cout<<"Not Found"<<endl;
	
}

public: void display_one(list_minor * n){						// overloaded function, which displays data from a node with a letter-pointer
	if(n){
		cout<<n->name<<" "<<n->surname<<". Professionalism level is "<<types[n->type- 1]<<endl;
		cout<<"CV:\n\t"<<n->cv<<endl;
	}
	else cout<<"Not Found"<<endl;
}
/*public: void del(list * first){
	while(first){
	first = delfirst(first);
	}
};*/

// ------------------Hash Part ------------------------

public: typedef struct list_hash_table{				//Hash table structure
    list_minor **keys;     								//Array of lists
    int max;											//Length of the array
}list_hash_table;

public: void display_all(list_hash_table * lht){			// displays all the elements from the hash table
	list_minor ** keys = lht->keys;
	w_number = 1;
	for(int i = 0; i<lht->max; i++){
		
		display(keys[i]);
	}
	
};
public: void list_export(list_hash_table * lht, string filename){
	list_minor ** keys = lht->keys;
	for(int i = 0; i<lht->max; i++){
		
		export_by_letter(keys[i], filename);
	}
	
};

public: list_hash_table* list_init_table(int n){												//Initializes the Hash Table

     list_hash_table *lht = (list_hash_table *)malloc(sizeof(list_hash_table));
     lht->max=n;
     lht->keys = (list_minor**)malloc(sizeof(list_minor)*lht->max);
     for(int i = 0; i<lht->max; i++) lht->keys[i] = NULL;
     return lht;
}

													

public : void list_insert_unit(list_hash_table *lht, char *name, char *surname, string cv, int type = 1){      //Inserts the DATA into the DATABASE
    if(!(lht->keys[hash(surname)])){
		lht->keys[hash(surname)] = create_node(name, surname, cv, type);

	}
    else {
        lht->keys[hash(surname)] = add_node(lht->keys[hash(surname)], name, surname, cv, type);
    }

}
public: int list_insert_from_file(list_hash_table *lht, string filename){		   // imports ingo into the database
	
	ifstream fr;					
	fr.open(filename);										//opens the in-stream in file that was passed into the function
	if(!fr.is_open()){										//checks wether the file opened successesfully
		cerr<<"Erron in file open"<<endl;
		return 0;
	}
	while(!fr.eof()){										// reads the data in file, while the re is any and writes it into the Data base

	string name, surname,cv, temp, type;
	int t;
	getline(fr, temp);
	std::istringstream ist(temp);
	ist>>name;
	ist>>surname;
	ist>>type;
	if(!name.length()) break;
	if(type[0] == 'J') t = 1;
	else if(type[0] == 'M') t = 2;
 	else if (type[0] == 'S')t = 3;
	getline(fr , cv);
	
	char namef[15] , surnamef[20];
	strcpy(namef, name.c_str());
	strcpy(surnamef, surname.c_str());
	list_insert_unit(lht, namef, surnamef, cv, t);
	}
	fr.close();
	return 1;
	
}

list * list_search_unit(list* first, char *name, char* surname){		//search by name and surname
	list * n = first;
	while(n){
		if(!strcmp(n->surname, surname) && !strcmp(n->name, name)){
			return n;
		}
		if(n->next)n=n->next;
		else n = NULL;
		
	}
	return NULL;
}

public: found_el * list_search_unit(list_hash_table *lht, char* unit){  	//search by surname

        found_el * answer = new found_el;

        list_minor* root = lht->keys[hash(unit)];
        
        while(root && root->surname[0] != unit[0]){
            if(!strcmp(root->surname, unit)){
            	answer->minor_el.push_back(root);
            	
			}
            root = root->next_L;
        }
        if(!root) {
     
			return answer;
		}
        if(!strcmp(root->surname, unit)){
            	answer->minor_el.push_back(root);
			}
        if(root->surname[0] != unit[0]){
			return answer;
		}
    	list*regular;
        if(root->next)regular = root->next;
        else regular = NULL;
			while(regular){
				if(!strcmp(regular->surname, unit)){
            		answer->list_el.push_back(regular);
				}
				regular = regular->next;
			}
		
		return answer;
    };
    
public: found_el * list_search_unit(list_hash_table *lht, char* surname, char*name){  //search by name and surname

        found_el * answer = new found_el;

        list_minor* root = lht->keys[hash(surname)];
        
        while(root && root->surname[0] != surname[0]){
            if(!strcmp(root->surname, surname)&& !strcmp(root->name, name)){
            	answer->minor_el.push_back(root);
            	
			}
            root = root->next_L;
        }
        if(!root) {
     
			return answer;
		}
        if(!strcmp(root->surname, surname)&& !strcmp(root->name, name)){
            	answer->minor_el.push_back(root);
			}
        if(root->surname[0] != surname[0]){
			return answer;
		}
    	list*regular;
        if(root->next)regular = root->next;
        else regular = NULL;
			while(regular){
				if(!strcmp(regular->surname, surname)&& !strcmp(regular->name, name)){
            		answer->list_el.push_back(regular);
				}
				regular = regular->next;
			}
		
		return answer;
    };
private: void list_search_type_ad(list_minor * root, int t, found_el * answer){		//searches by the professionalism level (helping function)
        
        while(root){
            if(root->type ==t){
            	answer->minor_el.push_back(root);

			}
			list*regular;
       		if(root->next)regular = root->next;
        	else regular = NULL;
			while(regular){
				if(regular->type == t){
            		answer->list_el.push_back(regular);
				}
				regular = regular->next;
			}
			
            root = root->next_L;
        }
    };
    
public: void list_search_type(list_hash_table * lht, int t, found_el * answer){		//searches by the professionalism level
	for(int i =0; i<lht->max; i++){
		list_search_type_ad(lht->keys[i], t, answer);
	}
};

public: int list_del_unit(list_hash_table *lht, char* surname, char* name){
        list_minor* root = lht->keys[hash(surname)];
		list_minor * prev= root;
        while(root && root->surname[0] != surname[0]){
			prev= root;
            root = root->next_L;
        }
        if(!root){
        	cout<<"Not Found"<<endl;
        	return 0;
		}
        if(!strcmp(root->surname, surname) && !strcmp(root->name, name)){
            	if(root->next){
            		list_minor *new_el = new list_minor;
					strcpy(new_el->name, root->next->name);
					strcpy(new_el->surname,root->next->surname);
					new_el->type = root->next->type;
					new_el->cv = root->next->cv;
					new_el->next_L = root->next_L;
					prev->next_L = new_el;
					if(root->next->next) new_el->next=root->next->next;
					else new_el = NULL;
					if(root == lht->keys[hash(surname)]) lht->keys[hash(surname)] = new_el;
					free(root->next);
					free(root);
					return 1;
				}
				else{
					prev->next_L = root->next_L;
					cout<<"The elem "<<surname<<' '<<name<<" was DELETED"<<endl;
					free(root);
					if(root == lht->keys[hash(surname)]) lht->keys[hash(surname)] = NULL;
					return 1;
				}
				
			}
        if(root->surname[0] != surname[0]){
        	cout<<"Not Found"<<endl;
        	return 0;
		}
        
    	list*regular;
        if(root->next)regular = root->next;
        else regular = NULL;
        list * prev_l = regular;
        
			while(regular){
				
				if(!strcmp(regular->surname, surname) && !strcmp(regular->name, name)){
            		if(regular == root->next) root->next = root->next->next;
            		else
            			prev_l->next = regular ->next;
            		cout<<"The elem "<<surname<<' '<<name<<" was DELETED"<<endl;
            		free(regular);
					return 1;
				}
				prev_l= regular;
				regular = regular->next;
			}
		cout<<"Not Found"<<endl;
        return 0;
    };
public: int list_del_unit(list_hash_table *lht, char* surname, char* name, int version){
    	list_minor * n = lht->keys[hash(surname)];
    	list_minor * prev = n;
    	while(n->surname[0] != surname[0]){
    		prev=n;
    		n= n->next_L;
		}
		if(prev==n){
			if(n->next){
				list_minor * next= create_node(n->next->name, n->next->surname, n->next->cv, n->next->type);
				next->next_L = n->next_L;
				if(n->next->next)next->next = n->next->next;
				else next->next = NULL;
				lht->keys[hash(surname)] = next;
				cout<<"The elem "<<surname<<' '<<name<<" was DELETED"<<endl;
				free(n);
				return 1;
			}
			else{
				lht->keys[hash(surname)] = NULL;
				cout<<"The elem "<<surname<<' '<<name<<" was DELETED"<<endl;
				free(n);
				return 1;
			}
			
		}
		else{
			if(n->next){
				list_minor * next= create_node(n->next->name, n->next->surname, n->next->cv, n->next->type);
				next->next_L = n->next_L;
				if(n->next->next)next->next = n->next->next;
				else next->next = NULL;
				prev->next_L = next;
				lht->keys[hash(surname)] = next;
				cout<<"The elem "<<surname<<' '<<name<<" was DELETED"<<endl;
				free(n);
				return 1;
			}
			else{
				prev->next_L = n->next_L;
				cout<<"The elem "<<surname<<' '<<name<<" was DELETED"<<endl;
				free(n);
				return 1;
			}
			
		}
		cerr<<"Not Found"<<endl;
        return -1;
	};
public: list_del_unit(list_hash_table * lht, list_minor * minor_el){
		list_del_unit(lht, minor_el->surname, minor_el->name, 1);
	};
public: list_del_unit(list_hash_table * lht, list * list_el){
		list_del_unit(lht, list_el->surname, list_el->name);
	};

};
