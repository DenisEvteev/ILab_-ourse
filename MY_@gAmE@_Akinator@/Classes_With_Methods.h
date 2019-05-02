#pragma once
#include <string>
#include <iostream>
#include <cstdio>
#include <windows.h>
#include <vector>
#include <clocale>
#include <algorithm>
#include <iterator>
//----------------------------------------------------------------
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::find;
//----------------------------------------------------------------

class Node
{
private:
	string infa_;
	Node* left_;
	Node* right_;
	Node* parent_;
	string word_;
public:
	Node()
	{
		left_ = NULL;
		right_ = NULL;
		parent_ = NULL;

	}
    //--------------setters-------------------------------------
	void Set_Infa(string info)
	{
		infa_ = info;
	}
	void Set_Left(Node* n)
	{
		left_ = n;
	}
	void Set_Right(Node* n)
	{
		right_ = n;
	}
	void Set_Parent(Node* n)
	{
		parent_ = n;
	}
	void Set_Word(string word)
	{
		word_ = word;
	}
	//-------------------getters----------------------------------
	string Get_Infa() 
	{
		return infa_;
	}
	Node* Get_Left()
	{
		return left_;
	}
	Node* Get_Right()
	{
		return right_;
	}
	Node* Get_Parent()
	{
		return parent_;
	}
	string Get_Word()
	{
		return word_;
	}
	//---------------------------------------------------------------------
	void Print_Info()
	{
		if (!infa_.empty())
			cout << infa_ << endl;
	}
	~Node()
	{
		parent_ = NULL;
		left_ = NULL;
		right_ = NULL;
	}
};
//---------------------------------------------------------------------------------------
class Tree
{
private:

	Node* root_;
public:
	explicit Tree() :
		root_(NULL)
	{}

	void Delete_Node_From_This(Node* good_bye)
	{
		if (good_bye != NULL)
		{
			Delete_Node_From_This(good_bye->Get_Left());
			Delete_Node_From_This(good_bye->Get_Right());
			if (good_bye != NULL)
				delete good_bye;
		}

	}

	void Clear()
	{
		Delete_Node_From_This(root_);
	}

	Node* Get()
	{
		return root_;
	}

	void Set(Node* node)
	{
		root_ = node;
	}

	Node* Find_Node(Node* node, string st)
	{
		if (node->Get_Left() == NULL && node->Get_Infa() == st)
			return node;

		if (node->Get_Left() != NULL)
		{
			Node* left_node = Find_Node(node->Get_Left(), st);
			if (left_node != NULL)
				return left_node;
		}

		if (node->Get_Right() != NULL) {
			Node* right_node = Find_Node(node->Get_Right(), st);
			if (right_node != NULL)
				return right_node;
		}
		return NULL;
	}

	void Write(FILE* file, Node* node)
	{
		char open = '{';
		char close = '}';
		char left = 'N';
		char space = ' ';
		size_t len_infa = (node->Get_Infa()).size();
		size_t len_word = (node->Get_Word()).size();
		fwrite(&open, sizeof(char), 1, file);
		fwrite(&len_infa, sizeof(size_t), 1, file);
		fwrite((node->Get_Infa()).c_str(), sizeof(char), len_infa, file);
		fwrite(&len_word, sizeof(size_t), 1, file);
		fwrite((node->Get_Word()).c_str(), sizeof(char), len_word, file);

		if (node->Get_Left() != NULL)
		{
			fwrite(&space, sizeof(char), 1, file);
			Write(file, node->Get_Left());
		}
		else
		{
			fwrite(&left, sizeof(char), 1, file);
		}

		if (node->Get_Right() != NULL)
		{
			fwrite(&space, sizeof(char), 1, file);
			Write(file, node->Get_Right());
		}
		else
		{
			fwrite(&left, sizeof(char), 1, file);
		}
		fwrite(&close, sizeof(char), 1, file);

	}


	Node* Read(FILE* file, Node* parent)
	{
		if (fgetc(file) == '{')
		{
			Node* node = new Node;
			size_t info_size = 0;
			size_t word_size = 0;
			fread(&info_size, sizeof(size_t), 1, file);
			string str(info_size, '\0');
			fread(&str[0], sizeof(char), info_size, file);
			fread(&word_size, sizeof(size_t), 1, file);
			string word(word_size, '\0');
			fread(&word[0], sizeof(char), word_size, file);
			node->Set_Infa(str.data());
			node->Set_Parent(parent);
			node->Set_Word(word.data());
			Node* node_l = NULL;
			Node* node_r = NULL;
			if (fgetc(file) == ' ')
			{
				node_l = Read(file, node);
				node->Set_Left(node_l);
			}
			if (fgetc(file) == ' ')
			{
				node_r = Read(file, node);
				node->Set_Right(node_r);
			}
			fgetc(file);
			return node;
		}
		else
			return nullptr;
	}

	~Tree()
	{
		root_ = NULL;
	}
};

//--------------------------------------------------------------------------------
class Game_Manager
{
private:
	Tree* Acinator_;

	void Push_New_Word(Node* node, string st)
	{
		Node* extra_node = new Node;
		string def;
		string meaning;
		cout << "//Enter the distinctive characteristic of new word//" << endl;
		cin >> def;
		cout << "....Enter the word, which is right to this characteristic....." << endl;
		cin >> meaning;
		string str = "Это " + def + ' ' + '?';
		extra_node->Set_Infa(str);
		extra_node->Set_Word(def);
		Node* node_1 = new Node;
		node_1->Set_Infa(meaning);
		node_1->Set_Parent(extra_node);
		extra_node->Set_Right(node_1);
		if (st == "Right")
		{
			extra_node->Set_Left(node->Get_Right());
			(node->Get_Right())->Set_Parent(extra_node);
			extra_node->Set_Parent(node);
			node->Set_Right(extra_node);
		}
		else
		{
			extra_node->Set_Left(node->Get_Left());
			(node->Get_Left())->Set_Parent(extra_node);
			extra_node->Set_Parent(node);
			node->Set_Left(extra_node);
		}

	}

	void Push_The_First_Node()
	{
		string str1;
		string word;
		string f_word;
		cout << "//I will do all my best to guess the word//" << endl;
		Tree* root = new  Tree;
		cout << "..Enter the first characteristic.." << endl;
		cin >> str1;
		Node* node = new Node;
		node->Set_Infa("Это " + str1 + ' ' + '?');
		cout << "//Enter the word which is correct answer to this question//" << endl;
		cin >> word;
		cout << "//Enter the word which is not correct answer to this question//" << endl;
		cin >> f_word;
		node->Set_Word(str1);
		root->Set(node);
		Node* node1 = new Node;
		node1->Set_Infa(word);
		node1->Set_Parent(root->Get());
		(root->Get())->Set_Right(node1);
		Node* node2 = new Node;
		node2->Set_Infa(f_word);
		node2->Set_Parent(root->Get());
		(root->Get())->Set_Left(node2);
		(this->Acinator_) = root;
		return;
	}

	void Func_For_Full_Array(vector<string>& str1, Node* n)
	{
		while (n->Get_Parent() != NULL)
		{
			if (n == (n->Get_Parent())->Get_Left())
			{
				str1.push_back("не " + (n->Get_Parent())->Get_Word());
				n = n->Get_Parent();
			}
			else
			{
				str1.push_back((n->Get_Parent())->Get_Word());
				n = n->Get_Parent();
			}
		}
	}

public:
	explicit Game_Manager() :
		Acinator_(NULL)
	{}


	void Play()
	{
		if (this->Acinator_ == NULL)
		{
			Push_The_First_Node();
		}
		else
		{
			Node* n = Acinator_->Get();
			while (n->Get_Left() != NULL)
			{
				string ans;
				n->Print_Info();
				cout << "......... Да или Нет ........." << endl;
				cin >> ans;
				if (ans == "Да")
				{
					n = n->Get_Right();
				}
				else
				{
					n = n->Get_Left();
				}
			}
			string str;
			cout << "Your word is ......" << endl;
			n->Print_Info();
			cout << "Is it correct word?? Say Да или Нет." << endl;
			cin >> str;
			if (str == "Да")
			{
				cout << "Excellent, I am right how as always!!!" << endl;
				return;
			}
			else
			{
				if(n == ((n->Get_Parent())->Get_Right()))
				    Push_New_Word(n->Get_Parent(), "Right");
				else {
					Push_New_Word(n->Get_Parent(), "Meom");
                }
				return;
			}
		}
	}



	void Description()
	{
		string word;
		cout << "Enter the word, which characteristic do you want to see" << endl;
		cin >> word;
		Node* elem = Acinator_->Find_Node(Acinator_->Get(), word);
		string description;
		while (elem->Get_Parent() != NULL)
		{
			if (elem == (elem->Get_Parent())->Get_Left())
			{
				description = description + ' ' + "не" + ' ' + (elem->Get_Parent())->Get_Word() + ' ';
				elem = elem->Get_Parent();
			}
			else
			{
				description = description + ' ' + (elem->Get_Parent())->Get_Word() + ' ';
				elem = elem->Get_Parent();
			}
		}
		cout << "the description of" << ' ' << word << ' ' << "is" << ' ';
		cout << description << endl;
	}

	void Compare()
	{
		string str1;
		string str2;
		cout << "Enter the first word for comparison" << endl;
		cin >> str1;
		cout << "Enter the second word for comparison" << endl;
		cin >> str2;
		vector<string> words_1;
		vector<string> words_2;

		vector<string> the_same_characteristic;

		Node* elem_1 = Acinator_->Find_Node(Acinator_->Get(), str1);
		Node* elem_2 = Acinator_->Find_Node(Acinator_->Get(), str2);

		Func_For_Full_Array(words_1, elem_1);
		Func_For_Full_Array(words_2, elem_2);

		words_2.push_back("Meom");

		vector<string>::iterator it;
		vector<string>::iterator ip = words_1.begin();

		int int_for_check = 0;
		int len_1 = words_1.size();

	    for(ip; ip != words_1.end(); ip++)
		{
			it = find(words_2.begin(), words_2.end(), *ip);
			if (it != words_2.end())
			{
				the_same_characteristic.push_back(*it);
				words_2.erase(it);
			    ip = words_1.erase(ip);
				ip--;
				int_for_check++;
				
			
				if (int_for_check == len_1)
					break;
				int_for_check--;
			}
			int_for_check++;
		}
		words_2.pop_back();

		if (!the_same_characteristic.empty())
		{
			cout << str1 << ' ' << "and" << ' ' << str2 << ' ' << "has the following same characteristics" << endl;
			ip = the_same_characteristic.begin();
			for (ip; ip != the_same_characteristic.end(); ++ip)
			{
				cout << *ip << ' ';
			}
			cout << endl;
			if (!words_1.empty())
			{
				cout << str1 << ' ' << "has its own characteristic: " << endl;
				ip = words_1.begin();
				for (ip; ip != words_1.end(); ++ip)
				{
					cout << *ip << ' ';
				}
			}
			else
			{
				cout << str1 << ' ' <<  "doesn't have its own charactristic" << endl;
			}
			cout << endl;
			if (!words_2.empty())
			{
				cout << str2 << ' ' << "has its own characteristic: " << endl;
				ip = words_2.begin();
				for (ip; ip != words_2.end(); ++ip)
				{
					cout << *ip << ' ';
				}
			}
			else
			{
				cout << str2 << ' ' <<  "doesn't have its own charactristic" << endl;
			}
			cout << endl;
		}
		else
		{
			cout << str1 << ' ' << "and" << ' ' << str2 << ' ' << "haven't got any same characteristics" << endl;
			cout << str1 << ' ' << "has such a characteristic: " << endl;
			ip = words_1.begin();
			for (ip; ip != words_1.end(); ++ip)
			{
				cout << *ip << ' ';
			}
			cout << endl;
			cout << str2 << ' ' << "has such a characteristic: " << endl;
			ip = words_2.begin();
			for (ip; ip != words_2.end(); ++ip)
			{
				cout << *ip << ' ';
			}
			cout << endl;
		}
	}


	void Save()
	{
		FILE* file;
		file = fopen("file_save.txt", "wb");
		if (file == nullptr)
		{
			cout << "ERROR IN OPENNING file_save.txt, SORRRY" << endl;
			return;
		}
		Acinator_->Write(file, Acinator_->Get());
		fclose(file);
	}


	void Load()
	{
		FILE* file;
		file = fopen("file_save.txt", "rb");
		if (file == nullptr)
		{
			cout << "ERROR IN OPENNING file_save.txt, SORRRY" << endl;
			return;
		}
		Tree* tree_from_file = new Tree;

		Node* first_node = new Node;
		Acinator_ = tree_from_file;

		first_node = Acinator_->Read(file, tree_from_file->Get());
		Acinator_->Set(first_node);
		fclose(file);
	}

	void Menu_For_Acinator()
	{
		short int start;
		while (1)
		{
			cout << "If you want to choose the function in menu of ACINATOR press 230" << endl;
			cin >> start;
			switch (start)
			{
			case 230:
				cout << "<1> - Play()" << endl;
				cout << "<2> - Description()" << endl;
				cout << "<3> - Save()" << endl;
				cout << "<4> - Load()" << endl;
				cout << "<5> - Comparison of two objects" << endl;
				cout << "<6> - Clear() the Tree" << endl;
				cout << "<7> - Exit the Game" << endl;
				break;
			case 1:
				Play();
				break;
			case 2:
				Description();
				break;
			case 3:
				Save();
				break;
			case 4:
				Load();
				break;
			case 5:
				Compare();
				break;
			case 6:
				Acinator_->Clear();
				break;
			case 7:
				cout << "ThE gAmE iS oVeR, THaNk YoU VeRy MuCh :) _and_ HaVe A nIcE dAy :)" << endl;
				return;
			default:
				cout << "LoOk MoRe CaReFuLlY, pLeAsE  _____///____   aNd DoN't PrEsS bAd ButTon ;(" << endl;
				break;
			}
		}
	}

	~Game_Manager()
	{
		delete Acinator_;
		Acinator_ = NULL;
	}
};