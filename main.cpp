#include <iostream>
#include <cstring>
#include <vector>
#include <sstream>
#include "List.h"

#define forbiden_name "forbiden.txt"  //filepath for recalibration. it is important not to use it in exporting or the Data may be lost

void insert_part(List list, List::list_hash_table *lht){
	char a[15],b[20], type[7];
	string cv;
	int t;
	cout<<"enter NAME"<<endl;
	cin>>a;
	cout<<"enter SURNAME"<<endl;
	cin>>b;
	cout<<"enter the CV"<<endl;
	cin>>ws;
	getline(cin, cv);

	cout<<"enter Professionalism level"<<endl;
	cin>>type;
	
			
	if(type[0] == 'J') t = 1;
	else if(type[0] == 'M') t = 2;
 	else if (type[0] == 'S')t = 3;
	list.list_insert_unit(lht, a, b, cv, t);
}




string set_settings(){
	char ch;
	string settings, temp;
	cout<<"Would you like to set your own settings for the DataBase? \ny/n"<<endl;
	cin>>ch;
	if(ch == 'y'){
		cout<<"Enter the least popular first Letters in the Surnames in your company without any separations"<<endl;
		cin>>settings; 
		cout<<"Your preference was amplified"<<endl;
		}
	else {
		settings = "HJQUWXYZ";
		cout<<"The Standart settings were amplified"<<endl;
	}
	for(int i = (int)('A'); i<(int)('Z');i++) {
		if(!(strchr(settings.c_str(), (char)(i))))temp+=(char)(i);
		
	}
	return temp;
	
}

void modify(List list, List::list_hash_table * lht, List::found_el * answer){
	system("cls");
	int choice, what;
	if(answer->list_el.size() || answer->minor_el.size()){
		for(int i = 0; i<answer->minor_el.size(); i++){
		list.display_one(answer->minor_el[i]);
		}
		for(int i = 0; i<answer->list_el.size(); i++){
		list.display_one(answer->list_el[i]);
		}
		
		cout<<"which one would you like to modify? enter his index number or enter 0 not to modify anything"<<endl;
		
		cin>>choice;
			
		}
		int exit = 1;

		if(choice == 0) return;
		
		
		choice--;
    	while(exit){
    	system("cls");
		cout<<"          MENU  \n"<<endl;
   		cout<<"1. Delete this worker from DataBase"<<endl;
   		cout<<"2. Change this worker`s level of professionalism."<<endl;
		cout<<"3. Change this worker`s CV."<<endl;
    	cout<<"4. End modifing"<<endl;
		cin>>what;
		switch(what){
			case 1:{
				
				if(answer->minor_el.size() && choice == 0){
					if(answer->minor_el[0])list.list_del_unit(lht, answer->minor_el[0]);
					else return;
				}	
				else {
					if(answer->list_el[choice])list.list_del_unit(lht, answer->list_el[choice]);
					else return;	
				}
				return;
				break;
			}
			case 2:{
				string type;
				int t;
				if(answer->minor_el.size() && choice == 0){
					if(answer->minor_el[0]){
						cout<<"enter Professionalism level"<<endl;
						cin>>type;		
						if(type[0] == 'J') t = 1;
						else if(type[0] == 'M') t = 2;
 						else if (type[0] == 'S')t = 3;
 						answer->minor_el[0]->type = t;
					}
					else{
						cout<<"Nothing to modify"<<endl;
						return;
					} 
				}	
				else {
					if(answer->list_el[choice]){
						cout<<"enter Professionalism level"<<endl;
						cin>>type;		
						if(type[0] == 'J') t = 1;
						else if(type[0] == 'M') t = 2;
 						else if (type[0] == 'S')t = 3;
 						answer->list_el[choice]->type = t;

					}
					else{
						cout<<"Nothing to modify"<<endl;
						return;
					} 	
				}
				break;
			}
			case 3:{
				string type;
				if(answer->minor_el.size() && choice == 0){
					if(answer->minor_el[0]){
						cout<<"enter new CV"<<endl;
						cin>>ws;
						getline(cin, type);		
 						answer->minor_el[0]->cv= type;
					}
					else{
						cout<<"Nothing to modify"<<endl;
						return;
					} 
				}	
				else {
					if(answer->list_el[choice]){
						cout<<"enter new CV"<<endl;
						cin>>ws;
						getline(cin, type);
 						answer->list_el[choice]->cv = type;
					}
					else{
						cout<<"Nothing to modify"<<endl;
						return;
					} 	
				}
				break;
			}
				
			case 4:{
				exit = 0;
				break;
			}
		
		
	}
	
		
	}
	
}

void search_part(List list, List::list_hash_table *lht){ //********************************************** a function to search by name + surname + add a feature to modify founded elemets
	string temp, name, surname;
	List::found_el * answer;
	cout<<"Enter the worker`s surname and name if it is known, which you want to find.\nIn Template: Surname Name"<<endl; 
	cin>>ws;
	getline(cin, temp);
	std::istringstream ist(temp);
	ist>>surname;
	ist>>name;
	

	if(surname.length() && name.length()){
		char surnamef[20], namef[15];
		strcpy(namef, name.c_str());
		strcpy(surnamef, surname.c_str());
		answer = list.list_search_unit(lht, surnamef,namef);
	}
	else if(surname.length()){
		char surnamef[20];
		strcpy(surnamef, surname.c_str());
		answer = list.list_search_unit(lht, surnamef);
	}
	else {
		cout<<"Blanc Input"<<endl;
		return;
	}

	if(answer->list_el.size() || answer->minor_el.size()){
		for(int i = 0; i<answer->minor_el.size(); i++){
		list.display_one(answer->minor_el[i]);
		}
		for(int i = 0; i<answer->list_el.size(); i++){
		list.display_one(answer->list_el[i]);
		}
		modify(list, lht, answer);
	}
	
	else cout<<"No worker with such Surname was found"<<endl;

}

void search_by_type(List list, List::list_hash_table *lht){ //********************************************** a function to search by name + surname + add a feature to modify founded elemets
	string type;
	List::found_el * answer = new List::found_el;
	cout<<"Enter the level of professionalism you are looking for."<<endl; 
	cin>>type;	
	if(type.length()){
		int t;
		if(type[0] == 'J') t = 1;
		else if(type[0] == 'M') t = 2;
 		else if (type[0] == 'S')t = 3;
		list.list_search_type(lht, t, answer);
	}
	else {
		cout<<"Blanc Input"<<endl;
		return;
	}

	if(answer->list_el.size() || answer->minor_el.size()){
		for(int i = 0; i<answer->minor_el.size(); i++){
		list.display_one(answer->minor_el[i]);
		}
		for(int i = 0; i<answer->list_el.size(); i++){
		list.display_one(answer->list_el[i]);
		}
		modify(list, lht, answer);
	}
	else cout<<"No worker with such level of professionalism"<<endl;


}



void del_part(List list, List::list_hash_table *lht){
	char b[20];
	int choice;
	cout<<"Write Surname, which you want to Delete"<<endl;
	cin>>b;
	List::found_el * answer = list.list_search_unit(lht, b);

	if(answer->list_el.size() || answer->minor_el.size()){
		if((answer->list_el.size() + answer->minor_el.size()) ==1){
			choice = 1;
		}
		else{
			for(int i = 0; i<answer->minor_el.size(); i++){
				list.display_one(answer->minor_el[i]);
			}
			for(int i = 0; i<answer->list_el.size(); i++){
				list.display_one(answer->list_el[i]);
			}
		cout<<"which one would you like to delete? enter his index number or enter 0 not to delete anything"<<endl;
		
		cin>>choice;
		if(choice == 0)	return;
		}
		choice--;

			if(answer->minor_el.size() && choice == 0){
				list.list_del_unit(lht, answer->minor_el[0]);  // function for minor_el (a must to create) *******************************************
			}
			else list.list_del_unit(lht, answer->list_el[choice]);


	}
	else {
		cout<<"No worker with such Surname was found"<<endl;
		return;
		
	}
	answer->list_el.clear();
	answer->minor_el.clear();
	answer = list.list_search_unit(lht, b);
	if(answer->list_el.size() || answer->minor_el.size()){
		for(int i = 0; i<answer->minor_el.size(); i++){
		list.display_one(answer->minor_el[i]);
		}
		for(int i = 0; i<answer->list_el.size(); i++){
		list.display_one(answer->list_el[i]);
		}
	}
	else cout<<"No worker with such Surname was found"<<endl;
	
}
List::list_hash_table * recalibrate(List list, List::list_hash_table *lht){
	ofstream fw(forbiden_name);
	fw.close();
	list.list_export(lht, forbiden_name);
	list.settings = set_settings();
	List::list_hash_table *lht2 = list.list_init_table(list.count_settings() + 1);
	list.list_insert_from_file(lht2, forbiden_name);
	free(lht);
	return lht2;
	
}

int main()
{

	List list;
	list.settings = set_settings();                                         //Required settings
	List::list_hash_table *lht = list.list_init_table(list.count_settings() + 1);

while (1)
  {
  	system("pause");
    system("cls");
    cout<<"          MENU  \n"<<endl;
    cout<<"1. Import DataBase from file by path."<<endl;
    cout<<"2. Add element by keyboard."<<endl;
    cout<<"3. View whole DataBase"<<endl;;
    cout<<"4. View Data linked to the leter"<<endl;
    cout<<"5. Search in DataBase by name"<<endl;
    cout<<"6. Search in DataBase by the level of professionalism"<<endl;
    cout<<"7. Delete by Surname"<<endl;
    cout<<"8. Export DataBase into the selected file"<<endl;
    cout<<"9. Recalibrate DataBase (set new settings)"<<endl;
	cout<<"0. Exit"<<endl;
    cout<<endl;
    int key;            
    cout<< "Choosen menu item:";
    cin>>key;
    system("cls");
    switch(key)        
    {
     case 1:  {string filename;cout<<"Enter the filepath"<<endl;cin>>filename;if(filename == forbiden_name){cout<<"This file is used for developer`s purposes"<<endl; break;}list.list_insert_from_file(lht, filename);list.display_all(lht);break;}
     case 2:  {insert_part(list, lht);break;}
     case 3:  {list.display_all(lht);break;}
     case 4:  {char letter[1];cout<<"Enter the letter"<<endl;cin>>letter;list.restart_number();list.display(lht->keys[list.hash(letter)]);break;}
     case 5:  {search_part(list, lht);break;}
     case 6:  {search_by_type(list, lht);break;}
     case 7:  {del_part(list, lht);break;}
     case 8:  {string filename;cout<<"Enter the filepath"<<endl;cin>>filename;list.list_export(lht, filename);break;}
     case 9:  {lht = recalibrate(list, lht);break;}
     case 0:  {exit (0); break;}
     default: {cout<<"Try another time...";system("pause");break;}
    }
  }
	
	
    
    return 0;
}
