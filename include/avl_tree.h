#pragma once

// структура ветки
struct Branch
{
	int Data;
	Branch* LeftBranch;
	Branch* RightBranch;
};

template <class T>
class AVL_tree
{
private:
	Branch* current_branch;
public:
	// внесение данных
	void Add(int aData, Branch*& aBranch)
	{
		//Если ветки не существует
		if (!aBranch) //создадим ее и зададим в нее данные
		{
			aBranch = new Branch;
			aBranch->Data = aData;
			aBranch->LeftBranch = 0;
			aBranch->RightBranch = 0;
		}
		else //Иначе сверим вносимое
			if (aBranch->Data > aData) //Если оно меньше того, что в этой ветке - добавим влево
				Add(aData, aBranch->LeftBranch);
			else //Иначе в ветку справа
				Add(aData, aBranch->RightBranch);
	}
	// конструктор с параметром
	AVL_tree(T aData)
	{
		Add(aData, this->current_branch);
	}
	// удаление дерева
	void FreeTree()
	{
		if (!current_branch) return;
		FreeTree(current_branch->LeftBranch);
		FreeTree(current_branch->RightBranch);
		delete current_branch;
		return;
	}
	// деструктор
	~AVL_tree()
	{
		FreeTree();
	}
	// прямой обход дерева
	void pr_obh()
	{
		if (nullptr == current_branch)    return;    //Если дерева нет, выходим
		std::cout << current_branch->Data << std::endl; //Посетили узел
		pr_obh(current_branch->LeftBranch); //Обошли левое поддерево   
		pr_obh(current_branch->RightBranch); //Обошли правое поддерево
	}
	// добавление элемента
	void add_elem(T aData)
	{
		if (!current_branch)
		{
			current_branch = new Branch;
			current_branch->Data = aData;
			current_branch->LeftBranch = 0;
			current_branch->RightBranch = 0;
		}
		else
		{
			if (aData < current_branch->Data)
				add_elem(aData, current_branch->LeftBranch);
			else
				if (aData > current_branch->Data)
					add_elem(aData, current_branch->RightBranch);
		}
	}
	// проверка на пустоту
	bool is_Empty()
	{
		if (!current_branch)
			return true;
		else
			return false;
	}
	// удаление элемента
	Branch* del_elem(T aData)
	{
		if (current_branch == nullptr)
			return current_branch;
		if (aData == current_branch->Data) {
			Branch* tmp;
			if (current_branch->RightBranch == nullptr)
				tmp = current_branch->LeftBranch;
			else {
				Branch* ptr = current_branch->RightBranch;
				if (ptr->LeftBranch == nullptr) {
					ptr->LeftBranch = aBranch->LeftBranch;
					tmp = ptr;
				}
				else {
					Branch* pmin = ptr->LeftBranch;
					while (pmin->LeftBranch != NULL) {
						ptr = pmin;
						pmin = ptr->LeftBranch;
					}
					ptr->LeftBranch = pmin->RightBranch;
					pmin->LeftBranch = current_branch->LeftBranch;
					pmin->RightBranch = current_branch->RightBranch;
					tmp = pmin;
				}
			}
			delete current_branch;
			return tmp;
		}
		else if (aData < current_branch->Data)
			current_branch->LeftBranch = del_elem(current_branch->LeftBranch, aData);
		else
			current_branch->RightBranch = del_elem(current_branch->RightBranch, aData);
		return current_branch;
	}
};